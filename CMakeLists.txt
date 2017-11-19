cmake_minimum_required(VERSION 2.8.3)
project(turtlebot_walker)

## Find catkin macros and libraries
find_package(catkin REQUIRED COMPONENTS
  roscpp
  rospy
  std_msgs
  message_generation
  geometry_msgs
)

#Declaring the package
catkin_package()

## Including directories for build
include_directories(include ${catkin_INCLUDE_DIRS})

add_executable(turtlebot_walker src/main.cpp src/Walker.cpp)
target_link_libraries(turtlebot_walker ${catkin_LIBRARIES})
