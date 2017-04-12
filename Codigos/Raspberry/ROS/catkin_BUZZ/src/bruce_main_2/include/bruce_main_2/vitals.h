#pragma once

#include "ros/ros.h"
#include "nav_msgs/Odometry.h"
#include "std_msgs/Bool.h"
#include "std_msgs/Int16.h"
#include "geometry_msgs/Point32.h"
#include "geometry_msgs/PoseArray.h"
#include "nav_msgs/Path.h"
#include "sensor_msgs/Range.h"
#include <tf/transform_listener.h>
#include <chrono>

#define PI 3.14159265
#define NUM_US 11
#define MAX_RANGE 2.0f
//#define PRINT_ENABLED

class Coordinates{
public:
	Coordinates(){x=0;y=0;}
	Coordinates(float x, float y):x(x),y(y){}
	Coordinates operator+ (const Coordinates& other)const {
		return Coordinates(x+other.x,y+other.y);
	}
	Coordinates operator- (const Coordinates& other)const {
		return Coordinates(x-other.x,y-other.y);
	}
	Coordinates operator/ (const float& other)const {
		return Coordinates(x/other,y/other);
	}
	Coordinates operator* (const float& other)const {
		return Coordinates(x*other,y*other);
	}	
	float norm(){return std::sqrt(x*x+y*y);}
	float x,y;
};

struct BasicTimer{
	std::string name;
	std::chrono::high_resolution_clock::time_point t;
};

struct BasicCounter{
	std::string name;
	int counter;
};

struct NEDCoord{
  double x,y,z;
};

struct ECEFCoord{
  double x,y,z;
};

struct GPSCoord{
  double lat,lng,alt;
};

NEDCoord GPS2NED(GPSCoord,GPSCoord);
ECEFCoord GPS2ECEF(GPSCoord);
double toRadian(double);
double distanceFromSegmentToPoint(NEDCoord P1 ,NEDCoord P2,NEDCoord P0);

struct robot_information{
	bool position_is_valid;
	bool route_calculated;
	bool calculating_route;
	bool cone_encontrado;
	bool sensor_toque;
	bool botao_verde;
	bool botao_preto;
	bool origin_received;
	geometry_msgs::Pose pose;
	NEDCoord currentMapGoal;
	NEDCoord originInMap;
	float US[NUM_US];
	float cameraReadDistance;
	float cameraReadOrientation;
	std::vector<BasicTimer> timers;
	std::vector<BasicCounter> counters;
	// ROS stuff
	ros::NodeHandle * n;
	ros::Publisher * pubRequestPath;
	ros::Publisher * pubMapBLCoordinate;
	ros::Publisher * pubPath;
	ros::Publisher * pubEnableFollowPath;
	ros::Publisher * pubObstacles;	
	ros::Publisher * pubOriginRequest;
	ros::Publisher * pubVelocity;
	ros::Publisher * pubFollowCamera
	tf::TransformListener * tfListener;
	GPSCoord origin;
	GPSCoord bottomLeft;
	std::vector<NEDCoord> path;
};


