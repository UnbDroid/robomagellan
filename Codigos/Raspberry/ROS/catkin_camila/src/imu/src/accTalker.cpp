#include <wiringPiI2C.h>
#include "ros/ros.h"
#include "raspberry_msgs/Acc.h"
#include "raspberry_msgs/ParamAcc.h"
#include <time.h>
#include "rosbag/bag.h"
#include <rosbag/view.h>
#include <boost/foreach.hpp>
#include "math.h"

#define DEBUG

#define foreach BOOST_FOREACH

#define SCALE 0.0039

#define g 9.80665

 //bias e fator dse escala de cada eixo do sensor
//#define BX -0.0618718
//#define BY -0.0261594
//#define BZ -0.571556
//#define SX 1.02559
//#define SY 0.987607
 #define foreach BOOST_FOREACH
//#define SZ 0.97193

rosbag::Bag bag;
ros::Time tempo;

int read_word(int fd, int adr_h,int adr_l){

	short high = wiringPiI2CReadReg8 (fd,adr_h);
	int low = wiringPiI2CReadReg8 (fd,adr_l);
	int val = ((high << 8) + low);

	return val;

}


int main(int argc, char **argv){

	float bx,by,bz,sx,sy,sz;

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
	ros::Rate loop_rate(25);

// Leitura parametros
//------------------------------------------------------------------
	rosbag::Bag bagParam;
        bagParam.open("/home/pi/Documents/robomagellan/Codigos/Raspberry/ROS/catkin_camila/parametrosAcc.bag", rosbag::bagmode::Read);

 	std::vector<std::string> topics;
    	topics.push_back(std::string("param_acc"));
   
    	rosbag::View view(bagParam, rosbag::TopicQuery(topics));

	foreach(rosbag::MessageInstance const m, view){
		raspberry_msgs::ParamAcc::ConstPtr s = m.instantiate<raspberry_msgs::ParamAcc>();
		if (s != NULL){
			bx = s->bx;
			by = s->by;
			bz = s->bz;
			sx = s->sx;
			sy = s->sy;
			sz = s->sz;
		
		}
	}

	bagParam.close();
//-------------------------------------------------------------------

	bag.open("acc.bag", rosbag::bagmode::Write);
	
	raspberry_msgs::Acc msg;

	int count = 0;
	while (ros::ok()){

		//leituras raw
		acc_x = read_word(fd,Register_XH,Register_XL);
		acc_y = read_word(fd,Register_YH,Register_YL);
		acc_z = read_word(fd,Register_ZH,Register_ZL);
		
		
		msg.a_x = (acc_x*SCALE*g - bx)/sx;
		msg.a_x = abs(msg.a_x) > 1 ? msg.a_x:0;
        	msg.a_y = (acc_y*SCALE*g - by)/sy;
		msg.a_y = abs(msg.a_y) > 1 ? msg.a_y:0;
        	msg.a_z = (acc_z*SCALE*g - bz)/sz;
		tempo = ros::Time::now();
		msg.time = tempo.toNSec() * 1e-6;
		
		#ifdef DEBUG
		ROS_INFO("x: %f", msg.a_x);
		ROS_INFO("y: %f", msg.a_y);
		ROS_INFO("z: %f", msg.a_z);

		bag.write("acc_data",ros::Time::now(),msg);
		#endif

		chatter_pub.publish(msg);
	    
		ros::spinOnce();
	
	    	loop_rate.sleep();
	    	++count;
	}

	bag.close();	
	
 return 0;
}
