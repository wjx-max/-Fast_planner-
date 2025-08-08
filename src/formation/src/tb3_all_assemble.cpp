#include <ros/ros.h>
#include "std_msgs/String.h"
#include <iostream>
#include <geometry_msgs/PoseStamped.h>
//rotopic info 话题名
//领航者实时位置消息类型
#include<geometry_msgs/PoseWithCovarianceStamped.h>
#include "nav_msgs/Odometry.h"
#include <tf/tf.h>
#include <ros/time.h> 

/*
1、先发布初始位置 PubStartPosition(仿真环境有初始位置可不调用)
2、集结所有车成编队队形 AssembledFormation
3、发布领航者目标点位置  PubLeadPosition (将is_start_ok ==true)
4、跟随者跟跟随领航者位置
*/

ros::Publisher cur1_pub;
ros::Publisher cur2_pub;
ros::Publisher cur3_pub;
ros::Publisher cur4_pub;
ros::Publisher cur5_pub;
ros::Publisher cur6_pub;


//2、集结所有车成编队队形 AssembledFormation
void AssembledFormation(){
    //----------//
    
    double cur1_pose_x, cur1_pose_y,cur1_pose_yaw;
    double cur2_pose_x, cur2_pose_y,cur2_pose_yaw;
    double cur3_pose_x, cur3_pose_y,cur3_pose_yaw;
    double cur4_pose_x, cur4_pose_y,cur4_pose_yaw;
    double cur5_pose_x, cur5_pose_y,cur5_pose_yaw;
    double cur6_pose_x, cur6_pose_y,cur6_pose_yaw;

   //跟随者需要根据领航者起始点和队形计算位置关系
    geometry_msgs::PoseStamped cur1_msg; 
    cur1_msg.header.frame_id = "world";
    cur1_msg.header.stamp = ros::Time::now();  //当前的时间，最好用领航者的时间戳
    cur1_msg.pose.position.x = -1.0;//cur1_pose_x;
    cur1_msg.pose.position.y = 0;//cur1_pose_y;
    cur1_msg.pose.position.z = 0;
    cur1_msg.pose.orientation = tf::createQuaternionMsgFromRollPitchYaw(0,0,1.55);

    geometry_msgs::PoseStamped cur2_msg; 
    cur2_msg.header.frame_id = "world";
    cur2_msg.header.stamp = ros::Time::now();  //当前的时间，最好用领航者的时间戳
    cur2_msg.pose.position.x = -1.0;//cur2_pose_x;
    cur2_msg.pose.position.y =  2.0;//cur2_pose_y;
    cur2_msg.pose.position.z = 0;//
    cur2_msg.pose.orientation = tf::createQuaternionMsgFromRollPitchYaw(0,0,1.55);

    geometry_msgs::PoseStamped cur3_msg; 
    cur3_msg.header.frame_id = "world";
    cur3_msg.header.stamp = ros::Time::now();  //当前的时间，最好用领航者的时间戳
    cur3_msg.pose.position.x = -1.0;//cur3_pose_x;
    cur3_msg.pose.position.y = -2.0;//cur3_pose_y;
    cur3_msg.pose.position.z = 0;
    cur3_msg.pose.orientation = tf::createQuaternionMsgFromRollPitchYaw(0,0,1.55);


    geometry_msgs::PoseStamped cur4_msg; 
    cur4_msg.header.frame_id = "world";
    cur4_msg.header.stamp = ros::Time::now();  //当前的时间，最好用领航者的时间戳
    cur4_msg.pose.position.x = -3.0;//cur2_pose_x;
    cur4_msg.pose.position.y = 0.0;//cur2_pose_y;
    cur4_msg.pose.position.z = 0;
    cur4_msg.pose.orientation = tf::createQuaternionMsgFromRollPitchYaw(0,0,1.55);


    geometry_msgs::PoseStamped cur5_msg; 
    cur5_msg.header.frame_id = "world";
    cur5_msg.header.stamp = ros::Time::now();  //当前的时间，最好用领航者的时间戳
    cur5_msg.pose.position.x = -3.0;//cur2_pose_x;
    cur5_msg.pose.position.y = 2.0;//cur2_pose_y;
    cur5_msg.pose.position.z = 0;
    cur5_msg.pose.orientation = tf::createQuaternionMsgFromRollPitchYaw(0,0,1.55);



    geometry_msgs::PoseStamped cur6_msg; 
    cur6_msg.header.frame_id = "world";
    cur6_msg.header.stamp = ros::Time::now();  //当前的时间，最好用领航者的时间戳
    cur6_msg.pose.position.x = -3.0;//cur2_pose_x;
    cur6_msg.pose.position.y = -2.0;//cur2_pose_y;
    cur6_msg.pose.position.z = 0;
    cur6_msg.pose.orientation = tf::createQuaternionMsgFromRollPitchYaw(0,0,1.55);




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


int main(int argc, char *argv[])
{
    std::cout << "init............. " << std::endl;
    ros::init(argc, argv, "navgoal_rviz");
    ros::NodeHandle nh;

    //订阅rviz 2Dgoal
    // ros::Subscriber sub = nh.subscribe("/ares2/move_base_simple/goal", 10, Callback);//队列长度:1000或1或其他
    //订阅领航者时时位置
    
    cur1_pub = nh.advertise<geometry_msgs::PoseStamped>("/tb3_1/move_base_simple/goal", 1); //initialize 
    cur2_pub = nh.advertise<geometry_msgs::PoseStamped>("/tb3_2/move_base_simple/goal", 1); //initialize 
    cur3_pub = nh.advertise<geometry_msgs::PoseStamped>("/tb3_3/move_base_simple/goal", 1); //initialize 
    cur4_pub = nh.advertise<geometry_msgs::PoseStamped>("/tb3_4/move_base_simple/goal", 1); //initialize 
    cur5_pub = nh.advertise<geometry_msgs::PoseStamped>("/tb3_5/move_base_simple/goal", 1); //initialize 
    cur6_pub = nh.advertise<geometry_msgs::PoseStamped>("/tb3_6/move_base_simple/goal", 1); //initialize 



    ros::AsyncSpinner spinner(4);
    spinner.start();

      
    //2、集结所有车成编队队形 AssembledFormation
    AssembledFormation();

    
    while(ros::ok())
    {
        ros::spinOnce();
    }

    spinner.stop();
  return 0;
}
