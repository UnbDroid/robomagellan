#!/usr/bin/env python

import rosbag
import rospy

bag = rosbag.Bag('gyro.bag')
for topic, msg, t in bag.read_messages('gyro_data'):

print msg.time,"\t", msg.g_x, "\t", msg.g_y, "\t", msg.g_z
#    print msg.time
bag.close();
