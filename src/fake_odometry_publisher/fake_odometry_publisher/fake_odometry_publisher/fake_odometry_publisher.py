# fake_odometry_publisher.py

import rclpy
from rclpy.node import Node
from nav_msgs.msg import Odometry
from geometry_msgs.msg import Pose, Quaternion, Twist
import tf_transformations
import sys
import select
import termios
import tty

class FakeOdometryPublisher(Node):
    def __init__(self):
        super().__init__('fake_odometry_publisher')
        self.publisher_ = self.create_publisher(Odometry, 'odom', 10)
        self.timer = self.create_timer(0.5, self.timer_callback)
        self.position = [0.0, 0.0, 0.0]
        self.orientation = [0.0, 0.0, 0.0, 1.0]
        self.key_settings()

    def key_settings(self):
        self.settings = termios.tcgetattr(sys.stdin)
        tty.setcbreak(sys.stdin.fileno())

    def get_key(self):
        if select.select([sys.stdin], [], [], 0) == ([sys.stdin], [], []):
            return sys.stdin.read(1)
        return None

    def timer_callback(self):
        key = self.get_key()
        if key == 'w':
            self.position[0] += 10.0  # Move forward by 10 meters
        elif key == 'a':
            yaw = tf_transformations.euler_from_quaternion(self.orientation)[2] + 0.1
            self.orientation = tf_transformations.quaternion_from_euler(0, 0, yaw)
        elif key == 'd':
            yaw = tf_transformations.euler_from_quaternion(self.orientation)[2] - 0.1
            self.orientation = tf_transformations.quaternion_from_euler(0, 0, yaw)
        elif key == 's':
            self.position[0] -= 10.0  # Move backward by 10 meters

        msg = Odometry()
        msg.header.stamp = self.get_clock().now().to_msg()
        msg.header.frame_id = 'os_sensor'
        msg.child_frame_id = 'os_lidar'
        msg.pose.pose.position.x = self.position[0]
        msg.pose.pose.position.y = self.position[1]
        msg.pose.pose.position.z = self.position[2]
        msg.pose.pose.orientation = Quaternion(
            x=self.orientation[0],
            y=self.orientation[1],
            z=self.orientation[2],
            w=self.orientation[3]
        )
        self.publisher_.publish(msg)

    def destroy_node(self):
        termios.tcsetattr(sys.stdin, termios.TCSADRAIN, self.settings)
        super().destroy_node()

def main(args=None):
    rclpy.init(args=args)
    node = FakeOdometryPublisher()

    try:
        rclpy.spin(node)
    except KeyboardInterrupt:
        pass

    node.destroy_node()
    rclpy.shutdown()

if __name__ == '__main__':
    main()
