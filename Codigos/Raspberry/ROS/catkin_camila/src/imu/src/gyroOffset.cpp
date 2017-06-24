#include <wiringPiI2C.h>
#include "ros/ros.h"
#include "rosbag/bag.h"
#include "raspberry_msgs/ParamGyro.h"
#include <time.h>

ros::Time tempo;

#define SCALE 0.0609756

int read_word(int fd, int adr_h,int adr_l){

	short high = wiringPiI2CReadReg8 (fd,adr_h);
	int low = wiringPiI2CReadReg8 (fd,adr_l);
	int val = ((high << 8) + low);

	return val;

}

int main(int argc, char **argv){
 
/*
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
*/

	int reg_x_h = 67;
	int reg_x_l =68;
	int reg_y_h = 69;
	int reg_y_l = 70;
	int reg_z_h = 71;
	int reg_z_l = 72;
	int Register_Scale = 27;

	short gyro_x = 0;
	short gyro_y = 0;
	short gyro_z = 0;

	float g_x = 0.0;
	float g_y = 0.0;
	float g_z = 0.0;

	float offset_x = 0;
	float offset_y = 0;
	float offset_z = 0;

	int fd = wiringPiI2CSetup(0x68);

	/*
	wiringPiI2CWriteReg8 (fd, ctrl_reg_1, 15);
	wiringPiI2CWriteReg8 (fd, ctrl_reg_2, 0);
	wiringPiI2CWriteReg8 (fd, ctrl_reg_3, 8);
	wiringPiI2CWriteReg8 (fd, ctrl_reg_4, 48);
	wiringPiI2CWriteReg8 (fd, ctrl_reg_5, 0);
	*/
	
	wiringPiI2CWriteReg8 (fd, Register_Scale, 0x18);
	
	ros::init(argc, argv, "gyroTalker");
	ros::NodeHandle n;
	ros::Rate loop_rate(100);

	rosbag::Bag bag;
	bag.open("parametrosGyro.bag", rosbag::bagmode::Write);

	raspberry_msgs::ParamGyro msg;

	int count = 0;

	ros::Time tInicial = ros::Time::now();
	while ((ros::Time::now().toSec() - tInicial.toSec()) < 30){

		gyro_x = read_word(fd,reg_x_h,reg_x_l);
		gyro_y = read_word(fd,reg_y_h,reg_y_l);
		gyro_z = read_word(fd,reg_z_h,reg_z_l);

		g_x = gyro_x*SCALE;
        	g_y = gyro_y*SCALE;
        	g_z = gyro_z*SCALE;

		offset_x += g_x;
		offset_y += g_y;
		offset_z += g_z;

		ROS_INFO("%f", g_x);
		ROS_INFO("%f", g_y);
		ROS_INFO("%f", g_z);

		ros::spinOnce();
	
	    	loop_rate.sleep();
	    	++count;
	}
	
	msg.offset_x = offset_x/count;
	msg.offset_y = offset_y/count;
	msg.offset_z = offset_z/count;

	bag.write("param_gyro",ros::Time::now(),msg);
	
	ROS_INFO("\n\n");

	ROS_INFO("x: %f", msg.offset_x);
	ROS_INFO("y: %f", msg.offset_y);
	ROS_INFO("z: %f", msg.offset_z);

	bag.close();

 return 0;
}
