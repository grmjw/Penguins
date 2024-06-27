cmake_minimum_required(VERSION 3.5)
project(my_cpp_package)

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

# Create an executable
add_executable(odometry_publisher src/odometry_publisher.cpp)

# Specify libraries to link executable targets against
ament_target_dependencies(odometry_publisher rclcpp std_msgs tf2_ros geometry_msgs nav_msgs sensor_msgs tf2 tf2_geometry_msgs)

# Link PCL and ncurses libraries
target_link_libraries(odometry_publisher ${PCL_LIBRARIES} ${CURSES_LIBRARIES})

# Install the executable
install(TARGETS
  odometry_publisher
  DESTINATION lib/${PROJECT_NAME})

# Ament package macro
ament_package()
