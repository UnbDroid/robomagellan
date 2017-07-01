#!/usr/bin/env python

import rospy
import rosbag
from std_msgs.msg import Int32, String

bag = rosbag.Bag('test.bag', 'w')
i = Int32()
i.data = 42
bag.write('numbers', i);
bag.close();
