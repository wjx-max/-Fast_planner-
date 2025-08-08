#include <ros/ros.h>
#include <sensor_msgs/PointCloud.h>
#include <tf2_ros/transform_listener.h>
#include <tf2_sensor_msgs/tf2_sensor_msgs.h>
#include <tf2/transform_datatypes.h>
#include <sensor_msgs/LaserScan.h>

ros::Publisher points_pub1;
ros::Publisher points_pub2;
ros::Publisher points_pub3;
ros::Publisher points_pub4;
ros::Publisher points_pub5;
ros::Publisher points_pub6;
tf2_ros::Buffer tfBuffer;


void pointCloudCallback1(const sensor_msgs::LaserScanConstPtr& laser_scan_msg)
{
    try {
        // 创建一个PointCloud2类型的消息
        sensor_msgs::PointCloud2 point_cloud_msg;

        // 将LaserScan消息转换为PointCloud2类型
        sensor_msgs::PointCloud2Modifier modifier(point_cloud_msg);
        modifier.setPointCloud2FieldsByString(1, "xyz");
        modifier.resize(laser_scan_msg->ranges.size());
        sensor_msgs::PointCloud2Iterator<float> iter_x(point_cloud_msg, "x");
        sensor_msgs::PointCloud2Iterator<float> iter_y(point_cloud_msg, "y");
        sensor_msgs::PointCloud2Iterator<float> iter_z(point_cloud_msg, "z");
        for (size_t i = 0; i < laser_scan_msg->ranges.size(); ++i, ++iter_x, ++iter_y, ++iter_z) {
            double range = laser_scan_msg->ranges[i];
            double angle = laser_scan_msg->angle_min + i * laser_scan_msg->angle_increment;
            *iter_x = range * cos(angle);
            *iter_y = range * sin(angle);
            *iter_z = 0.0; // Assuming the laser is planar
        }

        // 进行坐标变换
        geometry_msgs::TransformStamped transformStamped = tfBuffer.lookupTransform("tb3_1/odom", "tb3_1/base_scan", ros::Time(0));
        tf2::doTransform(point_cloud_msg, point_cloud_msg, transformStamped);

        // 发布转换后的PointCloud2消息
        points_pub1.publish(point_cloud_msg);
    } catch(tf2::TransformException &e) {
        ROS_WARN("Failed to transform point cloud: %s", e.what());
    }
}



void pointCloudCallback2(const sensor_msgs::LaserScanConstPtr& laser_scan_msg)
{
    try {
        // 创建一个PointCloud2类型的消息
        sensor_msgs::PointCloud2 point_cloud_msg;

        // 将LaserScan消息转换为PointCloud2类型
        sensor_msgs::PointCloud2Modifier modifier(point_cloud_msg);
        modifier.setPointCloud2FieldsByString(1, "xyz");
        modifier.resize(laser_scan_msg->ranges.size());
        sensor_msgs::PointCloud2Iterator<float> iter_x(point_cloud_msg, "x");
        sensor_msgs::PointCloud2Iterator<float> iter_y(point_cloud_msg, "y");
        sensor_msgs::PointCloud2Iterator<float> iter_z(point_cloud_msg, "z");
        for (size_t i = 0; i < laser_scan_msg->ranges.size(); ++i, ++iter_x, ++iter_y, ++iter_z) {
            double range = laser_scan_msg->ranges[i];
            double angle = laser_scan_msg->angle_min + i * laser_scan_msg->angle_increment;
            *iter_x = range * cos(angle);
            *iter_y = range * sin(angle);
            *iter_z = 0.0; // Assuming the laser is planar
        }

        // 进行坐标变换
        geometry_msgs::TransformStamped transformStamped = tfBuffer.lookupTransform("tb3_2/odom", "tb3_2/base_scan", ros::Time(0));
        tf2::doTransform(point_cloud_msg, point_cloud_msg, transformStamped);

        // 发布转换后的PointCloud2消息
        points_pub2.publish(point_cloud_msg);
    } catch(tf2::TransformException &e) {
        ROS_WARN("Failed to transform point cloud: %s", e.what());
    }
}



void pointCloudCallback3(const sensor_msgs::LaserScanConstPtr& laser_scan_msg)
{
    try {
        // 创建一个PointCloud2类型的消息
        sensor_msgs::PointCloud2 point_cloud_msg;

        // 将LaserScan消息转换为PointCloud2类型
        sensor_msgs::PointCloud2Modifier modifier(point_cloud_msg);
        modifier.setPointCloud2FieldsByString(1, "xyz");
        modifier.resize(laser_scan_msg->ranges.size());
        sensor_msgs::PointCloud2Iterator<float> iter_x(point_cloud_msg, "x");
        sensor_msgs::PointCloud2Iterator<float> iter_y(point_cloud_msg, "y");
        sensor_msgs::PointCloud2Iterator<float> iter_z(point_cloud_msg, "z");
        for (size_t i = 0; i < laser_scan_msg->ranges.size(); ++i, ++iter_x, ++iter_y, ++iter_z) {
            double range = laser_scan_msg->ranges[i];
            double angle = laser_scan_msg->angle_min + i * laser_scan_msg->angle_increment;
            *iter_x = range * cos(angle);
            *iter_y = range * sin(angle);
            *iter_z = 0.0; // Assuming the laser is planar
        }

        // 进行坐标变换
        geometry_msgs::TransformStamped transformStamped = tfBuffer.lookupTransform("tb3_3/odom", "tb3_3/base_scan", ros::Time(0));
        tf2::doTransform(point_cloud_msg, point_cloud_msg, transformStamped);

        // 发布转换后的PointCloud2消息
        points_pub3.publish(point_cloud_msg);
    } catch(tf2::TransformException &e) {
        ROS_WARN("Failed to transform point cloud: %s", e.what());
    }
}




void pointCloudCallback4(const sensor_msgs::LaserScanConstPtr& laser_scan_msg)
{
    try {
        // 创建一个PointCloud2类型的消息
        sensor_msgs::PointCloud2 point_cloud_msg;

        // 将LaserScan消息转换为PointCloud2类型
        sensor_msgs::PointCloud2Modifier modifier(point_cloud_msg);
        modifier.setPointCloud2FieldsByString(1, "xyz");
        modifier.resize(laser_scan_msg->ranges.size());
        sensor_msgs::PointCloud2Iterator<float> iter_x(point_cloud_msg, "x");
        sensor_msgs::PointCloud2Iterator<float> iter_y(point_cloud_msg, "y");
        sensor_msgs::PointCloud2Iterator<float> iter_z(point_cloud_msg, "z");
        for (size_t i = 0; i < laser_scan_msg->ranges.size(); ++i, ++iter_x, ++iter_y, ++iter_z) {
            double range = laser_scan_msg->ranges[i];
            double angle = laser_scan_msg->angle_min + i * laser_scan_msg->angle_increment;
            *iter_x = range * cos(angle);
            *iter_y = range * sin(angle);
            *iter_z = 0.0; // Assuming the laser is planar
        }

        // 进行坐标变换
        geometry_msgs::TransformStamped transformStamped = tfBuffer.lookupTransform("tb3_4/odom", "tb3_4/base_scan", ros::Time(0));
        tf2::doTransform(point_cloud_msg, point_cloud_msg, transformStamped);

        // 发布转换后的PointCloud2消息
        points_pub4.publish(point_cloud_msg);
    } catch(tf2::TransformException &e) {
        ROS_WARN("Failed to transform point cloud: %s", e.what());
    }
}



void pointCloudCallback5(const sensor_msgs::LaserScanConstPtr& laser_scan_msg)
{
    try {
        // 创建一个PointCloud2类型的消息
        sensor_msgs::PointCloud2 point_cloud_msg;

        // 将LaserScan消息转换为PointCloud2类型
        sensor_msgs::PointCloud2Modifier modifier(point_cloud_msg);
        modifier.setPointCloud2FieldsByString(1, "xyz");
        modifier.resize(laser_scan_msg->ranges.size());
        sensor_msgs::PointCloud2Iterator<float> iter_x(point_cloud_msg, "x");
        sensor_msgs::PointCloud2Iterator<float> iter_y(point_cloud_msg, "y");
        sensor_msgs::PointCloud2Iterator<float> iter_z(point_cloud_msg, "z");
        for (size_t i = 0; i < laser_scan_msg->ranges.size(); ++i, ++iter_x, ++iter_y, ++iter_z) {
            double range = laser_scan_msg->ranges[i];
            double angle = laser_scan_msg->angle_min + i * laser_scan_msg->angle_increment;
            *iter_x = range * cos(angle);
            *iter_y = range * sin(angle);
            *iter_z = 0.0; // Assuming the laser is planar
        }

        // 进行坐标变换
        geometry_msgs::TransformStamped transformStamped = tfBuffer.lookupTransform("tb3_5/odom", "tb3_5/base_scan", ros::Time(0));
        tf2::doTransform(point_cloud_msg, point_cloud_msg, transformStamped);

        // 发布转换后的PointCloud2消息
        points_pub5.publish(point_cloud_msg);
    } catch(tf2::TransformException &e) {
        ROS_WARN("Failed to transform point cloud: %s", e.what());
    }
}



void pointCloudCallback6(const sensor_msgs::LaserScanConstPtr& laser_scan_msg)
{
    try {
        // 创建一个PointCloud2类型的消息
        sensor_msgs::PointCloud2 point_cloud_msg;

        // 将LaserScan消息转换为PointCloud2类型
        sensor_msgs::PointCloud2Modifier modifier(point_cloud_msg);
        modifier.setPointCloud2FieldsByString(1, "xyz");
        modifier.resize(laser_scan_msg->ranges.size());
        sensor_msgs::PointCloud2Iterator<float> iter_x(point_cloud_msg, "x");
        sensor_msgs::PointCloud2Iterator<float> iter_y(point_cloud_msg, "y");
        sensor_msgs::PointCloud2Iterator<float> iter_z(point_cloud_msg, "z");
        for (size_t i = 0; i < laser_scan_msg->ranges.size(); ++i, ++iter_x, ++iter_y, ++iter_z) {
            double range = laser_scan_msg->ranges[i];
            double angle = laser_scan_msg->angle_min + i * laser_scan_msg->angle_increment;
            *iter_x = range * cos(angle);
            *iter_y = range * sin(angle);
            *iter_z = 0.0; // Assuming the laser is planar
        }

        // 进行坐标变换
        geometry_msgs::TransformStamped transformStamped = tfBuffer.lookupTransform("tb3_6/odom", "tb3_6/base_scan", ros::Time(0));
        tf2::doTransform(point_cloud_msg, point_cloud_msg, transformStamped);

        // 发布转换后的PointCloud2消息
        points_pub6.publish(point_cloud_msg);
    } catch(tf2::TransformException &e) {
        ROS_WARN("Failed to transform point cloud: %s", e.what());
    }
}

int main(int argc, char **argv) 
{
    ros::init(argc, argv, "point_cloud_transform_node");
    ros::NodeHandle nh;

    ros::Subscriber points_sub1 = nh.subscribe("tb3_1/scan", 10, pointCloudCallback1);
    ros::Subscriber points_sub2 = nh.subscribe("tb3_2/scan", 10, pointCloudCallback2);
    ros::Subscriber points_sub3 = nh.subscribe("tb3_3/scan", 10, pointCloudCallback3);
    ros::Subscriber points_sub4 = nh.subscribe("tb3_4/scan", 10, pointCloudCallback4);
    ros::Subscriber points_sub5 = nh.subscribe("tb3_5/scan", 10, pointCloudCallback5);
    ros::Subscriber points_sub6 = nh.subscribe("tb3_6/scan", 10, pointCloudCallback6);

    points_pub1 = nh.advertise<sensor_msgs::PointCloud2>("/tb3_1/point_cloud_map", 10);
    points_pub2 = nh.advertise<sensor_msgs::PointCloud2>("/tb3_2/point_cloud_map", 10);
    points_pub3 = nh.advertise<sensor_msgs::PointCloud2>("/tb3_3/point_cloud_map", 10);
    points_pub4 = nh.advertise<sensor_msgs::PointCloud2>("/tb3_4/point_cloud_map", 10);
    points_pub5 = nh.advertise<sensor_msgs::PointCloud2>("/tb3_5/point_cloud_map", 10);
    points_pub6 = nh.advertise<sensor_msgs::PointCloud2>("/tb3_6/point_cloud_map", 10);
	
    
    tf2_ros::TransformListener tfListener(tfBuffer);
    ros::spin();

    return 0;

}
