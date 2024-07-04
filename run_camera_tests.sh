#!/bin/bash

source install/setup.bash

# Run test_camera_poses tests
/usr/bin/python3 -m coverage run --source=cam_odom -m pytest src/cam_odom/test/test_camera_poses.py
/usr/bin/python3 -m coverage xml -o test_camera_poses_coverage.xml

# Run test_image_subscriber tests
/usr/bin/python3 -m coverage run --source=cam_odom -m pytest src/cam_odom/test/test_image_subscriber.py
/usr/bin/python3 -m coverage xml -o test_image_subscriber_coverage.xml

# Combine the coverage reports
/usr/bin/python3 -m coverage combine test_camera_poses_coverage.xml test_image_subscriber_coverage.xml

# Generate a combined report
/usr/bin/python3 -m coverage report
/usr/bin/python3 -m coverage html

# Clean up the intermediate files
rm test_camera_poses_coverage.xml test_image_subscriber_coverage.xml

echo "Tests completed and coverage report generated."

