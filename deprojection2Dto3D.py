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
        depth_to_color_extrin = depth_frame.profile.get_extrinsics_to(
            color_frame.profile)

        # print(depth_intrin.ppx, depth_intrin.ppy)

        # Convert images to numpy arrays
        depth_image = np.asanyarray(depth_frame.get_data())
        color_image = np.asanyarray(color_frame.get_data())

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
        cv2.imshow('depth_colormap',depth_colormap)

        #adaptive thresholding coming up
        gray = cv2.cvtColor(depth_colormap, cv2.COLOR_RGB2GRAY)
        binary = cv2.adaptiveThreshold(gray,255,cv2.ADAPTIVE_THRESH_MEAN_C,cv2.THRESH_BINARY,11,8)
        #cv2.imshow('binary',binary)
        contours, hierarchy = cv2.findContours(binary, cv2.RETR_TREE, cv2.CHAIN_APPROX_SIMPLE)[-2:]
        adaptive = cv2.drawContours(depth_colormap,contours,-1,(0,255,0),3)
        #cv2.namedWindow('Realsense Contours',cv2.WINDOW_AUTOSIZE)
        #cv2.imshow('Realsense Contours',adaptive)
        # IMPORTANT: DON'T PUT THE COLOR IMAGE DISPLAY CODE AFTER THIS> IT MERGES WITH THE CONTOUR CODE




        # Stack both images horizontally
        #images = np.hstack((color_image, depth_colormap))

        # Show images
        #
        #cv2.imshow('RealSense', color_image)
        #cv2.namedWindow('Realsense Depth',cv2.WINDOW_AUTOSIZE)
        #cv2.imshow('Realsense Depth',depth_colormap)
        #cv2.namedWindow('Realsense Contours',cv2.WINDOW_AUTOSIZE)
        #cv2.imshow('Realsense Contours',adaptive)
        cv2.waitKey(1)
        #cv2.imshow('Contours',adaptive)

finally:

    # Stop streaming
    pipeline.stop()