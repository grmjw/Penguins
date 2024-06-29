from setuptools import setup

package_name = 'cam_driver'

setup(
    name=package_name,
    version='1.0',
    packages=[package_name],
    data_files=[
        ('share/ament_index/resource_index/packages',
            ['resource/' + package_name]),
        ('share/' + package_name, ['package.xml']),
    ],
    install_requires=['setuptools'],
    zip_safe=True,
    maintainer='Thomas Rosendaal, Abbas Hussain',
    maintainer_email='t.r.e.rosendaal@student.tue.nl, a.hussain@student.tue.nl',
    description='ROS2 camera driver for Imperx Cheetah P67-C1911 CMOS 2.86 NP camera',
    license='Apache License 2.0',
    tests_require=['pytest'],
    entry_points={
        'console_scripts': [
        	'img_publisher = cam_driver.cam_driver:main'
        ],
    },
)
