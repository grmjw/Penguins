import rclpy
from rclpy.node import Node
from std_msgs.msg import Float32, Int32
from pynput import keyboard

# Define the KeyboardControl class which inherits from rclpy's Node class
class KeyboardControl(Node):
    def __init__(self):
        # Print a message to indicate that the node is being initialized
        print("Initializing KeyboardControl Node")
        
        # Call the constructor of the parent Node class with the node name 'keyboard_control_node'
        super().__init__('keyboard_control_node')

        # Initialize publishers for speed and direction topics with respective message types and queue size of 10
        self.speed_publisher = self.create_publisher(Float32, 'motor_speed', 10)
        self.direction_publisher = self.create_publisher(Int32, 'motor_direction', 10)

        # Print a message to indicate that the node is starting to listen to keyboard inputs
        print("Starting to listen to the keyboard inputs")
        
        # Create a keyboard listener that triggers the on_press method when a key is pressed
        self.listener = keyboard.Listener(on_press=self.on_press)
        self.listener.start()  # Start the keyboard listener

    # Define the on_press method that is called when a key is pressed
    def on_press(self, key):
        try:
            # Check if the pressed key is 'w'
            if key.char == 'w':
                print("Key 'w' detected: Forward with full speed")
                self.publish_motor_command(100.0, 1)  # Publish command to move forward with full speed
            # Check if the pressed key is 's'
            elif key.char == 's':
                print("Key 's' detected: Backward with full speed")
                self.publish_motor_command(100.0, 2)  # Publish command to move backward with full speed
            # Check if the pressed key is 'a'
            elif key.char == 'a':
                print("Key 'a' detected: Left with full speed")
                self.publish_motor_command(100.0, 3)  # Publish command to move left with full speed
            # Check if the pressed key is 'd'
            elif key.char == 'd':
                print("Key 'd' detected: Right with full speed")
                self.publish_motor_command(100.0, 4)  # Publish command to move right with full speed
            # Check if the pressed key is 'q'
            elif key.char == 'q':
                print("Key 'q' detected: Stop the motor")
                self.publish_motor_command(0.0, 0)  # Publish command to stop the motor
            # Handle other keys
            else:
                print("Other key detected: Stop the motor")
                self.publish_motor_command(0.0, 0)  # Publish command to stop the motor
        except AttributeError:
            # Handle non-character keys
            print("Non-character key pressed: Stop the motor")
            self.publish_motor_command(0.0, 0)  # Publish command to stop the motor

    # Define the publish_motor_command method to publish speed and direction commands
    def publish_motor_command(self, speed, direction):
        print(f"Publishing motor command: speed={speed}, direction={direction}")
        
        # Create and publish the speed message
        speed_msg = Float32()
        speed_msg.data = speed
        self.speed_publisher.publish(speed_msg)
        print(f"Published speed: {speed_msg.data}")
        
        # Create and publish the direction message
        direction_msg = Int32()
        direction_msg.data = direction
        self.direction_publisher.publish(direction_msg)
        print(f"Published direction: {direction_msg.data}")

    # Define the cleanup method to stop the keyboard listener
    def cleanup(self):
        print("Cleaning up: Stopping listener")
        self.listener.stop()  # Stop the keyboard listener


# Define the main function to initialize and run the node
def main(args=None):
    print("Starting main function")
    rclpy.init(args=args)  # Initialize the ROS2 Python client library
    print("Initialized rclpy")
    
    # Create an instance of the KeyboardControl node
    keyboard_control = KeyboardControl()

    try:
        print("Spinning node")
        rclpy.spin(keyboard_control)  # Keep the node alive and listening for events
    except KeyboardInterrupt:
        print("KeyboardInterrupt detected")  # Handle keyboard interrupt (Ctrl+C)
        pass
    finally:
        print("Cleaning up node")
        keyboard_control.cleanup()  # Perform cleanup tasks
        keyboard_control.destroy_node()  # Destroy the node
        rclpy.shutdown()  # Shutdown the ROS2 Python client library
        print("Shutdown rclpy")


# Check if the script is being run directly and, if so, call the main function
if __name__ == '__main__':
    main()
