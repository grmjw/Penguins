#include <rclcpp/rclcpp.hpp>
#include <tf2_ros/transform_broadcaster.h>
#include <geometry_msgs/msg/transform_stamped.hpp>
#include <nav_msgs/msg/odometry.hpp>
#include <sensor_msgs/msg/point_cloud2.hpp>
#include <tf2/LinearMath/Quaternion.h>
#include <tf2_geometry_msgs/tf2_geometry_msgs.h>
#include <pcl_conversions/pcl_conversions.h>
#include <pcl/point_cloud.h>
#include <pcl/point_types.h>
#include <pcl/io/pcd_io.h>
#include <cmath>
#include <chrono>
#include <ncurses.h>
#include "fake_odometry/odometry_publisher.hpp"

OdometryPublisher::OdometryPublisher()
    : Node("odometry_publisher"), x_(0.0), y_(0.0), th_(0.0), vx_(0.0), vy_(0.0), vth_(0.0)
{
    odom_pub_ = this->create_publisher<nav_msgs::msg::Odometry>("odom", 50);
    tf_broadcaster_ = std::make_shared<tf2_ros::TransformBroadcaster>(this);
    point_cloud_sub_ = this->create_subscription<sensor_msgs::msg::PointCloud2>(
        "ouster/points", 10, std::bind(&OdometryPublisher::point_cloud_callback, this, std::placeholders::_1));
    timer_ = this->create_wall_timer(
        100ms, std::bind(&OdometryPublisher::update, this));
    last_time_ = this->now();

    // Initialize ncurses
    initscr();
    timeout(0); // Non-blocking input
    noecho();
    cbreak();
}

OdometryPublisher::~OdometryPublisher()
{
    // End ncurses
    endwin();
}

void OdometryPublisher::point_cloud_callback(const sensor_msgs::msg::PointCloud2::SharedPtr msg)
{
    // Process the incoming PointCloud2 message
    pcl::PointCloud<pcl::PointXYZ> cloud;
    pcl::fromROSMsg(*msg, cloud);

    if (cloud.points.empty())
    {
        RCLCPP_WARN(this->get_logger(), "Received empty point cloud");
        return;
    }

    RCLCPP_INFO(this->get_logger(), "Received point cloud with %zu points", cloud.points.size());

    // Verify frame ID
    if (msg->header.frame_id != "os_sensor")
    {
        RCLCPP_WARN(this->get_logger(), "Frame ID mismatch: expected 'os_sensor', got '%s'", msg->header.frame_id.c_str());
    }
}

void OdometryPublisher::update()
{
    rclcpp::Time current_time = this->now();

    int ch = getch();
    if (ch == 'w')
    {
        vx_ = 1.0; // Move forward
    }
    else if (ch == 's')
    {
        vx_ = -1.0; // Move backward
    }
    else if (ch == 'a')
    {
        vy_ = 1.0; // Move left
    }
    else if (ch == 'd')
    {
        vy_ = -1.0; // Move right
    }
    else
    {
        vx_ = 0.0;
        vy_ = 0.0;
    }

    // Compute odometry based on the velocities of the robot
    double dt = (current_time.seconds() - last_time_.seconds());
    double delta_x = vx_ * dt;
    double delta_y = vy_ * dt;
    double delta_th = vth_ * dt;

    x_ += delta_x;
    y_ += delta_y;
    th_ += delta_th;

    // Create a quaternion from yaw
    tf2::Quaternion quat;
    quat.setRPY(0, 0, th_);
    geometry_msgs::msg::Quaternion odom_quat = tf2::toMsg(quat);

    // Publish the transform over tf
    geometry_msgs::msg::TransformStamped odom_trans;
    odom_trans.header.stamp = current_time;
    odom_trans.header.frame_id = "os_sensor";
    odom_trans.child_frame_id = "os_lidar";

    odom_trans.transform.translation.x = x_;
    odom_trans.transform.translation.y = y_;
    odom_trans.transform.translation.z = 0.0;
    odom_trans.transform.rotation = odom_quat;

    // Send the transform
    tf_broadcaster_->sendTransform(odom_trans);

    // Publish the odometry message over ROS
    nav_msgs::msg::Odometry odom;
    odom.header.stamp = current_time;
    odom.header.frame_id = "os_sensor";

    // Set the position
    odom.pose.pose.position.x = x_;
    odom.pose.pose.position.y = y_;
    odom.pose.pose.orientation = odom_quat;

    // Set the velocity
    odom.child_frame_id = "os_lidar";
    odom.twist.twist.linear.x = vx_;
    odom.twist.twist.linear.y = vy_;
    odom.twist.twist.angular.z = vth_;

    // Publish the message
    odom_pub_->publish(odom);

    last_time_ = current_time;
}

void OdometryPublisher::updateKey(int ch)
{
    // Mock key press handling for testing
    ungetch(ch);
    update();
}
