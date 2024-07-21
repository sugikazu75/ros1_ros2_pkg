#pragma once

#ifdef ROS2
#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"
#elif ROS1
#include <ros/ros.h>
#endif

#include "ros1_ros2_pkg/plugin.h"
#include <iostream>
#include "pluginlib/class_loader.hpp"
#include <memory>

class baseNode
{
public:
  baseNode();
  ~baseNode(){}

  pluginlib::ClassLoader<plugin_base::PluginBase> loader_;
  std::shared_ptr<plugin_base::PluginBase> instance_;

  void spin();
};
