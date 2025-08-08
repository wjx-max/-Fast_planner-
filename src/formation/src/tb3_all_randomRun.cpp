#include <ros/ros.h>
#include "std_msgs/String.h"
#include <iostream>
#include <geometry_msgs/PoseStamped.h>
#include <geometry_msgs/PoseWithCovarianceStamped.h>
#include "nav_msgs/Odometry.h"
#include <tf/tf.h>
#include <ros/time.h>
#include <cstdlib> // 引入rand函数
#include <ctime>   // 引入time函数来初始化随机数种子

ros::Publisher cur1_pub;
ros::Publisher cur2_pub;
ros::Publisher cur3_pub;
ros::Publisher cur4_pub;
ros::Publisher cur5_pub;
ros::Publisher cur6_pub;

// 随机生成指定范围内的浮动数值
double getRandomInRange(double min, double max) {
    return min + static_cast<double>(rand()) / (static_cast<double>(RAND_MAX / (max - min)));
}

// 2、给所有机器人分配随机目标位置
void RandomRunall(){
    
    // 随机生成目标位置范围在-8到8之间
    double cur1_pose_x = getRandomInRange(-8.0, 8.0);
    double cur1_pose_y = getRandomInRange(-8.0, 8.0);
    double cur1_pose_yaw = getRandomInRange(-3.14, 3.14); // 随机生成角度 yaw 范围为 -π 到 π
    
    double cur2_pose_x = getRandomInRange(-8.0, 8.0);
    double cur2_pose_y = getRandomInRange(-8.0, 8.0);
    double cur2_pose_yaw = getRandomInRange(-3.14, 3.14); // 随机生成角度 yaw 范围为 -π 到 π

    double cur3_pose_x = getRandomInRange(-8.0, 8.0);
    double cur3_pose_y = getRandomInRange(-8.0, 8.0);
    double cur3_pose_yaw = getRandomInRange(-3.14, 3.14); // 随机生成角度 yaw 范围为 -π 到 π

    double cur4_pose_x = getRandomInRange(-8.0, 8.0);
    double cur4_pose_y = getRandomInRange(-8.0, 8.0);
    double cur4_pose_yaw = getRandomInRange(-3.14, 3.14); // 随机生成角度 yaw 范围为 -π 到 π

    double cur5_pose_x = getRandomInRange(-8.0, 8.0);
    double cur5_pose_y = getRandomInRange(-8.0, 8.0);
    double cur5_pose_yaw = getRandomInRange(-3.14, 3.14); // 随机生成角度 yaw 范围为 -π 到 π

    double cur6_pose_x = getRandomInRange(-8.0, 8.0);
    double cur6_pose_y = getRandomInRange(-8.0, 8.0);
    double cur6_pose_yaw = getRandomInRange(-3.14, 3.14); // 随机生成角度 yaw 范围为 -π 到 π

    geometry_msgs::PoseStamped cur1_msg;
    cur1_msg.header.frame_id = "world";
    cur1_msg.header.stamp = ros::Time::now();
    cur1_msg.pose.position.x = cur1_pose_x;
    cur1_msg.pose.position.y = cur1_pose_y;
    cur1_msg.pose.position.z = 0;
    cur1_msg.pose.orientation = tf::createQuaternionMsgFromRollPitchYaw(0, 0, cur1_pose_yaw);

    geometry_msgs::PoseStamped cur2_msg;
    cur2_msg.header.frame_id = "world";
    cur2_msg.header.stamp = ros::Time::now();
    cur2_msg.pose.position.x = cur2_pose_x;
    cur2_msg.pose.position.y = cur2_pose_y;
    cur2_msg.pose.position.z = 0;
    cur2_msg.pose.orientation = tf::createQuaternionMsgFromRollPitchYaw(0, 0, cur2_pose_yaw);

    geometry_msgs::PoseStamped cur3_msg;
    cur3_msg.header.frame_id = "world";
    cur3_msg.header.stamp = ros::Time::now();
    cur3_msg.pose.position.x = cur3_pose_x;
    cur3_msg.pose.position.y = cur3_pose_y;
    cur3_msg.pose.position.z = 0;
    cur3_msg.pose.orientation = tf::createQuaternionMsgFromRollPitchYaw(0, 0, cur3_pose_yaw);


    geometry_msgs::PoseStamped cur4_msg;
    cur4_msg.header.frame_id = "world";
    cur4_msg.header.stamp = ros::Time::now();
    cur4_msg.pose.position.x = cur4_pose_x;
    cur4_msg.pose.position.y = cur4_pose_y;
    cur4_msg.pose.position.z = 0;
    cur4_msg.pose.orientation = tf::createQuaternionMsgFromRollPitchYaw(0, 0, cur4_pose_yaw);


    geometry_msgs::PoseStamped cur5_msg;
    cur5_msg.header.frame_id = "world";
    cur5_msg.header.stamp = ros::Time::now();
    cur5_msg.pose.position.x = cur5_pose_x;
    cur5_msg.pose.position.y = cur5_pose_y;
    cur5_msg.pose.position.z = 0;
    cur5_msg.pose.orientation = tf::createQuaternionMsgFromRollPitchYaw(0, 0, cur5_pose_yaw);


    geometry_msgs::PoseStamped cur6_msg;
    cur6_msg.header.frame_id = "world";
    cur6_msg.header.stamp = ros::Time::now();
    cur6_msg.pose.position.x = cur6_pose_x;
    cur6_msg.pose.position.y = cur6_pose_y;
    cur6_msg.pose.position.z = 0;
    cur6_msg.pose.orientation = tf::createQuaternionMsgFromRollPitchYaw(0, 0, cur6_pose_yaw);

    int i = 0;
    while (i < 5) {
        cur1_pub.publish(cur1_msg);
        cur2_pub.publish(cur2_msg);
        cur3_pub.publish(cur3_msg);
        cur4_pub.publish(cur4_msg);
        cur5_pub.publish(cur5_msg);
        cur6_pub.publish(cur6_msg);
        ros::Duration(0.1).sleep(); // 每发布一次目标，等待 0.1 秒
        i++;
        std::cout << "pub............. " << std::endl;
    }
}

int main(int argc, char *argv[])
{
    std::cout << "init............. " << std::endl;
    
    // 初始化 ROS 节点
    ros::init(argc, argv, "navgoal_rviz");
    ros::NodeHandle nh;
    
    // 初始化发布器
    cur1_pub = nh.advertise<geometry_msgs::PoseStamped>("/tb3_1/move_base_simple/goal", 1); 
    cur2_pub = nh.advertise<geometry_msgs::PoseStamped>("/tb3_2/move_base_simple/goal", 1); 
    cur3_pub = nh.advertise<geometry_msgs::PoseStamped>("/tb3_3/move_base_simple/goal", 1); 
    cur4_pub = nh.advertise<geometry_msgs::PoseStamped>("/tb3_4/move_base_simple/goal", 1); 
    cur5_pub = nh.advertise<geometry_msgs::PoseStamped>("/tb3_5/move_base_simple/goal", 1); 
    cur6_pub = nh.advertise<geometry_msgs::PoseStamped>("/tb3_6/move_base_simple/goal", 1); 
    
    ros::AsyncSpinner spinner(4); // 启动多线程
    spinner.start();
    
    // 初始化随机数生成器种子
    srand(time(0));

    // 调用函数让机器人跑向随机的目标点
    RandomRunall();

    while(ros::ok()) {
        ros::spinOnce();
    }

    spinner.stop();
    return 0;
}
