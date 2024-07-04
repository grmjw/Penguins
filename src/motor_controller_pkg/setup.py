import os
from glob import glob

from setuptools import setup

package_name = 'motor_controller_pkg'

setup(
    name=package_name,
    version='0.0.0',
    packages=[package_name],
    data_files=[
        (os.path.join('share', package_name, 'launch'), glob('launch/*.py')),
    ],
    install_requires=['setuptools'],
    zip_safe=True,
    maintainer='your_name',
    maintainer_email='your_email@example.com',
    description='ROS 2 package to control a motor using Jetson GPIO',
    license='Apache License 2.0',
    tests_require=['pytest'],
    entry_points={
        'console_scripts': [
            'motor_controller = motor_controller_pkg.motor_controller:main',
            'keyboard_control = motor_controller_pkg.keyboard_control:main',
        ],
    },
)
