#include <wiringSerial.h>
#include "ros/ros.h"
#include "rosbag/bag.h"
#include "raspberry_msgs/GPS.h"
#include "gps/gps.h"

GPS gps;
raspberry_msgs::GPS msg;
rosbag::Bag bag;

void leituras(){

	msg.valid = gps.location.isValid();

	if(msg.valid){

		msg.lat = gps.location.lat();
		msg.lng = gps.location.lng();
		msg.alt = gps.altitude.meters();
		msg.speed = gps.speed.kmph();
		msg.hdop = gps.hdop.realValue();
		msg.vdop = gps.vdop.realValue();
		msg.pdop = gps.pdop.realValue();
	
		ROS_INFO("lat: %f", msg.lat);
		ROS_INFO("lng: %f", msg.lng);
		ROS_INFO("alt: %f", msg.alt);
		ROS_INFO("speed: %f", msg.speed);
		ROS_INFO("hdop: %f", msg.hdop);
		ROS_INFO("vdop: %f", msg.vdop);
		ROS_INFO("pdop: %f", msg.pdop);

		bag.write("gps_data",ros::Time::now(),msg);
	
	}
	else{

		ROS_INFO("INVALID");
		bag.write("gps_data",ros::Time::now(),msg);
	
	}

}

int main(int argc, char **argv){

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

		if(gps.encode(serialGetchar(fd))){

			leituras();
		}
		
		chatter_pub.publish(msg);
	    
		ros::spinOnce();
	    loop_rate.sleep();
	
	}
	
	bag.close();
	
	
	return 0;

}