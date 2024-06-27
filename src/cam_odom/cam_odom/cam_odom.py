# Basic ROS 2 program to subscribe to real-time streaming 
# video from your built-in webcam
# Author:
# - Addison Sears-Collins
# - https://automaticaddison.com
  
# Import the necessary libraries
import rclpy # Python library for ROS 2
from rclpy.node import Node # Handles the creation of nodes
from sensor_msgs.msg import Image # Image is the message type being received
from nav_msgs.msg import Odometry #Odometry is the message type being sent
from cv_bridge import CvBridge # Package to convert between ROS and OpenCV Images
import cv2 # OpenCV library

from sympy import homogeneous_order

from tqdm import tqdm
import time

from matplotlib import pyplot as plt

import pytransform3d.transformations as pt
import pytransform3d.trajectories as ptr
import pytransform3d.rotations as pr
import pytransform3d.camera as pc

from cycler import cycle
import os
import numpy as np

class CameraPoses():

    #data_dir is directory containing data to be processed (But not used since we have live camera)
    #skip_frames is number of frames to skip during processing
    #intrinsic contains internal camera parameters (needs to be calibrated first)
    def __init__(self, data_dir, skip_frames, intrinsic):
        
        self.K = intrinsic
        self.extrinsic = np.array(((1,0,0,0),(0,1,0,0),(0,0,1,0)))
        self.P = self.K @ self.extrinsic
        self.orb = cv2.ORB_create(3000)
        FLANN_INDEX_LSH = 6
        index_params = dict(algorithm=FLANN_INDEX_LSH, table_number=6, key_size=12, multi_probe_level=1)
        search_params = dict(checks=50)
        self.flann = cv2.FlannBasedMatcher(indexParams=index_params, searchParams=search_params)
        
        self.world_points = []

        self.current_pose = None
    
    #load_images from data set
    #not used for live camera
    @staticmethod
    def _load_images(filepath, skip_frames):
    
        image_paths = [os.path.join(filepath, file) for file in sorted(os.listdir(filepath))]
        images = []
        
        for path in tqdm(image_paths[::skip_frames]):
            img = cv2.imread(path)
            if img is not None:
                #images.append(cv2.resize(img, (640,480)))
                images.append(img)
                
        return images
    

    #Creates 4x4 homogeneous transformation matrix using
    #3x3 rotation matrix and 3 element translation vector
    @staticmethod
    def _form_transf(R, t):
        
        T = np.eye(4, dtype=np.float64)
        T[:3, :3] = R
        T[:3, 3] = t
        
        return T

    #Method to get world points
    def get_world_points(self):
        return np.array(self.world_points)
    
    #This function finds and matches keypoints between 2 images
    #Using ORB feature detector and FLANN matcher
    def get_matches(self, img1, img2):
   
        # Find the keypoints and descriptors with ORB
        kp1, des1 = self.orb.detectAndCompute(img1, None)
        kp2, des2 = self.orb.detectAndCompute(img2, None)
        # Find matches
        if len(kp1) > 6 and len(kp2) > 6:
            matches = self.flann.knnMatch(des1, des2, k=2)

            # Find the matches there do not have a to high distance
            good_matches = []
            try:
                for m, n in matches:
                    if m.distance < 0.5 * n.distance:
                        good_matches.append(m)
            except ValueError:
                pass
            
            # Draw matches
            img_matches = np.empty((max(img1.shape[0], img2.shape[0]), img1.shape[1] + img2.shape[1], 3), dtype=np.uint8)
            #cv2.drawMatches(img1, kp1, img2, kp2, good_matches, img_matches, flags=cv2.DrawMatchesFlags_NOT_DRAW_SINGLE_POINTS)
    
            #cv2.imshow('Good Matches', img_matches)
            #cv2.waitKey(50)
            
            # Get the image points form the good matches
            #q1 = [kp1[m.queryIdx] for m in good_matches]
            #q2 = [kp2[m.trainIdx] for m in good_matches]
            q1 = np.float32([kp1[m.queryIdx].pt for m in good_matches])
            q2 = np.float32([kp2[m.trainIdx].pt for m in good_matches])
        
            return q1, q2
        else:
            return None, None

    #Function estimates the relative pose (rotation and translation)
    #Between two sets of corresponding 2D points from two images.
    def get_pose(self, q1, q2):
    
        # Essential matrix
        E, mask = cv2.findEssentialMat(q1, q2, self.K)

        # Decompose the Essential matrix into R and t
        R, t = self.decomp_essential_mat_old(E, q1, q2)

        # Get transformation matrix
        transformation_matrix = self._form_transf(R, np.squeeze(t))
        
        return transformation_matrix


    #This function decomposes the essential matrix E into possible rotation
    #And translation matrix. then selects the correct pair based on the reconstructed 3D points.
    #This is done by checking which pair results in the most points lying in front of both cameras 
    def decomp_essential_mat(self, E, q1, q2):

        R1, R2, t = cv2.decomposeEssentialMat(E)
        T1 = self._form_transf(R1,np.ndarray.flatten(t))
        T2 = self._form_transf(R2,np.ndarray.flatten(t))
        T3 = self._form_transf(R1,np.ndarray.flatten(-t))
        T4 = self._form_transf(R2,np.ndarray.flatten(-t))
        transformations = [T1, T2, T3, T4]
        
        # Homogenize K
        K = np.concatenate((self.K, np.zeros((3,1)) ), axis = 1)

        # List of projections
        projections = [K @ T1, K @ T2, K @ T3, K @ T4]

        np.set_printoptions(suppress=True)

        # print ("\nTransform 1\n" +  str(T1))
        # print ("\nTransform 2\n" +  str(T2))
        # print ("\nTransform 3\n" +  str(T3))
        # print ("\nTransform 4\n" +  str(T4))

        positives = []
        for P, T in zip(projections, transformations):
            hom_Q1 = cv2.triangulatePoints(P, P, q1.T, q2.T)
            hom_Q2 = T @ hom_Q1
            # Un-homogenize
            Q1 = hom_Q1[:3, :] / hom_Q1[3, :]
            Q2 = hom_Q2[:3, :] / hom_Q2[3, :]
             
            total_sum = sum(Q2[2, :] > 0) + sum(Q1[2, :] > 0)
            relative_scale = np.mean(np.linalg.norm(Q1.T[:-1] - Q1.T[1:], axis=-1)/
                                     np.linalg.norm(Q2.T[:-1] - Q2.T[1:], axis=-1))
            positives.append(total_sum + relative_scale)
            

        # Decompose the Essential matrix using built in OpenCV function
        # Form the 4 possible transformation matrix T from R1, R2, and t
        # Create projection matrix using each T, and triangulate points hom_Q1
        # Transform hom_Q1 to second camera using T to create hom_Q2
        # Count how many points in hom_Q1 and hom_Q2 with positive z value
        # Return R and t pair which resulted in the most points with positive z

        max = np.argmax(positives)
        if (max == 2):
            # print(-t)
            return R1, np.ndarray.flatten(-t)
        elif (max == 3):
            # print(-t)
            return R2, np.ndarray.flatten(-t)
        elif (max == 0):
            # print(t)
            return R1, np.ndarray.flatten(t)
        elif (max == 1):
            # print(t)
            return R2, np.ndarray.flatten(t)
        
    #This function decomposes the essential matrix E into possible rotation
    #And translation matrix. then selects the correct pair based on the reconstructed 3D points.
    #This is done by checking which pair results in the most points lying in front of both cameras     
    def decomp_essential_mat_old(self, E, q1, q2):
        def sum_z_cal_relative_scale(R, t):
            # Get the transformation matrix
            T = self._form_transf(R, t)
            # Make the projection matrix
            P = np.matmul(np.concatenate((self.K, np.zeros((3, 1))), axis=1), T)

            # Triangulate the 3D points
            hom_Q1 = cv2.triangulatePoints(self.P, P, q1.T, q2.T)
            # Also seen from cam 2
            hom_Q2 = np.matmul(T, hom_Q1)

            # Un-homogenize
            Q1 = hom_Q1[:3, :] / hom_Q1[3, :]
            Q2 = hom_Q2[:3, :] / hom_Q2[3, :]
            
            #self.world_points.append(Q1)

            # Find the number of points there has positive z coordinate in both cameras
            sum_of_pos_z_Q1 = sum(Q1[2, :] > 0)
            sum_of_pos_z_Q2 = sum(Q2[2, :] > 0)

            # Form point pairs and calculate the relative scale
            relative_scale = np.mean(np.linalg.norm(Q1.T[:-1] - Q1.T[1:], axis=-1)/
                                     np.linalg.norm(Q2.T[:-1] - Q2.T[1:], axis=-1))
            return sum_of_pos_z_Q1 + sum_of_pos_z_Q2, relative_scale

        # Decompose the essential matrix
        R1, R2, t = cv2.decomposeEssentialMat(E)
        t = np.squeeze(t)

        # Make a list of the different possible pairs
        pairs = [[R1, t], [R1, -t], [R2, t], [R2, -t]]

        # Check which solution there is the right one
        z_sums = []
        relative_scales = []
        for R, t in pairs:
            z_sum, scale = sum_z_cal_relative_scale(R, t)
            z_sums.append(z_sum)
            relative_scales.append(scale)

        # Select the pair there has the most points with positive z coordinate
        right_pair_idx = np.argmax(z_sums)
        right_pair = pairs[right_pair_idx]
        relative_scale = relative_scales[right_pair_idx]
        R1, t = right_pair
        t = t * relative_scale
        
        T = self._form_transf(R1, t)
        # Make the projection matrix
        P = np.matmul(np.concatenate((self.K, np.zeros((3, 1))), axis=1), T)

        # Triangulate the 3D points
        hom_Q1 = cv2.triangulatePoints(P, P, q1.T, q2.T)
        # Also seen from cam 2
        hom_Q2 = np.matmul(T, hom_Q1)

        # Un-homogenize
        Q1 = hom_Q1[:3, :] / hom_Q1[3, :]
        Q2 = hom_Q2[:3, :] / hom_Q2[3, :]
        
        self.world_points.append(Q1)

        return [R1, t]

#This node is responsible for subscribing to an image topic called 'video_frames' it estimates camera motion
#And update cameras pose over time. 
class ImageSubscriber(Node):
	"""
	Create an ImageSubscriber class, which is a subclass of the Node class.
	"""
	def __init__(self):
		"""
		Class constructor to set up the node
		"""
		# Initiate the Node class's constructor and give it a name
		super().__init__('image_subscriber')

		# Create the subscriber. This subscriber will receive an Image
		# from the video_frames topic. The queue size is 10 messages.
		self.subscription = self.create_subscription(Image, 'video_frames', self.listener_callback, 100)
		self.subscription # prevent unused variable warning

		# Used to convert between ROS and OpenCV images
		self.br = CvBridge()

		with open('/home/polar/Penguins/install/cam_odom/lib/python3.8/site-packages/cam_odom/intrinsic.npy', 'rb') as f:
			self.intrinsic = np.load(f)

		skip_frames = 2
		data_dir = ''
		self.vo = CameraPoses(data_dir, skip_frames, self.intrinsic)
		self.gt_path = []
		self.estimated_path = []
		self.camera_pose_list = []
		self.start_pose = np.ones((3,4))
		self.start_translation = np.zeros((3,1))
		self.start_rotation = np.identity(3)
		self.start_pose = np.concatenate((self.start_rotation, self.start_translation), axis=1)
		self.process_frames = False
		self.old_frame = None
		self.new_frame = None
		self.frame_counter = 0
		self.cur_pose = self.start_pose

    #Callback function that processes incoming video frames received as ROS			
	def listener_callback(self, data):
		"""
		Callback function.
		"""
		# Display the message on the console
		self.get_logger().info('Receiving video frame')

		# Convert ROS Image message to OpenCV image
		self.new_frame = self.br.imgmsg_to_cv2(data)

		# Display image
		self.start_calc()

		cv2.waitKey(1)

    #This method is for processing video frames to estimate camera motion and update
    #The camera's pose over time
	def start_calc(self):
		self.frame_counter += 1
		start = time.perf_counter()
		if self.process_frames:
			q1, q2 = self.vo.get_matches(self.old_frame, self.new_frame)
			if q1 is not None:
				if len(q1) > 20 and len(q2) > 20:
					transf = self.vo.get_pose(q1, q2)
					self.cur_pose = self.cur_pose @ transf

			hom_array = np.array([[0,0,0,1]])
			hom_camera_pose = np.concatenate((self.cur_pose,hom_array), axis=0)
			self.camera_pose_list.append(hom_camera_pose)
			self.estimated_path.append((self.cur_pose[0, 3], self.cur_pose[2, 3]))

			estimated_camera_pose_x, estimated_camera_pose_y = self.cur_pose[0, 3], self.cur_pose[2, 3]
		
		self.old_frame = self.new_frame
    
		self.process_frames = True

		end = time.perf_counter()

		total_time = end - start
		
		#uncomment this for visualizing the camera odometry
		fps = 1 / total_time

		cv2.putText(self.new_frame, f'FPS: {int(fps)}', (20,50), cv2.FONT_HERSHEY_SIMPLEX, 1, (0,255,0), 2)

		cv2.putText(self.new_frame, str(np.round(self.cur_pose[0, 0],2)), (260,50), cv2.FONT_HERSHEY_SIMPLEX, 1, (255, 0, 0), 1)
		cv2.putText(self.new_frame, str(np.round(self.cur_pose[0, 1],2)), (340,50), cv2.FONT_HERSHEY_SIMPLEX, 1, (255, 0, 0), 1)
		cv2.putText(self.new_frame, str(np.round(self.cur_pose[0, 2],2)), (420,50), cv2.FONT_HERSHEY_SIMPLEX, 1, (255, 0, 0), 1)
		cv2.putText(self.new_frame, str(np.round(self.cur_pose[1, 0],2)), (260,90), cv2.FONT_HERSHEY_SIMPLEX, 1, (255, 0, 0), 1)
		cv2.putText(self.new_frame, str(np.round(self.cur_pose[1, 1],2)), (340,90), cv2.FONT_HERSHEY_SIMPLEX, 1, (255, 0, 0), 1)
		cv2.putText(self.new_frame, str(np.round(self.cur_pose[1, 2],2)), (420,90), cv2.FONT_HERSHEY_SIMPLEX, 1, (255, 0, 0), 1)
		cv2.putText(self.new_frame, str(np.round(self.cur_pose[2, 0],2)), (260,130), cv2.FONT_HERSHEY_SIMPLEX, 1, (255, 0, 0), 1)
		cv2.putText(self.new_frame, str(np.round(self.cur_pose[2, 1],2)), (340,130), cv2.FONT_HERSHEY_SIMPLEX, 1, (255, 0, 0), 1)
		cv2.putText(self.new_frame, str(np.round(self.cur_pose[2, 2],2)), (420,130), cv2.FONT_HERSHEY_SIMPLEX, 1, (255, 0, 0), 1)

		cv2.putText(self.new_frame, str(np.round(self.cur_pose[0, 3],2)), (540,50), cv2.FONT_HERSHEY_SIMPLEX, 1, (0, 0, 255), 1)
		cv2.putText(self.new_frame, str(np.round(self.cur_pose[1, 3],2)), (540,90), cv2.FONT_HERSHEY_SIMPLEX, 1, (0, 0, 255), 1)
		cv2.putText(self.new_frame, str(np.round(self.cur_pose[2, 3],2)), (540,130), cv2.FONT_HERSHEY_SIMPLEX, 1, (0, 0, 255), 1)

		cv2.imshow("img", self.new_frame)

#This class publishes odometry information to topic called 'cam_odom'
#With message type odom		
class OdomPublisher(Node):
	def __init__(self):
		super().__init__('odom_publisher')
		self.publisher_ = self.create_publisher(Odometry, 'cam_odom', 100)
		
	def publish_odom(self, x, y, z, quat_x, quat_y, quat_z, quat_w):
		msg = Odometry()
		msg.header.stamp = self.get_clock().now().to_msg()
		msg.pose.pose.position.x = x
		msg.pose.pose.position.y = y
		msg.pose.pose.position.z = z
		msg.pose.pose.orientation.x = quat_x
		msg.pose.pose.orientation.y = quat_y
		msg.pose.pose.orientation.z = quat_z
		msg.pose.pose.orientation.w = quat_w
		self.publisher_.publish(msg)

def main(args=None):

	# Initialize the rclpy library
	rclpy.init(args=args)

	# Create the node
	image_subscriber = ImageSubscriber()

	# Spin the node so the callback function is called.
	rclpy.spin(image_subscriber)

	# Destroy the node explicitly
	# (optional - otherwise it will be done automatically
	# when the garbage collector destroys the node object)
	image_subscriber.destroy_node()

	# Shutdown the ROS client library for Python
	rclpy.shutdown()

if __name__ == '__main__':
	main()


