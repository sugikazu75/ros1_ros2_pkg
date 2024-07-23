#include <ros1_ros2_pkg/plugin.h>

plugin_implementation::hoge::hoge():
  PluginBase(),
  hoge_(0)
{
  std::cout << "constructor" << std::endl;
}

void plugin_implementation::hoge::initialize()
{
#ifdef ROS2
  node_ = std::make_shared<rclcpp::Node>("hoge_node");
  test_pub_ = node_->create_publisher<std_msgs::msg::String>("test_pub", 10);
  test_sub_ = node_->create_subscription<std_msgs::msg::String>("test_sub", 10, std::bind(&hoge::testCallback, this, std::placeholders::_1));
#elif ROS1
#endif
}

#ifdef ROS2
void plugin_implementation::hoge::testCallback(const std_msgs::msg::String::SharedPtr msg)
{
  RCLCPP_INFO(node_->get_logger(), "I heard: '%s'", msg->data.c_str());
}
#elif ROS1
#endif

void plugin_implementation::hoge::update()
{
#ifdef ROS2
  auto message = std_msgs::msg::String();
  message.data = "Hello, ROS 2!";
  test_pub_->publish(message);
  rclcpp::spin_some(node_);
#elif ROS1
#endif
}

#include "pluginlib/class_list_macros.hpp"
PLUGINLIB_EXPORT_CLASS(plugin_implementation::hoge, plugin_base::PluginBase)
