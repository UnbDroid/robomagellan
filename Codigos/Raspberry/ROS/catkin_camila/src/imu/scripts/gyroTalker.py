#!/usr/bin/env python
# license removed for brevity

import smbus
import rospy
import rosbag
from raspberry_msgs.msg import Gyro

def read_byte(adr):
    return bus.read_byte_data(address,adr)

def read_word(adrH,adrL):
    high = bus.read_byte_data(address,adrH)
    low = bus.read_byte_data(address,adrL)
    val = (high << 8) | low
    return val

def read_word_2c(adrH,adrL):
    val = read_word(adrH,adrL)
    if (val >= 0x8000):
        return -((65535 - val) + 1)
    else:
        return val

bus = smbus.SMBus(1)
address = 0x69

def gyroTalker():

    bag = rosbag.Bag('gyro.bag', 'w')
    
    pub = rospy.Publisher('gyroInfo', Gyro, queue_size=10)
    rospy.init_node('gyroInfo', anonymous=True)
    rate = rospy.Rate(10) # 10hz

    ctrl_reg_1 = 0x20
    ctrl_reg_2 = 0x21
    ctrl_reg_3 = 0x22
    ctrl_reg_4 = 0x23
    ctrl_reg_5 = 0x24

    bus.write_byte_data(address, ctrl_reg_1,0b00001111)
    bus.write_byte_data(address, ctrl_reg_2,0b00000000)
    bus.write_byte_data(address, ctrl_reg_3,0b00001000)
    bus.write_byte_data(address, ctrl_reg_4,0b00110000)
    bus.write_byte_data(address, ctrl_reg_5,0b00000000)

    msg = Gyro()
    
    while not rospy.is_shutdown():

        gyro_x = read_word_2c(0x29,0x28)*0.07
        gyro_y = read_word_2c(0x2B,0x2A)*0.07
        gyro_z = read_word_2c(0x2D,0x2C)*0.07

        msg.g_x = gyro_x
        msg.g_y = gyro_y
        msg.g_z = gyro_z
        
        rospy.loginfo(msg)
        pub.publish(msg)
        bag.write('gyro_data', msg);
    
        rate.sleep()

    bag.close();

if __name__ == '__main__':
    try:
        gyroTalker()
    except rospy.ROSInterruptException:
        pass
