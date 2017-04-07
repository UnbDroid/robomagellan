#include <ros/ros.h>
#include <tf/transform_broadcaster.h>
#include "nav_msgs/Odometry.h"
#include "geometry_msgs/Point32.h"
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

  /*Coordenadas dos cantos do mapa e origem --------------------------------------------------*/
  //GPSCoord tl = {-15.760877,-47.858675,1000};
  //GPSCoord tr = {-15.760864,-47.855953,1000};
  GPSCoord bl = {0,0,1000};
  //GPSCoord br = {-15.762879,-47.855981,1000};
  GPSCoord origin = {0,0,1000};
  //NEDCoord atualPosition = {0,0,onbl.z};
  /*Coordenadas dos cantos do mapa e origem --------------------------------------------------*/

nav_msgs::Odometry currentPose; 

NEDCoord GPS2NED(GPSCoord,GPSCoord);
ECEFCoord GPS2ECEF(GPSCoord);
float toRadian(float);
void odomCallback(const nav_msgs::Odometry::ConstPtr& msg);
void BottomCoordinateCallback(const geometry_msgs::Point32::ConstPtr& msg);
void OriginCallback(const geometry_msgs::Point32::ConstPtr& msg);


int main(int argc, char** argv){
  ros::init(argc, argv, "bruce_tf_broadcaster");

  ros::Time time;
  ros::NodeHandle node;

  currentPose.pose.pose.orientation.w = 1;

  /*Criando o subscriber da posicao atual do robo-----------------------------------------------*/
  ros::Subscriber subOdom = node.subscribe("odom", 1000, odomCallback);
  ros::Subscriber subOrigin = node.subscribe("origin", 1000, OriginCallback);
  ros::Subscriber subBottomCoordinate = node.subscribe("map_bl_coord", 1000, BottomCoordinateCallback);
  /*Criando o subscriber da posicao atual do robo-----------------------------------------------*/


  tf::TransformBroadcaster br;

  tf::Transform transformCamera(tf::Quaternion(0,0,0,1),tf::Vector3(0.2,0,0.2));

  tf::Transform transformUS1(tf::Quaternion(0,0,-0.707,0.707),tf::Vector3(0,-0.19,0.2));

  tf::Transform transformUS2(tf::Quaternion(0,0,-0.588,0.809),tf::Vector3(0.06,-0.16,0.2));

  tf::Transform transformUS3(tf::Quaternion(0,0,- 0.454,0.891),tf::Vector3(0.12,-0.14,0.2));

  tf::Transform transformUS4(tf::Quaternion(0,0,-0.309, 0.951),tf::Vector3(0.15,-0.11,0.2));

  tf::Transform transformUS5(tf::Quaternion(0,0,-0.156,0.988),tf::Vector3(0.16,-0.06,0.2));

  tf::Transform transformUS6(tf::Quaternion(0,0,0,1),tf::Vector3(0.17,0,0.2));

  tf::Transform transformUS7(tf::Quaternion(0,0, 0.156, 0.988),tf::Vector3(0.16,0.06,0.2));

  tf::Transform transformUS8(tf::Quaternion(0,0,0.309, 0.951),tf::Vector3(0.15,0.11,0.2));

  tf::Transform transformUS9(tf::Quaternion(0,0, 0.454,0.891),tf::Vector3(0.12,0.14,0.2));

  tf::Transform transformUS10(tf::Quaternion(0,0,0.588,0.809),tf::Vector3(0.06,0.16,0.2));

  tf::Transform transformUS11(tf::Quaternion(0,0,0.707,0.707),tf::Vector3(0,0.19,0.2));

  ros::Rate loop_rate(10);

  while (ros::ok()){
    time = ros::Time::now();
    NEDCoord onbl = GPS2NED(origin,bl);
    tf::Transform transformMAP(tf::Quaternion(currentPose.pose.pose.orientation.x,currentPose.pose.pose.orientation.y,currentPose.pose.pose.orientation.z,currentPose.pose.pose.orientation.w),tf::Vector3(currentPose.pose.pose.position.y+onbl.y,currentPose.pose.pose.position.x+onbl.x,0));
    br.sendTransform(tf::StampedTransform(transformMAP, time, "map", "base_link"));
    br.sendTransform(tf::StampedTransform(transformUS1, time, "base_link", "ultrasound1"));
    br.sendTransform(tf::StampedTransform(transformUS2, time, "base_link", "ultrasound2"));
    br.sendTransform(tf::StampedTransform(transformUS3, time, "base_link", "ultrasound3"));
    br.sendTransform(tf::StampedTransform(transformUS4, time, "base_link", "ultrasound4"));
    br.sendTransform(tf::StampedTransform(transformUS5, time, "base_link", "ultrasound5"));
    br.sendTransform(tf::StampedTransform(transformUS6, time, "base_link", "ultrasound6"));
    br.sendTransform(tf::StampedTransform(transformUS7, time, "base_link", "ultrasound7"));
    br.sendTransform(tf::StampedTransform(transformUS8, time, "base_link", "ultrasound8"));
    br.sendTransform(tf::StampedTransform(transformUS9, time, "base_link", "ultrasound9"));
    br.sendTransform(tf::StampedTransform(transformUS10, time, "base_link", "ultrasound10"));
    br.sendTransform(tf::StampedTransform(transformUS11, time, "base_link", "ultrasound11"));
    br.sendTransform(tf::StampedTransform(transformCamera, time, "base_link", "camera"));
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

void odomCallback(const nav_msgs::Odometry::ConstPtr& msg){
  currentPose.pose = msg->pose;
}

void BottomCoordinateCallback(const geometry_msgs::Point32::ConstPtr& msg){
  bl.lat = msg->x;
  bl.lng = msg->y;
}

void OriginCallback(const geometry_msgs::Point32::ConstPtr& msg){
  origin.lat = msg->x;
  origin.lng = msg->y; 
}
