#include "ros/ros.h"
#include "raspberry_msgs/GPS.h"
#include "raspberry_msgs/Gyro.h"
#include "raspberry_msgs/Acc.h"
#include <nav_msgs/Odometry.h>
#include <geometry_msgs/Point32.h>
#include <std_msgs/Bool.h>
#include "math.h"
#include <Eigen/Dense>
#include <unsupported/Eigen/MatrixFunctions>
#include <iostream>

#define DEBUG

#define PI 3.14159265
#define tAmostragem 0.01
#define g -9.7808439
#define tSetup 30

using namespace Eigen;
#define PI 3.14159265
struct GPSData{

	bool valid;
	double lat;
	double lng;
	double alt;
	double speed;
	double course;
	float hdop;
	float vdop;
	float pdop;
	

};

struct GyroData{

	float x;
	float y;
	float z;
	ros::Time time;

};

struct AccData{

	float x;
	float y;
	float z;
	ros::Time time;
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


GPSData gpsData;
GyroData gyroData;
AccData accData;
MatrixXf G(3,1);
MatrixXf R(10,10);
MatrixXf I10(10,10);

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
		gpsData.course = msg->course;
		gpsData.hdop = msg->hdop;
		gpsData.vdop = msg->vdop;
		gpsData.pdop = msg->pdop;

		//ROS_INFO("valid: %d",gpsData.valid);
		//ROS_INFO("lat: %f", gpsData.lat);
		//ROS_INFO("lng: %f", gpsData.lng);
		//ROS_INFO("alt: %f", gpsData.alt);
		//ROS_INFO("speed: %f", gpsData.speed);
		//ROS_INFO("hdop: %f", gpsData.hdop);
		//ROS_INFO("vdop: %f", gpsData.vdop);
		//ROS_INFO("pdop: %f", gpsData.pdop);
	
	}


}

void gyroCallback(const raspberry_msgs::Gyro::ConstPtr& msg){


	gyroData.x = msg->g_x;
	gyroData.y = msg->g_y;
	gyroData.z = msg->g_z;

	//ROS_INFO("g_x: %d", gyroData.x) ;
	//ROS_INFO("g_y: %d", gyroData.y);
	//ROS_INFO("g_z: %d", gyroData.z);
}

void accCallback(const raspberry_msgs::Acc::ConstPtr& msg){

	accData.x = msg->a_x;
	accData.y = msg->a_y;
	accData.z = msg->a_z;

	//ROS_INFO("a_x: %f", accData.x);
	//ROS_INFO("a_y: %f", accData.y);
	//ROS_INFO("a_z: %f", accData.z);

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

MatrixXf predicao(MatrixXf anterior){

	MatrixXf q_anterior(4,1), v_anterior(3,1), r_anterior(3,1);

	q_anterior << anterior(0,0), anterior(1,0), anterior(2,0), anterior(3,0);
	v_anterior << anterior(4,0), anterior(5,0), anterior(6,0);
	r_anterior << anterior(7,0), anterior(8,0), anterior(9,0);
	

	MatrixXf W(4,4), orient(4,4);

	W << 0, gyroData.x, gyroData.y, gyroData.z,
	     -gyroData.x, 0, -gyroData.z, gyroData.y,
	     -gyroData.y, gyroData.z, 0, -gyroData.x,
	     -gyroData.z, -gyroData.y, gyroData.x, 0;

	W = -W*tAmostragem;
	orient = W.exp()*q_anterior;

	MatrixXf C(3,3), vel(3,1), pos(3,1), acc(3,1);

	C << pow(q_anterior(0,0),2)+pow(q_anterior(1,0),2)-pow(q_anterior(2,0),2)-pow(q_anterior(3,0),2), 2*q_anterior(1,0)*q_anterior(2,0) + 2*q_anterior(0,0)*q_anterior(3,0), 2*q_anterior(1,0)*q_anterior(3,0) - 2*q_anterior(0,0)*q_anterior(2,0),
 	     2*q_anterior(1,0)*q_anterior(2,0) - 2*q_anterior(0,0)*q_anterior(3,0), pow(q_anterior(0,0),2)-pow(q_anterior(1,0),2)+pow(q_anterior(2,0),2)-pow(q_anterior(3,0),2), 2*q_anterior(2,0)*q_anterior(3,0) + 2*q_anterior(0,0)*q_anterior(1,0),
	     2*q_anterior(1,0)*q_anterior(3,0) + 2*q_anterior(0,0)*q_anterior(2,0), 2*q_anterior(2,0)*q_anterior(3,0) - 2*q_anterior(0,0)*q_anterior(1,0), pow(q_anterior(0,0),2)-pow(q_anterior(1,0),2)-pow(q_anterior(2,0),2)+pow(q_anterior(3,0),2);	 
 
	acc << accData.x, accData.y, accData.z;	

	vel = (C*acc + G)*tAmostragem + v_anterior;
	pos = (C*acc + G)*tAmostragem*tAmostragem/2 + v_anterior*tAmostragem +  r_anterior;

	MatrixXf est(10,1);

	est << orient, vel, pos;

	return est;
}

MatrixXf medicao(GPSCoord ref){

	MatrixXf pos(3,1), vel(3,1), orient(4,1);
	NEDCoord pointNed;
	GPSCoord pointGPS;

	pointGPS.lat = gpsData.lat;
	pointGPS.lng = gpsData.lng;
	pointGPS.alt = 0;

	std::cout << "ref: " << ref.lat << " " << ref.lng << std::endl;
	std::cout << "coord: " << pointGPS.lat << " " << pointGPS.lng  << std::endl;

	pointNed = GPS2NED(pointGPS, ref);

	pos << pointNed.x, pointNed.y, pointNed.z;

	std::cout << pos << std::endl;
	float speed, course;

	speed = gpsData.speed;
	course = gpsData.course;
	
	vel << speed*sin(course), speed*cos(course), 0;
//	std::cout<< vel << std::endl;
//	std::cout<< ""<< std::endl;
	orient << cos(course/2), 0, 0, sin(course/2);
//	std::cout<< orient << std::endl;
	MatrixXf med(10,1);
	
	med << orient, vel, pos;

	return med;

}

MatrixXf jacobianaModelo(MatrixXf anterior){

	MatrixXf A(10,10), orient(4,4);

	MatrixXf W(4,4), acc(3,1);

	W << 0, -gyroData.x, -gyroData.y, -gyroData.z,
	     gyroData.x, 0, gyroData.z, -gyroData.y,
	     -gyroData.y, gyroData.z, 0, -gyroData.x,
	     -gyroData.z, -gyroData.y, gyroData.x, 0;

	W = -W*tAmostragem;
	orient = W.exp();

	acc << accData.x, accData.y, accData.z;	

	A(0,0) = orient(0,0);
	A(0,1) = orient(0,1);
	A(0,2) = orient(0,2);	
	A(0,3) = orient(0,3);
	A(1,0) = orient(1,0);
	A(1,1) = orient(1,1);
	A(1,2) = orient(1,2);
	A(1,3) = orient(1,3);
	A(2,0) = orient(2,0);
	A(2,1) = orient(2,1);
	A(2,2) = orient(2,2);
	A(2,3) = orient(2,3);
	A(3,0) = orient(3,0);
	A(3,1) = orient(3,1);
	A(3,2) = orient(3,2);
	A(3,3) = orient(3,3);

	A.topRightCorner(4,6).setZero();

	A(4,0) = (2*anterior(0,0)*acc(0,0) + 2*acc(1,0) - 2*acc(2,0))*tAmostragem;
	A(4,1) = (2*anterior(1,0)*acc(0,0) + 2*acc(1,0) + 2*acc(2,0))*tAmostragem;	 
	A(4,2) = (-2*anterior(2,0)*acc(0,0) + 2*acc(1,0) - 2*acc(2,0))*tAmostragem;
	A(4,3) = (-2*anterior(3,0)*acc(0,0) + 2*acc(1,0) + 2*acc(2,0))*tAmostragem;

	A(4,4) = 1;
	A(4,5) = 0;
	A(4,6) = 0;
	A(4,7) = 0;
	A(4,8) = 0;
	A(4,9) = 0;
	
	A(5,0) = (-2*acc(0,0) + 2*anterior(0,0)*acc(1,0) + 2*acc(2,0))*tAmostragem;
	A(5,1) = (2*acc(0,0) - 2*anterior(1,0)*acc(1,0) + 2*acc(2,0))*tAmostragem;
	A(5,2) = (2*acc(0,0) + 2*anterior(2,0)*acc(1,0) + 2*acc(2,0))*tAmostragem;
	A(5,3) = (-2*acc(0,0) - 2*anterior(3,0)*acc(1,0) + 2*acc(2,0))*tAmostragem;
	
	A(5,4) = 0;
	A(5,5) = 1;
	A(5,6) = 0;
	A(5,7) = 0;
	A(5,8) = 0;
	A(5,9) = 0;

	A(6,0) = (2*anterior(0,0)*acc(0,0) + 2*acc(1,0) + 2*acc(2,0))*tAmostragem;
	A(6,1) = (2*anterior(1,0)*acc(0,0) - 2*acc(1,0) - 2*acc(2,0))*tAmostragem;
	A(6,2) = (2*anterior(2,0)*acc(0,0) - 2*acc(1,0) - 2*acc(2,0))*tAmostragem;
	A(6,3) = (2*anterior(3,0)*acc(0,0) + 2*acc(1,0) + 2*acc(2,0))*tAmostragem;
	
	A(6,4) = 0;
	A(6,5) = 0;
	A(6,6) = 1;
	A(6,7) = 0;
	A(6,8) = 0;
	A(6,9) = 0;

	A(7,0) = (2*acc(0,0) + 2*anterior(0,0)*acc(1,0) - 2*acc(2,0))*tAmostragem*tAmostragem/2;
	A(7,1) = (2*acc(0,0) + 2*anterior(1,0)*acc(1,0) + 2*acc(2,0))*tAmostragem*tAmostragem/2;
	A(7,2) = (-2*acc(0,0) + 2*anterior(2,0)*acc(1,0) - 2*acc(2,0))*tAmostragem*tAmostragem/2;
	A(7,3) = (-2*acc(0,0) + 2*anterior(3,0)*acc(1,0) + 2*acc(2,0))*tAmostragem*tAmostragem/2;


	A(7,4) = tAmostragem;
	A(7,5) = 0; 
	A(7,6) = 0;
	A(7,7) = 1;
	A(7,8) = 0;
	A(7,9) = 0; 

	A(8,0) = (-2*acc(0,0) + 2*anterior(0,0)*acc(1,0) + 2*acc(2,0))*tAmostragem*tAmostragem/2;
	A(8,1) = (2*acc(0,0) - 2*anterior(1,0)*acc(1,0) + 2*acc(2,0))*tAmostragem*tAmostragem/2;
	A(8,2) = (2*acc(0,0) + 2*anterior(2,0)*acc(1,0) + 2*acc(2,0))*tAmostragem*tAmostragem/2;
	A(8,3) = (-2*acc(0,0) - 2*anterior(3,0)*acc(1,0) + 2*acc(2,0))*tAmostragem*tAmostragem/2;
	
	A(8,4) = 0;
	A(8,5) = tAmostragem; 
	A(8,6) = 0;
	A(8,7) = 0;
	A(8,8) = 1;
	A(8,9) = 0;

	A(9,0) = (2*acc(0,0) + 2*acc(1,0) + 2*anterior(0,0)*acc(2,0))*tAmostragem*tAmostragem/2;
	A(9,1) = (2*acc(0,0) - 2*acc(1,0) - 2*anterior(1,0)*acc(2,0))*tAmostragem*tAmostragem/2;
	A(9,2) = (2*acc(0,0) - 2*acc(1,0) - 2*anterior(2,0)*acc(2,0))*tAmostragem*tAmostragem/2;
	A(9,3) = (2*acc(0,0) + 2*acc(1,0) + 2*anterior(3,0)*acc(2,0))*tAmostragem*tAmostragem/2;

	A(9,4) = 0;
	A(9,5) = 0; 
	A(9,6) = tAmostragem;
	A(9,7) = 0;
	A(9,8) = 0;
	A(9,9) = 1;

	return A;

}

MatrixXf jacobianaMedida(){

	MatrixXf C(10,10);
	
	C.topLeftCorner(4,4).setIdentity();
	C.topRightCorner(4,6).setZero();

	C(4,0) = 0; C(4,1) = 0; C(4,2) = 0; C(4,3) = 0;
	C(5,0) = 0; C(5,1) = 0; C(5,2) = 0; C(5,3) = 0;
	C(6,0) = 0; C(6,1) = 0; C(6,2) = 0; C(6,3) = 0;
	

	C(4,4) = 1; C(4,5) = 0; C(4,6) = 0;
	C(5,4) = 0; C(5,5) = 1; C(5,6) = 0;
	C(6,4) = 0; C(6,5) = 0; C(6,6) = 1; 

	C(4,7) = 0; C(4,8) = 0; C(4,9) = 0;
	C(5,7) = 0; C(5,8) = 0; C(5,9) = 0;
	C(6,7) = 0; C(6,8) = 0; C(6,9) = 0;
	
	C.bottomLeftCorner(3,7).setZero();
	C.bottomRightCorner(3,3).setIdentity();	

	return C;

}

GPSCoord setup(){

	GPSCoord ref;
	ref.lat = 0;
	ref.lng = 0;
	ref.alt = 0;

	int count = 0;	

	ros::Time tInicial = ros::Time::now();
	while (count < 100000){
		
		ref.lat += gpsData.lat;
		ref.lng += gpsData.lng;
		ref.alt += gpsData.alt;
		ROS_INFO("lat: %f", gpsData.lat);
		count++;
	}

	ref.lat = ref.lat/count;
	ref.lng = ref.lng/count;
	ref.alt = ref.alt/count;

	return ref;

}

int main(int argc, char **argv){	

  	ros::init(argc, argv, "filtro");
	ros::NodeHandle n;
	ros::Subscriber subGPS = n.subscribe("gpsInfo", 1000, GPSCallback);
	ros::Subscriber subGyro = n.subscribe("gyroInfo", 1000, gyroCallback);
	ros::Subscriber subAcc = n.subscribe("accInfo", 1000, accCallback);
	
	ros::Publisher odom_pub = n.advertise<nav_msgs::Odometry>("odom", 50);
  	ros::Publisher origin_pub = n.advertise<geometry_msgs::Point32>("origin", 50);
  	ros::Publisher odom_ok = n.advertise<std_msgs::Bool>("odom_ok", 50);

	ros::Time current_time;
	
	ros::Rate loop_rate(100);

	geometry_msgs::Point32 origin;
  	std_msgs::Bool odomOK;
	nav_msgs::Odometry odom;

	GPSCoord ref;

	ref.lat = 0;
	ref.lng = 0;
	ref.alt = 0;

	MatrixXf x_estPriori(10,1); // [q0 q1 q2 q3 vx vy vz rx ry rz] 
	MatrixXf x_estPosteriori(10,1); 
	MatrixXf x_medido(10,1);
	MatrixXf P_priori(10,10), P_posteriori(10,10);
	MatrixXf Q(10,10), H(10,10), F(10,10), KG(10,10);
	MatrixXf M(10,1);

	G << 0,0,g;

	H = jacobianaMedida();

	I10.setIdentity();

	x_estPosteriori << 1, 0, 0, 0, 0, 0, 0, 0, 0, 0;
	P_posteriori = I10*0.1;
	Q = I10*0.1;
	R = I10*0.001;
	
	int flagSetup = 1;
	ros::Time tInicial = ros::Time::now();
	int count = 0;	
	
	while (ros::ok()){

	if (flagSetup){	
       
		if(gpsData.valid){
                	std::cout << "setup" << std::endl;
                	odomOK.data = true;

			ref.lat += gpsData.lat;
			ref.lng += gpsData.lng;
			ref.alt += gpsData.alt;
			ROS_INFO("lat: %f", gpsData.lat);
			count++;
		}else{
                	odomOK.data = false;
         	       ref.lat = 0; ref.lng = 0; ref.alt = 0;
		}

		if(ros::Time::now().toSec() - tInicial.toSec() > 30){
			flagSetup = 0;
			ref.lat = ref.lat/count;
               		 ref.lng = ref.lng/count;
               		 ref.alt = 0;

                std::cout << "lat: " << ref.lat << std ::endl;
                std::cout <<" lng: " << ref.lng << std::endl;
                std::cout << "count : "<< count << std::endl;
                origin.x = ref.lat;
                origin.y = ref.lng;

		}
	}else{


		// Estimação
	//	x_estPriori = predicao(x_estPosteriori);
	//	F = jacobianaModelo(x_estPosteriori);
	//	P_priori = F + P_posteriori*F.transpose() + Q;

		// Correção
	//	if(gpsData.valid){
	//		KG = P_priori*H.transpose()*(H*P_priori*H.transpose() + R);
			M = medicao(ref);
			odomOK.data = true;
	//	}
	//	else{
	///		KG.setZero();
	//		M.setZero();
	//		odomOK.data = false;
	//	}
		x_estPosteriori = M;	
	//	x_estPosteriori = x_estPriori + KG*(M - x_estPriori);
	//	std::cout << "oi" << std::endl;	
	//	P_posteriori = (I10 - KG*H)*P_priori;
	
		#ifdef DEBUG
		std::cout << x_estPosteriori << std::endl;
		#endif

		std::cout << "\n";

		current_time = ros::Time::now();  
    		odom.header.stamp = current_time;
    		odom.header.frame_id = "odom";

		//set the position
    		odom.pose.pose.position.x = x_estPosteriori(7,0);
    		odom.pose.pose.position.y = x_estPosteriori(8,0);
    		odom.pose.pose.position.z = x_estPosteriori(9,0);

    		odom.pose.pose.orientation.x = x_estPosteriori(1,0);
    		odom.pose.pose.orientation.y = x_estPosteriori(2,0);
    		odom.pose.pose.orientation.z = x_estPosteriori(3,0);    
    		odom.pose.pose.orientation.w = x_estPosteriori(0,0);	

		odom_pub.publish(odom);
    		origin_pub.publish(origin);
    		odom_ok.publish(odomOK);	
	}

		loop_rate.sleep();
       		ros::spinOnce();

	}


return 0;

}
