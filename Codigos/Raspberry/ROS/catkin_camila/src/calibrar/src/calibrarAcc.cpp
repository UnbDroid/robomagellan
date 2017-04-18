/* Calibracao do acelerômetro:

Estimação dos parâmetros (bias e fator de escala) do acelerômetro pelo 
método de Gauss-Newton

Colocar o acelerômetro em pelo menos 7 posições estáricas diferentes 
e apertar q

*/

#include "ros/ros.h"
#include <wiringPiI2C.h>
#include <iostream>
#include <Eigen/Dense>
#include "math.h"
#include "rosbag/bag.h"
#include "raspberry_msgs/ParamAcc.h"

#define SCALE 0.0039
#define g 9.80665
#define iTotal 5
#define nMedidas 7

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

int Register_2D = 0x2D;
int Register_XL = 0x32;
int Register_XH = 0x33;
int Register_YL = 0x34;
int Register_YH = 0x35;
int Register_ZL = 0x36;
int Register_ZH = 0x37;

short acc_x = 0;
short acc_y = 0;
short acc_z = 0;

float a_x = 0;
float a_y = 0;
float a_z = 0;

int fd = wiringPiI2CSetup(0x53);
wiringPiI2CWriteReg8 (fd, Register_2D, 8);

rosbag::Bag bag;
bag.open("parametrosAcc.bag", rosbag::bagmode::Write);

raspberry_msgs::ParamAcc msg;

ros::init(argc, argv, "acc");
ros::NodeHandle n;
//----------------------------------------------------------------

MatrixXf theta; // Parâmetros [bx by bz sx sy sz]
MatrixXf G; // campo magnetico
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
		acc_x = read_word(fd,Register_XH,Register_XL);
		acc_y = read_word(fd,Register_YH,Register_YL);
		acc_z = read_word(fd,Register_ZH,Register_ZL);
			
		a_x += acc_x*SCALE*g;
		a_y += acc_y*SCALE*g;
		a_z += acc_z*SCALE*g;
		count++;
	}

	count = 0;
	fMedido(n,0) = a_x/30;
	fMedido(n,1) = a_y/30;
	fMedido(n,2) = a_z/30;

	a_x = 0;
	a_y = 0;
	a_z = 0;

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
G = G*9.7808439;

J = jacobiana(fMedido, theta.col(0));

int i = 0;

for(i = 1;i < iTotal;i++){

	J = jacobiana(fMedido, theta.col(i - 1));
	theta.col(i) = theta.col(i-1) - (J.transpose()*J).inverse()*J.transpose()*(G - F);

}

msg.bx = theta(0, i - 1);
msg.by = theta(1, i - 1);
msg.bz = theta(2, i - 1);
msg.sx = theta(3, i - 1);
msg.sy = theta(4, i - 1);
msg.sz = theta(5, i - 1);

bag.write("param_acc",ros::Time::now(),msg);

std::cout << "Parâmetros: " << std::endl;
std::cout << theta << std::endl;

bag.close();

return 0;

}
