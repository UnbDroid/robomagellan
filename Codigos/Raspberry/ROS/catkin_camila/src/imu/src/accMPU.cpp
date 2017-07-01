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

#define SCALE 0.00048828125

#define g 9.80665

rosbag::Bag bag;
ros::Time tempo;

short read_word(int fd, int adr_h,int adr_l){

	char high = wiringPiI2CReadReg8 (fd,adr_h);
	char low = wiringPiI2CReadReg8 (fd,adr_l);
	short val = ((high << 8) | low);

	return val;

}


int main(int argc, char **argv){

	float bx,by,bz,sx,sy,sz;

	int Register_PM = 108; // power management
   	int Register_XL = 60;
   	int Register_XH = 59;
   	int Register_YL = 62;
   	int Register_YH = 61;
   	int Register_ZL = 64;
   	int Register_ZH = 63;
   	int Register_Scale = 28;

	short acc_x = 0;
	short acc_y = 0;
	short acc_z = 0;

	int fd = wiringPiI2CSetup(0x68);

	//wiringPiI2CWriteReg8 (fd, Register_PM, 0);
	wiringPiI2CWriteReg8 (fd, Register_Scale, 0x18);

	ros::init(argc, argv, "acc");
	ros::NodeHandle n;
	ros::Publisher chatter_pub = n.advertise<raspberry_msgs::Acc>("accInfo", 1000);
	ros::Rate loop_rate(100);

//  Leitura parametros
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

	bagParam.close();// 
//-------------------------------------------------------------------

	bag.open("/home/pi/Documents/robomagellan/Codigos/Raspberry/ROS/catkin_camila/src/imu/scripts/acc5.bag", rosbag::bagmode::Write);
	
	raspberry_msgs::Acc msg;

	int count = 0;
	while (ros::ok()){

		//leituras raw
		acc_x = read_word(fd,Register_XH,Register_XL);
		acc_y = read_word(fd,Register_YH,Register_YL);
		acc_z = read_word(fd,Register_ZH,Register_ZL);
		
		msg.a_x = (acc_x*SCALE*g - bx)/sx;
		msg.a_y = (acc_y*SCALE*g - by)/sy;
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
