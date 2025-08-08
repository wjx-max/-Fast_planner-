/**
 * @file /src/qnode.cpp
 *
 * @brief Ros communication central!
 *
 * @date February 2011
 **/

/*****************************************************************************
** Includes
*****************************************************************************/

#include <ros/ros.h>
#include <ros/network.h>
#include <string>
#include <sstream>
#include "../include/robot_hmi/qnode.hpp"


/*****************************************************************************
** Namespaces
*****************************************************************************/

namespace robot_hmi {

/*****************************************************************************
** Implementation
*****************************************************************************/

QNode::QNode(int argc, char** argv ) :
	init_argc(argc),
	init_argv(argv)
	{}

QNode::~QNode() {
    if(ros::isStarted()) {
      ros::shutdown(); // explicitly needed since we use ros::start();
      ros::waitForShutdown();
    }
	wait();
}

bool QNode::init() {
	ros::init(init_argc,init_argv,"robot_hmi");
	if ( ! ros::master::check() ) {
		return false;
	}
	ros::start(); // explicitly needed since our nodehandle is going out of scope.
	ros::NodeHandle n;
	// Add your ros communications here.
	chatter_publisher = n.advertise<std_msgs::String>("chatter", 1000);
    chatter_sub=n.subscribe("chatter",1000,&QNode::chatter_callback,this);
    power_sub=n.subscribe("power",1000,&QNode::power_callback,this);
    odom_sub=n.subscribe("ares1/odom",1000,&QNode::odom_callback,this);
    amcl_pose_sub=n.subscribe("amcl_pose",1000,&QNode::amcl_pose_callback,this);
    goal_pub=n.advertise<geometry_msgs::PoseStamped>("move_base_simple/goal",1000);
	start();
	return true;
}

bool QNode::init(const std::string &master_url, const std::string &host_url) {
	std::map<std::string,std::string> remappings;
	remappings["__master"] = master_url;
	remappings["__hostname"] = host_url;
	ros::init(remappings,"robot_hmi");
	if ( ! ros::master::check() ) {
		return false;
	}
	ros::start(); // explicitly needed since our nodehandle is going out of scope.
	ros::NodeHandle n;
	// Add your ros communications here.
	chatter_publisher = n.advertise<std_msgs::String>("chatter", 1000);
    chatter_sub=n.subscribe("chatter",1000,&QNode::chatter_callback,this);
    power_sub=n.subscribe("power",1000,&QNode::power_callback,this);
    odom_sub=n.subscribe("ares1/odom",1000,&QNode::odom_callback,this);
    amcl_pose_sub=n.subscribe("amcl_pose",1000,&QNode::amcl_pose_callback,this);
    goal_pub=n.advertise<geometry_msgs::PoseStamped>("move_base_simple/goal",1000);
	start();
	return true;
}
void QNode::set_goal(double x,double y,double z)
{
    geometry_msgs::PoseStamped goal;
    //设置frame
    goal.header.frame_id="map";
    //设置时刻
    goal.header.stamp=ros::Time::now();
    goal.pose.position.x=x;
    goal.pose.position.y=y;
    goal.pose.orientation.z=z;
    goal_pub.publish(goal);
}
void QNode::amcl_pose_callback(const geometry_msgs::PoseWithCovarianceStamped &msg)
{

    emit position(msg.pose.pose.position.x,msg.pose.pose.position.y,msg.pose.pose.orientation.z);
}
void QNode::sub_image(QString topic_name)
{
    ros::NodeHandle n;
    image_transport::ImageTransport it_(n);
    image_sub=it_.subscribe(topic_name.toStdString(),1000,&QNode::image_callback,this);

}
void QNode::image_callback(const sensor_msgs::ImageConstPtr &msg)
{
    cv_bridge::CvImagePtr cv_ptr;
    cv_ptr=cv_bridge::toCvCopy(msg,msg->encoding);
    QImage im=Mat2QImage(cv_ptr->image);
    emit image_val(im);
}
QImage QNode::Mat2QImage(cv::Mat const& src)
{
  QImage dest(src.cols, src.rows, QImage::Format_ARGB32);

  const float scale = 255.0;

  if (src.depth() == CV_8U) {
    if (src.channels() == 1) {
      for (int i = 0; i < src.rows; ++i) {
        for (int j = 0; j < src.cols; ++j) {
          int level = src.at<quint8>(i, j);
          dest.setPixel(j, i, qRgb(level, level, level));
        }
      }
    } else if (src.channels() == 3) {
      for (int i = 0; i < src.rows; ++i) {
        for (int j = 0; j < src.cols; ++j) {
          cv::Vec3b bgr = src.at<cv::Vec3b>(i, j);
          dest.setPixel(j, i, qRgb(bgr[2], bgr[1], bgr[0]));
        }
      }
    }
  } else if (src.depth() == CV_32F) {
    if (src.channels() == 1) {
      for (int i = 0; i < src.rows; ++i) {
        for (int j = 0; j < src.cols; ++j) {
          int level = scale * src.at<float>(i, j);
          dest.setPixel(j, i, qRgb(level, level, level));
        }
      }
    } else if (src.channels() == 3) {
      for (int i = 0; i < src.rows; ++i) {
        for (int j = 0; j < src.cols; ++j) {
          cv::Vec3f bgr = scale * src.at<cv::Vec3f>(i, j);
          dest.setPixel(j, i, qRgb(bgr[2], bgr[1], bgr[0]));
        }
      }
    }
  }

  return dest;
}
void QNode::power_callback(const std_msgs::Float32 &msg)
{
    emit power_vel(msg.data);
}
void QNode::odom_callback(const nav_msgs::Odometry &msg)
{
    emit speed_vel(msg.twist.twist.linear.x,msg.twist.twist.linear.y);
}

void QNode::chatter_callback(const std_msgs::String &msg)
{
    log(Info,""+msg.data);
}
void QNode::run() {
	ros::Rate loop_rate(1);
	int count = 0;
	while ( ros::ok() ) {

        std_msgs::String msg;
        std::stringstream ss;
        ss<<"已与机器人成功连接！"<<count;
        msg.data=ss.str();
        chatter_publisher.publish(msg);
        log(Info,std::string("")+msg.data);

		ros::spinOnce();
        loop_rate.sleep();
        ++count;
	}
	std::cout << "Ros shutdown, proceeding to close the gui." << std::endl;
	Q_EMIT rosShutdown(); // used to signal the gui for a shutdown (useful to roslaunch)
}


void QNode::log( const LogLevel &level, const std::string &msg) {
	logging_model.insertRows(logging_model.rowCount(),1);
	std::stringstream logging_model_msg;
	switch ( level ) {
		case(Debug) : {
				ROS_DEBUG_STREAM(msg);
				logging_model_msg << "[DEBUG] [" << ros::Time::now() << "]: " << msg;
				break;
		}
		case(Info) : {
				ROS_INFO_STREAM(msg);
				logging_model_msg << "[INFO] [" << ros::Time::now() << "]: " << msg;
				break;
		}
		case(Warn) : {
				ROS_WARN_STREAM(msg);
				logging_model_msg << "[INFO] [" << ros::Time::now() << "]: " << msg;
				break;
		}
		case(Error) : {
				ROS_ERROR_STREAM(msg);
				logging_model_msg << "[ERROR] [" << ros::Time::now() << "]: " << msg;
				break;
		}
		case(Fatal) : {
				ROS_FATAL_STREAM(msg);
				logging_model_msg << "[FATAL] [" << ros::Time::now() << "]: " << msg;
				break;
		}
	}
	QVariant new_row(QString(logging_model_msg.str().c_str()));
	logging_model.setData(logging_model.index(logging_model.rowCount()-1),new_row);
	Q_EMIT loggingUpdated(); // used to readjust the scrollbar
}

}  // namespace robot_hmi
