#include <geometry_msgs/Twist.h>
#include <sensor_msgs/LaserScan.h>
#include <ros/console.h>
#include <sstream>
#include <cstdlib>
#include <string>
#include "ros/ros.h"
#include "std_msgs/String.h"
#include "Walker.h"

int main(int argc, char **argv) {
  ros::init(argc, argv, "walker");
  ros::NodeHandle n;
  Walker roomba;
  geometry_msgs::Twist input;

  ros::Rate loop_rate(10);

  ros::Publisher roombaPub = n.advertise < geometry_msgs::Twist
      > ("/cmd_vel_mux/input/teleop", 1000);

// SUBSCRIBE TO /scan to get info about sensor.
  ros::Subscriber subScan = n.subscribe("/scan", 100, &Walker::closest, &roomba);  // subscriber

  int count = 0;
  while (ros::ok()) {

    if (roomba.Obstacle_detect(roomba.sensor_data)) {

      input.linear.x = 0;
      input.angular.z = .5;
      ROS_INFO_STREAM("Dist: " << roomba.sensor_data << ", Turn");
      }
    else {

        input.linear.x = .15;
        input.angular.z = 0;
        ROS_INFO_STREAM("Dist: " << roomba.sensor_data << ", Forward");
        }

    roombaPub.publish(input);

    ros::spinOnce();
    loop_rate.sleep();
    ++count;
  }
  return 0;
}
