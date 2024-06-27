import os
import launch
from launch import LaunchDescription
from launch.actions import IncludeLaunchDescription
from launch.launch_description_sources import PythonLaunchDescriptionSource
from launch_ros.actions import Node

def generate_launch_description():
    # Get the path to the virtual environment
    venv_path = '~/myenv/bin/activate'

    return LaunchDescription([
        # Source the virtual environment
        launch.actions.ExecuteProcess(
            cmd=['source', venv_path],
            shell=True
        ),
        Node(
            package='motor_controller_pkg',
            executable='motor_controller',
            name='motor_controller_node',
            output='screen',
            parameters=[
                {'enable_pin': 32},  # GPIO13 for PWM
                {'in1_pin': 35},  # GPIO19 for IN1
                {'in2_pin': 37}  # GPIO26 for IN2
            ]
        ),
        Node(
            package='motor_controller_pkg',
            executable='keyboard_control',
            name='keyboard_control_node',
            output='screen',
        ),
    ])
