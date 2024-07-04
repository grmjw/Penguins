import rclpy
from rclpy.node import Node
import Jetson.GPIO as GPIO
from std_msgs.msg import Float32
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

        # Setup PWM for the first wheel
        print("Setting up PWM for the first wheel")
        self.pwm_1 = GPIO.PWM(self.enable_pin_1, 100)
        self.pwm_1.start(0)

        # Setup PWM for the second wheel
        print("Setting up PWM for the second wheel")
        self.pwm_2 = GPIO.PWM(self.enable_pin_2, 100)
        self.pwm_2.start(0)

        # Initialize the motor control subscriber
        print("Initializing the motor control subscriber")
        self.subscription = self.create_subscription(
            Float32,
            'motor_speed',
            self.motor_speed_callback,
            10
        )

    def motor_speed_callback(self, msg):
        print(f"Received motor speed command: {msg.data}")
        speed = msg.data

        # Control the motors based on received speed
        if speed > 0:
            print("Setting motors to move forward")
            GPIO.output(self.in1_pin_1, GPIO.HIGH)
            GPIO.output(self.in2_pin_1, GPIO.LOW)
            GPIO.output(self.in1_pin_2, GPIO.HIGH)
            GPIO.output(self.in2_pin_2, GPIO.LOW)
        elif speed < 0:
            print("Setting motors to move backward")
            GPIO.output(self.in1_pin_1, GPIO.LOW)
            GPIO.output(self.in2_pin_1, GPIO.HIGH)
            GPIO.output(self.in1_pin_2, GPIO.LOW)
            GPIO.output(self.in2_pin_2, GPIO.HIGH)
        else:
            print("Stopping motors")
            GPIO.output(self.in1_pin_1, GPIO.LOW)
            GPIO.output(self.in2_pin_1, GPIO.LOW)
            GPIO.output(self.in1_pin_2, GPIO.LOW)
            GPIO.output(self.in2_pin_2, GPIO.LOW)

        # Set the motor speed using PWM
        self.pwm_1.ChangeDutyCycle(abs(speed))
        self.pwm_2.ChangeDutyCycle(abs(speed))

    def destroy(self):
        print("Destroying MotorController Node")
        GPIO.cleanup()

    def pwm_control(self, duty_cycle, enable_pin):
        if hasattr(self, 'pwm_thread_1') and self.pwm_thread_1.is_alive():
            print("Stopping existing PWM thread for wheel 1")
            self.pwm_thread_1.join()
        if hasattr(self, 'pwm_thread_2') and self.pwm_thread_2.is_alive():
            print("Stopping existing PWM thread for wheel 2")
            self.pwm_thread_2.join()

        print(f"Starting PWM for wheel with duty cycle {duty_cycle}%")
        self.pwm_thread_1 = threading.Thread(target=GPIO.output, args=(enable_pin, GPIO.HIGH))
        self.pwm_thread_2 = threading.Thread(target=GPIO.output, args=(enable_pin, GPIO.HIGH))
        self.pwm_thread_1.start()
        self.pwm_thread_2.start()


def main(args=None):
    rclpy.init(args=args)
    motor_controller = MotorController()
    rclpy.spin(motor_controller)
    motor_controller.destroy()
    rclpy.shutdown()


if __name__ == '__main__':
    main()
