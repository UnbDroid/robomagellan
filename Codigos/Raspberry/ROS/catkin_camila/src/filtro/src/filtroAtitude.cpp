#include "ros/ros.h"
#include "raspberry_msgs/Gyro.h"
#include "raspberry_msgs/Acc.h"
#include "math.h"
#include <Eigen/Dense>
#include <iostream>

#define PI 3.14159265
#define tAmostragem 0.01

using namespace Eigen;

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


GyroData gyroData;
AccData accData;

MatrixXf jacobiana(MatrixXf posteriori){

	float sx = gyroData.x*tAmostragem;
	float sy = gyroData.y*tAmostragem;
	float sz = gyroData.z*tAmostragem;

	float v = sqrt(pow(sx,2) + pow(sy,2) + pow(sz,2));

	MatrixXf A(4,4);

	A << cos(v/2), sx*sin(v/2)/v, sy*sin(v/2)/v, sz*sin(v/2)/v,
             -sx*sin(v/2)/v, cos(v/2), -sz*sin(v/2)/v, sy*sin(v/2)/v,
	     -sy*sin(v/2)/v, sz*sin(v/2)/v, cos(v/2), -sx*sin(v/2)/v,
   	     -sz*sin(v/2)/v, -sy*sin(v/2)/v, sx*sin(v/2)/v, cos(v/2);

	return A*posteriori; 

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

	ROS_INFO("a_x: %d", accData.x);
	ROS_INFO("a_y: %d", accData.y);
	ROS_INFO("a_z: %d", accData.z);

}

int main(int argc, char **argv)
{
  	ros::init(argc, argv, "filtroAtitude");
	ros::NodeHandle n;
	ros::Subscriber subGyro = n.subscribe("gyroInfo", 1000, gyroCallback);
	ros::Subscriber subAcc = n.subscribe("accInfo", 1000, accCallback);
	
	ros::Rate loop_rate(100);

	MatrixXf q_estPriori(4,1);
	MatrixXf q_estPosteriori(4,1);

	q_estPosteriori << 1,
		           0,
		           0,
                           0;

	while (ros::ok()){

		q_estPriori = jacobiana(q_estPosteriori);
		q_estPosteriori = q_estPriori;

		std::cout << q_estPriori << std::endl;
		
		
		loop_rate.sleep();
       		ros::spinOnce();

	}

	




return 0;

}



