#!/usr/bin/env python

import rosbag
import rospy

bag = rosbag.Bag('odom.bag')
for topic, msg, t in bag.read_messages('odom_data'):
    
    print msg.tempo,"\t", msg.x, "\t", msg.y
    #x = dir y = esq
    
bag.close();
