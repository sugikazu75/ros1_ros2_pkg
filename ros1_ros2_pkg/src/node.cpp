#include <ros1_ros2_pkg/base.h>

int main (int argc, char **argv)
{
#ifdef ROS1
  ros::init (argc, argv, "hoge");
  ros::NodeHandle nh;
  hoge* hoge_node = new hoge();
  ros::waitForShutdown();
#elif ROS2
  rclcpp::init(argc, argv);
  baseNode* base_node = new baseNode();
  while(rclcpp::ok())
    {
      base_node->spin();
    }
  rclcpp::shutdown();
#endif

  delete base_node;
  return 0;
}
