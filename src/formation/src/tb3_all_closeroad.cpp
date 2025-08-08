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


ros::Publisher cur2_pub;
ros::Publisher cur3_pub;
ros::Publisher cur4_pub;
ros::Publisher cur5_pub;
ros::Publisher cur6_pub;


void LeaderPoseCallback(const nav_msgs::Odometry::ConstPtr& msg)
{   

    //double roll, pitch, yaw;//定义存储r\p\y的容器
    double roll;
    std::cout << " LeaderPoseCallback" << std::endl;
    //时间戳 领航者的时间戳 领航者的时间戳
    //ros::time 
    double x=msg->pose.pose.position.x;
    double y=msg->pose.pose.position.y;
    double pitch=msg->pose.pose.orientation.z;
    double yaw=msg->pose.pose.orientation.w;

     
    //四元数转欧拉角
    tf::Quaternion quat;
    tf::quaternionMsgToTF(msg->pose.pose.orientation, quat);
    tf::Matrix3x3(quat).getRPY(roll, pitch, yaw);//进行转换

    //打印输出
    std::cout<<"pos-x: "<<x<<"pos-y: "<<y<<"pos-pitch: "<<pitch<<"pos-yaw: "<<yaw<<std::endl;

    //x,y,yaw 是领航者0
    //通过相对位置关系）都是在同一坐标系
    //.........计算跟随者位置cur2_pose、cur3_pose..................//
    //TODU
    double cur2_pose_x, cur2_pose_y, cur2_pose_pitch,cur2_pose_yaw;
    double cur3_pose_x ,cur3_pose_y, cur3_pose_pitch,cur3_pose_yaw;
    double cur4_pose_x, cur4_pose_y, cur4_pose_pitch,cur4_pose_yaw;
    double cur5_pose_x ,cur5_pose_y, cur5_pose_pitch,cur5_pose_yaw;
    double cur6_pose_x, cur6_pose_y, cur6_pose_pitch,cur6_pose_yaw;

    //2
    cur2_pose_x = x;
    cur2_pose_y = y+2.0;
    
    cur2_pose_pitch=msg->pose.pose.orientation.z; //四元数中的z值，表示旋转轴向量 (v) 在 z 轴上的分量。
    cur2_pose_yaw=msg->pose.pose.orientation.w;//四元数中的w值，表示旋转角度的标量部分 (s)。
    
    //3
    cur3_pose_x=x;
    cur3_pose_y=y-2.0;

    cur3_pose_pitch=msg->pose.pose.orientation.z; //四元数中的z值，表示旋转轴向量 (v) 在 z 轴上的分量。
    cur3_pose_yaw=msg->pose.pose.orientation.w;//四元数中的w值，表示旋转角度的标量部分 (s)。

    //4
    cur4_pose_x = x-3.0;
    cur4_pose_y = y;
    
    cur4_pose_pitch=msg->pose.pose.orientation.z; //四元数中的z值，表示旋转轴向量 (v) 在 z 轴上的分量。
    cur4_pose_yaw=msg->pose.pose.orientation.w;//四元数中的w值，表示旋转角度的标量部分 (s)。


    //5
    cur5_pose_x = x-3.0;
    cur5_pose_y = y+2.0;
    
    cur5_pose_pitch=msg->pose.pose.orientation.z; //四元数中的z值，表示旋转轴向量 (v) 在 z 轴上的分量。
    cur5_pose_yaw=msg->pose.pose.orientation.w;//四元数中的w值，表示旋转角度的标量部分 (s)。


    //6
    cur6_pose_x = x-3.0;
    cur6_pose_y = y-2.0;
    
    cur6_pose_pitch=msg->pose.pose.orientation.z; //四元数中的z值，表示旋转轴向量 (v) 在 z 轴上的分量。
    cur6_pose_yaw=msg->pose.pose.orientation.w;//四元数中的w值，表示旋转角度的标量部分 (s)。



    //发布跟随者实时位置
    geometry_msgs::PoseStamped cur2_msg; 
    cur2_msg.header.frame_id = "world";
    cur2_msg.header.stamp = ros::Time::now();  //当前的时间，最好用领航者的时间戳
    cur2_msg.pose.position.x = cur2_pose_x;//cur1_pose_x;
    cur2_msg.pose.position.y = cur2_pose_y;//cur1_pose_y;
    cur2_msg.pose.position.z = 0;
    
    cur2_msg.pose.orientation.x = 0;
    cur2_msg.pose.orientation.y = 0;
    cur2_msg.pose.orientation.z =cur2_pose_pitch;
    cur2_msg.pose.orientation.w = cur2_pose_yaw;

    //角度需要转为四元数
    //如果角度不需要变直接取领航者角度四元数quat
    cur2_msg.pose.orientation = tf::createQuaternionMsgFromRollPitchYaw(0,0,1.55);//cur1_pose_yaw
    //如果需要变需要要转换
    //cur2_msg.pose.orientation = tf::createQuaternionMsgFromRollPitchYaw(roll,pitch,yaw);//欧拉角转四元数（geometry_msgs::Quaternion）
    
    //发布
    geometry_msgs::PoseStamped cur3_msg; 
    cur3_msg.header.frame_id = "world";
    cur3_msg.header.stamp = ros::Time::now();  //当前的时间，最好用领航者的时间戳
    cur3_msg.pose.position.x = cur3_pose_x;//cur2_pose_x;
    cur3_msg.pose.position.y = cur3_pose_y;//cur2_pose_y;
    cur3_msg.pose.position.z = 0;

    cur3_msg.pose.orientation.x = 0;
    cur3_msg.pose.orientation.y = 0;
    cur3_msg.pose.orientation.z = cur3_pose_pitch;
    cur3_msg.pose.orientation.w = cur3_pose_yaw;

    cur3_msg.pose.orientation = tf::createQuaternionMsgFromRollPitchYaw(0,0,1.55);//cur1_pose_yaw



    //发布
    geometry_msgs::PoseStamped cur4_msg; 
    cur4_msg.header.frame_id = "world";
    cur4_msg.header.stamp = ros::Time::now();  //当前的时间，最好用领航者的时间戳
    cur4_msg.pose.position.x = cur4_pose_x;//cur2_pose_x;
    cur4_msg.pose.position.y = cur4_pose_y;//cur2_pose_y;
    cur4_msg.pose.position.z = 0;

    cur4_msg.pose.orientation.x = 0;
    cur4_msg.pose.orientation.y = 0;
    cur4_msg.pose.orientation.z = cur4_pose_pitch;
    cur4_msg.pose.orientation.w = cur4_pose_yaw;

    cur4_msg.pose.orientation = tf::createQuaternionMsgFromRollPitchYaw(0,0,1.55);//cur1_pose_yaw




        //发布
    geometry_msgs::PoseStamped cur5_msg; 
    cur5_msg.header.frame_id = "world";
    cur5_msg.header.stamp = ros::Time::now();  //当前的时间，最好用领航者的时间戳
    cur5_msg.pose.position.x = cur5_pose_x;//cur2_pose_x;
    cur5_msg.pose.position.y = cur5_pose_y;//cur2_pose_y;
    cur5_msg.pose.position.z = 0;

    cur5_msg.pose.orientation.x = 0;
    cur5_msg.pose.orientation.y = 0;
    cur5_msg.pose.orientation.z = cur5_pose_pitch;
    cur5_msg.pose.orientation.w = cur5_pose_yaw;

    cur5_msg.pose.orientation = tf::createQuaternionMsgFromRollPitchYaw(0,0,1.55);//cur1_pose_yaw



        //发布
    geometry_msgs::PoseStamped cur6_msg; 
    cur6_msg.header.frame_id = "world";
    cur6_msg.header.stamp = ros::Time::now();  //当前的时间，最好用领航者的时间戳
    cur6_msg.pose.position.x = cur6_pose_x;//cur2_pose_x;
    cur6_msg.pose.position.y = cur6_pose_y;//cur2_pose_y;
    cur6_msg.pose.position.z = 0;

    cur6_msg.pose.orientation.x = 0;
    cur6_msg.pose.orientation.y = 0;
    cur6_msg.pose.orientation.z = cur6_pose_pitch;
    cur6_msg.pose.orientation.w = cur6_pose_yaw;

    cur6_msg.pose.orientation = tf::createQuaternionMsgFromRollPitchYaw(0,0,1.55);//cur1_pose_yaw

    int i = 0;
    while(i < 5){
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
    ros::init(argc, argv, "navgoal2_rviz");
    ros::NodeHandle nh;


    ros::Subscriber sub = nh.subscribe("/tb3_1/odom", 10, LeaderPoseCallback);//队列长度:1000或1或其他
    
    cur2_pub = nh.advertise<geometry_msgs::PoseStamped>("/tb3_2/move_base_simple/goal", 1); //initialize 
    cur3_pub = nh.advertise<geometry_msgs::PoseStamped>("/tb3_3/move_base_simple/goal", 1); //initialize 
    cur4_pub = nh.advertise<geometry_msgs::PoseStamped>("/tb3_4/move_base_simple/goal", 1); //initialize 
    cur5_pub = nh.advertise<geometry_msgs::PoseStamped>("/tb3_5/move_base_simple/goal", 1); //initialize 
    cur6_pub = nh.advertise<geometry_msgs::PoseStamped>("/tb3_6/move_base_simple/goal", 1); //initialize 
    
    ros::AsyncSpinner spinner(4);
    spinner.start();

    
    while(ros::ok())
    {
        ros::spinOnce();
    }
    spinner.stop();

  return 0;
}