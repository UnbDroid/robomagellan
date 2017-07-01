#!/usr/bin/env python

import rosbag
import rospy

bag = rosbag.Bag('/home/pi/Documents/robomagellan/Codigos/Raspberry/ROS/catkin_camila/src/imu/scripts/odom5.bag')
for topic, msg, t in bag.read_messages(topics = ['odom_data']):
    
    print t.secs*1000000000+t.nsecs, "\t", msg.x, "\t", msg.y
    #x = dir y = esq
    
bag.close();
