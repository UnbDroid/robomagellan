#include "ros/ros.h"
#include "raspberry_msgs/GPS.h"
#include "raspberry_msgs/Gyro.h"
#include "raspberry_msgs/Acc.h"
#include "math.h"
#include <Eigen/Dense>
#include <iostream>

#define PI 3.14159265

struct GPSData{

	bool valid;
	double lat;
	double lng;
	double alt;
	double speed;
	float hdop;
	float vdop;
	float pdop;
	

};

struct GyroData{

	int x;
	int y;
	int z;
	ros::Time time;

};

struct AccData{

	int x;
	int y;
	int z;
	ros::Time time;
};

struct NEDCoord{
  float x,y,z;
};

struct ECEFCoord{
  float x,y,z;
};

struct GPSCoord{
  float lat,lng,alt;
};

float toRadian(float degree){
  return (degree*PI/180.0);
}

GPSData gpsData;
GyroData gyroData;
AccData accData;

ECEFCoord GPS2ECEF(GPSCoord gpoint){
  float a = 6378137;
  float b = 6356752.31424518;
  float f = (a-b)/a;
  float e = std::sqrt(f*(2.0-f));
  float sinLat = std::sin(toRadian(gpoint.lat));
  float cosLat = std::cos(toRadian(gpoint.lat));
  float sinLng = std::sin(toRadian(gpoint.lng));
  float cosLng = std::cos(toRadian(gpoint.lng));
  float N = a/(std::sqrt(1-(e*e*sinLat*sinLat))); 

  ECEFCoord ecefPoint;

  ecefPoint.x = (N+gpoint.alt)*cosLat*cosLng;
  ecefPoint.y = (N+gpoint.alt)*cosLat*sinLng;
  ecefPoint.z = (N*(1-e*e)+gpoint.alt)*sinLat; 
  return ecefPoint;
}

NEDCoord GPS2NED(GPSCoord gpoint ,GPSCoord ref){
  
  
  ECEFCoord ecefPoint = GPS2ECEF(gpoint);
  ECEFCoord refEcefPoint = GPS2ECEF(ref);
  
  NEDCoord nedPoint,aux;
  
  float sLaR = std::sin(toRadian(ref.lat));
  float cLaR = std::cos(toRadian(ref.lat));
  float sLoR = std::sin(toRadian(ref.lng));
  float cLoR = std::cos(toRadian(ref.lng));

  aux.x = ecefPoint.x-refEcefPoint.x;
  aux.y = ecefPoint.y-refEcefPoint.y;
  aux.z = ecefPoint.z-refEcefPoint.z;

  nedPoint.x = -sLaR*cLoR*aux.x  - sLaR*sLoR*aux.y + cLaR*aux.z;
  nedPoint.y = -sLoR*aux.x          + cLoR*aux.y;
  nedPoint.z = -cLaR*cLoR*aux.x  - cLaR*sLoR*aux.y - sLaR*aux.z;

  return nedPoint;
}



void GPSCallback(const raspberry_msgs::GPS::ConstPtr& msg){

	if(!msg->valid){
		gpsData.valid = msg->valid;
		ROS_INFO("GPS sem sinal");	
	}
	else{
		gpsData.valid = msg->valid;
		gpsData.lat = msg->lat;
		gpsData.lng = msg->lng;
		gpsData.alt = msg->alt;
		gpsData.speed = msg->speed;
		gpsData.hdop = msg->hdop;
		gpsData.vdop = msg->vdop;
		gpsData.pdop = msg->pdop;

		ROS_INFO("lat: %f", gpsData.lat);
		ROS_INFO("lng: %f", gpsData.lng);
		ROS_INFO("alt: %f", gpsData.alt);
		ROS_INFO("speed: %f", gpsData.speed);
		ROS_INFO("hdop: %f", gpsData.hdop);
		ROS_INFO("vdop: %f", gpsData.vdop);
		ROS_INFO("pdop: %f", gpsData.pdop);
	
	}


}

void gyroCallback(const raspberry_msgs::Gyro::ConstPtr& msg){


	gyroData.x = msg->g_x;
	gyroData.y = msg->g_y;
	gyroData.z = msg->g_z;

	ROS_INFO("g_x: %d", gyroData.x) ;
	ROS_INFO("g_y: %d", gyroData.y);
	ROS_INFO("g_z: %d", gyroData.z);

}

void accCallback(const raspberry_msgs::Acc::ConstPtr& msg){

	accData.x = msg->a_x;
	accData.y = msg->a_y;
	accData.z = msg->a_z;

	ROS_INFO("a_x: %d", accData.x);
	ROS_INFO("a_y: %d", accData.y);
	ROS_INFO("a_z: %d", accData.z);

}

using Eigen::MatrixXd;

int main(int argc, char **argv)
{
  	ros::init(argc, argv, "filtro");
	ros::NodeHandle n;
	ros::Subscriber subGPS = n.subscribe("gpsInfo", 1000, GPSCallback);
	ros::Subscriber subGyro = n.subscribe("gyroInfo", 1000, gyroCallback);
	ros::Subscriber subAcc = n.subscribe("accInfo", 1000, accCallback);
	
	ros::Rate loop_rate(10);

	while (ros::ok()){

		
		loop_rate.sleep();
       		ros::spinOnce();

	}

	




return 0;

}



