#!/usr/bin/env python

import rosbag
import rospy

bag = rosbag.Bag('acc.bag')
for topic, msg, t in bag.read_messages('acc_data'):
    
    print msg.time,"\t", msg.a_x, "\t", msg.a_y, "\t", msg.a_z
bag.close();
