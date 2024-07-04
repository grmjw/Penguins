#!/bin/bash

# Run motor_controller tests
/usr/bin/python3 -m coverage run --source=motor_controller_pkg/motor_controller.py -m pytest src/motor_controller_pkg/tests/test_motor_controller.py
/usr/bin/python3 -m coverage xml -o motor_controller_coverage.xml

# Run keyboard_control tests
/usr/bin/python3 -m coverage run --source=motor_controller_pkg/keyboard_control.py -m pytest src/motor_controller_pkg/tests/test_keyboard_control.py
/usr/bin/python3 -m coverage xml -o keyboard_control_coverage.xml

# Combine the coverage reports
/usr/bin/python3 -m coverage combine motor_controller_coverage.xml keyboard_control_coverage.xml

# Generate a combined report
/usr/bin/python3 -m coverage report
/usr/bin/python3 -m coverage html

# Clean up the intermediate files
rm motor_controller_coverage.xml keyboard_control_coverage.xml

echo "Tests completed and coverage report generated."
