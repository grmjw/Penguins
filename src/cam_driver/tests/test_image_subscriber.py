import pytest
import unittest
from unittest.mock import MagicMock, patch
from sensor_msgs.msg import Image
import numpy as np

from cam_odom.cam_odom import ImageSubscriber
import rclpy

@pytest.fixture(scope='module', autouse=True)
def ros2_setup():
    rclpy.init()
    yield
    rclpy.shutdown()

@pytest.fixture
def image_subscriber():
    with patch('builtins.open', unittest.mock.mock_open(read_data=np.eye(3).tobytes())), patch('numpy.load') as mock_load:
        mock_load.return_value = np.eye(3)
        return ImageSubscriber()

@patch('cv_bridge.CvBridge.imgmsg_to_cv2')
@patch('cv2.imshow')
def test_start_calc(mock_imgmsg_to_cv2, mock_imshow, image_subscriber):
    image_subscriber.old_frame = np.zeros((480, 640, 3), dtype=np.uint8)
    image_subscriber.new_frame = np.zeros((480, 640, 3), dtype=np.uint8)
    image_subscriber.process_frames = True
    image_subscriber.vo.get_matches = MagicMock(return_value=(np.random.rand(30, 2), np.random.rand(30, 2)))
    image_subscriber.vo.get_pose = MagicMock(return_value=np.eye(4))

    image_subscriber.start_calc()

    assert image_subscriber.old_frame is not None
    assert image_subscriber.cur_pose is not None
