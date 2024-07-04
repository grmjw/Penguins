import unittest
from unittest.mock import patch, MagicMock
import rclpy
from motor_controller_pkg.motor_controller import MotorController
from std_msgs.msg import Float32
import Jetson.GPIO as GPIO


class TestMotorController(unittest.TestCase):

    @classmethod
    def setUpClass(cls):
        rclpy.init()

    @classmethod
    def tearDownClass(cls):
        rclpy.shutdown()

    def setUp(self):
        patcher1 = patch('Jetson.GPIO.setmode')
        patcher2 = patch('Jetson.GPIO.setup')
        patcher3 = patch('Jetson.GPIO.PWM')
        patcher4 = patch('Jetson.GPIO.output')
        patcher5 = patch('Jetson.GPIO.cleanup')

        self.mock_setmode = patcher1.start()
        self.mock_setup = patcher2.start()
        self.mock_pwm = patcher3.start()
        self.mock_output = patcher4.start()
        self.mock_cleanup = patcher5.start()

        self.addCleanup(patcher1.stop)
        self.addCleanup(patcher2.stop)
        self.addCleanup(patcher3.stop)
        self.addCleanup(patcher4.stop)
        self.addCleanup(patcher5.stop)

        self.mock_pwm.return_value = MagicMock(start=MagicMock(),
                                               ChangeDutyCycle=MagicMock(), stop=MagicMock())

        self.node = MotorController()

    def tearDown(self):
        self.node.destroy()

    def test_initialization(self):
        self.mock_setmode.assert_called_once_with(GPIO.BOARD)
        self.mock_setup.assert_any_call(self.node.enable_pin_1, GPIO.OUT)
        self.mock_setup.assert_any_call(self.node.in1_pin_1, GPIO.OUT)
        self.mock_setup.assert_any_call(self.node.in2_pin_1, GPIO.OUT)
        self.mock_setup.assert_any_call(self.node.enable_pin_2, GPIO.OUT)
        self.mock_setup.assert_any_call(self.node.in1_pin_2, GPIO.OUT)
        self.mock_setup.assert_any_call(self.node.in2_pin_2, GPIO.OUT)
        self.mock_pwm.assert_any_call(self.node.enable_pin_1, 100)
        self.mock_pwm.assert_any_call(self.node.enable_pin_2, 100)
        self.mock_pwm.return_value.start.assert_any_call(0)

    @patch('motor_controller_pkg.motor_controller.GPIO.output')
    def test_motor_speed_callback_forward(self, mock_gpio_output):
        msg = Float32()
        msg.data = 1.0
        self.node.motor_speed_callback(msg)
        mock_gpio_output.assert_any_call(self.node.in1_pin_1, GPIO.HIGH)
        mock_gpio_output.assert_any_call(self.node.in2_pin_1, GPIO.LOW)
        mock_gpio_output.assert_any_call(self.node.in1_pin_2, GPIO.HIGH)
        mock_gpio_output.assert_any_call(self.node.in2_pin_2, GPIO.LOW)
        self.node.pwm_1.ChangeDutyCycle.assert_called_with(1.0)
        self.node.pwm_2.ChangeDutyCycle.assert_called_with(1.0)

    @patch('motor_controller_pkg.motor_controller.GPIO.output')
    def test_motor_speed_callback_backward(self, mock_gpio_output):
        msg = Float32()
        msg.data = -1.0
        self.node.motor_speed_callback(msg)
        mock_gpio_output.assert_any_call(self.node.in1_pin_1, GPIO.LOW)
        mock_gpio_output.assert_any_call(self.node.in2_pin_1, GPIO.HIGH)
        mock_gpio_output.assert_any_call(self.node.in1_pin_2, GPIO.LOW)
        mock_gpio_output.assert_any_call(self.node.in2_pin_2, GPIO.HIGH)
        self.node.pwm_1.ChangeDutyCycle.assert_called_with(1.0)
        self.node.pwm_2.ChangeDutyCycle.assert_called_with(1.0)

    @patch('motor_controller_pkg.motor_controller.GPIO.output')
    def test_motor_speed_callback_stop(self, mock_gpio_output):
        msg = Float32()
        msg.data = 0.0
        self.node.motor_speed_callback(msg)
        mock_gpio_output.assert_any_call(self.node.in1_pin_1, GPIO.LOW)
        mock_gpio_output.assert_any_call(self.node.in2_pin_1, GPIO.LOW)
        mock_gpio_output.assert_any_call(self.node.in1_pin_2, GPIO.LOW)
        mock_gpio_output.assert_any_call(self.node.in2_pin_2, GPIO.LOW)
        self.node.pwm_1.ChangeDutyCycle.assert_called_with(0.0)
        self.node.pwm_2.ChangeDutyCycle.assert_called_with(0.0)

    def test_cleanup(self):
        self.node.destroy()
        self.mock_cleanup.assert_called_once()


if __name__ == '__main__':
    unittest.main()
