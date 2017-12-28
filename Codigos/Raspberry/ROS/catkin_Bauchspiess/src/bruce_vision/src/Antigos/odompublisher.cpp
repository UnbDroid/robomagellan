#include <unistd.h>
#include <sstream>
#include "ros/ros.h"
#include "std_msgs/String.h"
#include <rosbag/bag.h>
#include <rosbag/view.h>
#include <geometry_msgs/Point32.h>
#include "geometry_msgs/PoseStamped.h"


#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <sys/time.h>
#include <boost/foreach.hpp>

#include "opencv2/opencv.hpp"
#include "opencv2/calib3d/calib3d.hpp"
#include "opencv2/core/core.hpp"
#include <cv.h>
#include <highgui.h>



using namespace std;
using namespace cv;

void int_to_string(int valor, string* numeral){
  int inteiro = valor;
  int resto = valor;
  do{
    resto = inteiro%10;
    inteiro = inteiro/10;
    (*numeral).push_back( (char)(resto + 48) );
  }while(inteiro > 0);
  reverse((*numeral).begin(),(*numeral).end()); 
}

void float_to_string(float valor, string* numeral, int casas)
{
	bool neg = false;
  numeral->clear();
  if(valor < 0){
  	(*numeral) = "-";
  	neg = true;
  	valor = fabs(valor);
  }
  int val = valor;
  string aux;
  int_to_string(val,&aux);
  if(neg)
  	(*numeral) = (*numeral)+aux + ".";
  else
  	(*numeral) = aux + ".";
  valor -= val;
  valor *= pow(10,casas);
  val = valor;
  aux.clear();
  int_to_string(val,&aux);
  (*numeral) = (*numeral)+aux;
}


void grafico(float vd, float ve)
{
	static float VD[50];
	static float VE[50];
	static int index = 0;
	static bool maximo = false;
	int fim, i, j;


	VD[index] = vd;
	VE[index] = ve;

	if(maximo){
		fim = 49;
		j = index+1;
		if(j>=50)
			j=0;
	}
	else{
		fim = index;
		j = 0;
	}


	float vel_d = VD[j];
	float vel_e = VD[j];

	float maior = 0;

	for(i=0;i<=fim;i++)
	{
		if( fabs(VD[j]) > maior)
			maior = fabs(VD[j]);
		if(fabs(VE[j]) > maior)
			maior = fabs(VE[j]);
		j++;
		if(j>=50)
			j=0;
	}


	Mat mostra(500,500,CV_8UC3);
	mostra = Scalar(255,255,255);


	arrowedLine(mostra, Point(100,500),Point(100,0),Scalar(0,0,0));
	arrowedLine(mostra,Point(100,250),Point(500,250),Scalar(0,0,0));

	imshow("vel",mostra);



	index++;
	if(index>=50)
	{
		maximo = true;
		index = 0;
	}

}

int main(int argc, char **argv)
{

	ros::init(argc, argv, "odom");
	ros::NodeHandle n;
	ros::Publisher chatter_pub = n.advertise<geometry_msgs::Point32>("velocidade_atual", 1000);
	ros::Rate loop_rate(10);
	geometry_msgs::Point32 msg;


	
	rosbag::Bag bag;
    bag.open("odom5.bag", rosbag::bagmode::Read);
    

    std::vector<std::string> topics;
    topics.push_back(std::string("odom_data"));

    rosbag::View view(bag, rosbag::TopicQuery(topics));

	BOOST_FOREACH(rosbag::MessageInstance const m, view)
	{
	   	if (m.getTopic() == "odom_data") 
		{
		    geometry_msgs::Point32::ConstPtr odom_vel = m.instantiate<geometry_msgs::Point32>();
		    if (odom_vel != NULL){
		    	//cout<<"tb  ";
		        chatter_pub.publish(*odom_vel);
		        //grafico(cam_pos->x,cam_pos->y);
		    }
		}
		if(!(ros::ok()) )
			break;
		loop_rate.sleep();
	}
	
	bag.close();
	


}