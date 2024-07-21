#include <ros1_ros2_pkg/hoge.h>

int main (int argc, char **argv)
{
#ifdef ROS1
  ros::init (argc, argv, "hoge");
  ros::NodeHandle nh;
  hoge* hoge_node = new hoge();
  ros::waitForShutdown();
#elif ROS2
  rclcpp::init(argc, argv);
  hoge* hoge_node = new hoge();
  rclcpp::shutdown();
#endif

  delete hoge_node;
  return 0;
}
