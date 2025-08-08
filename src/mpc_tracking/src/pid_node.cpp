#include <ros/ros.h>
#include <geometry_msgs/Twist.h>
#include <nav_msgs/Odometry.h>
#include <nav_msgs/Path.h>
#include <geometry_msgs/PoseStamped.h>
#include <visualization_msgs/Marker.h>
#include <visualization_msgs/MarkerArray.h>
#include "bspline/non_uniform_bspline.h"
#include "mpc_tracking/Bspline.h"
#include "std_msgs/Empty.h"
#include <tf2_geometry_msgs/tf2_geometry_msgs.h>
#include "tf2/utils.h"


using fast_planner::NonUniformBspline;

ros::Publisher cmd_vel_pub, motion_path_pub, predict_path_pub;
nav_msgs::Path predict_path, motion_path;
nav_msgs::Odometry odom;

bool receive_traj = false;
vector<NonUniformBspline> traj;
double traj_duration;
ros::Time start_time;

ros::Timer control_cmd_pub, path_pub;

const int N = 1;
const double dt = 0.1;
const double u_max = 4;
const double w_max =2;
//转向控制增益
#define k_theta_  0.5
//直线速度控制增益
#define k_linear_  0.5
//转向阈值
#define threshold_heading_  0.1
//到达目标点距离阈值
#define threshold_distance  0.1
//最大直线速度
#define max_linear_velocity_  1.0
//最大角速度
#define max_angular_velocity_  1.0

Eigen::Vector3d current_state;


//计算当前角度与期望角度的差值
double compute_theta(double theta, double rotation1) {
    double w;

    if (theta * rotation1 < 0) {
        if (theta > 0) {
            if (std::abs(rotation1) + theta <= M_PI) {
                w = std::abs(rotation1) + theta;
            } else {
                w = -(2 * M_PI + rotation1 - theta);
            }
        } else {
            if (rotation1 + std::abs(theta) <= M_PI) {
                w = -(std::abs(theta) + rotation1);
            } else {
                w = (2 * M_PI - rotation1 + theta);
            }
        }
    } else {
        w = theta - rotation1;
    }

    return w;
}

void bsplineCallback(mpc_tracking::BsplineConstPtr msg) {
  // parse pos traj
  Eigen::MatrixXd pos_pts(msg->pos_pts.size(), 3);
  for (int i = 0; i < msg->pos_pts.size(); ++i) {
    pos_pts(i, 0) = msg->pos_pts[i].x;
    pos_pts(i, 1) = msg->pos_pts[i].y;
    pos_pts(i, 2) = msg->pos_pts[i].z;
  }

  Eigen::VectorXd knots(msg->knots.size());
  for (int i = 0; i < msg->knots.size(); ++i) {
    knots(i) = msg->knots[i];
  }

  NonUniformBspline pos_traj(pos_pts, msg->order, 0.1);
  pos_traj.setKnot(knots);

  // parse yaw traj
  Eigen::MatrixXd yaw_pts(msg->yaw_pts.size(), 1);
  for (int i = 0; i < msg->yaw_pts.size(); ++i) {
    yaw_pts(i, 0) = msg->yaw_pts[i];
  }

  NonUniformBspline yaw_traj(yaw_pts, msg->order, msg->yaw_dt);

  start_time = msg->start_time;

  traj.clear();
  traj.push_back(pos_traj);
  traj.push_back(traj[0].getDerivative());
  traj.push_back(traj[1].getDerivative());
  traj.push_back(yaw_traj);
  traj.push_back(yaw_traj.getDerivative());

  traj_duration = traj[0].getTimeSum();

  receive_traj = true;
}

void replanCallback(std_msgs::Empty msg) {
  /* reset duration */
  const double time_out = 0.01;
  ros::Time time_now = ros::Time::now();
  double t_stop = (time_now - start_time).toSec() + time_out;
  traj_duration = min(t_stop, traj_duration);
}

void odomCallback(const nav_msgs::Odometry &msg) {
    odom = msg;
    current_state(0) = msg.pose.pose.position.x;
    current_state(1) = msg.pose.pose.position.y;
    current_state(2) = tf2::getYaw(msg.pose.pose.orientation);

    //double yaw1 = tf2::getYaw(msg.pose.pose.orientation);
    // Eigen::Quaterniond quaternion;
    // quaternion.x() = msg.pose.pose.orientation.x;
    // quaternion.y() = msg.pose.pose.orientation.y;
    // quaternion.z() = msg.pose.pose.orientation.z;
    // quaternion.w() = msg.pose.pose.orientation.w;


    // Eigen::Matrix3d rotationMatrix = quaternion.toRotationMatrix();
    // double yaw2 = atan2(rotationMatrix(1, 0), rotationMatrix(0, 0));
    //cout << "x:" << current_state(0) << " " << "y:" << current_state(1) << endl;
    //cout << "yaw1:" << current_state(2) << endl;
    //cout << "yaw2:" << yaw2 << endl;

}

void publish_control_cmd(const ros::TimerEvent &e) {
    if (!receive_traj) return;
    
    ros::Time time_now = ros::Time::now();
    double t_cur = (time_now - start_time).toSec();
    Eigen::Vector3d pos, vel, acc, pos_f;
    double yaw, yawdot;

    Eigen::MatrixXd desired_state = Eigen::MatrixXd::Zero(N+1, 3);

    if (t_cur + (N-1) * dt <= traj_duration && t_cur > 0) {
      for (int i = 0; i <= N; ++i) {
        pos = traj[0].evaluateDeBoorT(t_cur + i * dt);
        vel = traj[1].evaluateDeBoorT(t_cur + i * dt);
        acc = traj[2].evaluateDeBoorT(t_cur + i * dt);
        yaw = traj[3].evaluateDeBoorT(t_cur + i * dt)[0];
        yawdot = traj[4].evaluateDeBoorT(t_cur + i * dt)[0];

        desired_state(i, 0) = pos[0];
        desired_state(i, 1) = pos[1];
        desired_state(i, 2) = yaw;
      }

    } else if (t_cur + (N-1) * dt > traj_duration && t_cur < traj_duration) {
        int more_num = (t_cur + (N-1) * dt - traj_duration) / dt;
        for (int i = 0; i < N - more_num; ++i) {
          pos = traj[0].evaluateDeBoorT(t_cur + i * dt);
          vel = traj[1].evaluateDeBoorT(t_cur + i * dt);
          acc = traj[2].evaluateDeBoorT(t_cur + i * dt);
          yaw = traj[3].evaluateDeBoorT(t_cur + i * dt)[0];
          yawdot = traj[4].evaluateDeBoorT(t_cur + i * dt)[0];

          desired_state(i, 0) = pos(0);
          desired_state(i, 1) = pos(1);
          desired_state(i, 2) = yaw;          
        }
        for (int i = N - more_num; i < N; ++i) {
          pos = traj[0].evaluateDeBoorT(traj_duration);
          vel.setZero();
          acc.setZero();
          yaw = traj[3].evaluateDeBoorT(traj_duration)[0];
          yawdot = traj[4].evaluateDeBoorT(traj_duration)[0];

          desired_state(i, 0) = pos(0);
          desired_state(i, 1) = pos(1);
          desired_state(i, 2) = yaw;
        }
    } else if (t_cur >= traj_duration)  {
      pos = traj[0].evaluateDeBoorT(traj_duration);
      vel.setZero();
      acc.setZero();
      yaw = traj[3].evaluateDeBoorT(traj_duration)[0];
      yawdot = traj[4].evaluateDeBoorT(traj_duration)[0];
      for (int i = 0; i <= N; ++i) {
          desired_state(i, 0) = pos(0);
          desired_state(i, 1) = pos(1);
          desired_state(i, 2) = yaw;
      }
    } else {
      cout << "[Traj server]: invalid time." << endl;
  }


    Eigen::MatrixXd desired_state1 = desired_state.transpose().col(0);
    ros::Time solve_start = ros::Time::now();
    //auto success = mpc_ptr->solve(current_state, desired_state1);

    //机器人当前位置信息
    double current_position_x=current_state[0];
    double current_position_y=current_state[1];
    double current_position_yaw=current_state[2];
    // cout<<"current_state: "<< current_state[0]<<endl ;
    // cout<<"current_state: "<< current_state[1]<<endl ;
    // cout<<"current_state: "<< current_state[2]<<endl ;
  

  //机器人期望位置信息
   double target_position_x=desired_state1(0,0);
   double target_position_y=desired_state1(1,0);
  double target_position_yaw=desired_state1(2,0);
     cout<<"desired_state1: "<< desired_state1(0,0)<<endl ;
     cout<<"desired_state2: "<< desired_state1(1,0)<<endl ;
     cout<<"desired_state3: "<< desired_state1(2,0)<<endl ;

 //Step 1: 计算车辆当前位置与目标位置之间的距离和方向
    double delta_x = target_position_x - current_position_x;
    double delta_y = target_position_y - current_position_y;
    double distance_to_target = sqrt(delta_x * delta_x + delta_y * delta_y);
    double heading_to_target = atan2(delta_y, delta_x);

    //Step 2: 计算当前车辆的航向角
    double current_heading = current_position_yaw;

    //Step 3: 计算目标航向角与当前航向角之间的差异 
    double heading_difference = compute_theta(heading_to_target , current_heading)* 180 / M_PI;

    //Step 4计算转向角速度,直线速度
    double angular_velocity = 0.0;
    if(fabs(heading_difference) > (threshold_heading_)) {
        angular_velocity = k_theta_ * heading_difference;
    }
    double linear_velocity = 0.0;
    if(distance_to_target > threshold_distance){
        linear_velocity = k_linear_ * distance_to_target;
    }
    
    //Step 5: 限制速度
    if(linear_velocity > max_linear_velocity_){
        linear_velocity = max_linear_velocity_;
    }
    if(fabs(angular_velocity) > max_angular_velocity_){
        angular_velocity = max_angular_velocity_;
    }

    //Step 6: 将速度下发/cmd_vel
    geometry_msgs::Twist cmd;
    cmd.linear.x = linear_velocity; 
    cmd.angular.z = angular_velocity; 
    cmd_vel_pub.publish(cmd);

}


int main(int argc, char **argv)
{
    ros::init(argc, argv, "pid_tracking_node");
    ros::NodeHandle nh;

    cmd_vel_pub = nh.advertise<geometry_msgs::Twist>("/cmd_vel", 1);
    predict_path_pub = nh.advertise<nav_msgs::Path>("/predict_path", 1);
    motion_path_pub = nh.advertise<nav_msgs::Path>("/motion_path", 1);
   
    ros::Subscriber odom_sub = nh.subscribe("/odom", 1, &odomCallback);
    ros::Subscriber bspline_sub = nh.subscribe("planning/bspline", 10, bsplineCallback);
    ros::Subscriber replan_sub = nh.subscribe("planning/replan", 10, replanCallback);

    control_cmd_pub = nh.createTimer(ros::Duration(0.1), publish_control_cmd);
    
    ros::spin();
    return 0;

}



