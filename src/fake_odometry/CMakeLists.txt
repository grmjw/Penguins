cmake_minimum_required(VERSION 3.5)
project(fake_odometry)

# Find dependencies
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(std_msgs REQUIRED)
find_package(tf2_ros REQUIRED)
find_package(geometry_msgs REQUIRED)
find_package(nav_msgs REQUIRED)
find_package(sensor_msgs REQUIRED)
find_package(tf2 REQUIRED)
find_package(tf2_geometry_msgs REQUIRED)
find_package(PCL REQUIRED)
find_package(Curses REQUIRED)
find_package(ament_cmake_gtest REQUIRED)


# Include directories
include_directories(include)

# Create a library
add_library(odometry_publisher_lib src/odometry_publisher.cpp)

# Specify libraries to link library targets against
ament_target_dependencies(odometry_publisher_lib rclcpp std_msgs tf2_ros geometry_msgs nav_msgs sensor_msgs tf2 tf2_geometry_msgs)
target_include_directories(odometry_publisher_lib PUBLIC include)
target_link_libraries(odometry_publisher_lib ${PCL_LIBRARIES} ${CURSES_LIBRARIES})

# Create an executable and link against the library
add_executable(odometry_publisher src/main.cpp)
target_include_directories(odometry_publisher PUBLIC include)
target_link_libraries(odometry_publisher odometry_publisher_lib)

# Install the executable
install(TARGETS
  odometry_publisher
  DESTINATION lib/${PROJECT_NAME})

# Add test executable
ament_add_gtest(test_odometry_publisher test/test_odometry_publisher.cpp)
ament_target_dependencies(test_odometry_publisher rclcpp std_msgs tf2_ros geometry_msgs nav_msgs sensor_msgs tf2 tf2_geometry_msgs)
target_include_directories(test_odometry_publisher PUBLIC include)
target_link_libraries(test_odometry_publisher odometry_publisher_lib)

# Ament package macro
ament_package()

