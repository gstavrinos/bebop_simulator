#include <ros/ros.h>
#include <tf/transform_broadcaster.h>
#include <nav_msgs/Odometry.h>


void odomCallback(const nav_msgs::Odometry::ConstPtr& msg){
  tf::TransformBroadcaster odom_broadcaster;
  tf::Transform transform;
  transform.setOrigin( tf::Vector3(msg->pose.pose.position.x, msg->pose.pose.position.y, msg->pose.pose.position.z) );
  tf::Quaternion q(msg->pose.pose.orientation.x, msg->pose.pose.orientation.y, msg->pose.pose.orientation.z, msg->pose.pose.orientation.w);
  transform.setRotation(q);
  odom_broadcaster.sendTransform(tf::StampedTransform(transform, ros::Time::now(), "/odom", "/base_link"));
}


int main(int argc, char** argv){
  ros::init(argc, argv, "bebop_odom_to_tf");

  ros::NodeHandle n;
  std::string odom_topic = "/bebop/odom";
  n.getParam("odom_topic", odom_topic);
  ros::Subscriber odom_sub = n.subscribe<nav_msgs::Odometry>(odom_topic, 1, odomCallback);
  tf::TransformBroadcaster odom_broadcaster;

  ros::Time current_time, last_time;
  current_time = ros::Time::now();
  last_time = ros::Time::now();

  ros::spin();
}