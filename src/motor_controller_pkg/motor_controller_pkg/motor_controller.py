import rclpy
from rclpy.node import Node
import Jetson.GPIO as GPIO
from std_msgs.msg import Float32, Int32
import time
import threading


class MotorController(Node):
    def __init__(self):
        print("Initializing MotorController Node")
        super().__init__('motor_controller_node')

        # Declare parameters for pins of the first wheel
        print("Declaring parameters for the first wheel")
        self.declare_parameter('enable_pin_1', 32)  # GPIO13 for PWM
        self.declare_parameter('in1_pin_1', 35)  # GPIO19 for IN1
        self.declare_parameter('in2_pin_1', 37)  # GPIO26 for IN2

        # Declare parameters for pins of the second wheel
        print("Declaring parameters for the second wheel")
        self.declare_parameter('enable_pin_2', 33)  # GPIO12 for PWM
        self.declare_parameter('in1_pin_2', 36)  # GPIO16 for IN1
        self.declare_parameter('in2_pin_2', 38)  # GPIO20 for IN2

        # Get parameter values for the first wheel
        print("Getting parameter values for the first wheel")
        self.enable_pin_1 = self.get_parameter('enable_pin_1').get_parameter_value().integer_value
        self.in1_pin_1 = self.get_parameter('in1_pin_1').get_parameter_value().integer_value
        self.in2_pin_1 = self.get_parameter('in2_pin_1').get_parameter_value().integer_value

        # Get parameter values for the second wheel
        print("Getting parameter values for the second wheel")
        self.enable_pin_2 = self.get_parameter('enable_pin_2').get_parameter_value().integer_value
        self.in1_pin_2 = self.get_parameter('in1_pin_2').get_parameter_value().integer_value
        self.in2_pin_2 = self.get_parameter('in2_pin_2').get_parameter_value().integer_value

        # Setup GPIO for the first wheel
        print("Setting up GPIO for the first wheel")
        GPIO.setmode(GPIO.BOARD)
        GPIO.setup(self.enable_pin_1, GPIO.OUT)
        GPIO.setup(self.in1_pin_1, GPIO.OUT)
        GPIO.setup(self.in2_pin_1, GPIO.OUT)

        # Setup GPIO for the second wheel
        print("Setting up GPIO for the second wheel")
        GPIO.setup(self.enable_pin_2, GPIO.OUT)
        GPIO.setup(self.in1_pin_2, GPIO.OUT)
        GPIO.setup(self.in2_pin_2, GPIO.OUT)

        # Initialize PWM manually for both wheels
        print("Initializing PWM")
        self.pwm_frequency = 500  # 500 Hz frequency
        self.pwm_duty_cycle_1 = 0  # Initial duty cycle for wheel 1
        self.pwm_duty_cycle_2 = 0  # Initial duty cycle for wheel 2
        self.pwm_thread_1 = None
        self.pwm_thread_2 = None
        self.start_pwm(self.pwm_duty_cycle_1, self.enable_pin_1, 1)
        self.start_pwm(self.pwm_duty_cycle_2, self.enable_pin_2, 2)

        # Set initial direction (default: stop)
        print("Setting initial motor direction to stop")
        GPIO.output(self.in1_pin_1, GPIO.LOW)
        GPIO.output(self.in2_pin_1, GPIO.LOW)
        GPIO.output(self.in1_pin_2, GPIO.LOW)
        GPIO.output(self.in2_pin_2, GPIO.LOW)

        # Create subscribers for speed and direction
        print("Creating subscribers for speed and direction")
        self.speed_subscription = self.create_subscription(
            Float32,
            'motor_speed',
            self.motor_speed_callback,
            10)
        self.direction_subscription = self.create_subscription(
            Int32,
            'motor_direction',
            self.motor_direction_callback,
            10)
        self.speed_subscription  # prevent unused variable warning
        self.direction_subscription  # prevent unused variable warning

    def start_pwm(self, duty_cycle, enable_pin, wheel):
        print(f"Starting PWM for wheel {wheel} with duty cycle {duty_cycle}%")
        if wheel == 1:
            if self.pwm_thread_1:
                print("Stopping existing PWM thread for wheel 1")
                self.pwm_thread_1 = None  # Stop the existing PWM thread
            self.pwm_duty_cycle_1 = duty_cycle
            self.pwm_thread_1 = threading.Thread(target=self.pwm_control, args=(duty_cycle, enable_pin))
            self.pwm_thread_1.daemon = True
            self.pwm_thread_1.start()
        elif wheel == 2:
            if self.pwm_thread_2:
                print("Stopping existing PWM thread for wheel 2")
                self.pwm_thread_2 = None  # Stop the existing PWM thread
            self.pwm_duty_cycle_2 = duty_cycle
            self.pwm_thread_2 = threading.Thread(target=self.pwm_control, args=(duty_cycle, enable_pin))
            self.pwm_thread_2.daemon = True
            self.pwm_thread_2.start()

    def pwm_control(self, duty_cycle, enable_pin):
        print(f"Controlling PWM: duty_cycle={duty_cycle}, enable_pin={enable_pin}")
        period = 1.0 / self.pwm_frequency
        high_time = period * (duty_cycle / 100.0)
        low_time = period - high_time

        while True:
            GPIO.output(enable_pin, GPIO.HIGH)
            time.sleep(high_time)
            GPIO.output(enable_pin, GPIO.LOW)
            time.sleep(low_time)

    def motor_speed_callback(self, msg):
        speed = msg.data
        print(f"Received motor speed: {speed}")
        duty_cycle = max(0, min(100, speed))  # Constrain to 0-100%
        self.start_pwm(duty_cycle, self.enable_pin_1, 1)
        self.start_pwm(duty_cycle, self.enable_pin_2, 2)
        self.get_logger().info('Motor speed set to {}%'.format(speed))

    def motor_direction_callback(self, msg):
        direction = msg.data
        print(f"Received motor direction: {direction}")
        if direction == 1:
            # Forward
            print("Setting motor direction to forward")
            GPIO.output(self.in1_pin_1, GPIO.HIGH)
            GPIO.output(self.in2_pin_1, GPIO.LOW)
            GPIO.output(self.in1_pin_2, GPIO.HIGH)
            GPIO.output(self.in2_pin_2, GPIO.LOW)
        elif direction == 2:
            # Backward
            print("Setting motor direction to backward")
            GPIO.output(self.in1_pin_1, GPIO.LOW)
            GPIO.output(self.in2_pin_1, GPIO.HIGH)
            GPIO.output(self.in1_pin_2, GPIO.LOW)
            GPIO.output(self.in2_pin_2, GPIO.HIGH)
        elif direction == 3:
            # Left
            print("Setting motor direction to left")
            GPIO.output(self.in1_pin_1, GPIO.LOW)
            GPIO.output(self.in2_pin_1, GPIO.HIGH)
            GPIO.output(self.in1_pin_2, GPIO.HIGH)
            GPIO.output(self.in2_pin_2, GPIO.LOW)
        elif direction == 4:
            # Right
            print("Setting motor direction to right")
            GPIO.output(self.in1_pin_1, GPIO.HIGH)
            GPIO.output(self.in2_pin_1, GPIO.LOW)
            GPIO.output(self.in1_pin_2, GPIO.LOW)
            GPIO.output(self.in2_pin_2, GPIO.HIGH)
        else:
            # Stop
            print("Stopping motor")
            GPIO.output(self.in1_pin_1, GPIO.HIGH)
            GPIO.output(self.in2_pin_1, GPIO.HIGH)
            GPIO.output(self.in1_pin_2, GPIO.HIGH)
            GPIO.output(self.in2_pin_2, GPIO.HIGH)
        self.get_logger().info('Motor direction set to {}'.format(direction))

    def cleanup(self):
        print("Cleaning up: stopping PWM threads and cleaning up GPIO")
        self.pwm_thread_1 = None
        self.pwm_thread_2 = None
        try:
            GPIO.cleanup()
        except RuntimeError as e:
            self.get_logger().error(f"Error during GPIO cleanup: {e}")


def main(args=None):
    print("Starting main function")
    rclpy.init(args=args)
    motor_controller = MotorController()

    try:
        print("Spinning node")
        rclpy.spin(motor_controller)
    except KeyboardInterrupt:
        print("KeyboardInterrupt detected")
        pass
    finally:
        print("Cleaning up node")
        motor_controller.cleanup()
        motor_controller.destroy_node()
        rclpy.shutdown()
        print("Shutdown rclpy")


if __name__ == '__main__':
    main()
