#include <wiringSerial.h>
#include "ros/ros.h"
#include "rosbag/bag.h"
#include "raspberry_msgs/GPS.h"
#include "gps/gps.h"
#include <time.h>
#include <iostream>

//#define DEBUG

GPS gps;
raspberry_msgs::GPS msg;
rosbag::Bag bag;
ros::Time tempo;
int utcTime, utcTimeAnterior = 0;

void leituras(){

	msg.valid = gps.location.isValid();

	if(msg.valid){

		if(gps.location.isUpdated() || gps.speed.isUpdated() || gps.pdop.isUpdated()){
			
			if(gps.location.isUpdated()){
				msg.lat = gps.location.lat();
				msg.lng = gps.location.lng();
				msg.alt = gps.altitude.meters();
			}
			if(gps.speed.isUpdated())
				msg.speed = gps.speed.kmph();
			if(gps.pdop.isUpdated()){
				msg.hdop = gps.hdop.realValue();
				//msg.vdop = gps.vdop.realValue();
				msg.pdop = gps.pdop.realValue();
			}
			tempo = ros::Time::now();
			msg.time = tempo.toNSec() * 1e-6;

			#ifdef DEBUG		
			ROS_INFO("lat: %f", msg.lat);
			ROS_INFO("lng: %f", msg.lng);
			ROS_INFO("alt: %f", msg.alt);
			ROS_INFO("speed: %f", msg.speed);
			ROS_INFO("hdop: %f", msg.hdop);
			ROS_INFO("vdop: %f", msg.vdop);
			ROS_INFO("pdop: %f", msg.pdop);
			
			bag.write("gps_data",ros::Time::now(),msg);
			#endif

		}
		else{
			#ifdef DEBUG
			ROS_INFO("NOT UPDATED");
			#endif
		}
	
	}
	else{
		utcTime = gps.time.getTime();

		#ifdef DEBUG
		ROS_INFO("INVALID");
		#endif
	}

}

int main(int argc, char **argv){

	char c;

	int fd = serialOpen("/dev/ttyS0",4800);
	
	if(fd < 0){
	
		ROS_INFO("Erro");
		return 1;	
	}
	
	ros::init(argc, argv, "gpsTalker");
	ros::NodeHandle n;
	ros::Publisher chatter_pub = n.advertise<raspberry_msgs::GPS>("gpsInfo", 1000);
	ros::Rate loop_rate(100);

	bag.open("gps.bag", rosbag::bagmode::Write);	

	while (ros::ok()){

		c = serialGetchar(fd);
		//std::cout << c;		
		//std::cout << "while" << std::endl;
		if(gps.encode(c)){
			
			leituras();

	
	}	
		chatter_pub.publish(msg);

	    	
		ros::spinOnce();
	   	loop_rate.sleep();
	
	}
	
	bag.close();
	
	return 0;

}
