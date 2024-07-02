# Penguin Readme

## General Overview
This is the readme for Team Penguin's project for their SEP at TU/e. Every chapter in this readme includes an individual component Team Penguin worked on, important notes on it and how to set up that component on ones's computer and use it. It also contains at the end of each chapter the files which are not to be look at when grading for the course. One important set of files that should never be graded are all the files located in the folders: build, install and log. These folders can be found on the root of the workspace and are auto generated and hence shouldn't be checked. This applies to all packages and the overall codebase.

In the general steps a Workspace should be created by simply making a folder then cloning the repository inside the folder. This will act as your workspace once inside the folder then the next steps can be followed to build the reporsitory:

## Steps to build the repository

## Step 1
Navigate to src

 ```
cd src
   ```
Obtain permission to build:
 ```
./smart_extract.sh
```

Navigate back to penguins:
 ```
cd ..
```
Source ROS to be able to build files:

```
source /opt/ros/foxy/setup.bash
```

Then finally build the repository:
 ```
colcon build
   ```
Once the build succeeds, you must source the install folder of your ROS2 workspace to add launch commands to your environment:
```
source install/setup.bash
```
you should now proceed and be able to do all the further steps.

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

### Files to be checked:
Everything in this package is written by Team Penguin and hence can be checked.

## Radar Setup
## Steps to set-up Radar with ROS Foxy on Ubuntu 20.04
## Step 1
After connecting the PEAK CAN to USB converter from the radar to your device, the CAN interface must be established.
Load the necessary CAN modules by running:
```
        sudo modprobe can \
        sudo modprobe can_raw \
        sudo modprobe can_dev \
        sudo modprobe peak_can
```
## Step 2
Set and bring up can connection named can0:
```
sudo ip link set can0 up type can bitrate 500000
```
To check if the CAN interface has been properly set up you can run (assuming can0 is the interface name):
```
ip link show can0
```
The output should look something like this:


3: can0: <NOARP,UP,LOWER_UP> mtu 16 qdisc fq_codel state UNKNOWN mode DEFAULT group default qlen 10

## Step 3 
Ensure these two libraries are installed:
```
sudo apt install ros-foxy-point-cloud-msg-wrapper
```
```
pip install python-can
```
## Step 4 
Now navigate back to the Penguins directory and source by running:
```
source install/setup.bash
```
## Step 5 
Then run the radar code by typing:
```
ros2 launch umrr_ros2_driver radar.launch.py
```
## Step 6 
To visualize the point cloud data on rviz it is possible to run:
```
rviz2 -d smart_rviz_plugin/config/rviz/recorder.rviz
```
## Step 7 
To check the ROS topic on which the point cloud data is recieved from the radar with more detail, you can run:
```
ros2 topic echo \smart_radar\targets_0
```
## Step 8 
To remove the warning for the visualization on rviz you can type:
```
ros2 run tf2_ros static_transform_publisher 0 0 0 0 0 0 world umrr
```
## Files not to be checked:
This driver was created by smartmicro not Team Penguin therefore the package should not be checked if configuration files are excluded.


## LiDAR Setup

A better version of the steps below can be found on this page (I suggest you use that for a better understanding of the system):
[Connecting to Sensors](https://static.ouster.dev/sensor-docs/image_route1/image_route2/connecting/connecting-to-sensors.html)

### Steps to Set-up LiDAR with ROS on Ubuntu

#### Step 1
After connecting the lidar to device, go into the settings for the wired connection and into IPv4 and set it to "link-local only" as seen below.

![Image](https://github.com/grmjw/Penguins/blob/main/res/link_local_only.png)
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

If the repository is cloned all cloning specific things for the Ouster lidar are already done for you.

Next, to compile the driver, you need to source the ROS environment into the active terminal:
```
source /opt/ros/foxy/setup.bash
```
Finally, invoke `colcon build` command from within the penguin workspace as shown below:
```
cd penguin
colcon build
```

Once the build succeeds, you must source the install folder of your ROS2 workspace to add launch commands to your environment:
```
source install/setup.bash
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
## Files not to be checked:
This driver was created by ouster not Team Penguin therefore the package should not be checked if configuration files are excluded.


## SLAM and Nav2

#### Step 1
Download the necessary packages: 
```
sudo apt install ros-foxy-slam-toolbox 
sudo apt install ros-foxy-navigation2
```

#### Step 2
While LiDAR is running, open a new terminal and navigate to your workspace
Source the workspace:
```
source install/setup.bash
```

To run SLAM, use the following launch file:
```
ros2 launch slam_toolbox online_async_launch.py
```

#### Step 3
If SLAM is currently running, open a new terminal and run Nav2 using the following launch file:
```
ros2 launch nav2_bringup navigation_launch.py params_file:=src/nav2_bringup/params/nav2_params.yaml
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
Penguins/src/cam_driver
```

needs to be transferred to the following location:

```
Penguins/install/cam_driver/lib/python3.8/site-packages/cam_driver
```

The **intrinsic.npy** file also needs to be put in the correct location, this contains the calibration of the camera that we use for odometry.

**intrinsic.npy** is in the following folder:
```
Penguins/src/cam_odom
```

Tranfer the file to the following location:

```
Penguins/install/cam_odom/lib/python3.8/site-packages/cam_odom
```

### Running the camera

Open a new terminal and run the following commands to run the image publisher:

```
cd Penguins
source /opt/ros/foxy/setup.bash
source install/setup.bash
export PYTHONPATH=${PYTHONPATH}:$PWD/install/cam_driver/lib/python3.8/site-packages/cam_driver/lib/Linux64_ARM/
ros2 run cam_driver img_publisher
```

The system should now connect to the camera available and start receiving video frames

### Receiving video and running odometry

To see the received video frames and camera odometry in action, open a new terminal (**Do not close the terminal with the img_publisher running**)

Run the following commands in the new terminal: 

```
cd Penguins
source /opt/ros/foxy/setup.bash
source install/setup.bash
ros2 run cam_odom img_subscriber
```

### Camera Calibration

Calibrating the camera is a slightly longer process, since we require a file called **intrinsic.npy** that is generated by cameraCalibration.py. We cannot directly use the built in ros2 camera calibration but still require it.

Firstly, we have to install the camera calibration for ros

```
# on linux with apt
sudo apt install ros-foxy-camera-calibration
```

Next, a pattern needs to be printed for calibration. This can be done via the following link:
https://calib.io/pages/camera-calibration-pattern-generator

Print the pattern on an A4 page with the following settings:
Target Type: Checkerboard
Board Width: 200
Board Height: 150
Rows: 8
Columns: 10
Checker Width: 15

After printing run the following code in the terminal:

```
ros2 run camera_calibration cameracalibrator --size 7x9 --square 0.015 \
  --ros-args -r image:=/cam_frames
```

On another terminal run the img_publisher

You should now see the calibration window and begin the calibration process. Next, move the pattern to all screen corners and tilt in every direction. When enough information is gathered, press the calibrate button. Save the calibration.

Find where the file the calibration images are stored. Take all the images from the file and copy them from to a new folder. 

Now in the cameraCalibration.py file change line 31 the location to the folder with the images:
```
images = glob.glob('C:/Users/nhoei/liveCameraPose/calibration/*.png')
```
Run the python file on the terminal, this will generate a file named **intrinsic.npy**. Now this new calibration file can be put in the location described in the getting started section.

### Files to not be checked 

The following files are not to be checked in the **src/cam_driver** folder:
```
Entire lib folder
Entire resource folder
Entire tests folder
package.xml
setup.cfg
setup.py
cam_driver/__init__.py
```

The following files are not to be checked in the **src/cam_odom** folder:
```
Entire resource folder
Entire tests folder
package.xml
setup.cfg
setup.py
intrinsic.npy
cam_odom/__init__.py
cam_odom/cameraCalibration.py
```

## Fake odometry

To run fake odometry, source the terminal:
```
source install/setup.bash
```
then to run the code:
```
ros2 run fake_odometry odometry_publisher
```
Then to move the frame the w,a,s,d keys can be clicked in the same terminal.

### Files to be checked:
Everything in this package is written by Team Penguin and hence can be checked.
