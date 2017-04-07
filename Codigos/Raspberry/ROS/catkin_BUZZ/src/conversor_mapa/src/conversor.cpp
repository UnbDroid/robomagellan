#include "ros/ros.h"
#include <string>
#include <sstream>
#include <cmath>

#define PI 3.14159265

struct NEDCoord{
  float x,y,z;
};

struct ECEFCoord{
  float x,y,z;
};

struct GPSCoord{
  float lat,lng,alt;
};

NEDCoord GPS2NED(GPSCoord,GPSCoord);
ECEFCoord GPS2ECEF(GPSCoord);
float toRadian(float);

int main(int argc, char **argv){
  ros::init(argc, argv, "conversor");

  ros::NodeHandle n;

  GPSCoord tl = {-15.760877,-47.858675,1000};
  GPSCoord tr = {-15.760864,-47.855953,1000};
  GPSCoord bl = {-15.762866,-47.858645,1000};
  GPSCoord br = {-15.762879,-47.855981,1000};
  GPSCoord origin = {-15.761870,-47.857670,1000};

  NEDCoord ntl = GPS2NED(tl,origin);
  NEDCoord ntr = GPS2NED(tr,origin);
  NEDCoord nbl = GPS2NED(bl,origin);
  NEDCoord nbr = GPS2NED(br,origin);
  NEDCoord onbl = GPS2NED(origin,bl);

  ros::Rate loop_rate(60);

  while (ros::ok()){
    ROS_INFO("Top Left x = %f, y = %f, z=%f",ntl.x,ntl.y,ntl.z);
    ROS_INFO("Top Right x = %f, y = %f, z=%f",ntr.x,ntr.y,ntr.z);
    ROS_INFO("Bottom Left x = %f, y = %f, z=%f",nbl.x,nbl.y,nbl.z);
    ROS_INFO("Bottom Right x = %f, y = %f, z=%f",nbr.x,nbr.y,nbr.z);
    ROS_INFO("Origin regards 2 BL x = %f, y = %f, z=%f",onbl.x,onbl.y,onbl.z);  
    loop_rate.sleep();
    ros::spinOnce();
  }
  return 0;
}

float toRadian(float degree){
  return (degree*PI/180.0);
}


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
