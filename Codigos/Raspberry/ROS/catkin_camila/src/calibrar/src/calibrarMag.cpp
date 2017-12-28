/* Calibracao do acelerômetro:

Estimação dos parâmetros (bias e fator de escala) do acelerômetro pelo 
método de Gauss-Newton

Colocar o acelerômetro em pelo menos 7 posições estáricas diferentes 
e apertar q

*/

/*

#include "ros/ros.h"
#include <wiringPiI2C.h>
#include <iostream>
#include <Eigen/Dense>
#include "math.h"
#include "rosbag/bag.h"
#include "raspberry_msgs/ParamMag.h"

#define SCALE 0.00152
#define t 0.0001 
#define iTotal 1000
#define nMedidas 7
#define m  23.4622

using namespace Eigen;

MatrixXf F(nMedidas,1);

int read_word(int fd, int adr_h,int adr_l){

	short high = wiringPiI2CReadReg8 (fd,adr_h);
	int low = wiringPiI2CReadReg8 (fd,adr_l);
	int val = ((high << 8) + low);

	return val;

}

float fEstimado(VectorXf medidas, VectorXf param){

	float r = sqrt( pow(((medidas(0) - param(0))/param(3)),2) + pow(((medidas(1) - param(1))/param(4)),2) + pow(((medidas(2) - param(2))/param(5)),2) );
	
	return r;
}

MatrixXf jacobiana(MatrixXf medidas, VectorXf param){

	MatrixXf J(nMedidas,6);

	float f1 = fEstimado(medidas.row(0), param);
	float f2 = fEstimado(medidas.row(1), param);
	float f3 = fEstimado(medidas.row(2), param);
	float f4 = fEstimado(medidas.row(3), param);
	float f5 = fEstimado(medidas.row(4), param);
	float f6 = fEstimado(medidas.row(5), param);
	float f7 = fEstimado(medidas.row(6), param);

	F << f1,
	     f2,
	     f3,
             f4,
             f5, 
             f6,
             f7;

	J << (medidas(0,0) - param(0))/(pow(param(3),2)*f1), (medidas(0,1) - param(1))/(pow(param(4),2)*f1), (medidas(0,2) - param(2))/(pow(param(5),2)*f1), pow((medidas(0,0) - param(0)),2)/(pow(param(3),3)*f1), pow((medidas(0,1) - param(1)),2)/(pow(param(4),3)*f1), pow((medidas(0,2) - param(2)),2)/(pow(param(5),3)*f1),                  
	     (medidas(1,0) - param(0))/(pow(param(3),2)*f2), (medidas(1,1) - param(1))/(pow(param(4),2)*f2), (medidas(1,2) - param(2))/(pow(param(5),2)*f2), pow((medidas(1,0) - param(0)),2)/(pow(param(3),3)*f2), pow((medidas(1,1) - param(1)),2)/(pow(param(4),3)*f2), pow((medidas(1,2) - param(2)),2)/(pow(param(5),3)*f2),
	     (medidas(2,0) - param(0))/(pow(param(3),2)*f3), (medidas(2,1) - param(1))/(pow(param(4),2)*f3), (medidas(2,2) - param(2))/(pow(param(5),2)*f3), pow((medidas(2,0) - param(0)),2)/(pow(param(3),3)*f3), pow((medidas(2,1) - param(1)),2)/(pow(param(4),3)*f3), pow((medidas(2,2) - param(2)),2)/(pow(param(5),3)*f3),
	     (medidas(3,0) - param(0))/(pow(param(3),2)*f4), (medidas(3,1) - param(1))/(pow(param(4),2)*f4), (medidas(3,2) - param(2))/(pow(param(5),2)*f4), pow((medidas(3,0) - param(0)),2)/(pow(param(3),3)*f4), pow((medidas(3,1) - param(1)),2)/(pow(param(4),3)*f4), pow((medidas(3,2) - param(2)),2)/(pow(param(5),3)*f4),
	     (medidas(4,0) - param(0))/(pow(param(3),2)*f5), (medidas(4,1) - param(1))/(pow(param(4),2)*f5), (medidas(4,2) - param(2))/(pow(param(5),2)*f5), pow((medidas(4,0) - param(0)),2)/(pow(param(3),3)*f5), pow((medidas(4,1) - param(1)),2)/(pow(param(4),3)*f5), pow((medidas(4,2) - param(2)),2)/(pow(param(5),3)*f5),
	     (medidas(5,0) - param(0))/(pow(param(3),2)*f6), (medidas(5,1) - param(1))/(pow(param(4),2)*f6), (medidas(5,2) - param(2))/(pow(param(5),2)*f6), pow((medidas(5,0) - param(0)),2)/(pow(param(3),3)*f6), pow((medidas(5,1) - param(1)),2)/(pow(param(4),3)*f6), pow((medidas(5,2) - param(2)),2)/(pow(param(5),3)*f6),
	     (medidas(6,0) - param(0))/(pow(param(3),2)*f7), (medidas(6,1) - param(1))/(pow(param(4),2)*f7), (medidas(6,2) - param(2))/(pow(param(5),2)*f7), pow((medidas(6,0) - param(0)),2)/(pow(param(3),3)*f7), pow((medidas(6,1) - param(1)),2)/(pow(param(4),3)*f7), pow((medidas(6,2) - param(2)),2)/(pow(param(5),3)*f7);

	return J;

}

int main(int argc, char **argv){

	int Register_A = 0x00;
	int Register_B = 0x01;
	int Register_Mode = 0x02;
   	int Register_XL = 0x04;
   	int Register_XH = 0x03;
   	int Register_YL = 0x08;
   	int Register_YH = 0x07;
   	int Register_ZL = 0x06;
   	int Register_ZH = 0x05;

	short mag_x = 0;
	short mag_y = 0;
	short mag_z = 0;

float m_x = 0;
float m_y = 0;
float m_z = 0;

int fd = wiringPiI2CSetup(0x1E);

	wiringPiI2CWriteReg8 (fd, Register_A,  0x38);  //
	wiringPiI2CWriteReg8 (fd, Register_B,  0x60); 
	wiringPiI2CWriteReg8 (fd, Register_Mode,  0x00); 

rosbag::Bag bag;
bag.open("parametrosMag.bag", rosbag::bagmode::Write);

raspberry_msgs::ParamMag msg;

ros::init(argc, argv, "mag");
ros::NodeHandle n;
//----------------------------------------------------------------

MatrixXf theta; // Parâmetros [bx by bz sx sy sz]
MatrixXf G; // Aceleracao da gravidade
MatrixXf fMedido(nMedidas,3); //Medidas do sensor em diferentes posiçõeçs [x y z]
MatrixXf J(nMedidas,6); //Jacobiana do erro

//Aquisiçaão de dados
//----------------------------------------------------------------

char c = 'a';
int count = 0;

for(int n = 0;n < nMedidas; n++){

	while(c != 'q'){
		std::cout << "Esperando" << std::endl;
		std::cin >> c;
	}	
	
	c = 'a';

	while(count < 30){
	
		mag_x = read_word(fd,Register_XH,Register_XL);
		mag_y = read_word(fd,Register_YH,Register_YL);
		mag_z = read_word(fd,Register_ZH,Register_ZL);
			
		m_x += mag_x*SCALE*t*1e6;
		m_y += mag_y*SCALE*t*1e6;
		m_z += mag_z*SCALE*t*1e6;
		count++;
	}

	count = 0;
	fMedido(n,0) = m_x/30;
	fMedido(n,1) = m_y/30;
	fMedido(n,2) = m_z/30;

	m_x = 0;
	m_y = 0;
	m_z = 0;

	std::cout << "x: " << fMedido(n,0) << " y: " << fMedido(n,1) << " z: " << fMedido(n,2) << std::endl;
	

}

//Métdo de Gauss-Newton
//----------------------------------------------------------------
theta.setZero(6, iTotal);
theta.col(0) << 0.0,
		0.0,
		0.0,
		1.0,
		1.0,
		1.0; 

G.setOnes(nMedidas,1);
G = G*m;

std::cout <<"campo magnético: " <<  G  << std::endl;

J = jacobiana(fMedido, theta.col(0));

int i = 0;

for(i = 1;i < iTotal;i++){

	J = jacobiana(fMedido, theta.col(i - 1));
	theta.col(i) = theta.col(i-1) - 0.01*(J.transpose()*J).inverse()*J.transpose()*(G - F);

}

msg.bx = theta(0, i - 1);
msg.by = theta(1, i - 1);
msg.bz = theta(2, i - 1);
msg.sx = theta(3, i - 1);
msg.sy = theta(4, i - 1);
msg.sz = theta(5, i - 1);

bag.write("param_mag",ros::Time::now(),msg);

//wiringPiI2CWriteReg8 (fd, Register_Mode,  0x01); 
mag_x = read_word(fd,Register_XH,Register_XL);
mag_y = read_word(fd,Register_YH,Register_YL);
mag_z = read_word(fd,Register_ZH,Register_ZL);
			
m_x = (mag_x*SCALE*t*1000000.0 - msg.bx)/msg.sx	;
m_y = (mag_y*SCALE*t*1000000.0 - msg.by)/msg.sy;
m_z = (mag_z*SCALE*t*1000000.0 - msg.bz)/msg.sz;

std::cout << "Parâmetros: " << std::endl;
std::cout << theta.col(i-2) << std::endl;
std::cout << theta.col(i-1) << std::endl;
std::cout << "Medidas: " << std::endl;
std::cout << "x:  " << m_x << " y: " << m_y << " z: " << m_z << std::endl;



bag.close();

return 0;

}*/

#include <wiringPiI2C.h>
#include "ros/ros.h"
#include "rosbag/bag.h"
#include "raspberry_msgs/ParamMag.h"
#include <time.h>

ros::Time tempo;

#define SCALE 0.15

short read_word(int fd, int adr_h,int adr_l){

	char high = wiringPiI2CReadReg8 (fd,adr_h);
//	ROS_INFO("High %d",high);
	char st2h = wiringPiI2CReadReg8 (fd,0x09);
	char low = wiringPiI2CReadReg8 (fd,adr_l);
	char st2l = wiringPiI2CReadReg8 (fd,0x09);
//	ROS_INFO("Low %d",low);
	
	short val = 0;

	if(!(st2h&0x08) && !(st2l&0x08))
		val = ((high << 8) + low);
//	ROS_INFO("Val %d", val);
	return val;

}


int main(int argc, char **argv){
 
    int Register_BypassEn = 0x37;
	
	int Register_Control = 0x0A;
   	int Register_XL = 0x03;
   	int Register_XH = 0x04;
   	int Register_YL = 0x05;
   	int Register_YH = 0x06;
   	int Register_ZL = 0x07;
   	int Register_ZH = 0x08;
   	int Register_ST1 = 0x02;
   	int Register_ST2 = 0x09;

	short mag_x = 0;
	short mag_y = 0;
	short mag_z = 0;
	short mag_st2;
	
	float m_x = 0;
	float m_y = 0;
	float m_z = 0;

	//mpu adress
	int fd_mpu = wiringPiI2CSetup(0x68);
	
	// enable bypass mode (pra ler o mag)
	wiringPiI2CWriteReg8 (fd_mpu, Register_BypassEn,  0x02);  // 

	// mag adress
	int fd = wiringPiI2CSetup(0x0C);
	//std::cout << "fd: " << fd << std::endl;

	wiringPiI2CWriteReg8 (fd, Register_Control,  0x16);
	
	ros::init(argc, argv, "mag");
	ros::NodeHandle n;
	ros::Rate loop_rate(100);

	rosbag::Bag bag;
	bag.open("parametrosMag.bag", rosbag::bagmode::Write);

	raspberry_msgs::ParamMag msg;

	int count = 0;

	ros::Time tInicial = ros::Time::now();
	while ((ros::Time::now().toSec() - tInicial.toSec()) < 30){

		mag_x = read_word(fd,Register_XH,Register_XL);
		mag_y = read_word(fd,Register_YH,Register_YL);
		mag_z = read_word(fd,Register_ZH,Register_ZL);
		
		m_x += (mag_x*SCALE);
       	m_y += (mag_y*SCALE);
       	m_z += (mag_z*SCALE);

		ROS_INFO("%d", mag_x);
		ROS_INFO("%d", mag_y);
		ROS_INFO("%d", mag_z);

		ros::spinOnce();
	
	    	loop_rate.sleep();
	    	++count;
	}
	
	msg.bx = (m_x/count) - 19.452;
	msg.by = (m_y/count) + 7.668;
	msg.bz = (m_z/count) + 10.640;

	bag.write("param_mag",ros::Time::now(),msg);
	
	ROS_INFO("\n\n");

	ROS_INFO("x: %f", msg.bx);
	ROS_INFO("y: %f", msg.by);
	ROS_INFO("z: %f", msg.bz);

	bag.close();

 return 0;
}



