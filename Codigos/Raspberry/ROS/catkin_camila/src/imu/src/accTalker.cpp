#include <wiringPiI2C.h>
#include "ros/ros.h"
#include "raspberry_msgs/Acc.h"

int read_word(int fd, int adr_h,int adr_l){

	short high = wiringPiI2CReadReg8 (fd,adr_h);
	int low = wiringPiI2CReadReg8 (fd,adr_l);
	int val = ((high << 8) + low);

	return val;

}


int main(int argc, char **argv){

	int Register_2D = 0x2D;
   	int Register_XL = 0x32;
   	int Register_XH = 0x33;
   	int Register_YL = 0x34;
   	int Register_YH = 0x35;
   	int Register_ZL = 0x36;
   	int Register_ZH = 0x37;
 

	short acc_x = 0;
	short acc_y = 0;
	short acc_z = 0;

	int fd = wiringPiI2CSetup(0x53);

	wiringPiI2CWriteReg8 (fd, Register_2D, 8);

	ros::init(argc, argv, "acc");
	ros::NodeHandle n;
	ros::Publisher chatter_pub = n.advertise<raspberry_msgs::Acc>("accInfo", 1000);
	ros::Rate loop_rate(10);
	
	raspberry_msgs::Acc msg;

	int count = 0;
	while (ros::ok()){

		acc_x = read_word(fd,Register_XH,Register_XL);
		acc_y = read_word(fd,Register_YH,Register_YL);
		acc_z = read_word(fd,Register_ZH,Register_ZL);

		msg.a_x = acc_x;
        	msg.a_y = acc_y;
        	msg.a_z = acc_z;

		ROS_INFO("%d", msg.a_x);
		ROS_INFO("%d", msg.a_y);
		ROS_INFO("%d", msg.a_z);

		chatter_pub.publish(msg);
	    
		ros::spinOnce();
	
	    	loop_rate.sleep();
	    	++count;
	}
	
	
 return 0;
}