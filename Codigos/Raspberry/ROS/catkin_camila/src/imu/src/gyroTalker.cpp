#include <wiringPiI2C.h>
#include "ros/ros.h"
#include "raspberry_msgs/Gyro.h"

int read_word(int fd, int adr_h,int adr_l){

	short high = wiringPiI2CReadReg8 (fd,adr_h);
	int low = wiringPiI2CReadReg8 (fd,adr_l);
	int val = ((high << 8) + low);

	return val;

}


int main(int argc, char **argv){
 

	int ctrl_reg_1 = 0x20;
	int ctrl_reg_2 = 0x21;
	int ctrl_reg_3 = 0x22;
	int ctrl_reg_4 = 0x23;
	int ctrl_reg_5 = 0x24;
	
	int reg_x_h = 0x29;
	int reg_x_l = 0x28;
	int reg_y_h = 0x2B;
	int reg_y_l = 0x2A;
	int reg_z_h = 0x2D;
	int reg_z_l = 0x2C;

	short gyro_x = 0;
	short gyro_y = 0;
	short gyro_z = 0;

	int fd = wiringPiI2CSetup(0x69);

	wiringPiI2CWriteReg8 (fd, ctrl_reg_1, 15);
	wiringPiI2CWriteReg8 (fd, ctrl_reg_2, 0);
	wiringPiI2CWriteReg8 (fd, ctrl_reg_3, 8);
	wiringPiI2CWriteReg8 (fd, ctrl_reg_4, 48);
	wiringPiI2CWriteReg8 (fd, ctrl_reg_5, 0);

	ros::init(argc, argv, "gyroTalker");
	ros::NodeHandle n;
	ros::Publisher chatter_pub = n.advertise<raspberry_msgs::Gyro>("gyroInfo", 1000);
	ros::Rate loop_rate(10);
	
	raspberry_msgs::Gyro msg;

	int count = 0;
	while (ros::ok()){

		gyro_x = read_word(fd,reg_x_h,reg_x_l);
		gyro_y = read_word(fd,reg_y_h,reg_y_l);
		gyro_z = read_word(fd,reg_z_h,reg_z_l);

		msg.g_x = gyro_x;
        	msg.g_y = gyro_y;
        	msg.g_z = gyro_z;

		ROS_INFO("%d", msg.g_x);
		ROS_INFO("%d", msg.g_y);
		ROS_INFO("%d", msg.g_z);

		chatter_pub.publish(msg);
	    
		ros::spinOnce();
	
	    	loop_rate.sleep();
	    	++count;
	}
	
	
 return 0;
}