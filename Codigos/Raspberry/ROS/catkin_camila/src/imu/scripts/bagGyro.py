#!/usr/bin/env python

import rosbag
import rospy

bag = rosbag.Bag('/home/pi/Documents/robomagellan/Codigos/Raspberry/ROS/catkin_camila/src/imu/scripts/gyro5.bag')
for topic, msg, t in bag.read_messages('gyro_data'):

	print msg.time,"\t", msg.g_x, "\t", msg.g_y, "\t", msg.g_z
#    print msg.time
bag.close();
