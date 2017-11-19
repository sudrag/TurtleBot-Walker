/* MIT License
 Copyright (c) 2017 Sudarshan Raghunathan
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 The above copyright notice and this permission notice shall be included in all
 copies or substantial portions of the Software.
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 SOFTWARE.
 * @copyright Copyright 2017 Sudarshan Raghunathan
 * @file main.cpp
 * @author Sudarshan Raghunathan
 * @brief Node to follow the walking algorithm of turning when seeing obstacle
 *
 */

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

// SUBSCRIBE TO /scan and use the data from the sensor.
  ros::Subscriber subScan = n.subscribe("/scan", 100,
           &Walker::closest, &roomba);  // subscriber

  int count = 0;
  while (ros::ok()) {
    if (roomba.Obstacle_detect(roomba.sensor_data)) {
      input.linear.x = 0;
      input.angular.z = .5;
      ROS_INFO_STREAM("Dist: " << roomba.sensor_data << ", Turn");
      } else {
        input.linear.x = .15;
        input.angular.z = 0;
        ROS_INFO_STREAM("Dist: " << roomba.sensor_data << ", Drive");
        }

    roombaPub.publish(input);

    ros::spinOnce();
    loop_rate.sleep();
    ++count;
  }
  return 0;
}
