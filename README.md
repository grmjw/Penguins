# Penguine Readme

## Motors

The device has 4 motors and 4 motor controllers. This readme assumes the current configuration and placement of the mini cube is as provided to team Penguin in week 3. 

### Motor Connections

In this specific case:
- **Right Motor**:
  - Connect the 3 pins from the motor controller to the pins on the Jetson labeled 33, 37, and 35.
    - 33 is the PWM signal pin.
    - 35 is the high pin.
    - 37 is the low pin.

- **Left Motor**:
  - Connect the 3 pins from the motor controller to the pins on the Jetson labeled 32, 34, and 36.
    - 32 is the PWM signal pin.
    - 34 is the high pin.
    - 36 is the low pin.

Details on these pins and their functions can be found in the motor controller datasheet. For more information, refer to the [L298N Motor Controller Datasheet](https://www.sparkfun.com/datasheets/Robotics/L298_H_Bridge.pdf).

### Running the Code

1. After the pins have been connected successfully, to run the code, simply execute the following command:
   ```sh
   ros2 run motor_controller_pkg keyboard_control
   ```

2. A terminal should open up. This terminal is currently reading your keyboard inputs.

3. **Keyboard Controls**:
   - `w` - Move forward (both motors move forward).
   - `s` - Move backward (both motors move in reverse).
   - `d` - Spin right (opposite rotation to opposite motors).
   - `a` - Spin left (opposite rotation to opposite motors).
   - `q` - Stop all motors.
   - Any other button - Stops all motors.

### Changing Speed

To change the speed of the vehicle, use the following command:
```sh
ros2 topic pub /motor_speed std_msgs/Float32 "data: 50.0"  # 50% duty cycle
```
- Change the `50.0` to the desired percentage.

The code runs with a default speed of 50% and continuously monitors the speed change on a topic. This command updates the speed on that topic.

Note that the `50%` value represents power, not speed. It is analogous to pressing the gas pedal in a car. Consistently keeping it at 50% does not ensure 50% speed; it ensures 50% force from the motors at all times. Given that mass is constant, force is proportional to acceleration (F = ma).

## LiDAR Setup

A better version of the steps below can be found on this page (I suggest you use that for a better understanding of the system):
[Connecting to Sensors](https://static.ouster.dev/sensor-docs/image_route1/image_route2/connecting/connecting-to-sensors.html)

### Steps to Set-up LiDAR with ROS on Ubuntu

#### Step 1
Go into the settings for the wired connection and into IPv4 and do link local only, or else nothing will work.

#### Step 2
Go to this website: 
```
http://os-122333001117.local/
```
`<122333001117>` this number will be different for you since it's based on your LiDAR, look at your LiDAR and find the number of similar length on it and replace this with that number in the URL.

#### Step 3
Take the IPv4 address; you will need it to put it in the YAML file as the hostname. e.g.: 
IPv4 (Link-local):  `169.254.245.175` (without the `/16`)

**Note**:you dont have a yaml file yet because you havent set up the sdk yet, do that first

### Setting Up the ROS SDK

#### Steps on How to Set Up the Files for LiDAR with ROS
Go to this website there are 2 ways to do it again, one is to go to this website and follow the steps in their readme and the easier but less detailed way is to follow these steps here at the end of which you will have a live rviz vizualization of the lidar sensor data.:
[Ouster ROS](https://github.com/ouster-lidar/ouster-ros/tree/ros2)

#### Overview
This ROS package provides support for all Ouster sensors with FW v2.0 or later targeting ROS2 distros. Upon launch, the driver will configure and connect to the selected sensor device. Once connected, the driver will handle incoming IMU and LiDAR packets, decode LiDAR frames, and publish corresponding ROS messages on the topics of `/ouster/imu` and `/ouster/points`. If the used sensor supports dual return and it was configured to use this capability, another topic will be published under the name `/ouster/points2` which corresponds to the second point cloud.

#### Supported Devices
The driver supports the following list of Ouster sensors:
- OS0
- OS1
- OS2
- OSDome

You can obtain detailed spec sheets about the sensors and updated FW through the website's downloads section.

#### Requirements
This branch is only intended for use with Rolling, Humble, and Iron ROS 2 distros. Please refer to ROS 2 online documentation on how to set up ROS on your machine before proceeding with the remainder of this guide.

If you have the `rosdep` tool installed on your system, you can then use the following command to get all required dependencies:
```
rosdep install --from-paths $OUSTER_ROS_PATH -y --ignore-src    
```

#### Linux
In addition to the base ROS installation, the following ROS packages are required:
```
sudo apt install -y             \
    ros-$ROS_DISTRO-pcl-ros     \
    ros-$ROS_DISTRO-tf2-eigen   \
    ros-$ROS_DISTRO-rviz2
```
where `$ROS_DISTRO` can be either rolling, humble, or iron.

**Note**: Installing `ros-$ROS_DISTRO-rviz` package is optional in case you don't need to visualize the point cloud using RViz but remember to always set `viz` launch arg to false.

The following packages are also required:
```
sudo apt install -y         \
    build-essential         \
    libeigen3-dev           \
    libjsoncpp-dev          \
    libspdlog-dev           \
    libcurl4-openssl-dev    \
    cmake                   \
    python3-colcon-common-extensions
```
**Note**: You may choose a different SSL backend for the curl library such as `libcurl4-gnutls-dev` or `libcurl4-nss-dev`.

### Getting Started

To build the driver using ROS2, you need to clone the project into the `src` folder of a ROS2 workspace as shown below:
```
mkdir -p ros2_ws/src && cd ros2_ws/src
git clone -b ros2 --recurse-submodules https://github.com/ouster-lidar/ouster-ros.git
```
Next, to compile the driver, you need to source the ROS environment into the active terminal:
```
source /opt/ros/<ros-distro>/setup.bash # replace <ros-distro> with 'rolling', 'humble', or 'iron'
```
Finally, invoke `colcon build` command from within the catkin workspace as shown below:
```
cd ros2_ws
colcon build --symlink-install --cmake-args -DCMAKE_BUILD_TYPE=Release
```
**Note**: Specifying `Release` as the build type is important to have a reasonable performance of the driver.

Once the build succeeds, you must source the install folder of your ROS2 workspace to add launch commands to your environment:
```
source ros2_ws/install/setup.bash
```

### Usage

#### Launching Nodes
The package supports three modes of interaction: you can connect to a live sensor, replay a recorded bag, or record a new bag file using the corresponding launch files. Recently, we have added a new mode that supports multicast. The commands are listed below. For convenience, we provide both launch file formats (XML and Python) but the Python format is the preferred method:

**Sensor Mode**
To connect to a live sensor, use the following launch file:
```
ros2 launch ouster_ros sensor.launch.xml    \
    sensor_hostname:=<sensor host name>
```
The equivalent Python launch file is:
```
ros2 launch ouster_ros driver.launch.py    \
    params_file:=<path to params yaml file>
```
Use the hostname you found and make sure to update the hostname in the YAML file. The location of the YAML file will most probably be:
```
~/<workspace name>/src/ouster-ros/ouster-ros/config/driver_params.yaml
```
If it doesn't run properly, open a new terminal and run this command in parallel:
```
ros2 run tf2_ros static_transform_publisher 0 0 0 0 0 0 world os_sensor
```


## Camera 

### Getting Started 

Clone the repository onto your workspace 

Navigate to the workspace directory and build the package 

```
cd Penguins
colcon build
```

After building, the Ipx Camera API needs to be transferred to the correct folder so it gets recognised when running the camera publisher node.
To do this the **lib** folder in the following directory:

```
Penguins/src/cv_basics
```

needs to be transferred to the following location:

```
Penguins/install/cv_basics/lib/python3.8/site-packages/cv_basics
```

### Running the camera

Open a new terminal and run the following commands to run the image publisher:

```
cd Penguins
source /opt/ros/foxy/setup.bash
source install/setup.bash
export PYTHONPATH=${PYTHONPATH}:$PWD/install/cv_basics/lib/python3.8/site-packages/cv_basics/lib/Linux64_x64/
ros2 run cv_basics img_publisher
```

The system should now connect to the camera available and start receiving video frames

To see the received video frames and camera odometry in action, open a new terminal (**Do not close the terminal with the img_publisher running**)

Run the following commands in the new terminal: 

```
cd Penguins
source /opt/ros/foxy/setup.bash
source install/setup.bash
ros2 run cv_basics img_subscriber
```
