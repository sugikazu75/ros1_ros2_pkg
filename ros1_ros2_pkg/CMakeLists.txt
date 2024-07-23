cmake_minimum_required(VERSION 3.5)
project(ros1_ros2_pkg)

# Default to C++14
if(NOT CMAKE_CXX_STANDARD)
  set(CMAKE_CXX_STANDARD 14)
endif()

# package dependencies
if($ENV{ROS_VERSION} STREQUAL "2")
  find_package(ament_cmake REQUIRED)
  find_package(ament_cmake_ros REQUIRED)
  find_package(rclcpp REQUIRED)
  find_package(rclcpp_components REQUIRED)
  find_package(pluginlib REQUIRED)
elseif($ENV{ROS_VERSION} STREQUAL "1")
  find_package(catkin REQUIRED COMPONENTS
    pluginlib
    roscpp
    )
endif()
find_package(std_msgs REQUIRED)


# build
if($ENV{ROS_VERSION} STREQUAL "2")
  add_definitions(-DROS2)

  add_library(plugin src/plugin.cpp)
  target_include_directories(plugin PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>)
  ament_target_dependencies(plugin rclcpp rclcpp_components std_msgs pluginlib)
  pluginlib_export_plugin_description_file(ros1_ros2_pkg plugins/plugin_ros2.xml)
  install(
    TARGETS plugin
    EXPORT export_${PROJECT_NAME}
    ARCHIVE DESTINATION lib
    LIBRARY DESTINATION lib
    RUNTIME DESTINATION bin)

  add_library(base src/base.cpp)
  target_include_directories(base PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>)
  target_link_libraries(base plugin)
  ament_target_dependencies(base rclcpp rclcpp_components std_msgs pluginlib)
  install(
    TARGETS base
    EXPORT export_${PROJECT_NAME}
    ARCHIVE DESTINATION lib
    LIBRARY DESTINATION lib
    RUNTIME DESTINATION bin)

  add_executable(node src/node.cpp)
  target_include_directories(node PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>)
  target_link_libraries(node plugin base)
  ament_target_dependencies(node rclcpp rclcpp_components std_msgs pluginlib)
  install(
    TARGETS node
    DESTINATION lib/${PROJECT_NAME})

  install(
    DIRECTORY include/
    DESTINATION include
    )

  ament_export_libraries(
    plugin
    )

  ament_export_targets(
    export_${PROJECT_NAME}
    )

  ament_package()

elseif($ENV{ROS_VERSION} STREQUAL "1")
  add_definitions(-DROS1)

  catkin_package(
    CATKIN_DEPENDS pluginlib roscpp)

  include_directories(
    include
    ${catkin_INCLUDE_DIRS}
    )

  add_library(plugin src/plugin.cpp)
  target_link_libraries(plugin ${catkin_LIBRARIES})

  add_library(base src/base.cpp)
  target_link_libraries(base plugin ${catkin_LIBRARIES})

  add_executable(node src/node.cpp)
  target_link_libraries(node base plugin ${catkin_LIBRARIES} )

endif()

