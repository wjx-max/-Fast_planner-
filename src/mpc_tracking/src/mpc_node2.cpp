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

#include "mpc_tracking/mpc.h"

#include <fstream>
#include <sstream>
using fast_planner::NonUniformBspline;

ros::Publisher cmd_vel_pub2, motion_path_pub2, predict_path_pub2;
nav_msgs::Path predict_path, motion_path;
nav_msgs::Odometry odom;

bool receive_traj = false;
vector<NonUniformBspline> traj;
double traj_duration;
ros::Time start_time;

ros::Timer control_cmd_pub2, path_pub2;

const int N = 10;
const double dt = 0.1;
const double u_max = 0.5;
const double w_max =1.0;
vector<double> weights = {20,20,1,1,1,0}; //Q,R
Eigen::Vector3d current_state;

unique_ptr<Mpc> mpc_ptr;


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



// 角度标准化函数，使其在 -π 到 π 范围内
double normalizeAngle(double angle) {
    while (angle > M_PI) {
        angle -= 2 * M_PI;
    }
    while (angle < -M_PI) {
        angle += 2 * M_PI;
    }
    return angle;
}

void odomCallback(const nav_msgs::Odometry &msg) {
    odom = msg;

    // 读取当前的 x, y 位置和角度
    double current_x = msg.pose.pose.position.x;
    double current_y = msg.pose.pose.position.y;
    double current_theta = tf2::getYaw(msg.pose.pose.orientation);  // 获取当前机器人的航向角

    // 如果当前角度与之前的角度差值过大，则进行标准化处理
    double delta_theta = normalizeAngle(current_theta - current_state(2)); // current_state(2) 存储的是上一时刻的角度

    // 更新当前状态
    current_state(0) = current_x;
    current_state(1) = current_y;
    current_state(2) += delta_theta;  // 更新为标准化后的角度

}



// void odomCallback(const nav_msgs::Odometry &msg) {
//     odom = msg;
//     current_state(0) = msg.pose.pose.position.x;
//     current_state(1) = msg.pose.pose.position.y;
//     current_state(2) = tf2::getYaw(msg.pose.pose.orientation);

// }



void saveToCSV(const Eigen::MatrixXd &desired_state, const Eigen::Vector3d &current_state, const std::string &filename) {
    std::ofstream file;
    file.open(filename, std::ios::app);  // 打开文件，追加数据模式

    // 判断文件是否成功打开
    if (!file.is_open()) {
        ROS_ERROR("Failed to open file for writing.");
        return;
    }

    // 写入列名（如果文件是空的，可以在此写入标题行）
    static bool header_written = false;
    if (!header_written) {
        file << "desired_x, desired_y, desired_yaw, current_x, current_y, current_yaw" << std::endl;
        header_written = true;
    }

    // 写入数据：desired_state 和 current_state
    for (int i = 0; i < desired_state.rows(); ++i) {
        file << desired_state(i, 0) << ","  // desired_x
             << desired_state(i, 1) << ","  // desired_y
             << desired_state(i, 2) << ","  // desired_yaw
             << current_state(0) << ","     // current_x
             << current_state(1) << ","     // current_y
             << current_state(2) << std::endl;  // current_yaw
    }

    file.close();
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
        //cout<<"Test01"<<endl;
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
          //cout<<"Test02_01"<<endl;
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
          //cout<<"Test02_02"<<endl;
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
      //cout<<"Test03"<<endl;
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
      //cout << "[Traj server]: invalid time." << endl;
  }

      //将 desired_state 和 current_state 保存到 CSV 文件
    saveToCSV(desired_state, current_state, "/home/wjx/nrypp_ws/src/mpc_tracking/desired_current_state32.csv");


    Eigen::MatrixXd desired_state2 = desired_state.transpose();
    ros::Time solve_start = ros::Time::now();
    auto success = mpc_ptr->solve(current_state, desired_state2);
    //cout<<"desired_state2:"<<desired_state2<<endl;
    //cout << "solve success" << endl;
    ros::Time solve_end = ros::Time::now();
    double t_cur1 = (solve_end - solve_start).toSec();
   // cout << "solve time:" << t_cur1 << endl;

    geometry_msgs::Twist cmd;
    auto control_cmd = mpc_ptr->getFirstU();
    //cout << "got cmd" << endl;

    //cout << "linear:" << control_cmd[0] << endl;
    //cout << "angular:" << control_cmd[1] << endl;

    cmd.linear.x = control_cmd[0];
    //cmd.linear.y = control_cmd[1];
    cmd.angular.z = control_cmd[1];



    cmd_vel_pub2.publish(cmd);
    //cout << "u:" << result[0] << " " << "r:" << result[1] << endl;

    predict_path.header.frame_id = "tb3_2/odom";
    predict_path.header.stamp = ros::Time::now();
    geometry_msgs::PoseStamped pose_msg;
    geometry_msgs::Point pt;
    auto predict_states = mpc_ptr->getPredictX();
    //cout << "got predict x" << endl;
    for (int i = 0; i < predict_states.size(); i += 2) {
        pose_msg.pose.position.x = predict_states[i];
        pose_msg.pose.position.y = predict_states[i + 1];
        predict_path.poses.push_back(pose_msg);
    }
    predict_path_pub2.publish(predict_path);
    
    predict_path.poses.clear();
}


int main(int argc, char **argv)
{
    ros::init(argc, argv, "mpc_tracking_node2");
    ros::NodeHandle nh;
    mpc_ptr.reset(new Mpc());

    cmd_vel_pub2 = nh.advertise<geometry_msgs::Twist>("tb3_2/cmd_vel", 1);
    predict_path_pub2 = nh.advertise<nav_msgs::Path>("tb3_2/predict_path", 1);
    motion_path_pub2 = nh.advertise<nav_msgs::Path>("tb3_2/motion_path", 1);
   
    ros::Subscriber odom_sub2 = nh.subscribe("tb3_2/odom", 1, &odomCallback);
    ros::Subscriber bspline_sub2 = nh.subscribe("tb3_2/planning/bspline", 10, bsplineCallback);
    ros::Subscriber replan_sub2 = nh.subscribe("tb3_2/planning/replan", 10, replanCallback);

    control_cmd_pub2 = nh.createTimer(ros::Duration(0.1), publish_control_cmd);
    
    ros::spin();
    return 0;

}



