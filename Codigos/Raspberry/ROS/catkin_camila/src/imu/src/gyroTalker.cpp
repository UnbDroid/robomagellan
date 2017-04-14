#include <wiringPiI2C.h>
#include "ros/ros.h"
#include "raspberry_msgs/Gyro.h"
#include "raspberry_msgs/ParamGyro.h"
#include "rosbag/bag.h"
#include <time.h>
#include <rosbag/view.h>
#include <boost/foreach.hpp>

#define DEBUG

#define foreach BOOST_FOREACH

#define SCALE 0.07

#define PI 3.14159265359

#define FC 0.01


//rosbag::Bag bag;
ros::Time tempo;

int read_word(int fd, int adr_h,int adr_l){

	short high = wiringPiI2CReadReg8 (fd,adr_h);
	int low = wiringPiI2CReadReg8 (fd,adr_l);
	int val = ((high << 8) + low);

	return val;

}

float parseRadians(float degree){

	return degree*PI/180;

}

int main(int argc, char **argv){
 
	float offset_x, offset_y, offset_z;

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
	
	double g_x, g_y, g_z;
	double g_xAnt = 0;
	double g_yAnt = 0;
	double  g_zAnt = 0;
	double g_xEst, g_yEst, g_zEst;
	double g_xEstAnt = 0;
	double g_yEstAnt = 0;
	double  g_zEstAnt = 0;
	
	float RC = 1;(2*PI*FC);
	float alfa = RC/(RC+0.01);

	int fd = wiringPiI2CSetup(0x69);

	wiringPiI2CWriteReg8 (fd, ctrl_reg_1, 15);
	wiringPiI2CWriteReg8 (fd, ctrl_reg_2, 0);
	wiringPiI2CWriteReg8 (fd, ctrl_reg_3, 8);
	wiringPiI2CWriteReg8 (fd, ctrl_reg_4, 48);
	wiringPiI2CWriteReg8 (fd, ctrl_reg_5, 0);

	ros::init(argc, argv, "gyroTalker");
	ros::NodeHandle n;
	ros::Publisher chatter_pub = n.advertise<raspberry_msgs::Gyro>("gyroInfo", 1000);
	ros::Rate loop_rate(100);

//Leitura parametros
//-------------------------------------------------------------------
/*	rosbag::Bag bagParam;
	bagParam.open("/home/pi/Documents/robomagellan/Codigos/Raspberry/ROS/catkin_camila/parametrosGyro.bag", rosbag::bagmode::Read);

 	std::vector<std::string> topics;
    	topics.push_back(std::string("param_gyro"));
   
    	rosbag::View view(bagParam, rosbag::TopicQuery(topics));

	foreach(rosbag::MessageInstance const m, view){
		raspberry_msgs::ParamGyro::ConstPtr s = m.instantiate<raspberry_msgs::ParamGyro>();
		if (s != NULL){
			offset_x = s->offset_x;
			offset_y = s->offset_y;
			offset_z = s->offset_z;
		
		}
	}

	bagParam.close()*/;
//-------------------------------------------------------------------
	
	//bag.open("gyro.bag", rosbag::bagmode::Write);

	raspberry_msgs::Gyro msg;

	int count = 0;
	while (ros::ok()){

		gyro_x = read_word(fd,reg_x_h,reg_x_l);
		gyro_y = read_word(fd,reg_y_h,reg_y_l);
		gyro_z = read_word(fd,reg_z_h,reg_z_l);

		g_x = parseRadians(gyro_x*SCALE ) ;//- offset_x);
        g_y = parseRadians(gyro_y*SCALE ) ;//- offset_y);
        g_z = parseRadians(gyro_z*SCALE ); //- offset_z);

		//Filtro passa-alta para tirar a componente dc (offset)
		g_xEst = alfa*g_xEstAnt + alfa*(g_x - g_xAnt);
		g_xAnt= g_x;
		g_xEstAnt = g_xEst; 
		
		g_yEst = alfa*g_yEstAnt + alfa*(g_y - g_yAnt);
		g_yAnt = g_y;
		g_yEstAnt = g_yEst; 
		
		g_zEst = alfa*g_zEstAnt + alfa*(g_z - g_zAnt);
		g_zAnt = g_z;
		g_zEstAnt = g_zEst; 

		msg.g_x = g_xEst;
		msg.g_y = g_yEst;
		msg.g_z = g_zEst;

		tempo = ros::Time::now();
		msg.time = tempo.toNSec() * 1e-6;		

		#ifdef DEBUG
		ROS_INFO("%f", msg.g_x);
		ROS_INFO("%f", msg.g_y);
		ROS_INFO("%f", msg.g_z);	

		//bag.write("gyro_data",ros::Time::now(),msg);
		#endif

		chatter_pub.publish(msg);
	    
		ros::spinOnce();
	
	    loop_rate.sleep();
	    ++count;
	}
	
	//bag.close();
	
 return 0;
}
