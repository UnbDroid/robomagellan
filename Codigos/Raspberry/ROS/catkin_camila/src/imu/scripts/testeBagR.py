#!/usr/bin/env python

import rosbag
import rospy

bag = rosbag.Bag('gyro.bag')
for topic, msg, t in bag.read_messages('gyro_data'):
    print "x: ", msg.g_x
    print "y: ", msg.g_y
    print "z: ", msg.g_z
bag.close();
