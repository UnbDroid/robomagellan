#!/usr/bin/env python

import rosbag
import rospy

bag = rosbag.Bag('/home/pi/Documents/robomagellan/Codigos/Raspberry/ROS/catkin_camila/src/imu/scripts/mag5.bag')
for topic, msg, t in bag.read_messages('mag_data'):

    print msg.tempo,"\t", msg.m_x, "\t", msg.m_y, "\t", msg.m_z
#    print msg.time
bag.close();
