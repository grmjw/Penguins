import unittest
from unittest.mock import patch, MagicMock
import rclpy
from motor_controller_pkg.keyboard_control import KeyboardControl, main
from std_msgs.msg import Float32, Int32


class TestKeyboardControl(unittest.TestCase):

    @classmethod
    def setUpClass(cls):
        rclpy.init()

    @classmethod
    def tearDownClass(cls):
        rclpy.shutdown()

    def setUp(self):
        self.node = KeyboardControl()

    @patch('motor_controller_pkg.keyboard_control.KeyboardControl.publish_motor_command')
    def test_on_press_w(self, mock_publish_motor_command):
        self.node.on_press(MagicMock(char='w'))
        mock_publish_motor_command.assert_called_once_with(100.0, 1)

    @patch('motor_controller_pkg.keyboard_control.KeyboardControl.publish_motor_command')
    def test_on_press_s(self, mock_publish_motor_command):
        self.node.on_press(MagicMock(char='s'))
        mock_publish_motor_command.assert_called_once_with(100.0, 2)

    @patch('motor_controller_pkg.keyboard_control.KeyboardControl.publish_motor_command')
    def test_on_press_a(self, mock_publish_motor_command):
        self.node.on_press(MagicMock(char='a'))
        mock_publish_motor_command.assert_called_once_with(100.0, 3)

    @patch('motor_controller_pkg.keyboard_control.KeyboardControl.publish_motor_command')
    def test_on_press_d(self, mock_publish_motor_command):
        self.node.on_press(MagicMock(char='d'))
        mock_publish_motor_command.assert_called_once_with(100.0, 4)

    @patch('motor_controller_pkg.keyboard_control.KeyboardControl.publish_motor_command')
    def test_on_press_q(self, mock_publish_motor_command):
        self.node.on_press(MagicMock(char='q'))
        mock_publish_motor_command.assert_called_once_with(0.0, 0)

    @patch('motor_controller_pkg.keyboard_control.KeyboardControl.publish_motor_command')
    def test_on_press_other(self, mock_publish_motor_command):
        self.node.on_press(MagicMock(char='x'))
        mock_publish_motor_command.assert_called_once_with(0.0, 0)

    @patch('motor_controller_pkg.keyboard_control.KeyboardControl.publish_motor_command')
    def test_on_press_non_char(self, mock_publish_motor_command):
        self.node.on_press(MagicMock(char=None))
        mock_publish_motor_command.assert_called_once_with(0.0, 0)

    @patch('motor_controller_pkg.keyboard_control.rclpy.Publisher.publish')
    def test_publish_motor_command(self, mock_publish):
        speed_msg = Float32()
        speed_msg.data = 100.0
        direction_msg = Int32()
        direction_msg.data = 1

        self.node.publish_motor_command(100.0, 1)

        self.node.speed_publisher.publish.assert_called_once_with(speed_msg)
        self.node.direction_publisher.publish.assert_called_once_with(direction_msg)

    @patch('motor_controller_pkg.keyboard_control.KeyboardControl.cleanup')
    @patch('motor_controller_pkg.keyboard_control.KeyboardControl.destroy_node')
    @patch('motor_controller_pkg.keyboard_control.rclpy.shutdown')
    @patch('motor_controller_pkg.keyboard_control.rclpy.spin')
    @patch('motor_controller_pkg.keyboard_control.rclpy.init')
    def test_main(self, mock_init, mock_spin, mock_shutdown, mock_destroy_node, mock_cleanup):
        with patch('motor_controller_pkg.keyboard_control.KeyboardControl') as MockKeyboardControl:
            mock_keyboard_control_instance = MockKeyboardControl.return_value

            main()

            mock_init.assert_called_once()
            mock_spin.assert_called_once_with(mock_keyboard_control_instance)
            mock_keyboard_control_instance.cleanup.assert_called_once()
            mock_keyboard_control_instance.destroy_node.assert_called_once()
            mock_shutdown.assert_called_once()


if __name__ == '__main__':
    unittest.main()
