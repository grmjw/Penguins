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
import logging

logger = logging.getLogger(__name__)

#This class defines an enumeration of flags using the IntFlag class from the enum module in Python. 
class PixelTypeFlags(enum.IntFlag):
	PixelTypeIdBit = 0
	PixelTypeIdMask = 0xFFFF << PixelTypeIdBit
	PixelSizeOccupyBit = 16
	PixelSizeOccupyMask = 0xFF << PixelSizeOccupyBit
	PixelChromaticityBit = 24
	PixelChromaticityMask = 0xFF << PixelChromaticityBit

#This class is an enumeration (enum) that defines various pixel types along with their corresponding hexadecimal values. 
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

#This class is responsible for publishing images to the 'cam_frames' topic. 
class ImagePublisher(Node):
	"""
	Create an ImagePublisher class, which is a subclass of the Node class.
	"""
	def __init__(self):
		"""
		Class constructor to set up the node
		"""
		# Initiate the Node class's constructor and give it a name
		logger.debug('Initializing the Node class constructor')		
		super().__init__('image_publisher')

		# Create the publisher. This publisher will publish an Image
		# to the video_frames topic. The queue size is 10 messages.
		logger.debug('creating the publisher')
		self.publisher_ = self.create_publisher(Image, 'cam_frames', 100)
 
		# Used to convert between ROS and OpenCV images
		logger.debug('create CVBridge object')
		self.br = CvBridge()
    
	# This function allows user to select the interface and camera to get the IpxCam::DeviceInfo object
	def SelectDevice(self, ipxSystem):
		
		# Get Interface list
		logger.debug('get the interface list')
		intLst = ipxSystem.GetInterfaceList()
		if(len(intLst)<1):
			logger.error('No interface found')
			return None

		# Get list of cameras connected to each interface 
		devList=[]
		gv_num=0
		for infs in intLst:
			logger.debug('currently checking interface: ' + infs.GetDescription())
			# Get list of cameras connected to the current interface
			infs.ReEnumerateDevices(500)
			devListInt = infs.GetDeviceInfoList()
			for dv in devListInt:
				devList.append(dv)
				logger.debug(dv.GetModel() + ' connected to interface: ' + infs.GetDescription())
		
		#Checks the number of devices
		if(len(devList)<1):
			logger.error('No device found')
			return None
		#should figure out how to log the thing you are connecting to
		return devList[0]
	
	def reconnect_device(self, ipxSystem):
		for attempt in range(6):
			logger.info("Attempt %d to reconnect", attempt)
			deviceInfo = self.SelectDevice(ipxSystem)
			if deviceInfo:
				dev1 = self.connectToDevice(deviceInfo)
				if dev1:
					logger.info('reconnected to device')
					return dev1
			logger.error('failed to reconnect. Waiting 10 seconds before retrying')
			time.sleep(10)
		logger.critical('failed to reconnect after 6 attempts')
		return None

	# This function connects to the camera, specified by devInfo argument
	def connectToDevice(self, devInfo):
		logger.info('connecting to: ' + devInfo.GetDisplayName()) 
		dev1 = libIpxCameraApiPy.PyIpxCreateDevice(devInfo) 	
		err_code = libIpxCameraApiPy.GetLastError()	
		if err_code!=0:
			logger.error('Error code: %d', err_code)
			return 0
		tCnt = dev1.GetNumStreams()	
		if tCnt < 1 :		
			return 0
		else:		
			return dev1
			
	# This function creates the buffers queue
	def CreateDataStreamBuffers(self, data_stream):	
		bufSize = data_stream.GetBufferSize()	
		logger.debug('Buffer size: %d', bufSize)
		minNumBuffers = data_stream.GetMinNumBuffers()	
		logger.debug('Minimum number of buffers: %d', minNumBuffers)
		list1 = []
		for x in range(minNumBuffers+1):
			logger.debug('created buffer number %d', x)
			list1.append(data_stream.CreateBuffer(bufSize))
		return list1

	# This function releases the created buffers queue
	def FreeDataStreamBuffers(self, data_stream, sbLst):
		for x in sbLst:
			data_stream.RevokeBuffer(x)
		logger.debug('Revoked buffers')

	#This function is used to convert a pixel type to an OpenCV Bayer conversion code. 	
	def PixelTypeToBayerType(self, pixelType, isBGR):
		if pixelType == PixelType.BayerGR8 or pixelType == PixelType.BayerGR10 or pixelType == PixelType.BayerGR12:
			logger.debug('recolouring pixel of type %r', pixelType)
			return cv.COLOR_BayerGR2BGR if isBGR else cv.COLOR_BayerGR2RGB
		elif pixelType == PixelType.BayerRG8 or pixelType == PixelType.BayerRG10 or pixelType == PixelType.BayerRG12:
			logger.debug('recolouring pixel of type %r', pixelType)
			return cv.COLOR_BayerRG2BGR if isBGR else cv.COLOR_BayerRG2RGB
		elif pixelType == PixelType.BayerGB8 or pixelType == PixelType.BayerGB10 or pixelType == PixelType.BayerGB12:
			logger.debug('recolouring pixel of type %r', pixelType)
			return cv.COLOR_BayerGB2BGR if isBGR else cv.COLOR_BayerGB2RGB
		# default	
		return cv.COLOR_BayerBG2BGR if isBGR else cv.COLOR_BayerBG2RGB
		
	# Function to set Exposure parameters
	def SetupExposure(self, camera):
		pars = camera.GetCameraParameters()	
		
		parAec = pars.GetEnum("ExposureAuto")	
		logger.debug('set exposure to continious')
		parAec.SetValueStr("Continuous")
	
	#This method configures the Auto Exposure Control (AEC) parameters for a camera. 
	def SetupAec(self, camera):
		pars = camera.GetCameraParameters()	
		
		parAec = pars.GetEnum("ExposureAuto")	
		logger.debug('set AEC to continuous')
		parAec.SetValueStr("Continuous")
		
		parAecExpMin = pars.GetInt("AecExposureMin")
		logger.debug('set minimum AEC exposure to 200')
		parAecExpMin.SetValue(200)
		
		parAecExpMax = pars.GetInt("AecExposureMax")
		logger.debug('set maximum AEC exposure to 200')
		parAecExpMax.SetValue(20000)
	
	# This function setups the AGC parameters of the camera
	# AGC / AEC function not included in models: POE-C2000, POE-C2400  
	def SetupAgc(self, camera):
		pars = camera.GetCameraParameters()	
		
		parAgc = pars.GetEnum("GainAuto")	
		logger.debug('set AGC to continuous')
		parAgc.SetValueStr("Continuous")

		parAgcAec = pars.GetEnum("AgcAecAicLuminanceType")
		logger.debug('set AGC/AEC function to average')
		parAgcAec.SetValueStr("Average")

		parAgcSpeed = pars.GetEnum("AgcAecAicSpeed")
		logger.debug('set AGC speed to x6')
		parAgcSpeed.SetValueStr("x6")

	# Process image with OpenCV library here
	def AcquireImages(self, dev1, data_stream):	
		
		logger.info('set device parameters')
		self.SetupExposure(dev1)
		self.SetupAec(dev1)
		self.SetupAgc(dev1)

		# Get PyIpxSystem object
		PyIpxSystem1 = libIpxCameraApiPy.PyIpxSystem()
		
		gPars = dev1.GetCameraParameters()
		gPars.SetIntegerValue("TLParamsLocked", 1)
		logger.debug('send aquisition start command')
		data_stream.StartAcquisition()
		gPars.ExecuteCommand("AcquisitionStart")

		# get pixel type
		logger.debug('getting pixel type')
		res, pixelType = gPars.GetEnumValue("PixelFormat")
		if not res:
			logger.error("Error while reading PixelFormat parameter")
			return

		img = None # image to display
		x = 0
		reconnect_attempts = 0
		# Acquire the image. Timeout = 1000ms (1 second). Use value of -1 for Infinite timeout
		while True:
			buffer = data_stream.GetBuffer(1000)
			if buffer is None:
				err_code = data_stream.GetLastError()
				if err_code != 0:
					logger.error('Error code: %d', err_code)
					reconnect_attempts += 1
					if reconnect_attempts >= 6:
						logger.critical("Max reconnect attempts reached. Exiting.")
						break
					logger.info("Attempting to reconnect...")
					dev1 = self.reconnect_device(PyIpxSystem1)
					if dev1 is None:
						logger.error("Reconnection failed. Exiting.")
						break
					logger.info("Reconnection successful. Continuing acquisition.")
					logger.debug('Open the stream to device')
					data_stream = dev1.GetStreamByIndex(0)
					logger.debug('Create buffers')
					self.CreateDataStreamBuffers(data_stream)
					logger.debug('Acquire the images')
					self.AcquireImages(dev1, data_stream)
					reconnect_attempts = 0
				else:
					logger.warning("Buffer is None, but no error code. Continuing.")
					break
			logger.info('Frame %d received', x)
			logger.debug('frame width: %d and frame height: %d', buffer.GetWidth(), buffer.GetHeight())
			if x % 2 == 1:
				#uncomment this command to save each frame to a jpg file
				#libIpxCameraApiPy.PySaveImage(buffer, "PyFrame%d." % (x) + "jpg") 
					
				# convert raw data into numpy array
				logger.debug('convert buffer data to np array')
				img = np.array(buffer.GetBufferPtr()).reshape((buffer.GetHeight(), buffer.GetWidth()))

				# check pixel type to decide if Bayer conversion is needed
				logger.debug('check for pixel conversion')
				if pixelType != PixelType.Mono8 and pixelType != PixelType.Mono10 and pixelType != PixelType.Mono12:
				 	# convert pixel type to opencv bayer code
				 	bayerCode = self.PixelTypeToBayerType(pixelType, False)
				 	img = cv.cvtColor(img, bayerCode)

				# apply blur filter
				logger.debug('apply blur filter')
				img = cv.GaussianBlur(img, (5, 5), 0)
				#img = cv.medianBlur(img, 5)
				
				#sending the image to the topic
				logger.info('publish frame %d', x)
				self.publisher_.publish(self.br.cv2_to_imgmsg(img))

			x +=1
			data_stream.QueueBuffer(buffer)
		
		logger.debug('Sending AcquisitionStop command')
		gPars.ExecuteCommand("AcquisitionStop")
		data_stream.StopAcquisition(1)
		gPars.SetIntegerValue("TLParamsLocked", 0)

def main(args=None):
	logging.basicConfig(stream=sys.stderr, level=logging.INFO)
	
	# Initialize the rclpy library
	rclpy.init(args=args)
  
	# Create the node
	logger.info('Initializing image publisher node')
	image_publisher = ImagePublisher()
	
	# Get PyIpxSystem object
	logger.debug('Intializing Ipx library')
	PyIpxSystem1 = libIpxCameraApiPy.PyIpxSystem()

	# An example of how to register external GenTL
	# Note: use ReEnumerateDevices() of interface before calling GetDeviceInfoList()
	#if PyIpxSystem1.RegisterGenTLProvider(r"c:\Program Files\KAYA Instruments\Common\bin\KYFGLibGenTL.cti") == False:
	#	print('Unable to register Kaya cti')

	logger.debug('Ipx Library object: ' + PyIpxSystem1.GetDisplayName())
	
	# Select the Camera
	logger.info('Selecting device')
	deviceInfo = image_publisher.SelectDevice(PyIpxSystem1)
	if deviceInfo != None: # none has been selected
		if deviceInfo != 0: # wrong index has been selected
        	# Connect to the camera
			logger.info('Device selected')
			logger.info('Connecting to device')
			dev1 = image_publisher.connectToDevice(deviceInfo)
			if dev1 != 0:
				logger.info('Device connected')
				logger.debug('Open the stream to device')
				data_stream = dev1.GetStreamByIndex(0)
				logger.debug('Create buffers')
				sbLst = image_publisher.CreateDataStreamBuffers(data_stream)
				logger.debug('Acquire the images')		
				image_publisher.AcquireImages(dev1,data_stream)
				logger.debug('Flush buffers')
				data_stream.FlushBuffers(data_stream.Flush_AllDiscard)
				logger.debug('Release the buffers')
				image_publisher.FreeDataStreamBuffers(data_stream, sbLst)
				logger.debug('Close the stream')	
				data_stream.Release()
				logger.info('Disconnect device')
				dev1.Release()		
			else:
				logger.critical('Incorrect device')
		else:
			logger.critical('Incorrect choice or no cameras found')
	else:
		logger.critical('Unable to select a device')
  
	# Destroy the node explicitly
	# (optional - otherwise it will be done automatically
	# when the garbage collector destroys the node object)
	logger.info('Destroying image publisher node')
	image_publisher.destroy_node()
  
	# Shutdown the ROS client library for Python
	rclpy.shutdown()
  
if __name__ == '__main__':
  main()
