#!/usr/bin/env python

import rosbag
import rospy

bag = rosbag.Bag('/home/pi/Documents/robomagellan/Codigos/Raspberry/ROS/catkin_camila/src/imu/scripts/gpsUBX5.bag')
for topic, msg, t in bag.read_messages('gps_data'):
##    print "valid: ", msg.valid
##    print "lat: ", msg.lat
##    print "lng: ", msg.lng
##    print "alt: ", msg.alt
##    print "speed: ", msg.speed
##    print "hdop: ", msg.hdop
##    print "vdop: ", msg.vdop
##    print "pdop: ", msg.pdop

    print msg.tempo , "\t", msg.gpsFixOk , "\t", msg.gpsFix ,"\t", msg.ecefX, "\t", msg.ecefY,"\t", msg.ecefZ , "\t", msg.pAcc, "\t", msg.lat , "\t", msg.lng , "\t", msg.velN , "\t", msg.velE , "\t", msg.velD, "\t", msg.cAcc ,"\t", msg.sAcc 
bag.close();
