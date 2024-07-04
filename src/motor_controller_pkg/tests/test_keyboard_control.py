import unittest
from unittest.mock import patch, MagicMock
import rclpy
from motor_controller_pkg.keyboard_control import KeyboardControl
from std_msgs.msg import Float32, Int32
from pynput import keyboard


class TestKeyboardControl(unittest.TestCase):

    @classmethod
    def setUpClass(cls):
        rclpy.init()

    @classmethod
    def tearDownClass(cls):
        rclpy.shutdown()

    def setUp(self):
        with patch.object(keyboard, 'Listener', return_value=MagicMock(start=MagicMock())):
            self.node = KeyboardControl()

    def tearDown(self):
        self.node.cleanup()

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
    def test_on_press_non_character_key(self, mock_publish_motor_command):
        self.node.on_press(MagicMock(char=None))
        mock_publish_motor_command.assert_called_once_with(0.0, 0)

    @patch('motor_controller_pkg.keyboard_control.KeyboardControl.create_publisher')
    def test_initialization(self, mock_create_publisher):
        with patch.object(keyboard, 'Listener', return_value=MagicMock(start=MagicMock())):
            node = KeyboardControl()
            self.assertIsInstance(node, KeyboardControl)
            self.assertEqual(mock_create_publisher.call_count, 3)  # Expecting 3 calls now
            mock_create_publisher.assert_any_call(Float32, 'motor_speed', 10)
            mock_create_publisher.assert_any_call(Int32, 'motor_direction', 10)
            node.cleanup()

    @patch('motor_controller_pkg.keyboard_control.KeyboardControl.create_publisher')
    def test_publish_motor_command(self, mock_create_publisher):
        mock_speed_publisher = MagicMock()
        mock_direction_publisher = MagicMock()
        # Providing enough return values for all calls to create_publisher
        mock_create_publisher.side_effect = [mock_speed_publisher, mock_direction_publisher, MagicMock()]

        with patch.object(keyboard, 'Listener', return_value=MagicMock(start=MagicMock())):
            node = KeyboardControl()
            
            # Patch the publish method of the publishers
            mock_speed_publisher.publish = MagicMock()
            mock_direction_publisher.publish = MagicMock()
            
            # Assign the patched publishers to the node
            node.speed_publisher = mock_speed_publisher
            node.direction_publisher = mock_direction_publisher
            
            node.publish_motor_command(50.0, 1)

            speed_msg = Float32()
            speed_msg.data = 50.0
            direction_msg = Int32()
            direction_msg.data = 1

            mock_speed_publisher.publish.assert_called_once_with(speed_msg)
            mock_direction_publisher.publish.assert_called_once_with(direction_msg)
            node.cleanup()

    def test_cleanup(self):
        with patch.object(self.node.listener, 'stop') as mock_listener_stop:
            self.node.cleanup()
            mock_listener_stop.assert_called_once()

    @patch('motor_controller_pkg.keyboard_control.rclpy.spin')
    @patch('motor_controller_pkg.keyboard_control.rclpy.shutdown')
    def test_main(self, mock_shutdown, mock_spin):
        with patch.object(KeyboardControl, 'cleanup') as mock_cleanup:
            with patch.object(KeyboardControl, 'destroy_node') as mock_destroy_node:
                with patch.object(rclpy, 'init') as mock_init:
                    from motor_controller_pkg.keyboard_control import main
                    main()
                    mock_init.assert_called_once()
                    mock_spin.assert_called_once()
                    mock_cleanup.assert_called_once()
                    mock_destroy_node.assert_called_once()
                    mock_shutdown.assert_called_once()


if __name__ == '__main__':
    unittest.main()
