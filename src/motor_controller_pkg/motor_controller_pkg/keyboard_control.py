import rclpy
from rclpy.node import Node
from std_msgs.msg import Float32, Int32
from pynput import keyboard


class KeyboardControl(Node):
    def __init__(self):
        print("Initializing KeyboardControl Node")
        super().__init__('keyboard_control')
        print("Creating speed publisher")
        self.speed_publisher = self.create_publisher(Float32, 'motor_speed', 10)
        print("Creating direction publisher")
        self.direction_publisher = self.create_publisher(Int32, 'motor_direction', 10)
        print("Setting up keyboard listener")
        self.listener = keyboard.Listener(on_press=self.on_press)
        self.listener.start()
        self.get_logger().info('Keyboard control node has started.')
        print("Keyboard control node has started.")

    def on_press(self, key):
        print(f"Key pressed: {key}")
        try:
            if key.char == 'w':
                print("Key 'w' detected: Forward with full speed")
                self.publish_motor_command(100.0, 1)  # Forward with full speed
            elif key.char == 's':
                print("Key 's' detected: Backward with full speed")
                self.publish_motor_command(100.0, 2)  # Backward with full speed
            elif key.char == 'a':
                print("Key 'a' detected: Left with full speed")
                self.publish_motor_command(100.0, 3)  # Left with full speed
            elif key.char == 'd':
                print("Key 'd' detected: Right with full speed")
                self.publish_motor_command(100.0, 4)  # Right with full speed
            elif key.char == 'q':
                print("Key 'q' detected: Stop the motor")
                self.publish_motor_command(0.0, 0)  # Stop the motor
            else:
                print("Other key detected: Stop the motor")
                self.publish_motor_command(0.0, 0)  # Stop the motor for any other key
        except AttributeError:
            print("Non-character key pressed: Stop the motor")
            self.publish_motor_command(0.0, 0)  # Stop the motor on any non-character key press

    def publish_motor_command(self, speed, direction):
        print(f"Publishing motor command: speed={speed}, direction={direction}")
        speed_msg = Float32()
        speed_msg.data = speed
        self.speed_publisher.publish(speed_msg)
        print(f"Published speed: {speed_msg.data}")
        
        direction_msg = Int32()
        direction_msg.data = direction
        self.direction_publisher.publish(direction_msg)
        print(f"Published direction: {direction_msg.data}")

    def cleanup(self):
        print("Cleaning up: Stopping listener")
        self.listener.stop()


def main(args=None):
    print("Starting main function")
    rclpy.init(args=args)
    print("Initialized rclpy")
    keyboard_control = KeyboardControl()

    try:
        print("Spinning node")
        rclpy.spin(keyboard_control)
    except KeyboardInterrupt:
        print("KeyboardInterrupt detected")
        pass
    finally:
        print("Cleaning up node")
        keyboard_control.cleanup()
        keyboard_control.destroy_node()
        rclpy.shutdown()
        print("Shutdown rclpy")


if __name__ == '__main__':
    main()
