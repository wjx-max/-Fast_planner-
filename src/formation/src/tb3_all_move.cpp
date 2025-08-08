#include <ros/ros.h>
#include "geometry_msgs/PoseStamped.h"
#include "tf/tf.h"

// 定义发布器
ros::Publisher cur1_pub;
ros::Publisher cur2_pub;
ros::Publisher cur3_pub;
ros::Publisher cur4_pub;
ros::Publisher cur5_pub;
ros::Publisher cur6_pub;

// std::vector<geometry_msgs::PoseStamped> tb3_goal_buf_;


// 目标点回调函数，获取机器人1的目标点并设置其他机器人目标点
void GoalCallback(const geometry_msgs::PoseStamped::ConstPtr& msg)
{

    // tb3_goal_buf_.push_back(*msg);
    // if(tb3_goal_buf_.size() > 20){
    //     tb3_goal_buf_.erase(tb3_goal_buf_.begin());
    // }

    // geometry_msgs::PoseStamped tb31_msg;
    // tb31_msg = tb3_goal_buf_.back();

    // 获取机器人1的目标点位置
    double lead_x = msg->pose.position.x;
    double lead_y = msg->pose.position.y;
    double lead_yaw = tf::getYaw(msg->pose.orientation);  // 机器人1的航向角

    // 创建并发布机器人1的目标点
    geometry_msgs::PoseStamped cur1_msg;
    cur1_msg.header.frame_id = "world";
    cur1_msg.header.stamp = ros::Time::now();
    cur1_msg.pose.position.x = lead_x;
    cur1_msg.pose.position.y = lead_y;
    cur1_msg.pose.position.z = 0;
    cur1_msg.pose.orientation = msg->pose.orientation;  // 保持原有的旋转
    //cur1_pub.publish(cur1_msg);

    // 根据机器人1的位置计算其他机器人的目标点位置
    double formation_offset = 2.0;  // 假设其他机器人和机器人1的相对位置偏移量
    geometry_msgs::PoseStamped cur2_msg, cur3_msg, cur4_msg, cur5_msg, cur6_msg;

    // 计算其他机器人的目标点（假设为沿着X轴和Y轴对称分布）
    cur2_msg.pose.position.x = lead_x + 0;
    cur2_msg.pose.position.y = lead_y + formation_offset;
    cur3_msg.pose.position.x = lead_x + 0;
    cur3_msg.pose.position.y = lead_y - formation_offset;
    cur4_msg.pose.position.x = lead_x - formation_offset;
    cur4_msg.pose.position.y = lead_y + 0;
    cur5_msg.pose.position.x = lead_x - formation_offset;
    cur5_msg.pose.position.y = lead_y + formation_offset;
    cur6_msg.pose.position.x = lead_x - formation_offset;
    cur6_msg.pose.position.y = lead_y - formation_offset;  // 假设有一个更多的偏移

    // 设置其他机器人的目标点的方向（可以是根据机器人1的朝向来调整）
    cur2_msg.pose.orientation = tf::createQuaternionMsgFromRollPitchYaw(0, 0, lead_yaw);
    cur3_msg.pose.orientation = tf::createQuaternionMsgFromRollPitchYaw(0, 0, lead_yaw);
    cur4_msg.pose.orientation = tf::createQuaternionMsgFromRollPitchYaw(0, 0, lead_yaw);
    cur5_msg.pose.orientation = tf::createQuaternionMsgFromRollPitchYaw(0, 0, lead_yaw);
    cur6_msg.pose.orientation = tf::createQuaternionMsgFromRollPitchYaw(0, 0, lead_yaw);

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
    ros::init(argc, argv, "navgoal_rviz");
    ros::NodeHandle nh;

    // 初始化发布器
    //cur1_pub = nh.advertise<geometry_msgs::PoseStamped>("/tb3_1/move_base_simple/goal", 1);
    cur2_pub = nh.advertise<geometry_msgs::PoseStamped>("/tb3_2/move_base_simple/goal", 1);
    cur3_pub = nh.advertise<geometry_msgs::PoseStamped>("/tb3_3/move_base_simple/goal", 1);
    cur4_pub = nh.advertise<geometry_msgs::PoseStamped>("/tb3_4/move_base_simple/goal", 1);
    cur5_pub = nh.advertise<geometry_msgs::PoseStamped>("/tb3_5/move_base_simple/goal", 1);
    cur6_pub = nh.advertise<geometry_msgs::PoseStamped>("/tb3_6/move_base_simple/goal", 1);

    // 订阅机器人1的目标点话题
    ros::Subscriber sub = nh.subscribe("/tb3_1/move_base_simple/goal", 10, GoalCallback);


    //ros::spin();  // 等待回调函数


    // 使用多线程异步处理
    ros::AsyncSpinner spinner(4);  // 这里4表示4个线程
    spinner.start();

    ros::waitForShutdown();  // 等待直到ROS系统关闭
    return 0;

    
    return 0;
}
