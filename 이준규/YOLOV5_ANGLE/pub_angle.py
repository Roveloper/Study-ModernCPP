#! /usr/bin/env python3
import rospy
# import actionlib
import tf
import math
import numpy as np
import pyrealsense2 as rs2
from sensor_msgs.msg import Image, CameraInfo
from array import array
from math import cos, sin, acos
from std_msgs.msg import Float64, Int64


trash_detected = False
x = 0
y = 0
x_center = 0
y_center = 0
angle_degrees = 0
angle = 0
depth = 0
intrinsics = None
base = 0
height = 170
quaternion=[0, 0, 0]
t = [0, 0]
goal_matrix=np.array((3,1),dtype = 'complex_')


def x_sub(data):
    global x_center
    x_center = data.data

    return x_center

def y_sub(data):
    global y_center
    y_center = data.data

    return y_center

def dep_sub(data):
    global depth
    if depth < 3500 and depth > 1000 :
        depth = data.data
    elif depth == 0 :
        pass
    else :
        depth = 1500
    
    return depth



def camera_info(cameraInfo):
    global intrinsics
    # import pdb; pdb.set_trace()
    if intrinsics:
        return
    intrinsics = rs2.intrinsics()
    intrinsics.width = cameraInfo.width
    intrinsics.height = cameraInfo.height
    # camera 렌즈의 위치값
    intrinsics.ppx = cameraInfo.K[2]
    intrinsics.ppy = cameraInfo.K[5]
    intrinsics.fx = cameraInfo.K[0]
    intrinsics.fy = cameraInfo.K[4]
    if cameraInfo.distortion_model == 'plumb_bob':
        intrinsics.model = rs2.distortion.brown_conrady
    elif cameraInfo.distortion_model == 'equidistant':
        intrinsics.model = rs2.distortion.kannala_brandt4
    intrinsics.coeffs = [i for i in cameraInfo.D]

    return intrinsics

def get_camera_position(intrinsics):
    # Extract the intrinsic parameters of the camera
    fx = intrinsics.fx
    fy = intrinsics.fy
    cx = intrinsics.ppx
    cy = intrinsics.ppy
    # Calculate the position of the camera in 3D space
    camera_pos = np.array([fx, fy, cx, cy])

    return camera_pos


# def Calculate_angle(x, y, z):
#     global angle
#     global angle_degrees
#     global depth


#     camera_pos = get_camera_position(intrinsics)
#     theta_x = math.atan2(x_center - camera_pos[2], camera_pos[0])
#     theta_y = math.atan2(y_center - camera_pos[3], camera_pos[1])
#     theta_z = math.atan2(depth, camera_pos[0])

#     angle = math.sqrt(theta_x ** 2 + theta_y ** 2 + theta_z ** 2)
#     angle_degrees = np.rad2deg(angle)

    
#     return angle, angle_degrees

def Calculate_angle(x, y, z):
    global angle
    global angle_degrees
    global depth

    camera_pos = get_camera_position(intrinsics)
    theta_x = math.atan2(x_center - camera_pos[2], camera_pos[0])
    theta_y = math.atan2(y_center - camera_pos[3], camera_pos[1])
    theta_z = math.atan2(depth, camera_pos[0])

    angle = math.sqrt(theta_x ** 2 + theta_y ** 2 + theta_z ** 2)
    angle_degrees = np.rad2deg(angle)

    # check if the angle is positive or negative and print accordingly
    if theta_x >= 0:
        print(f"Angle: {angle_degrees} degrees (right)")
    else:
        print(f"Angle: {-angle_degrees} degrees (left)")

    return angle, angle_degrees
def bounding_boxes_callback(x ,y):
    
    global trash_detected

    if x == 0 and y == 0 :
        trash_detected = False
    else :
        trash_detected = True
        print('find bottle')
    return trash_detected




if __name__ == '__main__':
    rospy.init_node('trash_collector')

    # bounding_boxes_sub = rospy.Subscriber('/yolov5/detections', BoundingBoxes, bounding_boxes_callback)
    depth_sub = rospy.Subscriber('/depth', Int64, dep_sub)
    x_center_sub = rospy.Subscriber('x_center_value', Int64, x_sub)
    y_center_sub = rospy.Subscriber('y_center_value', Int64, y_sub)
    sub_info = rospy.Subscriber('/camera/depth/camera_info', CameraInfo, camera_info)

    
    rate = rospy.Rate(10)
    while not rospy.is_shutdown():
        bounding_boxes_callback(x_center, y_center)
        if trash_detected == True:
            Calculate_angle(x_center, y_center, depth)
            # print(angle_degrees)
            trash_detected == False

        else :
            print('There is no object!!!')
        rate.sleep()

    rospy.spin()