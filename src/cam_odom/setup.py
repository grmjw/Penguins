from setuptools import setup

package_name = 'cam_odom'

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
    maintainer='Thomas Rosendaal, Abbas Husain, Gede Arya Divo Abimanyu',
    maintainer_email='t.r.e.rosendaal@student.tue.nl, a.hussain@student.tue.nl, d.gede.arya.divo.abimanyu@student.tue.nl',
    description='Contains implementation of camera odometry using images received from a specified ros topic and camera calibrition to calculate the extrinsic and intrinsic matrices for the connected camera',
    license='Apache License 2.0',
    tests_require=['pytest'],
    entry_points={
        'console_scripts': [
        	'img_subscriber = cam_odom.cam_odom:main'
        ],
    },
)
