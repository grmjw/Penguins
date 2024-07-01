#include <gtest/gtest.h>
#include <rclcpp/rclcpp.hpp>
#include <nav_msgs/msg/odometry.hpp>
#include <memory>
#include <chrono>
#include "fake_odometry/odometry_publisher.hpp"

using namespace std::chrono_literals;

class OdometryPublisherTest : public ::testing::Test
{
protected:
    void SetUp() override
    {
        RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "Setting up test...");
        rclcpp::init(0, nullptr);
        node_ = std::make_shared<OdometryPublisher>();
        odom_sub_ = node_->create_subscription<nav_msgs::msg::Odometry>(
            "odom", 10, [this](nav_msgs::msg::Odometry::SharedPtr msg) { last_odom_ = msg; });

        executor_ = std::make_shared<rclcpp::executors::SingleThreadedExecutor>();
        executor_->add_node(node_);
        last_odom_ = nullptr;
    }

    void TearDown() override
    {
        RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "Tearing down test...");
        executor_.reset();
        node_.reset();
        rclcpp::shutdown();
    }

    void spin_some()
    {
        executor_->spin_some();
    }

    std::shared_ptr<OdometryPublisher> node_;
    rclcpp::Subscription<nav_msgs::msg::Odometry>::SharedPtr odom_sub_;
    nav_msgs::msg::Odometry::SharedPtr last_odom_;
    std::shared_ptr<rclcpp::executors::SingleThreadedExecutor> executor_;
};

TEST_F(OdometryPublisherTest, TestOdometryUpdateOnKeyPressW)
{
    RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "Testing key press 'w'...");
    // Simulate 'w' key press
    node_->updateKey('w');
    std::this_thread::sleep_for(200ms); // Wait for the timer to trigger
    spin_some();

    // Check if odometry was published
    ASSERT_NE(last_odom_, nullptr) << "Odometry message is null after pressing 'w'";
    EXPECT_EQ(last_odom_->twist.twist.linear.x, 1.0);
    EXPECT_EQ(last_odom_->twist.twist.linear.y, 0.0);
    EXPECT_EQ(last_odom_->twist.twist.angular.z, 0.0);
}

TEST_F(OdometryPublisherTest, TestOdometryUpdateOnKeyPressS)
{
    RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "Testing key press 's'...");
    // Simulate 's' key press
    node_->updateKey('s');
    std::this_thread::sleep_for(200ms); // Wait for the timer to trigger
    spin_some();

    // Check if odometry was published
    ASSERT_NE(last_odom_, nullptr) << "Odometry message is null after pressing 's'";
    EXPECT_EQ(last_odom_->twist.twist.linear.x, -1.0);
    EXPECT_EQ(last_odom_->twist.twist.linear.y, 0.0);
    EXPECT_EQ(last_odom_->twist.twist.angular.z, 0.0);
}

TEST_F(OdometryPublisherTest, TestOdometryUpdateOnKeyPressA)
{
    RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "Testing key press 'a'...");
    // Simulate 'a' key press
    node_->updateKey('a');
    std::this_thread::sleep_for(200ms); // Wait for the timer to trigger
    spin_some();

    // Check if odometry was published
    ASSERT_NE(last_odom_, nullptr) << "Odometry message is null after pressing 'a'";
    EXPECT_EQ(last_odom_->twist.twist.linear.x, 0.0);
    EXPECT_EQ(last_odom_->twist.twist.linear.y, 1.0);
    EXPECT_EQ(last_odom_->twist.twist.angular.z, 0.0);
}

TEST_F(OdometryPublisherTest, TestOdometryUpdateOnKeyPressD)
{
    RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "Testing key press 'd'...");
    // Simulate 'd' key press
    node_->updateKey('d');
    std::this_thread::sleep_for(200ms); // Wait for the timer to trigger
    spin_some();

    // Check if odometry was published
    ASSERT_NE(last_odom_, nullptr) << "Odometry message is null after pressing 'd'";
    EXPECT_EQ(last_odom_->twist.twist.linear.x, 0.0);
    EXPECT_EQ(last_odom_->twist.twist.linear.y, -1.0);
    EXPECT_EQ(last_odom_->twist.twist.angular.z, 0.0);
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
