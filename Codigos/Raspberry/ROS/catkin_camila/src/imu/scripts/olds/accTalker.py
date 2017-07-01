#!/usr/bin/env python
# license removed for brevity

#chmod +x listener.py

import smbus
import rospy
import rosbag
from raspberry_msgs.msg import Acc

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
address = 0x68

def accTalker():
    
    bag = rosbag.Bag('acc.bag', 'w')
    
    pub = rospy.Publisher('accInfo', Acc, queue_size=10)
    rospy.init_node('accInfo', anonymous=True)
    rate = rospy.Rate(10) # 10hz

    #Register_2D = 0x2D
    #Register_XL = 0x32
    #Register_XH = 0x33
    #Register_YL = 0x34
    #Register_YH = 0x35
    #Register_ZL = 0x36
    #Register_ZH = 0x37

    Register_XL = 60;
    Register_XH = 59;
    Register_YL = 62;
    Register_YH = 61;
    Register_ZL = 64;
    Register_ZH = 63;
    Register_Scale = 28;

    bus.write_byte_data(address, Register_Scale,0x18)

    msg = Acc()
    
    while not rospy.is_shutdown():

        acc_x = read_word_2c(Register_XH,Register_XL)
        acc_y = read_word_2c(Register_YH,Register_YL)
        acc_z = read_word_2c(Register_ZH, Register_ZL)

        msg.a_x = acc_x
        msg.a_y = acc_y
        msg.a_z = acc_z
        
        rospy.loginfo(msg)
        pub.publish(msg)
        #bag.write('acc_data', msg);
    
        rate.sleep()

    bag.close();

if __name__ == '__main__':
    try:
        accTalker()
    except rospy.ROSInterruptException:
        pass
