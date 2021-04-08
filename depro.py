import pyrealsense2 as rs
import numpy as np
import cv2
import os

# Configure depth and color streams
pipeline = rs.pipeline()
config = rs.config()
config.enable_stream(rs.stream.depth, 640, 480, rs.format.z16, 30)
config.enable_stream(rs.stream.color, 640, 480, rs.format.bgr8, 30)

# Start streaming
pipe_profile = pipeline.start(config)

j = 640 // 2
i = 480 // 2

try:
    while True:

        # Wait for a coherent pair of frames: depth and color
        frames = pipeline.wait_for_frames()
        depth_frame = frames.get_depth_frame()
        color_frame = frames.get_color_frame()
        adaptive_frame = frames.get_depth_frame()

        #pc = rs.pointcloud()
        #points = pc.calculate(depth_frame)
        #pc.map_to(color_frame)
        if not depth_frame or not color_frame:
            continue

        # Intrinsics & Extrinsics
        depth_intrin = depth_frame.profile.as_video_stream_profile().intrinsics
        color_intrin = color_frame.profile.as_video_stream_profile().intrinsics
        #depth_to_color_extrin = depth_frame.profile.get_extrinsics_to(
        #    color_frame.profile)

        # print(depth_intrin.ppx, depth_intrin.ppy)

        # Convert images to numpy arrays
        depth_image = np.asanyarray(depth_frame.get_data())
        color_image = np.asanyarray(color_frame.get_data())
        adaptive_image = np.asanyarray(adaptive_frame.get_data())

        depth = depth_frame.get_distance(j, i)
        depth_point = rs.rs2_deproject_pixel_to_point(
            depth_intrin, [j, i], depth)
        text = "%.5lf, %.5lf, %.5lf\n" % (
            depth_point[0], depth_point[1], depth_point[2])
        print(text)
        color_image = cv2.circle(color_image,(j,i),2,(0,0,255),2)                    

         # Apply colormap on depth image (image must be converted to 8-bit per pixel first)
        depth_colormap = cv2.applyColorMap(cv2.convertScaleAbs(
            depth_image, alpha=0.03), cv2.COLORMAP_JET)
        adaptive_colormap = cv2.applyColorMap(cv2.convertScaleAbs(
            adaptive_image,alpha=0.03), cv2.COLORMAP_BONE)
        cv2.imshow('ada',adaptive_colormap)

        #Simple Thresholding
        #gray = cv2.cvtColor(adaptive_colormap,cv2.COLOR_BGR2GRAY)
        #gray = np.copy(adaptive_colormap)
        #cv2.imshow('gray',gray)
        gray_pixel = adaptive_colormap[i,j]
        print(gray_pixel[0])

        if( depth_point[2] != 0):



        	lower_black = np.array([gray_pixel[0],gray_pixel[1],gray_pixel[2]])
        	upper_black = np.array([gray_pixel[0],gray_pixel[1],gray_pixel[2]])
        	mask = cv2.inRange(adaptive_colormap,lower_black,upper_black)
        	cv2.imshow('mask',mask)

        	masked_image = np.copy(adaptive_colormap)
        	masked_image[mask != 0] = [255,255,255]
        	#cv2.imshow('masked_image',masked_image)

        	binary = cv2.adaptiveThreshold(mask,255,cv2.ADAPTIVE_THRESH_MEAN_C,cv2.THRESH_BINARY,11,8)
        	#cv2.imshow('binary',binary)
        	contours, hierarchy = cv2.findContours(binary, cv2.RETR_TREE, cv2.CHAIN_APPROX_SIMPLE)[-2:]
        	adaptive = cv2.drawContours(adaptive_colormap,contours,-1,(0,255,0),3)
        	#cv2.namedWindow('Realsense Contours',cv2.WINDOW_AUTOSIZE)
        	#cv2.imshow('Realsense Contours',adaptive)
        	# IMPORTANT: DON'T PUT THE COLOR IMAGE DISPLAY CODE AFTER THIS> IT MERGES WITH THE CONTOUR CODE
        	cv2.imshow('adaptive',adaptive)

        	#c = max(contours,key = cv2.contourArea)
        	#adaptive = cv2.drawContours(adaptive_colormap,c,-1,(0,255,0),3)
        	#cv2.imshow('adaptive',adaptive)





        	# Stack both images horizontally
        	#images = np.hstack((color_image, depth_colormap))

        	# Show images
        	#cv2.namedWindow('RealSense', cv2.WINDOW_AUTOSIZE)
        	#cv2.imshow('RealSense', images)
        	cv2.imshow('color',color_image)
        	#cv2.imshow('Realsense_adaptive',adaptive_colormap)
        	cv2.waitKey(1)

finally:

    # Stop streaming
    pipeline.stop()