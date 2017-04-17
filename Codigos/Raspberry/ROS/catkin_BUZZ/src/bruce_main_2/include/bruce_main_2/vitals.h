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
#define PRINT_ENABLED

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
	ros::Publisher * pubFollowCamera;
	tf::TransformListener * tfListener;
	GPSCoord origin;
	GPSCoord bottomLeft;
	std::vector<NEDCoord> path;
};

static void  * getMember(robot_information * info, std::string MemberName){
  if(MemberName == "position_is_valid"){
  	return (void *) & info->position_is_valid;
  }
  if(MemberName == "route_calculated"){
  	return (void *) & info->route_calculated;
  }
  if(MemberName == "calculating_route"){
  	return (void *) & info->calculating_route;
  }
  if(MemberName == "cone_encontrado"){
  	return (void *) & info->cone_encontrado;
  }
  if(MemberName == "sensor_toque"){
  	return (void *) & info->sensor_toque;
  } 
  if(MemberName == "botao_verde"){
  	return (void *) & info->botao_verde;
  }
  if(MemberName == "botao_preto"){
  	return (void *) & info->botao_preto;
  }
  if(MemberName == "origin_received"){
  	return (void *) & info->origin_received;
  }
  if(MemberName == "pose"){
  	return (void *) & info->pose;
  }
  if(MemberName == "pose.x"){
  	return (void *) & info->pose.position.x;
  }
  if(MemberName == "pose.y"){
  	return (void *) & info->pose.position.y;
  }
  if(MemberName == "pose.z"){
  	return (void *) & info->pose.position.z;
  }
  if(MemberName == "pose.q.x"){
  	return (void *) & info->pose.orientation.x;
  }
  if(MemberName == "pose.q.y"){
  	return (void *) & info->pose.orientation.y;
  }
  if(MemberName == "pose.q.z"){
  	return (void *) & info->pose.orientation.z;
  }
  if(MemberName == "pose.q.w"){
  	return (void *) & info->pose.orientation.w;
  }  
  if(MemberName == "currentMapGoal"){
  	return (void *) & info->currentMapGoal;
  }
  if(MemberName == "currentMapGoal.x"){
  	return (void *) & info->currentMapGoal.x;
  }
  if(MemberName == "currentMapGoal.y"){
  	return (void *) & info->currentMapGoal.y;
  }
  if(MemberName == "currentMapGoal.z"){
  	return (void *) & info->currentMapGoal.z;
  }
  if(MemberName == "originInMap"){
  	return (void *) & info->originInMap;
  }
  if(MemberName == "originInMap.x"){
  	return (void *) & info->originInMap.x;
  }
  if(MemberName == "originInMap.y"){
  	return (void *) & info->originInMap.y;
  }
  if(MemberName == "originInMap.z"){
  	return (void *) & info->originInMap.z;
  }
  if(MemberName == "us1"){
  	return (void *) & info->US[0];
  }
  if(MemberName == "us2"){
  	return (void *) & info->US[1];
  }
  if(MemberName == "us3"){
  	return (void *) & info->US[2];
  }
  if(MemberName == "us4"){
  	return (void *) & info->US[3];
  }
  if(MemberName == "us5"){
  	return (void *) & info->US[4];
  }
  if(MemberName == "us6"){
  	return (void *) & info->US[5];
  }
  if(MemberName == "us7"){
  	return (void *) & info->US[6];
  }
  if(MemberName == "us8"){
  	return (void *) & info->US[7];
  }
  if(MemberName == "us9"){
  	return (void *) & info->US[8];
  }
  if(MemberName == "us10"){
  	return (void *) & info->US[9];
  }
  if(MemberName == "us11"){
  	return (void *) & info->US[10];
  }
  if(MemberName == "cameraReadDistance"){
  	return (void *) & info->cameraReadDistance;
  }
  if(MemberName == "cameraReadOrientation"){
  	return (void *) & info->cameraReadOrientation;
  }
  if(MemberName == "origin"){
  	return (void *) & info->origin;
  }
  if(MemberName == "origin.lat"){
  	return (void *) & info->origin.lat;
  }
  if(MemberName == "origin.lng"){
  	return (void *) & info->origin.lng;
  }
  if(MemberName == "origin.alt"){
  	return (void *) & info->origin.alt;
  }
  if(MemberName == "bottomLeft"){
  	return (void *) & info->bottomLeft;
  }
  if(MemberName == "bottomLeft.lat"){
  	return (void *) & info->bottomLeft.lat;
  }
  if(MemberName == "bottomLeft.lng"){
  	return (void *) & info->bottomLeft.lng;
  }
  if(MemberName == "bottomLeft.alt"){
  	return (void *) & info->bottomLeft.alt;
  }

  return NULL;
}

