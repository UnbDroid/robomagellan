#include <wiringPiI2C.h>
#include "ros/ros.h"
#include "raspberry_msgs/Mag.h"
#include "raspberry_msgs/ParamMag.h"
#include <time.h>
#include "rosbag/bag.h"
#include <rosbag/view.h>
#include <boost/foreach.hpp>


#define DEBUG

#define foreach BOOST_FOREACH

#define SCALE 0.00152

#define t 0.0001 

 //bias e fator dse escala de cada eixo do sensor
//#define BX -0.0618718
//#define BY -0.0261594
//#define BZ -0.571556
//#define SX 1.02559
//#define SY 0.987607 #define foreach BOOST_FOREACH
//#define SZ 0.97193

ros::Time tempo;

int read_word(int fd, int adr_h,int adr_l){

	short high = wiringPiI2CReadReg8 (fd,adr_h);
//	ROS_INFO("High %d",high);
	int low = wiringPiI2CReadReg8 (fd,adr_l);
//	ROS_INFO("Low %d",low);
	int val = ((high << 8) + low);
//	ROS_INFO("Val %d", val);
	return val;

}


int main(int argc, char **argv){

	float bx = 7.5,by = 0,bz = 3,sx = 0.943,sy = 0.996,sz = 0.827;

	int Register_A = 0x00;
	int Register_B = 0x01;
	int Register_Mode = 0x02;
   	int Register_XL = 0x04;
   	int Register_XH = 0x03;
   	int Register_YL = 0x08;
   	int Register_YH = 0x07;
   	int Register_ZL = 0x06;
   	int Register_ZH = 0x05;

	short mag_x = 0;
	short mag_y = 0;
	short mag_z = 0;

	int fd = wiringPiI2CSetup(0x1E);
	ROS_INFO("Sera que abriu? %d", fd);

	wiringPiI2CWriteReg8 (fd, Register_A,  0x38);  //
	wiringPiI2CWriteReg8 (fd, Register_B,  0x60); //
	wiringPiI2CWriteReg8 (fd, Register_Mode,  0x00); 

	ros::init(argc, argv, "mag");
	ros::NodeHandle n;
	ros::Publisher chatter_pub = n.advertise<raspberry_msgs::Mag>("magInfo", 1000);
	ros::Rate loop_rate(25);

// Leitura parametros
//------------------------------------------------------------------
/*	rosbag::Bag bagParam;
        bagParam.open("/home/pi/Documents/robomagellan/Codigos/Raspberry/ROS/catkin_camila/parametrosMag.bag", rosbag::bagmode::Read);

 	std::vector<std::string> topics;
    	topics.push_back(std::string("param_mag"));
   
    	rosbag::View view(bagParam, rosbag::TopicQuery(topics));

	foreach(rosbag::MessageInstance const m, view){
		raspberry_msgs::ParamMag::ConstPtr s = m.instantiate<raspberry_msgs::ParamMag>();
		if (s != NULL){
			bx = s->bx;
			by = s->by;
			bz = s->bz;
			sx = s->sx;
			sy = s->sy;
			sz = s->sz;
		
		}
	}

	bagParam.close();*/
//-------------------------------------------------------------------

	//bag.open("acc.bag", rosbag::bagmode::Write);
	
	raspberry_msgs::Mag msg;

	int count = 0;
	while (ros::ok()){

		//leituras raw
		
		mag_x = read_word(fd,Register_XH,Register_XL);
		mag_y = read_word(fd,Register_YH,Register_YL);
		mag_z = read_word(fd,Register_ZH,Register_ZL);
		ROS_INFO("x: %f", mag_x*SCALE*t*1000000.0);
                ROS_INFO("y: %f", mag_y*SCALE*t*1000000.0);
                ROS_INFO("z: %f", mag_z*SCALE*t*1000000.0);
		
		msg.m_x = ((mag_x*SCALE*t)*1000000.0 - bx)/sx;
       		 msg.m_y = ((mag_y*SCALE*t)*1000000.0- by)/sy;
       		 msg.m_z = ((mag_z*SCALE*t)*1000000.0- bz)/sz;
		tempo = ros::Time::now();
		msg.tempo = tempo.toNSec() * 1e-6;
		
		#ifdef DEBUG
		ROS_INFO("x: %f", msg.m_x);
		ROS_INFO("y: %f", msg.m_y);
		ROS_INFO("z: %f", msg.m_z);

		//bag.write("acc_data",ros::Time::now(),msg);
		#endif

		chatter_pub.publish(msg);
	    
		ros::spinOnce();
	
	    	loop_rate.sleep();
	    	++count;
	}

	//bag.close();	
	
 return 0;
}
