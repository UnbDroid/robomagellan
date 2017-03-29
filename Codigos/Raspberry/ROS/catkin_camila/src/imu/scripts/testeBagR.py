#!/usr/bin/env python

import rosbag
import rospy

bag = rosbag.Bag('gps.bag')
for topic, msg, t in bag.read_messages('gps_data'):
    print "valid: ", msg.valid
    print "lat: ", msg.lat
    print "lng: ", msg.lng
    print "alt: ", msg.alt
    print "speed: ", msg.speed
    print "hdop: ", msg.hdop
    print "vdop: ", msg.vdop
    print "pdop: ", msg.pdop
bag.close();
