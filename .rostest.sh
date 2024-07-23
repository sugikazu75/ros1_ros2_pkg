#!/bin/bash

set -ex

apt-get update -qq && apt-get install -y -q wget curl sudo lsb-release gnupg git sed build-essential # for docker
echo 'debconf debconf/frontend select Noninteractive' | sudo debconf-set-selections

# Install ROS
if [[ "$ROS_DISTRO" ==  "noetic" ]]; then # https://wiki.ros.org/noetic/Installation/Ubuntu
    sudo sh -c "echo \"deb http://packages.ros.org/ros/ubuntu `lsb_release -sc` main\" > /etc/apt/sources.list.d/ros-latest.list"
    curl -s https://raw.githubusercontent.com/ros/rosdistro/master/ros.asc | sudo apt-key add -
    sudo apt-get update -qq
    sudo apt-get install -y -q ros-noetic-desktop-full
    sudo apt-get install -y -q python3-catkin-pkg python3-catkin-tools python3-rosdep python3-wstool python3-rosinstall-generator python3-osrf-pycommon python-is-python3
else # https://docs.ros.org/en/foxy/Installation/Ubuntu-Install-Debians.html
    locale  # check for UTF-8
    sudo apt-get update -qq  && sudo apt install -y -q locales
    sudo locale-gen en_US en_US.UTF-8
    sudo update-locale LC_ALL=en_US.UTF-8 LANG=en_US.UTF-8
    export LANG=en_US.UTF-8
    locale  # verify settings sudo add-apt-repository universe

    sudo curl -sSL https://raw.githubusercontent.com/ros/rosdistro/master/ros.key -o /usr/share/keyrings/ros-archive-keyring.gpg
    sudo sh -c "echo \"deb [arch=`dpkg --print-architecture` signed-by=/usr/share/keyrings/ros-archive-keyring.gpg] http://packages.ros.org/ros2/ubuntu `. /etc/os-release && echo $UBUNTU_CODENAME` main\" | sudo tee /etc/apt/sources.list.d/ros2.list > /dev/null"
    sudo apt-get update -qq
    sudo apt-get install -y -q ros-${ROS_DISTRO}-desktop
    sudo apt-get install -y -q python3-argcomplete python3-colcon-common-extensions python3-rosdep
fi

source /opt/ros/${ROS_DISTRO}/setup.bash

sudo rosdep init
rosdep update --include-eol-distros


# Install source code
mkdir -p ~/catkin_ws/src
cd ~/catkin_ws
cp -r ${CI_SOURCE_PATH} src/${REPOSITORY_NAME} # copy the whole contents instead of create symbolic link


# Build
if [[ "$ROS_DISTRO" ==  "noetic" ]]; then
    catkin build --no-status
else
    colcon build
fi
