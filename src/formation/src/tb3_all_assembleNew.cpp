#include "ros/ros.h"
#include "geometry_msgs/PoseStamped.h"
#include "nav_msgs/Odometry.h"
#include "tf/transform_datatypes.h"
#include "std_msgs/String.h"
#include <iostream>
//rotopic info 话题名
//领航者实时位置消息类型
#include<geometry_msgs/PoseWithCovarianceStamped.h>
#include <tf/tf.h>
#include <ros/time.h> 

// 发布器
ros::Publisher cur1_pub;
ros::Publisher cur2_pub;
ros::Publisher cur3_pub;
ros::Publisher cur4_pub;
ros::Publisher cur5_pub;
ros::Publisher cur6_pub;

ros::Publisher complete_pub;  // 发布完成话题

// 目标位置
double cur1_target_x = -1.0, cur1_target_y = 0.0;
double cur2_target_x = -1.0, cur2_target_y = 1.0;
double cur3_target_x = -1.0, cur3_target_y = -1.0;
double cur4_target_x = -2.0, cur4_target_y = 0.0;
double cur5_target_x = -2.0, cur5_target_y = 1.0;
double cur6_target_x = -2.0, cur6_target_y = -1.0;

bool is_tb3_1_ok_ = false;
bool is_tb3_2_ok_ = false;
bool is_tb3_3_ok_ = false;
bool is_tb3_4_ok_ = false;
bool is_tb3_5_ok_ = false;
bool is_tb3_6_ok_ = false;

// 距离阈值
const double threshold = 0.2; // 阈值，根据实际需要调整

// 里程计回调函数
void odomCallback1(const nav_msgs::Odometry::ConstPtr& msg) {
    double robot_x = msg->pose.pose.position.x;
    double robot_y = msg->pose.pose.position.y;
    if (fabs(robot_x - cur1_target_x) < threshold && fabs(robot_y - cur1_target_y) < threshold) {
        is_tb3_1_ok_ = true;
    }
}

// 里程计回调函数
void odomCallback2(const nav_msgs::Odometry::ConstPtr& msg) {
    double robot_x = msg->pose.pose.position.x;
    double robot_y = msg->pose.pose.position.y;
    if (fabs(robot_x - cur2_target_x) < threshold && fabs(robot_y - cur2_target_y) < threshold) {
        is_tb3_2_ok_ = true;
    }
}

// 里程计回调函数
void odomCallback3(const nav_msgs::Odometry::ConstPtr& msg) {
    double robot_x = msg->pose.pose.position.x;
    double robot_y = msg->pose.pose.position.y;
    if (fabs(robot_x - cur3_target_x) < threshold && fabs(robot_y - cur3_target_y) < threshold) {
        is_tb3_3_ok_ = true;
    }
}

// 里程计回调函数
void odomCallback4(const nav_msgs::Odometry::ConstPtr& msg) {
    double robot_x = msg->pose.pose.position.x;
    double robot_y = msg->pose.pose.position.y;
    if (fabs(robot_x - cur4_target_x) < threshold && fabs(robot_y - cur4_target_y) < threshold) {
        is_tb3_4_ok_ = true;
    }
}

// 里程计回调函数
void odomCallback5(const nav_msgs::Odometry::ConstPtr& msg) {
    double robot_x = msg->pose.pose.position.x;
    double robot_y = msg->pose.pose.position.y;
    if (fabs(robot_x - cur5_target_x) < threshold && fabs(robot_y - cur5_target_y) < threshold) {
        is_tb3_5_ok_ = true;
    }
}

// 里程计回调函数
void odomCallback6(const nav_msgs::Odometry::ConstPtr& msg) {
    double robot_x = msg->pose.pose.position.x;
    double robot_y = msg->pose.pose.position.y;
    if (fabs(robot_x - cur6_target_x) < threshold && fabs(robot_y - cur6_target_y) < threshold) {
        is_tb3_6_ok_ = true;
    }
}

// 订阅里程计
void subscribeOdom(ros::NodeHandle& nh) {
    // 检查各个机器人的里程计话题是否有效
    if (ros::topic::waitForMessage<nav_msgs::Odometry>("/tb3_1/odom", nh, ros::Duration(1.0)) == nullptr) {
        ROS_INFO("Robot 1 does not have odom data, assuming it's at the target position.");
        is_tb3_1_ok_ = true;
    }
    if (ros::topic::waitForMessage<nav_msgs::Odometry>("/tb3_2/odom", nh, ros::Duration(1.0)) == nullptr) {
        ROS_INFO("Robot 2 does not have odom data, assuming it's at the target position.");
        is_tb3_2_ok_ = true;
    }
    if (ros::topic::waitForMessage<nav_msgs::Odometry>("/tb3_3/odom", nh, ros::Duration(1.0)) == nullptr) {
        ROS_INFO("Robot 3 does not have odom data, assuming it's at the target position.");
        is_tb3_3_ok_ = true;
    }
    if (ros::topic::waitForMessage<nav_msgs::Odometry>("/tb3_4/odom", nh, ros::Duration(1.0)) == nullptr) {
        ROS_INFO("Robot 4 does not have odom data, assuming it's at the target position.");
        is_tb3_4_ok_ = true;
    }
    if (ros::topic::waitForMessage<nav_msgs::Odometry>("/tb3_5/odom", nh, ros::Duration(1.0)) == nullptr) {
        ROS_INFO("Robot 5 does not have odom data, assuming it's at the target position.");
        is_tb3_5_ok_ = true;
    }
    if (ros::topic::waitForMessage<nav_msgs::Odometry>("/tb3_6/odom", nh, ros::Duration(1.0)) == nullptr) {
        ROS_INFO("Robot 6 does not have odom data, assuming it's at the target position.");
        is_tb3_6_ok_ = true;
    }
}

void AssembledFormation(){
    // 发布机器人的初始位置（与目标位置一致，机器人开始移动）
    geometry_msgs::PoseStamped cur1_msg, cur2_msg, cur3_msg, cur4_msg, cur5_msg, cur6_msg;

    // 设置目标位置并发布
    cur1_msg.header.frame_id = "world";
    cur1_msg.header.stamp = ros::Time::now();
    cur1_msg.pose.position.x = cur1_target_x;
    cur1_msg.pose.position.y = cur1_target_y;
    cur1_msg.pose.position.z = 0;
    cur1_msg.pose.orientation = tf::createQuaternionMsgFromRollPitchYaw(0, 0, 1.55);

    cur2_msg.header.frame_id = "world";
    cur2_msg.header.stamp = ros::Time::now();
    cur2_msg.pose.position.x = cur2_target_x;
    cur2_msg.pose.position.y = cur2_target_y;
    cur2_msg.pose.position.z = 0;
    cur2_msg.pose.orientation = tf::createQuaternionMsgFromRollPitchYaw(0, 0, 1.55);

    cur3_msg.header.frame_id = "world";
    cur3_msg.header.stamp = ros::Time::now();
    cur3_msg.pose.position.x = cur3_target_x;
    cur3_msg.pose.position.y = cur3_target_y;
    cur3_msg.pose.position.z = 0;
    cur3_msg.pose.orientation = tf::createQuaternionMsgFromRollPitchYaw(0, 0, 1.55);

    cur4_msg.header.frame_id = "world";
    cur4_msg.header.stamp = ros::Time::now();
    cur4_msg.pose.position.x = cur4_target_x;
    cur4_msg.pose.position.y = cur4_target_y;
    cur4_msg.pose.position.z = 0;
    cur4_msg.pose.orientation = tf::createQuaternionMsgFromRollPitchYaw(0, 0, 1.55);

    cur5_msg.header.frame_id = "world";
    cur5_msg.header.stamp = ros::Time::now();
    cur5_msg.pose.position.x = cur5_target_x;
    cur5_msg.pose.position.y = cur5_target_y;
    cur5_msg.pose.position.z = 0;
    cur5_msg.pose.orientation = tf::createQuaternionMsgFromRollPitchYaw(0, 0, 1.55);

    cur6_msg.header.frame_id = "world";
    cur6_msg.header.stamp = ros::Time::now();
    cur6_msg.pose.position.x = cur6_target_x;
    cur6_msg.pose.position.y = cur6_target_y;
    cur6_msg.pose.position.z = 0;
    cur6_msg.pose.orientation = tf::createQuaternionMsgFromRollPitchYaw(0, 0, 1.55);

    // 发布
    int i = 0;
    while(i < 5){
        cur1_pub.publish(cur1_msg);
        cur2_pub.publish(cur2_msg);
        cur3_pub.publish(cur3_msg);
        cur4_pub.publish(cur4_msg);
        cur5_pub.publish(cur5_msg);
        cur6_pub.publish(cur6_msg);

        ros::Duration(0.1).sleep();
        i++;
        std::cout << "pub............. " << std::endl;
    }
}

int main(int argc, char **argv) {
    ros::init(argc, argv, "formation_control");
    ros::NodeHandle nh;

    // 发布器初始化
    complete_pub = nh.advertise<std_msgs::String>("/complete", 1);

    ros::Subscriber sub1 = nh.subscribe<nav_msgs::Odometry>("/tb3_1/odom", 10, odomCallback1);
    ros::Subscriber sub2 = nh.subscribe<nav_msgs::Odometry>("/tb3_2/odom", 10, odomCallback2);
    ros::Subscriber sub3 = nh.subscribe<nav_msgs::Odometry>("/tb3_3/odom", 10, odomCallback3);
    ros::Subscriber sub4 = nh.subscribe<nav_msgs::Odometry>("/tb3_4/odom", 10, odomCallback4);
    ros::Subscriber sub5 = nh.subscribe<nav_msgs::Odometry>("/tb3_5/odom", 10, odomCallback5);
    ros::Subscriber sub6 = nh.subscribe<nav_msgs::Odometry>("/tb3_6/odom", 10, odomCallback6);

    // 发布器初始化
    cur1_pub = nh.advertise<geometry_msgs::PoseStamped>("/tb3_1/move_base_simple/goal", 1);
    cur2_pub = nh.advertise<geometry_msgs::PoseStamped>("/tb3_2/move_base_simple/goal", 1);
    cur3_pub = nh.advertise<geometry_msgs::PoseStamped>("/tb3_3/move_base_simple/goal", 1);
    cur4_pub = nh.advertise<geometry_msgs::PoseStamped>("/tb3_4/move_base_simple/goal", 1);
    cur5_pub = nh.advertise<geometry_msgs::PoseStamped>("/tb3_5/move_base_simple/goal", 1);
    cur6_pub = nh.advertise<geometry_msgs::PoseStamped>("/tb3_6/move_base_simple/goal", 1);

    // 订阅里程计话题
    subscribeOdom(nh);

    // 初始化编队
    AssembledFormation();

    // 检查所有机器人是否都到达目标点
    while (ros::ok()) {
        if (is_tb3_1_ok_ && is_tb3_2_ok_ && is_tb3_3_ok_ && is_tb3_4_ok_ && is_tb3_5_ok_ && is_tb3_6_ok_) {
            
            // 当所有机器人都到达目标位置时，发布"complete"话题
            std_msgs::String complete_msg;
            complete_msg.data = "All robots reached their target positions!";
            complete_pub.publish(complete_msg);

            //ROS_INFO("All robots reached their target positions!");
            break;  // 退出循环，表示任务完成

            
        }
        ros::spinOnce();  // 继续循环执行回调
    }

    return 0;
}
