import unittest
from unittest.mock import patch, MagicMock
import rclpy
from motor_controller_pkg.motor_controller import MotorController, main
from std_msgs.msg import Float32, Int32


class TestMotorController(unittest.TestCase):

    @classmethod
    def setUpClass(cls):
        rclpy.init()

    @classmethod
    def tearDownClass(cls):
        rclpy.shutdown()

    def setUp(self):
        self.node = MotorController()

    @patch('motor_controller_pkg.motor_controller.GPIO.output')
    def test_motor_speed_callback(self, mock_gpio_output):
        msg = Float32()
        msg.data = 75.0
        self.node.motor_speed_callback(msg)

        self.assertEqual(self.node.pwm_duty_cycle_1, 75.0)
        self.assertEqual(self.node.pwm_duty_cycle_2, 75.0)

    @patch('motor_controller_pkg.motor_controller.GPIO.output')
    def test_motor_direction_callback_forward(self, mock_gpio_output):
        msg = Int32()
        msg.data = 1
        self.node.motor_direction_callback(msg)
        
        mock_gpio_output.assert_any_call(self.node.in1_pin_1, GPIO.HIGH)
        mock_gpio_output.assert_any_call(self.node.in2_pin_1, GPIO.LOW)
        mock_gpio_output.assert_any_call(self.node.in1_pin_2, GPIO.HIGH)
        mock_gpio_output.assert_any_call(self.node.in2_pin_2, GPIO.LOW)

    @patch('motor_controller_pkg.motor_controller.GPIO.output')
    def test_motor_direction_callback_backward(self, mock_gpio_output):
        msg = Int32()
        msg.data = 2
        self.node.motor_direction_callback(msg)
        
        mock_gpio_output.assert_any_call(self.node.in1_pin_1, GPIO.LOW)
        mock_gpio_output.assert_any_call(self.node.in2_pin_1, GPIO.HIGH)
        mock_gpio_output.assert_any_call(self.node.in1_pin_2, GPIO.LOW)
        mock_gpio_output.assert_any_call(self.node.in2_pin_2, GPIO.HIGH)

    @patch('motor_controller_pkg.motor_controller.GPIO.output')
    def test_motor_direction_callback_stop(self, mock_gpio_output):
        msg = Int32()
        msg.data = 0
        self.node.motor_direction_callback(msg)
        
        mock_gpio_output.assert_any_call(self.node.in1_pin_1, GPIO.HIGH)
        mock_gpio_output.assert_any_call(self.node.in2_pin_1, GPIO.HIGH)
        mock_gpio_output.assert_any_call(self.node.in1_pin_2, GPIO.HIGH)
        mock_gpio_output.assert_any_call(self.node.in2_pin_2, GPIO.HIGH)

    @patch('motor_controller_pkg.motor_controller.GPIO.cleanup')
    def test_cleanup(self, mock_gpio_cleanup):
        self.node.cleanup()
        self.assertIsNone(self.node.pwm_thread_1)
        self.assertIsNone(self.node.pwm_thread_2)
        mock_gpio_cleanup.assert_called_once()

    @patch('motor_controller_pkg.motor_controller.rclpy.init')
    @patch('motor_controller_pkg.motor_controller.rclpy.spin')
    @patch('motor_controller_pkg.motor_controller.rclpy.shutdown')
    @patch('motor_controller_pkg.motor_controller.MotorController.cleanup')
    @patch('motor_controller_pkg.motor_controller.MotorController.destroy_node')
    def test_main(self, mock_destroy_node, mock_cleanup, mock_shutdown, mock_spin, mock_init):
        with patch('motor_controller_pkg.motor_controller.MotorController') as MockMotorController:
            mock_motor_controller_instance = MockMotorController.return_value

            main()

            mock_init.assert_called_once()
            mock_spin.assert_called_once_with(mock_motor_controller_instance)
            mock_motor_controller_instance.cleanup.assert_called_once()
            mock_motor_controller_instance.destroy_node.assert_called_once()
            mock_shutdown.assert_called_once()


if __name__ == '__main__':
    unittest.main()
