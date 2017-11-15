#include <ros/ros.h>
#include <actionlib/client/simple_action_client.h>
#include <hector_uav_msgs/PoseAction.h>
#include <hector_uav_msgs/LandingAction.h>
#include <hector_quadrotor_interface/helpers.h>
#include <hector_quadrotor_actions/base_action.h>

namespace bebop_actions{

class EmergencyActionServer{
public:
  EmergencyActionServer(ros::NodeHandle nh) :
  server_(nh, "action/emergency", boost::bind(&EmergencyActionServer::emergencyActionCb, this, _1)),
  pose_client_(nh, "action/pose")
  {
    if(!pose_client_.waitForServer(ros::Duration(10.0))){
      ROS_ERROR_STREAM("Could not connect to " << nh.resolveName("action/pose"));
    }
  }

  void emergencyActionCb(const hector_uav_msgs::LandingGoalConstPtr &goal){
    if(server_.enableMotors(false)){
      server_.get()->setSucceeded();
      ROS_WARN("Emergency landing succeeded");
      return;
    }
    ROS_WARN("Emergency landing failed");
    server_.get()->setAborted();
  }

private:
  actionlib::SimpleActionClient<hector_uav_msgs::PoseAction> pose_client_;
  hector_quadrotor_actions::BaseActionServer<hector_uav_msgs::LandingAction> server_;
};

} // namespace bebop_actions


int main(int argc, char **argv){
  ros::init(argc, argv, "emergency_action");

  ros::NodeHandle nh;
  bebop_actions::EmergencyActionServer server(nh);

  ros::spin();

  return 0;
}
