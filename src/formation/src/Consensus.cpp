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
3、发布领航者目标点位置  PubLeadPosition (将is_start_ok ==true)
4、跟随者跟跟随领航者位置
*/

bool is_start_ok_ = false;

//odom数据最好放在一个队列里面 维护一个队列 ,20帧大小;
std::vector<nav_msgs::Odometry> ares1_odom_buf_;
std::vector<nav_msgs::Odometry> ares2_odom_buf_;
std::vector<nav_msgs::Odometry> ares3_odom_buf_;
ros::Publisher cur1_pub;
ros::Publisher cur2_pub;
ros::Publisher cur3_pub;

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
    double cur1_pose_x, cur1_pose_y, cur1_pose_pitch,cur1_pose_yaw;
    double cur2_pose_x, cur2_pose_y, cur2_pose_pitch,cur2_pose_yaw;
    double cur3_pose_x ,cur3_pose_y, cur3_pose_pitch,cur3_pose_yaw;


     cur1_pose_x = 12.5;
     cur1_pose_y = 0;
    
    cur1_pose_pitch=msg->pose.pose.orientation.z; //四元数中的z值，表示旋转轴向量 (v) 在 z 轴上的分量。
    cur1_pose_yaw=msg->pose.pose.orientation.w;//四元数中的w值，表示旋转角度的标量部分 (s)。

    if (ares2_odom_buf_.size() > 0) {
        // 获取 tb3_2 的位置信息
        const nav_msgs::Odometry& cur2_odom = ares2_odom_buf_.back();
        cur2_pose_x = cur2_odom.pose.pose.position.x;
        cur2_pose_y = cur2_odom.pose.pose.position.y;
        cur2_pose_pitch = cur2_odom.pose.pose.orientation.z;  // 使用四元数的z作为pitch
        cur2_pose_yaw = cur2_odom.pose.pose.orientation.w;     // 使用四元数的w作为yaw
    }


    if (ares3_odom_buf_.size() > 0) {
        // 获取 tb3_3 的位置信息
        const nav_msgs::Odometry& cur3_odom = ares3_odom_buf_.back();
        cur3_pose_x = cur3_odom.pose.pose.position.x;
        cur3_pose_y = cur3_odom.pose.pose.position.y;
        cur3_pose_pitch = cur3_odom.pose.pose.orientation.z;  // 使用四元数的z作为pitch
        cur3_pose_yaw = cur3_odom.pose.pose.orientation.w;     // 使用四元数的w作为yaw
    }


     cur2_pose_x=(msg->pose.pose.position.x-cur2_pose_x-(0-(-1)))+(cur3_pose_x-cur2_pose_x-(-1-(-1)))+cur2_pose_x;
     cur2_pose_y=(msg->pose.pose.position.y-cur2_pose_y-(0-(1)))+(cur3_pose_y-cur2_pose_y-(-1-(1)))+cur2_pose_y;
    
    cur2_pose_pitch=msg->pose.pose.orientation.z; //四元数中的z值，表示旋转轴向量 (v) 在 z 轴上的分量。
    cur2_pose_yaw=msg->pose.pose.orientation.w;//四元数中的w值，表示旋转角度的标量部分 (s)。
    
    
     cur3_pose_x=(msg->pose.pose.position.x-cur3_pose_x-(0-(-1)))+(cur2_pose_x-cur3_pose_x-(-1-(-1)))+cur3_pose_x;
     cur3_pose_y=(msg->pose.pose.position.y-cur3_pose_y-(0-(-1)))+(cur2_pose_y-cur3_pose_y-(1-(-1)))+cur3_pose_y;

    cur3_pose_pitch=msg->pose.pose.orientation.z; //四元数中的z值，表示旋转轴向量 (v) 在 z 轴上的分量。
    cur3_pose_yaw=msg->pose.pose.orientation.w;//四元数中的w值，表示旋转角度的标量部分 (s)。

//发布领航者目标位置
    geometry_msgs::PoseStamped cur1_msg; 
    cur1_msg.header.frame_id = "world";
    cur1_msg.header.stamp = ros::Time::now();  //当前的时间，最好用领航者的时间戳
    cur1_msg.pose.position.x = cur1_pose_x;//cur1_pose_x;
    cur1_msg.pose.position.y = cur1_pose_y;//cur1_pose_y;
    cur1_msg.pose.position.z = 0;
    
    cur1_msg.pose.orientation.x = 0;
    cur1_msg.pose.orientation.y = 0;
    cur1_msg.pose.orientation.z =cur1_pose_pitch;
    cur1_msg.pose.orientation.w = cur1_pose_yaw;

    //角度需要转为四元数
    //如果角度不需要变直接取领航者角度四元数quat
    cur1_msg.pose.orientation = tf::createQuaternionMsgFromRollPitchYaw(0,0,1.55);//cur1_pose_yaw
    //如果需要变需要要转换
    //cur2_msg.pose.orientation = tf::createQuaternionMsgFromRollPitchYaw(roll,pitch,yaw);//欧拉角转四元数（geometry_msgs::Quaternion）


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

    if(is_start_ok_){
         std::cout << "is_start_ok_" << std::endl;

         //cur1_pub.publish(cur1_msg);
         cur2_pub.publish(cur2_msg);
         cur3_pub.publish(cur3_msg);
         
    }

}


void ares1OdomCallback(const nav_msgs::Odometry::ConstPtr& msg){
    //接收/ares1/odom
    // std::cout << " 接收/ares1/odom" << std::endl;
    ares1_odom_buf_.push_back(*msg);
     if(ares1_odom_buf_.size() > 20){
        ares1_odom_buf_.erase(ares1_odom_buf_.begin());
    }
}

void ares2OdomCallback(const nav_msgs::Odometry::ConstPtr& msg){
    //接收/ares2/odom
    // std::cout << " 接收/ares2/odom" << std::endl;
    ares2_odom_buf_.push_back(*msg);
    if(ares2_odom_buf_.size() > 20){
        ares2_odom_buf_.erase(ares2_odom_buf_.begin());
    }

}

void ares3OdomCallback(const nav_msgs::Odometry::ConstPtr& msg){
    //接收/ares3/odom
    // std::cout << "接收/ares3/odom" << std::endl;
     ares3_odom_buf_.push_back(*msg);
      if(ares3_odom_buf_.size() > 20){
        ares3_odom_buf_.erase(ares3_odom_buf_.begin());
    }
}

//3、发布领航者目标点位置  PubLeadPosition (将is_start_ok ==true)
void PubLeadPosition(){
    //-----------//
std::cout << "PubLeadPosition is  OK............. " << std::endl;
    //开始跟随标志位
    is_start_ok_ = true;
}

bool ChekFormationOK(){
    // ros::Duration duration(20).sleep();
      ros::Duration(2).sleep();

    //订阅车的位置，如果位置在一定时间内没有变则意味着车到达目标点返回true;
    //要分别判断三台车是否都到达目标点
    //注意最好加一个判断，车要先走后再判断是否到达目标点
    int num1 = 0;
    int num2 = 0;
    int num3 = 0;

    std::cout << "ChekFormationOK2 waiting............. " << std::endl;
   
    while(true){
        if(ares1_odom_buf_.size()>0){
            nav_msgs::Odometry cur1_msg;
            cur1_msg = ares1_odom_buf_.back(); 
            std::cout << "ares1_odom_buf............. " << cur1_msg.twist.twist.linear.x << ", " << cur1_msg.twist.twist.linear.y << std::endl;
            if(std::abs(cur1_msg.twist.twist.linear.x ) < 1e-3 && std::abs(cur1_msg.twist.twist.linear.y)  < 1e-3 &&  num1 <  31){
                std::cout << "num1: " << num1 << std::endl; 
                num1++;
            }
        }
        if(ares2_odom_buf_.size()>0 ){
            //  std::cout << "ares2_odom_buf............. " << std::endl;
            nav_msgs::Odometry cur2_msg;
            cur2_msg = ares2_odom_buf_.back();
            if(std::abs(cur2_msg.twist.twist.linear.x ) < 1e-3 && std::abs(cur2_msg.twist.twist.linear.y)  < 1e-3 ){
                num2++;
            }
        }
        if(ares3_odom_buf_.size()>0 ){
            //  std::cout << "ares3_odom_buf............. " << std::endl;
            nav_msgs::Odometry cur3_msg;
            cur3_msg = ares3_odom_buf_.back();
            if(std::abs(cur3_msg.twist.twist.linear.x ) < 1e-3 && std::abs(cur3_msg.twist.twist.linear.y)  < 1e-3 ){
                num3++;
            }
        }
        if(num1 > 30 && num2 >30 && num3 > 30){
            std::cout << "ChekFormationOK waiting OK " << std::endl;
            return true;
        }
    } 
}

int main(int argc, char *argv[])
{
    std::cout << "init............. " << std::endl;
    ros::init(argc, argv, "navgoal2_rviz");
    ros::NodeHandle nh;

    //订阅rviz 2Dgoal
    // ros::Subscriber sub = nh.subscribe("/ares2/move_base_simple/goal", 10, Callback);//队列长度:1000或1或其他
    //订阅领航者时时位置

     ros::Subscriber sub = nh.subscribe("/tb3_1/odom", 10, LeaderPoseCallback);//队列长度:1000或1或其他

    ros::Subscriber sub1 = nh.subscribe("/tb3_1/odom", 10, ares1OdomCallback);//队列长度:1000或1或其他
    ros::Subscriber sub2= nh.subscribe("/tb3_2/odom", 10, ares2OdomCallback);//队列长度:1000或1或其他
    ros::Subscriber sub3= nh.subscribe("/tb3_3/odom", 10, ares3OdomCallback);//队列长度:1000或1或其他
    
    cur1_pub = nh.advertise<geometry_msgs::PoseStamped>("/tb3_1/move_base_simple/goal", 1); //initialize 
    cur2_pub = nh.advertise<geometry_msgs::PoseStamped>("/tb3_2/move_base_simple/goal", 1); //initialize 
    cur3_pub = nh.advertise<geometry_msgs::PoseStamped>("/tb3_3/move_base_simple/goal", 1); //initialize 
    
    ros::AsyncSpinner spinner(4);
    spinner.start();

     //先检查是否到目标点
    if(ChekFormationOK()){
    //  3、发布领航者目标点位置  PubLeadPosition (将is_start_ok ==true)
        PubLeadPosition();
    }
    
    while(ros::ok())
    {
        ros::spinOnce();
    }
    spinner.stop();

  return 0;
}
