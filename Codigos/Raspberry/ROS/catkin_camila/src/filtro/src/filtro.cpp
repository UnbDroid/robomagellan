#include "ros/ros.h"
#include "raspberry_msgs/GPS.h"
#include "raspberry_msgs/Gyro.h"
#include "raspberry_msgs/Acc.h"
#include "raspberry_msgs/Mag.h"
#include <nav_msgs/Odometry.h>
#include <geometry_msgs/Point32.h>
#include <std_msgs/Bool.h>
#include "math.h"
#include <Eigen/Dense>
#include <unsupported/Eigen/MatrixFunctions>
#include <iostream>
#include <chrono>
//#include "tf/transform_datatypes.h"
//#include "geometry_msgs/Quaternion.h"

//#define debug_posteriori
//#define debug_priori
//#define debug_ganho
//#define debug_covarPriori
//#define debug_covarPosteriori

#define PI 3.14159265
#define tAmostragem 0.05
#define g -9.79997
#define m 48.3346
#define tSetup 30
#define ERRO 0.3
#define B 0.075 //comprimento do robo
#define r 0.06 //raio da roda�
#define LAT 37.6596071
#define LNG -121.8862376
#define L_ERRO 0.01

using namespace Eigen;

struct GPSData{

	bool valid;
	double lat;
	double lng;
	double alt;
	double speed;
	double course;
	float hdop;
	bool updated;
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

struct MagData{

	float x;
	float y;
	float z;

};

struct VelData{

	float dir,esq;
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
MagData magData;
VelData velData;
bool parar;
MatrixXf G(3,1);
MatrixXf R(10,10);
MatrixXf I10(10,10);
MatrixXf Z10(10,10);
Vector3f g_unitario_n;
Vector3f m_unitario_n;

void GPSCallback(const raspberry_msgs::GPS::ConstPtr& msg){

	//if(!msg->valid){
		//gpsData.valid = msg->valid;
		//ROS_INFO("GPS sem sinal");	
//	}
	//else{
		//gpsData.valid = msg->valid;
		//gpsData.updated = msg->updated;
		gpsData.lat = msg->lat;
		gpsData.lng = msg->lng;
		//gpsData.alt = msg->alt;
		//gpsData.speed = msg->speed;
		//gpsData.course = msg->course;
		//gpsData.hdop = msg->hdop;
		//gpsData.vdop = msg->vdop;
		//gpsData.pdop = msg->pdop;

		//ROS_INFO("valid: %d",gpsData.valid);
		//ROS_INFO("lat: %f", gpsData.lat);
		//ROS_INFO("lng: %f", gpsData.lng);
		//ROS_INFO("alt: %f", gpsData.alt);
		//ROS_INFO("speed: %f", gpsData.speed);
		//ROS_INFO("hdop: %f", gpsData.hdop);
		//ROS_INFO("vdop: %f", gpsData.vdop);
		//ROS_INFO("pdop: %f", gpsData.pdop);
	
//	}


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

void magCallback(const raspberry_msgs::Mag::ConstPtr& msg){

	magData.x = msg->m_x;
	magData.y = msg->m_y;
	magData.z = msg->m_z;

	//ROS_INFO("a_x: %f", accData.x);

	//ROS_INFO("a_y: %f", accData.y);
	//ROS_INFO("a_z: %f", accData.z);

}

void velCallback(const geometry_msgs::Point32::ConstPtr& msg){

	velData.dir = msg->x*2*PI;
	velData.esq = msg->y*2*PI;

}

void paradaCallback(const std_msgs::Bool::ConstPtr& msg){

	parar = msg->data;

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

float quaternion2euler_yaw(MatrixXf q){

	double t1 = 2.0*(q(0,0)*q(3,0) + q(1,0)*q(2,0));
	double t2 = 1.0 - 2.0*(q(2,0)*q(2,0) + q(3,0)*q(3,0));
	float yaw = atan2(t1,t2);

	return yaw;
}

MatrixXf predicao(MatrixXf anterior){

	MatrixXf q_anterior(4,1), v_anterior(3,1), r_anterior(3,1);

	q_anterior << anterior(0,0), 0, 0, anterior(3,0);
	v_anterior << anterior(4,0), anterior(5,0), anterior(6,0);
	r_anterior << anterior(7,0), anterior(8,0), anterior(9,0);

	//Predicao atitude
	MatrixXf W(4,4), orient(4,1);
	W << 0, gyroData.x, gyroData.y, gyroData.z,
	     -gyroData.x, 0, -gyroData.z, gyroData.y,
	     -gyroData.y, gyroData.z, 0, -gyroData.x,
	     -gyroData.z, -gyroData.y, gyroData.x, 0;

	W = -W*tAmostragem;
	//orient = W.exp()*q_anterior;
	//orient(1,0) = 0;
	//orient(2,0) = 0;
	
	//orient = orient/orient.norm();

	//Predicao posicao acc
//	MatrixXf C(3,3), vel(3,1), pos(3,1), acc(3,1);

//	C << pow(q_anterior(0,0),2)+pow(q_anterior(1,0),2)-pow(q_anterior(2,0),2)-pow(q_anterior(3,0),2), 2*q_anterior(1,0)*q_anterior(2,0) + 2*q_anterior(0,0)*q_anterior(3,0), 2*q_anterior(1,0)*q_anterior(3,0) - 2*q_anterior(0,0)*q_anterior(2,0),
// 	     2*q_anterior(1,0)*q_anterior(2,0) - 2*q_anterior(0,0)*q_anterior(3,0), pow(q_anterior(0,0),2)-pow(q_anterior(1,0),2)+pow(q_anterior(2,0),2)-pow(q_anterior(3,0),2), 2*q_anterior(2,0)*q_anterior(3,0) + 2*q_anterior(0,0)*q_anterior(1,0),
//	     2*q_anterior(1,0)*q_anterior(3,0) + 2*q_anterior(0,0)*q_anterior(2,0), 2*q_anterior(2,0)*q_anterior(3,0) - 2*q_anterior(0,0)*q_anterior(1,0), pow(q_anterior(0,0),2)-pow(q_anterior(1,0),2)-pow(q_anterior(2,0),2)+pow(q_anterior(3,0),2);	 
 
//	acc << accData.x, accData.y, accData.z;	

//	std::cout << C*acc << std::endl;
//	std::cout << "\n";

//	vel = (C*acc + G)*tAmostragem + v_anterior;
//	pos = (C*acc + G)*tAmostragem*tAmostragem/2 + v_anterior*tAmostragem +  r_anterior;
	
//	if(velData.x == 0) vel(0,0) = 0;
//	if(velData.y == 0) vel(1,0) = 0;
//	if(velData.z == 0) vel(2,0) = 0;

	//Predicao posicao odometria

	// velocidade em x e y, matriz de rotacao, velocidades de rotacao das rodas
	MatrixXf vel(2,1), t(2,2), rot(2,1), pos(3,1), t_angular(1,2),v_angular(1,1); 
	
	t << r/2*cos(quaternion2euler_yaw(q_anterior)), r/2*cos(quaternion2euler_yaw(q_anterior)),
	     r/2*sin(quaternion2euler_yaw(q_anterior)), r/2*sin(quaternion2euler_yaw(q_anterior));

	//t_angular <<  r/B, -r/B;

	rot << velData.dir, velData.esq;
	//v_angular = -t_angular*rot;
	vel = t*rot;
	pos = v_anterior*tAmostragem + r_anterior;
	
	float yaw = quaternion2euler_yaw(q_anterior) - v_angular(0,0)*tAmostragem;

	float ta = cos(yaw/2);
	float tb = sin(yaw/2);

	orient << ta, 0, 0, tb;
	orient = orient/ orient.norm();

	MatrixXf est(10,1);

	est << orient, vel,0, pos;
	
	//std::cout << W << std::endl;

	return est;
}

Eigen::Quaternionf quatMult(Eigen::Quaternionf q1, Eigen::Quaternionf q2) {
    Eigen::Quaternionf resultQ;
    resultQ.setIdentity();

    resultQ.w() = q1.w() * q2.w() - q1.vec().dot(q2.vec());
    resultQ.vec() = q1.w() * q2.vec() + q2.w() * q1.vec() + q1.vec().cross(q2.vec());

    return resultQ;
}

//Correção da atitude pela fusão do acc e do mag
MatrixXf TRIAD(MatrixXf anterior){

		
	float mod_g = sqrt(pow(accData.x,2)+pow(accData.y,2)+pow(accData.z,2));
	if(std::abs(std::abs(mod_g) - std::abs(g)) > ERRO )
		return anterior;

	Vector3f g_unitario_b;
	g_unitario_b << accData.x, accData.y, accData.z;
	g_unitario_b = g_unitario_b/mod_g;

	// std::cout << g_unitario_b << std::endl;

	float mod_m = sqrt(pow(magData.x,2)+pow(magData.y,2)+pow(magData.z,2));
	Vector3f m_unitario_b;
	m_unitario_b << magData.x, magData.y, magData.z;
	m_unitario_b = m_unitario_b/mod_m;

	//std::cout << "n: "<< m_unitario_n << std::endl;
	//std::cout << "b: "<<  mod_m << std::endl;

	Vector3f i_n;
	Vector3f j_n;
	Vector3f k_n;
	
	Vector3f soma_n;
	Vector3f sub_n;
	
	soma_n = g_unitario_n+m_unitario_n;

    i_n = soma_n/soma_n.norm();
    
    sub_n = i_n.cross(g_unitario_n-m_unitario_n);
    
	j_n = sub_n/sub_n.norm();
	k_n = i_n.cross(j_n);

	Vector3f i_b;
	Vector3f j_b;
	Vector3f k_b;
	
	Vector3f soma_b;
	Vector3f sub_b;
	
	soma_b = g_unitario_b+m_unitario_b;
 
 	i_b = soma_b/soma_b.norm();
 	
 	sub_b = i_b.cross(g_unitario_b-m_unitario_b);
 	
	j_b = sub_b/sub_b.norm();
	k_b = i_b.cross(j_b);

	MatrixXf C_n(3,3);
	MatrixXf C_b(3,3);
	MatrixXf C_n_b(3,3);

	C_n << i_n,j_n,k_n;
	C_b << i_b, j_b, k_b;
	C_n_b = C_b*C_n.transpose();

//	std::cout << C_n_b << std::endl;

	float q0 = sqrt(1 + C_n_b(0,0) + C_n_b(1,1) + C_n_b(2,2))/2;
	float q1 = (C_n_b(2,1) - C_n_b(1,2))/(4*q0);
	float q2 = (C_n_b(0,2) - C_n_b(2,0))/(4*q0);
	float q3 = (C_n_b(1,0) - C_n_b(0,1))/(4*q0);

	MatrixXf orient(4,1);
	orient << q0, q1, q2, q3;	
	
	float declination = toRadian(13.4593);
	MatrixXf q_declination(4,1);

	float ta = cos(declination/2);
        float tb = sin(declination/2);

        q_declination << ta, 0, 0, tb;
	//std::cout << q_declination << std::endl;
	Quaternionf q_orient;
	q_orient = quatMult(Quaternionf(orient(0,0), orient(1,0), orient(2,0), orient(3,0)), Quaternionf(q_declination(0,0),q_declination(1,0), q_declination(2,0), q_declination(3,0)));
	orient  << q_orient.w(), q_orient.x(), q_orient.y(), q_orient.z();
	
	

	return orient;

}

//Correção da posição e velocidade pela medicao do GPS e da atitude pelo algoritmo TRIAD
MatrixXf medicao(GPSCoord ref, MatrixXf q_anterior){

	MatrixXf pos(3,1), vel(2,1), orient(4,1);
	NEDCoord pointNed;
	GPSCoord pointGPS;


	pointGPS.lat = gpsData.lat;
	pointGPS.lng = gpsData.lng;
	pointGPS.alt = 0;

	static std::chrono::high_resolution_clock::time_point t1 = std::chrono::high_resolution_clock::now();
	std::chrono::high_resolution_clock::time_point t = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double> time_span = std::chrono::duration_cast<std::chrono::duration<double>>(t-t1);
	//ROS_INFO("tempo: %f", time_span.count());
	//ROS_INFO("lat m: %f",pointGPS.lat );
	//ROS_INFO("lng m: %f", pointGPS.lng);
	
//	std::cout << "ref: " << ref.lat << " " << ref.lng << std::endl;
//	std::cout << "coord: " << pointGPS.lat << " " << pointGPS.lng  << std::endl;

	pointNed = GPS2NED(pointGPS, ref);

//	ROS_INFO("NED x: %f", pointNed.x);
//	ROS_INFO("NED y: %f", pointNed.y);

	pos << pointNed.x, pointNed.y, 0;

	//std::cout << pos << std::endl;

	//orient << q_anterior;
	orient = TRIAD(q_anterior);

	//float speed = gpsData.speed/3.6;
	//float course = toRadian(gpsData.course);
	
	//float ta = cos(course/2);
	//float tb = sin(course/2);

	//orient << ta, 0, 0, tb;

	//coreecao com a velocidade do gps
	//float yaw;

	//double ta = 2*(orient(0,0)*orient(3,0) + orient(1,0)*orient(2,0));
	//double tb = 1 - 2*(orient(2,0)*orient(2,0) + orient(3,0)*orient(3,0));
	//yaw =  atan2(ta,tb);
	
	//vel(0,0) = speed*cos(yaw);
	//vel(1,0) = speed*sin(yaw);
	//vel(2,0) = 0;

	//correcao velocidade estimada
	MatrixXf tr(2,2), rot(2,1);

	tr << r/2*cos(quaternion2euler_yaw(q_anterior)), r/2*cos(quaternion2euler_yaw(q_anterior)),
             r/2*sin(quaternion2euler_yaw(q_anterior)), r/2*sin(quaternion2euler_yaw(q_anterior));


        rot << velData.dir, velData.esq;

        vel = tr*rot;

		
//	std::cout<< vel << std::endl;
//	std::cout<< ""<< std::endl;
//	std::cout<< orient << std::endl;
	MatrixXf med(10,1);
	
	med << orient, vel,0, pos;

	return med;

}

MatrixXf jacobianaPredicao(MatrixXf anterior){

	MatrixXf A(10,10), orient(4,4);

	MatrixXf W(4,4), acc(3,1);
	
	MatrixXf q_anterior(4,1);
	
	q_anterior << anterior(0,0), anterior(1,0), anterior(2,0), anterior(3,0);

	W << 0, -gyroData.x, -gyroData.y, -gyroData.z,
	     gyroData.x, 0, gyroData.z, -gyroData.y,
	     -gyroData.y, gyroData.z, 0, -gyroData.x,
	     -gyroData.z, -gyroData.y, gyroData.x, 0;

	W = -W*tAmostragem;
	orient = W.exp()/orient.norm();

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
	
	//A(4,0) = -r/2*sin(quaternion2euler_yaw(q_anterior))*2*q_anterior(3,0)*(1 - 2*q_anterior(3,0)*q_anterior(3,0))/((1 - 2*q_anterior(3,0)*q_anterior(3,0)) *(1 - 2*q_anterior(3,0)*q_anterior(3,0)) + (2*q_anterior(0,0)*q_anterior(3,0)*2*q_anterior(0,0)*q_anterior(3,0)));
	//A(4,1) = 0; 
	//A(4,2) = 0;
	//A(4,3) = -r/2*sin(quaternion2euler_yaw(q_anterior))*2*q_anterior(0,0)*(2*q_anterior(3,0)*q_anterior(3,0) + 1)/((1 - 2*q_anterior(3,0)*q_anterior(3,0))*(1 - 2*q_anterior(3,0)*q_anterior(3,0)) - (2*q_anterior(0,0)*q_anterior(3,0)*2*q_anterior(0,0)*q_anterior(3,0)));

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
	
	//A(5,0) =  r/2*cos(quaternion2euler_yaw(q_anterior))*2*q_anterior(3,0)*(1 - 2*q_anterior(3,0)*q_anterior(3,0))/((1 - 2*q_anterior(3,0)*q_anterior(3,0)) *(1 - 2*q_anterior(3,0)*q_anterior(3,0)) + (2*q_anterior(0,0)*q_anterior(3,0)*2*q_anterior(0,0)*q_anterior(3,0)));
	//A(5,1) = 0;
	//A(5,2) = 0;
	//A(5,3) = r/2*cos(quaternion2euler_yaw(q_anterior))*2*q_anterior(0,0)*(2*q_anterior(3,0)*q_anterior(3,0) + 1)/((1 - 2*q_anterior(3,0)*q_anterior(3,0))*(1 - 2*q_anterior(3,0)*q_anterior(3,0)) - (2*q_anterior(0,0)*q_anterior(3,0)*2*q_anterior(0,0)*q_anterior(3,0)) );
	
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
	
	//A(6,0) = 0;
	//A(6,1) = 0;
	//A(6,2) = 0;
	//A(6,3) = 0;
	
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
	
	//A(7,0) = 0;
	//A(7,1) = 0;
	//A(7,2) = 0;
	//A(7,3) = 0;


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
	
	//A(8,0) = 0;
	//A(8,1) = 0;
	//A(8,2) = 0;
	//A(8,3) = 0;
		
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
	
	//A(9,0) = 0;
	//A(9,1) = 0;
	//A(9,2) = 0;
	//A(9,3) = 0;

	A(9,4) = 0;
	A(9,5) = 0; 
	A(9,6) = tAmostragem;
	A(9,7) = 0;
	A(9,8) = 0;
	A(9,9) = 1;

	return A;

}

MatrixXf jacobianaCorrecao(){

	MatrixXf C(10,10), C_O(4,4);
	
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


int main(int argc, char **argv){	

	//Variaveis ROS
  	ros::init(argc, argv, "filtro");
	ros::NodeHandle n;
	ros::Subscriber subGPS = n.subscribe("gpsInfo", 1000, GPSCallback);
	ros::Subscriber subGyro = n.subscribe("gyroInfo", 1000, gyroCallback);
	ros::Subscriber subAcc = n.subscribe("accInfo", 1000, accCallback);
	ros::Subscriber subMag = n.subscribe("magInfo", 1000, magCallback);
	ros::Subscriber subVel = n.subscribe("velocidade_atual", 1000, velCallback);	
	ros::Subscriber subParada = n.subscribe("parada", 1000, paradaCallback);

	ros::Publisher odom_pub = n.advertise<nav_msgs::Odometry>("odom", 50);
  	ros::Publisher origin_pub = n.advertise<geometry_msgs::Point32>("origin", 50,true);
  	ros::Publisher odom_ok = n.advertise<std_msgs::Bool>("odom_ok", 50);
	ros::Publisher correcao_pub = n.advertise<std_msgs::Bool>("correcao", 50);

	ros::Time current_time;
	
	ros::Rate loop_rate(20);

	geometry_msgs::Point32 origin;
  	std_msgs::Bool odomOK;
	nav_msgs::Odometry odom;

	//Variaveis GPS
	GPSCoord ref;
	float courseInicial = 0;
	std_msgs::Bool corrigi;
	corrigi.data = false;
	parar = 0;

	ref.lat = 0;
	ref.lng = 0;
	ref.alt = 0;

	//Variaveis filtro
	MatrixXf x_estPriori(10,1); // [q0 q1 q2 q3 vx vy vz rx ry rz] 
	MatrixXf x_estPosteriori(10,1); 
	MatrixXf x_medido(10,1);
	MatrixXf P_priori(10,10), P_posteriori(10,10);
	MatrixXf Q(10,10), H(10,10), H_O(4,4), F(10,10), KG(10,10);
	MatrixXf M(10,1);

	MatrixXf q_anterior(4,1);

	G << 0,0,g;

	//Variaveis TRIAD
	g_unitario_n << 0, 0, 1;
	m_unitario_n << 22.6254, 5.4149, -42.3674;
	m_unitario_n = m_unitario_n/m;

	H = jacobianaCorrecao();
	H_O.setIdentity();

	I10.setIdentity();
	Z10.setZero();
	Z10.topLeftCorner(4,4).setIdentity();

	x_estPosteriori << 1, 0, 0, 0, 0, 0, 0, 0, 0, 0;
	//q_anterior << 0,0,0,1;
	P_posteriori = I10*0.0001;
	//estimacao
	Q  = I10*0.0001;
	//correcao 
	R = I10*0.01;
	
	int flagSetup = 0;
	ros::Time tInicial = ros::Time::now();
	int count = 0, countParada = 0;		


	while (ros::ok()){

		//Setup para pegar posição inicial
		if (flagSetup){	
	       
			if(gpsData.valid){
			
	        	std::cout << "setup" << std::endl;
	            odomOK.data = true;

				ref.lat += gpsData.lat;
				ref.lng += gpsData.lng;
				ref.alt += gpsData.alt;
				q_anterior = TRIAD(q_anterior);
				count++;



			}else{
	            		odomOK.data = false;
	         		ref.lat = 0; ref.lng = 0; ref.alt = 0; courseInicial = 0;
			}

			if(ros::Time::now().toSec() - tInicial.toSec() > 30){
				
				ref.lat = ref.lat/count;
                                ref.lng = ref.lng/count;

				if((ref.lat != ref.lat || ref.lng !=ref.lng) || ref.lat > LAT + L_ERRO || ref.lat < LAT - L_ERRO || ref.lng < LNG - L_ERRO || ref.lng > LNG + L_ERRO ){
					flagSetup = 1;
					count = 0;
					ref.lat = 0;
					ref.lng = 0;
					tInicial = ros::Time::now();
				}else{
					ref.alt = 0; 
					flagSetup = 0;
					std::cout << q_anterior << std::endl;
                                	x_estPosteriori(0,0) = q_anterior(0,0);
                                	x_estPosteriori(1,0) = q_anterior(1,0);
                                	x_estPosteriori(2,0) = q_anterior(2,0);
                               		x_estPosteriori(3,0) = q_anterior(3,0);
					origin.x = ref.lat;
                    			origin.y = ref.lng;
                    			origin_pub.publish(origin);
				}
				
	     
			}

		//Filtro	
		}else{

			x_estPosteriori << 1,0,0,0,0,0,0,0,0,0;

			// Estimação
			x_estPriori = predicao(x_estPosteriori);
			//F = jacobianaPredicao(x_estPosteriori);
			//P_priori = F + P_posteriori*F.transpose() + Q;
			
			#ifdef debug_priori
			std::cout << x_estPriori << std::endl;
			ROS_INFO("");
			std:: cout << "\n";
			#endif

			#ifdef debug_covarPriori
			std::cout << P_priori << std::endl;
			std:: cout << "\n";
			#endif

			// Correcao 
			//KG = P_priori*H.transpose()*(H*P_priori*H.transpose() + R).inverse();
			//M = medicao(ref, q_anterior);
	    	        //if (!parar){
				//KG = Z10*KG;
				//M = Z10*M;
		//	}else{

		//		while(countParada < 10){
		//			if(gpsData.updated){
		//				M = medicao(ref, q_anterior);
		//				countParada++;
		//			}
		//		}		
		//		M = M*(1/countParada);
		//		countParada = 0;
		//		corrigi.data = true;
		//		correcao_pub.publish(corrigi);
		//	}
				
			#ifdef debug_ganho
			std::cout << KG << std::endl;
			std:: cout << "\n";
			#endif
			x_estPosteriori = x_estPriori;
		//	x_estPosteriori = M;	
			x_estPosteriori = x_estPriori + KG*(M - x_estPriori);
		//	std::cout << "oi" << std::endl;	
			//P_posteriori = (I10 - KG*H)*P_priori;

			q_anterior << x_estPosteriori(0,0), x_estPosteriori(1,0), x_estPosteriori(2,0), x_estPosteriori(3,0);
		
			#ifdef debug_posteriori
			std::cout << x_estPosteriori << std::endl;
			std::cout << "\n";
			#endif
			
			#ifdef debug_covarPosteriori
			std::cout << P_posteriori << std::endl;
			std:: cout << "\n";
			#endif

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
	    	odom_ok.publish(odomOK);	
		}

		loop_rate.sleep();
	    ros::spinOnce();

	}


return 0;

}
























