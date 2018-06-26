#include </opt/ros/jade/include/ros/ros.h>
#include "std_msgs/String.h"
#include "std_msgs/Float64.h"
#include "sensor_msgs/Joy.h"

#include <sstream>


ros::Publisher _pub_EffortsTh;
ros::Publisher _pub_EffortsSt;

std_msgs::Float64 steerCmd, throtCmd;

void joyCallback(const sensor_msgs::Joy::ConstPtr& msg)
{

  steerCmd.data = msg->axes[4];
  throtCmd.data = msg->axes[3];

  ROS_INFO("joyCallback : I heard: steering [%fd], throttle [%fd]", steerCmd.data, throtCmd.data);


  // std_msgs::Float64 steer_msg, throt_msg;
  // ROS_INFO("I heard: steering [%fd], throttle [%fd]", msg->axes[3], msg->axes[4]);
  // steer_msg.data=msg->axes[4];
  // throt_msg.data=msg->axes[3];
  // _pub_EffortsTh.publish(steer_msg);
  // _pub_EffortsSt.publish(throt_msg);
}


void applyCmd(const ros::TimerEvent&)
{
  ROS_INFO("applyCmd :I heard: steering [%fd], throttle [%fd]", steerCmd.data, throtCmd.data);
  _pub_EffortsTh.publish(steerCmd);
  _pub_EffortsSt.publish(throtCmd);
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

  
  ros::Timer cmd_timer = n.createTimer(ros::Duration(0.01), applyCmd);


  //ros::Rate loop_rate(10);
  
  system("rosnode kill llc_node");
  ros::spin();
  system("rosrun llc llc_node");


  return 0;
}
