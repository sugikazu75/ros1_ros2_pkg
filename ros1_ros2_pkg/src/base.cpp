#include <ros1_ros2_pkg/base.h>

baseNode::baseNode():
  loader_("ros1_ros2_pkg", "plugin_base::PluginBase")
{
  try
    {
      std::string plugin_name = "plugin_implementation::hoge";
      instance_ = loader_.createSharedInstance(plugin_name);
    }
  catch(pluginlib::PluginlibException& ex)
    {
      std::cout << "The plugin failed to load for some reason. Error: " << ex.what() << std::endl;
    }
  instance_->initialize();
}

void baseNode::spin()
{
  instance_->update();
}
