# Basic ROS 2 program to publish real-time streaming 
# video from your built-in webcam
# Author:
# - Addison Sears-Collins
# - https://automaticaddison.com
  
# Import the necessary libraries

import cv2 as cv # OpenCV library
import libIpxCameraApiPy
import rclpy # Python library for ROS 2
from rclpy.node import Node # Handles the creation of nodes
from sensor_msgs.msg import Image # Image is the message type
from cv_bridge import CvBridge # Package to convert between ROS and OpenCV Images
import enum
import sys
import os
import platform
import numpy as np
import time

#Device number from command prompt
g_devNum = -1

class PixelTypeFlags(enum.IntFlag):
	PixelTypeIdBit = 0
	PixelTypeIdMask = 0xFFFF << PixelTypeIdBit
	PixelSizeOccupyBit = 16
	PixelSizeOccupyMask = 0xFF << PixelSizeOccupyBit
	PixelChromaticityBit = 24
	PixelChromaticityMask = 0xFF << PixelChromaticityBit


class PixelType(enum.IntEnum):
	Mono8                    = 0x01080001 # PFNC Monochrome 8-bit
	Mono8s                   = 0x01080002 # PFNC Monochrome 8-bit signed
	Mono10                   = 0x01100003 # PFNC Monochrome 10-bit unpacked
	Mono10Packed             = 0x010C0004 # GigE Vision 2.0 Monochrome 10-bit packed
	Mono12                   = 0x01100005 # PFNC Monochrome 12-bit unpacked
	Mono12Packed             = 0x010C0006 # GigE Vision 2.0 Monochrome 12-bit packed
	Mono16                   = 0x01100007 # PFNC Monochrome 16-bit
	BayerGR8                 = 0x01080008 # PFNC Bayer Green-Red 8-bit
	BayerRG8                 = 0x01080009 # PFNC Bayer Red-Green 8-bit
	BayerGB8                 = 0x0108000A # PFNC Bayer Green-Blue 8-bit
	BayerBG8                 = 0x0108000B # PFNC Bayer Blue-Green 8-bit
	BayerGR10                = 0x0110000C # PFNC Bayer Green-Red 10-bit unpacked
	BayerRG10                = 0x0110000D # PFNC Bayer Red-Green 10-bit unpacked
	BayerGB10                = 0x0110000E # PFNC Bayer Green-Blue 10-bit unpacked
	BayerBG10                = 0x0110000F # PFNC Bayer Blue-Green 10-bit unpacked
	BayerGR12                = 0x01100010 # PFNC Bayer Green-Red 12-bit unpacked
	BayerRG12                = 0x01100011 # PFNC Bayer Red-Green 12-bit unpacked
	BayerGB12                = 0x01100012 # PFNC Bayer Green-Blue 12-bit unpacked
	BayerBG12                = 0x01100013 # PFNC Bayer Blue-Green 12-bit unpacked
	RGB8                     = 0x02180014 # PFNC Red-Green-Blue 8-bit
	BGR8                     = 0x02180015 # PFNC Blue-Green-Red 8-bit
	RGBa8                    = 0x02200016 # PFNC Red-Green-Blue-alpha 8-bit
	BGRa8                    = 0x02200017 # PFNC Blue-Green-Red-alpha 8-bit
	RGB10                    = 0x02300018 # PFNC Red-Green-Blue 10-bit unpacked
	BGR10                    = 0x02300019 # PFNC Blue-Green-Red 10-bit unpacked
	RGB12                    = 0x0230001A # PFNC Red-Green-Blue 12-bit unpacked
	BGR12                    = 0x0230001B # PFNC Blue-Green-Red 12-bit unpacked
	RGB10V1Packed            = 0x0220001C # GigE Vision 2.0 Red-Green-Blue 10-bit packed - variant 1
	RGB10p32                 = 0x0220001D # PFNC Red-Green-Blue 10-bit packed into 32-bit
	YUV411_8_UYYVYY          = 0x020C001E # PFNC YUV 4:1:1 8-bit
	YUV422_8_UYVY            = 0x0210001F # PFNC YUV 4:2:2 8-bit
	YUV8_UYV                 = 0x02180020 # PFNC YUV 4:4:4 8-bit
	RGB8_Planar              = 0x02180021 # PFNC Red-Green-Blue 8-bit planar
	RGB10_Planar             = 0x02300022 # PFNC Red-Green-Blue 10-bit unpacked planar
	RGB12_Planar             = 0x02300023 # PFNC Red-Green-Blue 12-bit unpacked planar
	RGB16_Planar             = 0x02300024 # PFNC Red-Green-Blue 16-bit planar
	Mono14                   = 0x01100025 # PFNC Monochrome 14-bit unpacked
	BayerGR10Packed          = 0x010C0026 # GigE Vision 2.0 Bayer Green-Red 10-bit packed
	BayerRG10Packed          = 0x010C0027 # GigE Vision 2.0 Bayer Red-Green 10-bit packed
	BayerGB10Packed          = 0x010C0028 # GigE Vision 2.0 Bayer Green-Blue 10-bit packed
	BayerBG10Packed          = 0x010C0029 # GigE Vision 2.0 Bayer Blue-Green 10-bit packed
	BayerGR12Packed          = 0x010C002A # GigE Vision 2.0 Bayer Green-Red 12-bit packed
	BayerRG12Packed          = 0x010C002B # GigE Vision 2.0 Bayer Red-Green 12-bit packed
	BayerGB12Packed          = 0x010C002C # GigE Vision 2.0 Bayer Green-Blue 12-bit packed
	BayerBG12Packed          = 0x010C002D # GigE Vision 2.0 Bayer Blue-Green 12-bit packed
 
class ImagePublisher(Node):
	"""
	Create an ImagePublisher class, which is a subclass of the Node class.
	"""
	def __init__(self):
		"""
		Class constructor to set up the node
		"""
		# Initiate the Node class's constructor and give it a name
		super().__init__('image_publisher')

		# Create the publisher. This publisher will publish an Image
		# to the video_frames topic. The queue size is 10 messages.
		self.publisher_ = self.create_publisher(Image, 'video_frames', 100)

		# We will publish a message every 0.1 seconds
		#timer_period = 0.1  # seconds

		# Create the timer
		#self.timer = self.create_timer(timer_period, self.timer_callback)
		 
		# Create a VideoCapture object
		# The argument '0' gets the default webcam.
		#self.cap = cv2.VideoCapture(3)
 
		# Used to convert between ROS and OpenCV images
		self.br = CvBridge()

	#def timer_callback(self):
	"""
	Callback function.
	This function gets called every 0.1 seconds.
	"""
	# Capture frame-by-frame
	# This method returns True/False as well
	# as the video frame.
	#ret, frame = self.cap.read()
	  
	#if ret == True:
	# Publish the image.
	# The 'cv2_to_imgmsg' method converts an OpenCV
	# image to a ROS 2 image message
	# self.publisher_.publish(self.br.cv2_to_imgmsg(frame))

	# Display the message on the console
	#self.get_logger().info('Publishing video frame')
    
	# This function allows user to select the interface and camera to get the IpxCam::DeviceInfo object
	def SelectDevice(self, ipxSystem):
		global g_devNum
		# Get Interface list
		intLst = ipxSystem.GetInterfaceList()
		if(len(intLst)<1):
			print('No interface found')
			return None

		# Get list of cameras connected to each interface 
		devList=[]
		gv_num=0
		for infs in intLst:
			print (infs.GetDescription(), ':')
			# Get list of cameras connected to the current interface
			infs.ReEnumerateDevices(500)
			devListInt = infs.GetDeviceInfoList()
			for dv in devListInt:
				devList.append(dv)
				print ('[', gv_num, ']    ',dv.GetModel())
				#gv_num+=1
		
		if(len(devList)<1):
			print('No device found')
			return None
		# else:
		# 	if g_devNum>-1:
		# 		return devList[g_devNum]	

		# print('Please select the camera number to connect to: ')
		# dv_select = sys.stdin.readline()[:-1]
		# # Return None if user does not select any camera
		# if not dv_select:
		# 	return None

		# # Return selected camera's DeviceInfo object
		# if (int(dv_select)<gv_num) :
		# 	return devList[int(dv_select)]
		# else:
		# 	return 0
		return devList[0]
	
	def reconnect_device(self, ipxSystem):
		for attempt in range(6):
			print(f"Attempt {attempt + 1} to reconnect.")
			deviceInfo = self.SelectDevice(ipxSystem)
			if deviceInfo:
				dev1 = self.connectToDevice(deviceInfo)
				if dev1:
					print("Reconnected to device.")
					return dev1
			print("Failed to reconnect. Waiting 10 seconds before retrying...")
			time.sleep(10)
			print("Failed to reconnect after 6 attempts.")
		return None

	# This function connects to the camera, specified by devInfo argument
	def connectToDevice(self, devInfo):
		print ('connecting to ', devInfo.GetDisplayName())
		dev1 = IpxCameraApiPy.PyIpxCreateDevice(devInfo) if platform.system()=='Windows' else libIpxCameraApiPy.PyIpxCreateDevice(devInfo) 	
		err_code = IpxCameraApiPy.GetLastError() if platform.system()=='Windows' else libIpxCameraApiPy.GetLastError()	
		if err_code!=0:
			print ('Error code: ', err_code) 
			return 0
		print ('device model: ', devInfo.GetModel())
		tCnt = dev1.GetNumStreams()	
		if tCnt < 1 :		
			return 0
		else:		
			return dev1
			
	# This function creates the buffers queue
	def CreateDataStreamBuffers(self, data_stream):	
		bufSize = data_stream.GetBufferSize()	
		minNumBuffers = data_stream.GetMinNumBuffers()	
		list1 = []
		for x in range(minNumBuffers+1):
			list1.append(data_stream.CreateBuffer(bufSize))
		return list1

	# This function releases the created buffers queue
	def FreeDataStreamBuffers(self, data_stream, sbLst):
		for x in sbLst:
			data_stream.RevokeBuffer(x)
			
	def PixelTypeToBayerType(self, pixelType, isBGR):
		if pixelType == PixelType.BayerGR8 or pixelType == PixelType.BayerGR10 or pixelType == PixelType.BayerGR12:
			return cv.COLOR_BayerGR2BGR if isBGR else cv.COLOR_BayerGR2RGB
		elif pixelType == PixelType.BayerRG8 or pixelType == PixelType.BayerRG10 or pixelType == PixelType.BayerRG12:
			return cv.COLOR_BayerRG2BGR if isBGR else cv.COLOR_BayerRG2RGB
		elif pixelType == PixelType.BayerGB8 or pixelType == PixelType.BayerGB10 or pixelType == PixelType.BayerGB12:
			return cv.COLOR_BayerGB2BGR if isBGR else cv.COLOR_BayerGB2RGB
		# default
		#elif pixelType == BayerBG8 or pixelType == BayerBG10 or pixelType == BayerBG12:	
		return cv.COLOR_BayerBG2BGR if isBGR else cv.COLOR_BayerBG2RGB
		
	# Function to set Exposure parameters
	def SetupExposure(self, camera):
		#global g_expValue
		#global g_paramsFromPrompt

		pars = camera.GetCameraParameters()	

		# Set ExposureAuto = Off
		parAec = pars.GetEnum("ExposureAuto")	
		parAec.SetValueStr("Continuous")

		# Set ExposureMode = Timed 
		#parExposureMode = pars.GetEnum("ExposureMode")
		#parExposureMode.SetValueStr("Timed")

		# Set ExposureTime in microseconds
		#parExposureTime = pars.GetFloat("ExposureTime")
		#expMin = parExposureTime.GetMin()
		#expMax = parExposureTime.GetMax()
		#expCur = parExposureTime.GetValue()

		#if g_paramsFromPrompt :
		#	expVal=g_expValue
		#else:
		#print('Enter Exposure value in microseconds, Min=',expMin[1], 'Max=',expMax[1], 'Current=',expCur[1])
		#expVal = float(sys.stdin.readline()[:-1])
		
		#if expVal > expMax[1] or expVal < expMin[1] :
		#	print('Value ', expVal, 'is out of range')
		#else: 
		#	parExposureTime.SetValue(expVal)
		
	def SetupAec(self, camera):
		pars = camera.GetCameraParameters()	

		#print('Setup AEC')

		# Set ExposureAuto = Continuous
		parAec = pars.GetEnum("ExposureAuto")	
		parAec.SetValueStr("Continuous")

		# set AecExposureMin = 200us
		parAecExpMin = pars.GetInt("AecExposureMin")
		parAecExpMin.SetValue(200)

		# set AecExposureMax = 220us
		parAecExpMax = pars.GetInt("AecExposureMax")
		parAecExpMax.SetValue(20000)


		# set AecExposureMax = (MAX-MIN)/2
		#parAecExpMax = pars.GetInt("AecExposureMax")
		#aecExpMaxMax = parAecExpMax.GetMax()[1]
		#aecExpMaxMin = parAecExpMax.GetMin()[1]
		#parAecExpMax.SetValue((aecExpMaxMax-aecExpMaxMin)/2)
	
	# This function setups the AGC parameters of the camera
	# AGC / AEC function not included in models: POE-C2000, POE-C2400  
	def SetupAgc(self, camera):

		pars = camera.GetCameraParameters()	

		#print('Setup AGC')

		# Set GainAuto = Continuous
		parAgc = pars.GetEnum("GainAuto")	
		parAgc.SetValueStr("Continuous")

		# set AgcGainMin = 0.1dB
		#parAgcGainMin = pars.GetFloat("AgcGainMin")
		#parAgcGainMin.SetValue(1)

		# set AgcGainMax = 7dB
		#parAgcGainMax = pars.GetFloat("AgcGainMax")
		#parAgcGainMax.SetValue(7.0)

		#setAgcAecAicLuminanceType = Average
		parAgcAec = pars.GetEnum("AgcAecAicLuminanceType")
		parAgcAec.SetValueStr("Average")

		#setAgcAecAicSpeed = x6
		parAgcSpeed = pars.GetEnum("AgcAecAicSpeed")
		parAgcSpeed.SetValueStr("x6")

	# This function setups the Gain parameters of the camera
	def SetupGain(self, camera):
		#global g_gain
		#global g_paramsFromPrompt
		pars = camera.GetCameraParameters()	

		# Set GainAuto = Off
		parAgc = pars.GetEnum("GainAuto")	
		parAgc.SetValueStr("Continious")

		# Set Digital Gain =1 dB, DigitalOffset=0
		#parDigGain = pars.GetFloat("DigitalGain")
		#parDigGain.SetValue(1.0)
		#parDigOffset = pars.GetInt("DigitalOffset")
		#if(not parDigOffset):
		#	parDigOffset= pars.GetFloat("DigitalBlackLevel")
		#parDigOffset.SetValue(0)
			
		# Set Gain in dB
		#parGain = pars.GetFloat("Gain")
		#gainMin = parGain.GetMin()
		#gainMax = parGain.GetMax()
		#currGain = parGain.GetValue()

		#if g_paramsFromPrompt :
		#	gainVal=g_gain
		#else:
		#print('Enter Gain value in dB, Min=',gainMin[1], 'Max=',gainMax[1], 'Current=', currGain[1])
		#gainVal = float (sys.stdin.readline()[:-1])
		#if gainVal > gainMax[1] or gainVal < gainMin[1] :
		#	print('Value ', gainVal, 'is out of range')
		#else: 
		#	parGain.SetValue(gainVal)

	# Process image with OpenCV library here
	def AcquireImages(self, dev1,data_stream):	
		
		self.SetupGain(dev1)
		self.SetupExposure(dev1)
		self.SetupAec(dev1)
		self.SetupAgc(dev1)

		# Get PyIpxSystem object
		PyIpxSystem1 = libIpxCameraApiPy.PyIpxSystem()
		
		gPars = dev1.GetCameraParameters()
		gPars.SetIntegerValue("TLParamsLocked", 1)
		print("Send AcquisitionStart command.")
		data_stream.StartAcquisition()
		gPars.ExecuteCommand("AcquisitionStart")

		# get pixel type
		res, pixelType = gPars.GetEnumValue("PixelFormat")
		if not res:
			print("Error while reading PixelFormat parameter")
			return

		# image to display
		img = None
		x = 0
		reconnect_attempts = 0
		while True:
		# Acquire the image. Timeout = 1000ms (1 second). Use value of -1 for Infinite timeout
			buffer = data_stream.GetBuffer(1000)
			if buffer is None:
				err_code = data_stream.GetLastError()
				if err_code != 0:
					print('Error code: ', err_code)
					reconnect_attempts += 1
					if reconnect_attempts >= 6:
						print("Max reconnect attempts reached. Exiting.")
						break
					print("Attempting to reconnect...")
					dev1 = self.reconnect_device(PyIpxSystem1)
					if dev1 is None:
						print("Reconnection failed. Exiting.")
						break
					print("Reconnection successful. Continuing acquisition.")
					data_stream = dev1.GetStreamByIndex(0)
					self.CreateDataStreamBuffers(data_stream)
					self.AcquireImages(dev1, data_stream)
					reconnect_attempts = 0
				else:
					print("Buffer is None, but no error code. Continuing.")
					break
			print ('FrameID: ', x, 'W:', buffer.GetWidth(),' H:',buffer.GetHeight())
			if x % 2 == 1:
				#libIpxCameraApiPy.PySaveImage(buffer, "PyFrame%d." % (x) + "jpg") 	
				# convert raw data into numpy array
				img = np.array(buffer.GetBufferPtr()).reshape((buffer.GetHeight(), buffer.GetWidth()))
				
				######################################### OpenCV Code #########################################

				# check pixel type to decide if Bayer conversion is needed
				# if pixelType != PixelType.Mono8 and pixelType != PixelType.Mono10 and pixelType != PixelType.Mono12:
					
				# 	# convert pixel type to opencv bayer code
				# 	bayerCode = self.PixelTypeToBayerType(pixelType, False)
				# 	img = cv.cvtColor(img, bayerCode)

				# apply blur filter
				img = cv.GaussianBlur(img, (5, 5), 0)
				#img = cv.medianBlur(img, 5)
				
				# save raw image and png compressed
				# with open("PyFrame%d.raw" % (x), 'wb') as f:
				# 	f.write(buffer.GetBufferPtr())
				# 	cv.imwrite("PyFrame%d.png" % (x), img, (cv.IMWRITE_PNG_COMPRESSION, 0))
				
				#sending the image to the topic
				self.publisher_.publish(self.br.cv2_to_imgmsg(img, encoding='mono8'))

				###############################################################################################

			x +=1
			data_stream.QueueBuffer(buffer)

		# display output image
		#if not img is None:
			# OpenCV Code
			#hist = cv.calcHist([img],[0],None,[256],[0,256])
			#plt.subplot(121), plt.imshow(img)
			#plt.subplot(122), plt.plot(hist)
			#plt.show()
		
		print("Sending AcquisitionStop command to the device")
		gPars.ExecuteCommand("AcquisitionStop")
		data_stream.StopAcquisition(1)
		gPars.SetIntegerValue("TLParamsLocked", 0)

def main(args=None):
	#getting the arguments from the command line
	#if len(sys.argv)>1 :
	#	g_devNum=int(sys.argv[1])
	
	# Initialize the rclpy library
	rclpy.init(args=args)
  
	# Create the node
	image_publisher = ImagePublisher()
	
	# Get PyIpxSystem object
	PyIpxSystem1 = libIpxCameraApiPy.PyIpxSystem()

	# An example of how to register external GenTL
	# Note: use ReEnumerateDevices() of interface before calling GetDeviceInfoList()
	#if PyIpxSystem1.RegisterGenTLProvider(r"c:\Program Files\KAYA Instruments\Common\bin\KYFGLibGenTL.cti") == False:
	#	print('Unable to register Kaya cti')

	print(PyIpxSystem1.GetDisplayName())
	print('Interfaces available:' )
	
	# Select the Camera
	deviceInfo = image_publisher.SelectDevice(PyIpxSystem1)
	if deviceInfo != None: # none has been selected
		if deviceInfo != 0: # wrong index has been selected
        	# Connect to the camera
			dev1 = image_publisher.connectToDevice(deviceInfo)
			if dev1 != 0:
				print ('Open the stream to device')
				data_stream = dev1.GetStreamByIndex(0)
				print ('Create the buffers, size: ', data_stream.GetBufferSize())
				sbLst = image_publisher.CreateDataStreamBuffers(data_stream)
				print ('Acquire the images')			
				image_publisher.AcquireImages(dev1,data_stream)
				print ('Flush the buffers')
				data_stream.FlushBuffers(data_stream.Flush_AllDiscard)
				print ('Release the buffers')
				image_publisher.FreeDataStreamBuffers(data_stream, sbLst)
				print ('Close the stream')	
				data_stream.Release()
				print ('Disconnect the device')
				dev1.Release()		
			else:
				print ('Incorrect device')
		else:
			print ('Incorrect choice or no cameras found')
  	
	# Spin the node so the callback function is called.
	#rclpy.spin(image_publisher)
  
	# Destroy the node explicitly
	# (optional - otherwise it will be done automatically
	# when the garbage collector destroys the node object)
	image_publisher.destroy_node()
  
	# Shutdown the ROS client library for Python
	rclpy.shutdown()
  
if __name__ == '__main__':
  main()
