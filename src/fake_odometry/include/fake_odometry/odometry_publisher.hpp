#ifndef FAKE_ODOMETRY__ODOMETRY_PUBLISHER_HPP_
#define FAKE_ODOMETRY__ODOMETRY_PUBLISHER_HPP_

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

using namespace std::chrono_literals;

class OdometryPublisher : public rclcpp::Node
{
public:
    OdometryPublisher();
    ~OdometryPublisher();

    void updateKey(int ch);

private:
    void point_cloud_callback(const sensor_msgs::msg::PointCloud2::SharedPtr msg);
    void update();

    rclcpp::Publisher<nav_msgs::msg::Odometry>::SharedPtr odom_pub_;
    std::shared_ptr<tf2_ros::TransformBroadcaster> tf_broadcaster_;
    rclcpp::Subscription<sensor_msgs::msg::PointCloud2>::SharedPtr point_cloud_sub_;
    rclcpp::TimerBase::SharedPtr timer_;

    double x_, y_, th_;
    double vx_, vy_, vth_;
    rclcpp::Time last_time_;
};

#endif  // FAKE_ODOMETRY__ODOMETRY_PUBLISHER_HPP_

