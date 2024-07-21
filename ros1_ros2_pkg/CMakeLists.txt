cmake_minimum_required(VERSION 3.5)
project(ros1_ros2_pkg)

# Default to C++14
if(NOT CMAKE_CXX_STANDARD)
  set(CMAKE_CXX_STANDARD 14)
endif()

# package dependencies
if($ENV{ROS_VERSION} STREQUAL "2")
  find_package(ament_cmake REQUIRED)
  find_package(rclcpp REQUIRED)
  find_package(rclcpp_components REQUIRED)

elseif($ENV{ROS_VERSION} STREQUAL "1")
  find_package(catkin REQUIRED COMPONENTS
    roscpp
    )

endif()
find_package(std_msgs REQUIRED)


# build
if($ENV{ROS_VERSION} STREQUAL "2")
  add_definitions(-DROS2)

  ament_package()

  include_directories(include)

  add_library(hoge SHARED
    src/hoge.cpp)
  ament_target_dependencies(hoge rclcpp rclcpp_components std_msgs)

  add_executable(hoge_node src/hoge_node.cpp)
  target_link_libraries(hoge_node hoge)
  ament_target_dependencies(hoge_node rclcpp rclcpp_components std_msgs)

  install(TARGETS
    hoge
    ARCHIVE DESTINATION lib
    LIBRARY DESTINATION lib
    RUNTIME DESTINATION bin)

  install(TARGETS
    hoge_node
    DESTINATION lib/${PROJECT_NAME})

elseif($ENV{ROS_VERSION} STREQUAL "1")
  add_definitions(-DROS1)

  catkin_package()

  include_directories(
    include
    ${catkin_INCLUDE_DIRS}
    )

  add_library(hoge src/hoge.cpp)
  target_link_libraries(hoge ${catkin_LIBRARIES})

  add_executable(hoge_node src/hoge_node.cpp)
  target_link_libraries(hoge_node ${catkin_LIBRARIES} hoge)

endif()

