import pytest
from unittest.mock import MagicMock, patch
import numpy as np
import cv2

from cam_odom.cam_odom import CameraPoses  # Updated import

@pytest.fixture
def camera_poses():
    intrinsic = np.eye(3)
    return CameraPoses(data_dir='', skip_frames=2, intrinsic=intrinsic)

def test_form_transf(camera_poses):
    R = np.eye(3)
    t = np.array([1, 2, 3])
    T = camera_poses._form_transf(R, t)
    expected_T = np.array([
        [1, 0, 0, 1],
        [0, 1, 0, 2],
        [0, 0, 1, 3],
        [0, 0, 0, 1]
    ])
    np.testing.assert_array_equal(T, expected_T)

@patch('cv2.ORB_create')
@patch('cv2.FlannBasedMatcher')
def test_get_matches(mock_orb_create, mock_flann_based_matcher, camera_poses):
    mock_orb = MagicMock()
    mock_orb.detectAndCompute.return_value = ([], np.array([]))
    mock_orb_create.return_value = mock_orb

    mock_flann = MagicMock()
    mock_flann.knnMatch.return_value = []
    mock_flann_based_matcher.return_value = mock_flann

    img1 = np.zeros((480, 640), dtype=np.uint8)
    img2 = np.zeros((480, 640), dtype=np.uint8)
    q1, q2 = camera_poses.get_matches(img1, img2)

    assert q1 is None
    assert q2 is None

def test_get_world_points(camera_poses):
    camera_poses.world_points = [np.array([1, 2, 3])]
    points = camera_poses.get_world_points()
    expected_points = np.array([[1, 2, 3]])
    np.testing.assert_array_equal(points, expected_points)
