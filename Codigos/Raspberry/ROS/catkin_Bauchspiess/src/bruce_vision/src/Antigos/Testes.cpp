#define USEBAG
#define usuario
#include "RastreiaCone.hpp"

#include <sys/time.h>
#include "ros/ros.h"
#include "std_msgs/String.h"

#include <unistd.h>

#include <sstream>

#include "ros/serialization.h"
#include "ros/builtin_message_traits.h"
#include "ros/message_operations.h"
#include "ros/message.h"
#include "ros/time.h"
#include <rosbag/bag.h>
#include <rosbag/view.h>

#include <geometry_msgs/Point32.h>


using namespace cv;
using namespace std;

RastreiaCone cone;

int comando;

bool p2 = false;
bool p3 = false;
bool p4 = false;


void Painel2(){
	namedWindow( "PAINEL 2", WINDOW_NORMAL );
	resizeWindow("PAINEL 2", 250, 1);
	createTrackbar( "minL", "PAINEL 2", &cone.minB, 256);
	createTrackbar( "maxL", "PAINEL 2", &cone.maxB, 256);
	createTrackbar( "minA", "PAINEL 2", &cone.minG, 256);
	createTrackbar( "maxA", "PAINEL 2", &cone.maxG, 256);
	createTrackbar( "minB", "PAINEL 2", &cone.minR, 256);
	createTrackbar( "maxB", "PAINEL 2", &cone.maxR, 256);
	createTrackbar( "minaceita", "PAINEL 2", &cone.min_aceita, 256);
	createTrackbar( "aceitafinal", "PAINEL 2", &cone.aceita_final, 256);
}

void Painel3(){
	namedWindow( "PAINEL 3", WINDOW_NORMAL );
	resizeWindow("PAINEL 3", 250, 1);
	createTrackbar( "minLo", "PAINEL 3", &cone.minBo, 256);
	createTrackbar( "maxLo", "PAINEL 3", &cone.maxBo, 256);
	createTrackbar( "minAo", "PAINEL 3", &cone.minGo, 256);
	createTrackbar( "maxAo", "PAINEL 3", &cone.maxGo, 256);
	createTrackbar( "minBo", "PAINEL 3", &cone.minRo, 256);
	createTrackbar( "maxBo", "PAINEL 3", &cone.maxRo, 256);
}


void Painel4(){


	namedWindow( "PAINEL 4", WINDOW_NORMAL );
	resizeWindow("PAINEL 4", 250, 1);
	createTrackbar( "minLo", "PAINEL 4", &cone.difLo, 50);
	createTrackbar( "maxLo", "PAINEL 4", &cone.difLb, 50);
	createTrackbar( "minAo", "PAINEL 4", &cone.difAo, 50);
	createTrackbar( "maxAo", "PAINEL 4", &cone.difAb, 50);
	createTrackbar( "minBo", "PAINEL 4", &cone.difBo, 50);
	createTrackbar( "maxBo", "PAINEL 4", &cone.difBb, 50);
	createTrackbar( "maxdif", "PAINEL 4", &cone.max_dif, 100);

}



bool Comando(bool aberta ){
	comando = waitKey(1);
		switch(comando){
			case('p'):
				if(cone.atualiza){
					cone.atualiza = false;
				}	
				else{
					cone.atualiza = true;
				}	
				break;
			case(50):
				if(p2){
					p2 = false;
					destroyWindow("PAINEL 2");
				}
				else{
					Painel2();
					p2 = true;
				}
				break;
			case(51):
				if(p3){
					p3 = false;
					destroyWindow("PAINEL 3");
				}
				else{
					Painel3();
					p3 = true;
				}
				break;
			case(52):
				if(p4){
					p4 = false;
					destroyWindow("PAINEL 4");
				}
				else{
					Painel4();
					p4 = true;
				}
				break;	
			case(97):
				if(cone.filtro){
					cone.filtro = false;
				}
				else{
					cone.filtro = true;
				}
				break;		
		
			
			case( 27 ):  //Sair
				aberta = false;
				break;
			default:
				break;
		}

	return aberta;
}


int main(int argc, char **argv){

	ros::init(argc, argv, "vision");
	Mat img;//imagem da câmera
	VideoCapture cap; //Captura da câmera
	bool aberta;
	if(!cap.open(1))
        aberta = false;
    else 
    	aberta = true;

    Mat temp, aux;

    int t = 200;




	while( (aberta == true)&&(ros::ok() ) ){


			if(cone.atualiza)
				cap >> img;
			if( img.empty() ){
				aberta = false;
				break;
			}
			else
				aberta = true;
			if(aberta == false)
				break;

			//float ratio = (float)img.rows/(float)img.cols;
			resize(img,img,Size(320,240));
			img.copyTo(aux);
			cvtColor(aux,temp,CV_BGR2GRAY);

			if(cone.filtro)
			{
				cone.PreencheTabela();
				cone.filtro = false;
			}

			

			imshow("src",aux);
			blur(aux,aux,Size(3,3));
			imshow("blur",aux);
			cone.Thresh(aux,&temp);
			imshow("lab",aux);
			imshow("thresh",temp);



			
		    
			cone.objetos.clear();


			cone.varredura2(aux,Rect(0,0,320,240),temp);

			
			Mat seg;
			img.copyTo(seg);
			cone.DesenhaSeg(&seg);
			imshow("seg",seg);
			

			/*

			vector<vector<Point> > contours;
    		findContours(aux, contours, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_SIMPLE);

    		Mat markers = Mat::zeros(aux.size(), CV_32SC1);
		    // Draw the foreground markers
		    for (size_t i = 0; i < contours.size(); i++)
		        drawContours(markers, contours, static_cast<int>(i), Scalar::all(static_cast<int>(i)+1), -1);
		    // Draw the background marker
		    circle(markers, Point(5,5), 3, CV_RGB(255,255,255), -1);
		    imshow("Markers", markers*10000);

		     // Perform the watershed algorithm
		    watershed(img, markers);
		    Mat mark = Mat::zeros(markers.size(), CV_8UC1);
		    markers.convertTo(mark, CV_8UC1);
		    bitwise_not(mark, mark);
		//    imshow("Markers_v2", mark); // uncomment this if you want to see how the mark
		                                  // image looks like at that point
		    // Generate random colors
		    vector<Vec3b> colors;
		    for (size_t i = 0; i < contours.size(); i++)
		    {
		        int b = theRNG().uniform(0, 255);
		        int g = theRNG().uniform(0, 255);
		        int r = theRNG().uniform(0, 255);
		        colors.push_back(Vec3b((uchar)b, (uchar)g, (uchar)r));
		    }
		    // Create the result image
		    Mat dst = Mat::zeros(markers.size(), CV_8UC3);
		    // Fill labeled objects with random colors
		    for (int i = 0; i < markers.rows; i++)
		    {
		        for (int j = 0; j < markers.cols; j++)
		        {
		            int index = markers.at<int>(i,j);
		            if (index > 0 && index <= static_cast<int>(contours.size()))
		                dst.at<Vec3b>(i,j) = colors[index-1];
		            else
		                dst.at<Vec3b>(i,j) = Vec3b(0,0,0);
		        }
		    }
		    // Visualize the final image
		    imshow("Final Result", dst);
			*/
			aberta = Comando(aberta);
		
	}


	return 0;	
}