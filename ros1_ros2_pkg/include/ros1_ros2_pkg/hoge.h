#pragma once

#ifdef ROS2
#include "rclcpp/rclcpp.hpp"
#elif ROS1
#include <ros/ros.h>
#endif
#include <iostream>

class hoge
{
public:
  hoge();
  ~hoge(){}

  int hoge_;

#ifdef ROS1
  ros::NodeHandle nh_;
#elif ROS2
#endif

};

