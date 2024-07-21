#pragma once

#ifdef ROS2
#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"
#elif ROS1
#include <ros/ros.h>
#endif

#include <iostream>
#include "pluginlib/class_loader.hpp"
#include <memory>

namespace plugin_base
{
  class PluginBase
  {
  public:
    virtual ~PluginBase(){};
    virtual void initialize() = 0;
    virtual void update(){};
  private:
    int base_int_;
  };
};

namespace plugin_implementation
{
  class hoge : public plugin_base::PluginBase
  {
  public:
    hoge();
    ~hoge(){}

    void initialize() override;
    void update() override;

    int hoge_;

#ifdef ROS1
    ros::NodeHandle nh_;
    ros::Publisher test_pub_;
    ros::Subscriber test_sub_;
#elif ROS2
    rclcpp::Node::SharedPtr node_;
    rclcpp::Publisher<std_msgs::msg::String>::SharedPtr test_pub_;
    rclcpp::Subscription<std_msgs::msg::String>::SharedPtr test_sub_;
#endif

  private:
    void testCallback(const std_msgs::msg::String::SharedPtr msg);
  };
};
