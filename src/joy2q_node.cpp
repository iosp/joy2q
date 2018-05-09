#include </opt/ros/jade/include/ros/ros.h>
#include "std_msgs/String.h"
#include "std_msgs/Float64.h"
#include "sensor_msgs/Joy.h"

#include <sstream>


ros::Publisher _pub_EffortsTh;
ros::Publisher _pub_EffortsSt;

void joyCallback(const sensor_msgs::Joy::ConstPtr& msg)
{
  std_msgs::Float64 steer_msg, throt_msg;
  ROS_INFO("I heard: steering [%fd], throttle [%fd]", msg->axes[3], msg->axes[4]);
  steer_msg.data=msg->axes[3];
  throt_msg.data=msg->axes[4];
  _pub_EffortsTh.publish(steer_msg);
  _pub_EffortsSt.publish(throt_msg);
}

int main(int argc, char **argv)
{
  /**
   * The ros::init() function needs to see argc and argv so that it can perform
   * any ROS arguments and name remapping that were provided at the command line.
   * For programmatic remappings you can use a different version of init() which takes
   * remappings directly, but for most command-line programs, passing argc and argv is
   * the easiest way to do it.  The third argument to init() is the name of the node.
   *
   * You must call one of the versions of ros::init() before using any other
   * part of the ROS system.
   */
  ros::init(argc, argv, "joy2q_node");

    
  ros::NodeHandle n;
  
  ros::Subscriber _sub_joystick = n.subscribe("/joy", 10, joyCallback);

  _pub_EffortsTh = n.advertise<std_msgs::Float64>("/LLC/EFFORTS/Throttle", 10);
  _pub_EffortsSt = n.advertise<std_msgs::Float64>("/LLC/EFFORTS/Steering", 10);

  ros::Rate loop_rate(10);
  
  system("rosnode kill llc_node");
  ros::spin();
  system("rosrun llc llc_node");



  return 0;
}
