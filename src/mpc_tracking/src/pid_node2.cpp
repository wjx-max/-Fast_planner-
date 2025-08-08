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
#include<iostream>
#include <fstream>

using fast_planner::NonUniformBspline;


// 全局变量，用于存储连续的数据状态
std::vector<std::vector<double>> data_buffer(3, std::vector<double>(3, -1)); // 初始化为-1，假设坐标和角度不可能为-1

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

Eigen::Vector3d current_state;


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

}

void publish_control_cmd(const ros::TimerEvent &e) {
    if (!receive_traj) return;
    
    ros::Time time_now = ros::Time::now();
    double t_cur = (time_now - start_time).toSec();
    Eigen::Vector3d pos, vel, acc;
    double yaw, yawdot;

    Eigen::MatrixXd desired_state = Eigen::MatrixXd::Zero(N+1, 3);

    //std::vector<std::vector<double>> data_buffer(3, std::vector<double>(3, 0)); // 缓冲最近三次的数据

    std::ofstream csv_file;
    csv_file.open("/home/wjx/nryp_ws/src/swarm/waypoint_loader/waypoints/bspline_path.csv", std::ofstream::app);

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

    for (int i = 0; i < N; i++) {
        std::vector<double> current_data = {desired_state(i, 0), desired_state(i, 1), desired_state(i, 2)};

        // 检查数据是否连续三次一致
        if (current_data == data_buffer[1] && data_buffer[1] == data_buffer[0]) {
            ROS_INFO("Data identical for three iterations. Stopping writing to CSV.");
            break;  // 退出循环
        }

        // 更新缓冲
        data_buffer[0] = data_buffer[1];
        data_buffer[1] = current_data;

        // 写入CSV文件
        csv_file << current_data[0] << "," << current_data[1] << "," << current_data[2] << "\n";
    }

    csv_file.close(); // 关闭文件
    ROS_INFO("B-spline path data has been written to bspline_path.csv");
}
  //   } else if (t_cur + (N-1) * dt > traj_duration && t_cur < traj_duration) {
  //       int more_num = (t_cur + (N-1) * dt - traj_duration) / dt;
  //       for (int i = 0; i < N - more_num; ++i) {
  //         pos = traj[0].evaluateDeBoorT(t_cur + i * dt);
  //         vel = traj[1].evaluateDeBoorT(t_cur + i * dt);
  //         acc = traj[2].evaluateDeBoorT(t_cur + i * dt);
  //         yaw = traj[3].evaluateDeBoorT(t_cur + i * dt)[0];
  //         yawdot = traj[4].evaluateDeBoorT(t_cur + i * dt)[0];

  //         desired_state(i, 0) = pos(0);
  //         desired_state(i, 1) = pos(1);
  //         desired_state(i, 2) = yaw;          
  //       }
  //       for (int i = N - more_num; i < N; ++i) {
  //         pos = traj[0].evaluateDeBoorT(traj_duration);
  //         vel.setZero();
  //         acc.setZero();
  //         yaw = traj[3].evaluateDeBoorT(traj_duration)[0];
  //         yawdot = traj[4].evaluateDeBoorT(traj_duration)[0];

  //         desired_state(i, 0) = pos(0);
  //         desired_state(i, 1) = pos(1);
  //         desired_state(i, 2) = yaw;

  //   std::ofstream csv_file;
  //   csv_file.open("/home/wjx/nryp_ws/src/swarm/waypoint_loader/waypoints/bspline_path.csv", std::ofstream::out); // 打开CSV文件以写入模式，自动覆盖
    
  //   cout<<"wjx"<<endl;
  //   for (int i = N - more_num; i <N; ++i) {
  //       double x = desired_state(i, 0);
  //       double y = desired_state(i, 1);
  //       double yaw = desired_state(i, 2); // 假设一个简单的角度

  //       // 写入CSV文件
  //       csv_file << x << "," << y << "," << yaw << "\n";
  //   }
    
  //   csv_file.close(); // 关闭文件
  //   ROS_INFO("B-spline path data has been written to bspline_path.csv");

  //       }
  //   } else if (t_cur >= traj_duration)  {
  //     pos = traj[0].evaluateDeBoorT(traj_duration);
  //     vel.setZero();
  //     acc.setZero();
  //     yaw = traj[3].evaluateDeBoorT(traj_duration)[0];
  //     yawdot = traj[4].evaluateDeBoorT(traj_duration)[0];
  //     for (int i = 0; i <= N; ++i) {
  //         desired_state(i, 0) = pos(0);
  //         desired_state(i, 1) = pos(1);
  //         desired_state(i, 2) = yaw;

  //   std::ofstream csv_file;
  //   csv_file.open("/home/wjx/nryp_ws/src/swarm/waypoint_loader/waypoints/bspline_path.csv", std::ofstream::out); // 打开CSV文件以写入模式，自动覆盖
    
  //   cout<<"wjx"<<endl;
  //   for (int i = 0; i <= N; ++i) {
  //       double x = desired_state(i, 0);
  //       double y = desired_state(i, 1);
  //       double yaw = desired_state(i, 2); // 假设一个简单的角度

  //       // 写入CSV文件
  //       csv_file << x << "," << y << "," << yaw << "\n";
  //   }
    
  //   csv_file.close(); // 关闭文件
  //   ROS_INFO("B-spline path data has been written to bspline_path.csv");

  //     }
  //   } else {
  //     cout << "[Traj server]: invalid time." << endl;
  // }

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

    control_cmd_pub = nh.createTimer(ros::Duration(0.3), publish_control_cmd);
    
    ros::spin();
    return 0;

}



