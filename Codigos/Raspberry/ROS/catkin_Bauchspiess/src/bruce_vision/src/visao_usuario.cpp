//#define usuario
//#define ve_tempo
//#define novo_codigo
//#define codigo_continuo
#define Rastreia9

#include "RastreiaCone9.hpp"
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

#include <geometry_msgs/Point32.h>


using namespace cv;
using namespace std;

RastreiaCone cone;

#ifdef ve_tempo
struct timeval tempo1, tempo2;
#endif


#ifdef usuario

Point inicio, fim;
int pontos;
int comando;
int quadro;


void normaliza(Mat source, Mat* dest){
	float B,G,R,Sum, value, Bn, Gn, Rn;
	for(int i= 0; i<source.cols; i++){
		for(int j = 0; j<source.rows; j++){
			B = ((float)source.at<Vec3b>(Point(i, j))[0]);
			G = ((float)source.at<Vec3b>(Point(i, j))[1]);
			R = ((float)source.at<Vec3b>(Point(i, j))[2]);
			Sum = B+G+R;
			value = max(max(B,G), R);
			Bn = (255.0*B)/Sum;
			Gn = (255.0*G)/Sum;
			Rn = (255.0*R)/Sum;
			(*dest).at<Vec4b>(Point(i, j))[0] = (int)Bn;
			(*dest).at<Vec4b>(Point(i, j))[1] = (int)Gn;
			(*dest).at<Vec4b>(Point(i, j))[2] = (int)Rn;
			(*dest).at<Vec4b>(Point(i, j))[3] = (int)value;
		}
	}
}


void on_mouse(int event, int x, int y, int flags, void *userdata)
{
	if(comando == 's'){
		if (event == CV_EVENT_LBUTTONDOWN)
		{
			if(pontos == 0){
				pontos = 1;
				inicio.x = x;
				inicio.y = y; 
			}
			else if(pontos == 1){
				pontos = 2;
				fim.x = x;
				fim.y = y;
			}
			else
				cout<<"pontos excessivos, erro"<<endl;
		}
	}		
}


void sonda(Mat img){
	Mat temp;
	Mat hsv;
	Mat gray;
	Mat intensity(img.size(), CV_8UC1);
	Mat norm(img.size(), CV_8UC4);
	normaliza(img, &norm);

	int min_x, max_x, min_y, max_y;
	if(inicio.x < fim.x){
		min_x = inicio.x;
		max_x = fim.x;
	}
	else{
		min_x = fim.x;
		max_x = inicio.x;
	}
	if(inicio.y < fim.y){
		min_y = inicio.y;
		max_y = fim.y;
	}
	else{
		min_y = fim.y;
		max_y = inicio.y;
	}
	//temp = img.clone();
	float ratio_original = (float)img.cols/(float)img.rows;
	resize(img, temp, Size((int)(((float)cone.tamanho0)*ratio_original), cone.tamanho0 ));
	cvtColor(temp, gray, CV_BGR2GRAY);


	cvtColor(temp, hsv, CV_BGR2HSV);

	vector<Mat> channels; 
    Mat img_hist_equalized;
    cvtColor(temp, img_hist_equalized, CV_BGR2YCrCb); //change the color image from BGR to YCrCb format
    split(img_hist_equalized,channels); //split the image into channels
    equalizeHist(channels[0], channels[0]); //equalize histogram on the 1st channel (Y)
   	//equalizeHist(channels[1], channels[1]);	
	//equalizeHist(channels[2], channels[2]);
  	merge(channels,img_hist_equalized); //merge 3 channels including the modified 1st channel into one image
   	cvtColor(img_hist_equalized, img_hist_equalized, CV_YCrCb2BGR); //change the color image from YCrCb to BGR format (to display image properly)

   	Mat hsv2;
	cvtColor(img_hist_equalized, hsv2, CV_BGR2HSV);


   	float azulH = 0;
	float verdeH = 0;
	float vermelhoH = 0;
	float H2 = 0;
	float S2 = 0;
	float V2 = 0;


	float azulN = 0;
	float verdeN = 0;
	float vermelhoN = 0;
	float I_norm = 0;


	float azul = 0;
	float verde = 0;
	float vermelho = 0;
	float H = 0;
	float S = 0;
	float V = 0;
	float cinza = 0;
	int aux;
	for(int i = min_x; i<= max_x; i++){
		for(int j = min_y; j<= max_y; j++){
			aux = temp.at<Vec3b>(Point(i, j))[0];
			azul += aux;
			aux = temp.at<Vec3b>(Point(i, j))[1];
			verde += aux;
			aux = temp.at<Vec3b>(Point(i, j))[2];
			vermelho += aux;

			aux = hsv.at<Vec3b>(Point(i, j))[0];
			H += aux;
			aux = hsv.at<Vec3b>(Point(i, j))[1];
			S += aux;
			aux = hsv.at<Vec3b>(Point(i, j))[2];
			V += aux;

			aux = norm.at<Vec4b>(Point(i, j))[0];
			azulN += aux;
			aux = norm.at<Vec4b>(Point(i, j))[1];
			verdeN += aux;
			aux = norm.at<Vec4b>(Point(i, j))[2];
			vermelhoN += aux;

			aux = norm.at<Vec4b>(Point(i, j))[3];
			I_norm += aux;


			aux = img_hist_equalized.at<Vec3b>(Point(i, j))[0];
			azulH += aux;
			aux = img_hist_equalized.at<Vec3b>(Point(i, j))[1];
			verdeH += aux;
			aux = img_hist_equalized.at<Vec3b>(Point(i, j))[2];
			vermelhoH += aux;

			aux = hsv2.at<Vec3b>(Point(i, j))[0];
			H2 += aux;
			aux = hsv2.at<Vec3b>(Point(i, j))[1];
			S2 += aux;
			aux = hsv2.at<Vec3b>(Point(i, j))[2];
			V2 += aux;


			aux = gray.at<uchar>(Point(i, j));
			cinza += aux;
		}
		cout<<endl;
	}
	int comprimento = max_x-min_x+1;
	int altura =  max_y - min_y + 1; 

	H2 = H2/(comprimento*altura);
	S2 = S2/(comprimento*altura);
	V2 = V2/(comprimento*altura);
	cout<<"Media HSV = ("<<H2<<","<<S2<<","<<V2<<")"<<endl;
	//imshow("HSV EQUALIZADA", hsv2);



	//quadrado ao redor da área análisada
	line( temp, Point(min_x, min_y), Point(max_x, min_y), Scalar(0,255,0), 2, CV_AA);
	line( temp, Point(min_x, min_y), Point(min_x, max_y), Scalar(0,255,0), 2, CV_AA);
	line( temp, Point(max_x, max_y), Point(max_x, min_y), Scalar(0,255,0), 2, CV_AA);
	line( temp, Point(max_x, max_y), Point(min_x, max_y), Scalar(0,255,0), 2, CV_AA);
	imshow("SOURCE", temp);
}




//variaveis dos paineis
bool p1 = false;
bool p2 = false;
bool p3 = false;
bool p4 = false;
bool p5 = false;
bool p6 = false;
bool p7 = false;


void Painel2(){
	namedWindow( "PAINEL 2", WINDOW_NORMAL );
	resizeWindow("PAINEL 2", 250, 1);


	createTrackbar( "Janela final", "PAINEL 2", &cone.tamanho_final, 1000);
	createTrackbar( "Janela 0", "PAINEL 2", &cone.tamanho0, 1000);
	createTrackbar( "Janela 1", "PAINEL 2", &cone.tamanho_mat, 1000);
	createTrackbar( "Minimo pontos", "PAINEL 2", &cone.min_pontos, 1000);
	createTrackbar( "Percentual pontos", "PAINEL 2", &cone.perc_pontosi, 1000);

	createTrackbar( "Aceita Range", "PAINEL 2", &cone.min_aceita, 256);



}


#ifndef Rastreia9

void Painel1(){


	 namedWindow( "Aceita HSV", WINDOW_NORMAL );
	resizeWindow("Aceita HSV", 250, 1);
	 createTrackbar( "Min H1", "Aceita HSV", &cone.min_H1i, 256);
	 createTrackbar( "Max H1", "Aceita HSV", &cone.max_H1i, 256);
	 createTrackbar( "Min S1", "Aceita HSV", &cone.min_S1i, 256);
	 createTrackbar( "Max S1", "Aceita HSV", &cone.max_S1i, 256);
	 createTrackbar( "Min V1", "Aceita HSV", &cone.min_V1i, 256);
	 createTrackbar( "Max V1", "Aceita HSV", &cone.max_V1i, 256);
	 createTrackbar( "Min H2", "Aceita HSV", &cone.min_H2i, 256);
	 createTrackbar( "Max H2", "Aceita HSV", &cone.max_H2i, 256);
	 createTrackbar( "Min S2", "Aceita HSV", &cone.min_S2i, 256);
	 createTrackbar( "Max S2", "Aceita HSV", &cone.max_S2i, 256);
	 createTrackbar( "Min V2", "Aceita HSV", &cone.min_V2i, 256);
	 createTrackbar( "Max V2", "Aceita HSV", &cone.max_V2i, 256);
	 

	  
}


void Painel3(){


	namedWindow( "PROXIMO", WINDOW_NORMAL );
	resizeWindow("PROXIMO", 250, 1);
	createTrackbar( "Min H1", "PROXIMO", &cone.min_H1p, 256);
	createTrackbar( "Max H1", "PROXIMO", &cone.max_H1p, 256);
	createTrackbar( "Min S1", "PROXIMO", &cone.min_S1p, 256);
	createTrackbar( "Max S1", "PROXIMO", &cone.max_S1p, 256);
	createTrackbar( "Min V1", "PROXIMO", &cone.min_V1p, 256);
	createTrackbar( "Max V1", "PROXIMO", &cone.max_V1p, 256);
	createTrackbar( "Min H2", "PROXIMO", &cone.min_H2p, 256);
	createTrackbar( "Max H2", "PROXIMO", &cone.max_H2p, 256);
	createTrackbar( "Min S2", "PROXIMO", &cone.min_S2p, 256);
	createTrackbar( "Max S2", "PROXIMO", &cone.max_S2p, 256);
	createTrackbar( "Min V2", "PROXIMO", &cone.min_V2p, 256);
	createTrackbar( "Max V2", "PROXIMO", &cone.max_V2p, 256);
	
}


void Painel4(){

	 namedWindow( "ZOOM", WINDOW_NORMAL );
	resizeWindow("ZOOM", 250, 1);
	 createTrackbar( "Min H1", "ZOOM", &cone.min_H1z, 255);
	 createTrackbar( "Max H1", "ZOOM", &cone.max_H1z, 255);
	 createTrackbar( "Min S1", "ZOOM", &cone.min_S1z, 255);
	 createTrackbar( "Max S1", "ZOOM", &cone.max_S1z, 255);
	 createTrackbar( "Min V1", "ZOOM", &cone.min_V1z, 255);
	 createTrackbar( "Max V1", "ZOOM", &cone.max_V1z, 255);
	 createTrackbar( "Min H2", "ZOOM", &cone.min_H2z, 255);
	 createTrackbar( "Max H2", "ZOOM", &cone.max_H2z, 255);
	 createTrackbar( "Min S2", "ZOOM", &cone.min_S2z, 255);
	 createTrackbar( "Max S2", "ZOOM", &cone.max_S2z, 255);
	 createTrackbar( "Min V2", "ZOOM", &cone.min_V2z, 255);
	 createTrackbar( "Max V2", "ZOOM", &cone.max_V2z, 255);
	 
	  
}


#ifdef novo_codigo
void Painel5(){


	namedWindow( "HUE", WINDOW_NORMAL );
	resizeWindow("HUE", 250, 1);
	createTrackbar( "Min H bom", "HUE", &cone.min_Hb, 255);
	createTrackbar( "Max H nom", "HUE", &cone.max_Hb, 255);
	createTrackbar( "Min H medio", "HUE", &cone.min_Hm, 255);
	createTrackbar( "Max H medio", "HUE", &cone.max_Hm, 255);
	createTrackbar( "Min H ruim", "HUE", &cone.min_Hr, 255);
	createTrackbar( "Max H ruim", "HUE", &cone.max_Hr, 255);
	
}

void Painel6(){


	namedWindow( "SATURATION", WINDOW_NORMAL );
	resizeWindow("SATURATION", 250, 1);
	createTrackbar( "Min S bom", "SATURATION", &cone.min_Sb, 255);
	createTrackbar( "Max S nom", "SATURATION", &cone.max_Sb, 255);
	createTrackbar( "Min S medio", "SATURATION", &cone.min_Sm, 255);
	createTrackbar( "Max S medio", "SATURATION", &cone.max_Sm, 255);
	createTrackbar( "Min S ruim", "SATURATION", &cone.min_Sr, 255);
	createTrackbar( "Max S ruim", "SATURATION", &cone.max_Sr, 255);
	
}

void Painel7(){


	namedWindow( "VALUE", WINDOW_NORMAL );
	resizeWindow("VALUE", 250, 1);
	createTrackbar( "Min V bom", "VALUE", &cone.min_Vb, 255);
	createTrackbar( "Max V nom", "VALUE", &cone.max_Vb, 255);
	createTrackbar( "Min V medio", "VALUE", &cone.min_Vm, 255);
	createTrackbar( "Max V medio", "VALUE", &cone.max_Vm, 255);
	createTrackbar( "Min V ruim", "VALUE", &cone.min_Vr, 255);
	createTrackbar( "Max V ruim", "VALUE", &cone.max_Vr, 255);
	
}

#endif

#ifdef codigo_continuo
void Painel5(){


	namedWindow( "CorLuz", WINDOW_NORMAL );
	resizeWindow("CorLuz", 250, 1);
	createTrackbar( "Min H", "CorLuz", &cone.min_Hf, 255);
	createTrackbar( "Max H", "CorLuz", &cone.max_Hf, 255);
	createTrackbar( "S ideal", "CorLuz", &cone.S_ideal, 255);
	createTrackbar( "V ideal", "CorLuz", &cone.V_ideal, 255);
	createTrackbar( "Min Range", "CorLuz", &cone.min_range, 255);

	
}

#endif

#endif


#ifdef Rastreia9
void Painel1(){


	namedWindow( "H", WINDOW_NORMAL );
	resizeWindow("H", 250, 1);
	createTrackbar( "H1 subida", "H", &cone.subidaH1, 256);
	createTrackbar( "H1 degrau subida", "H", &cone.step1_H1, 100);
	createTrackbar( "H1 topo", "H", &cone.altoH1, 256);
	createTrackbar( "H1 descida", "H", &cone.descidaH1, 256);
	createTrackbar( "H1 degrau descida", "H", &cone.step2_H1, 100);
	createTrackbar( "H1 baixo", "H", &cone.baixoH1, 256);

	createTrackbar( "H2 subida", "H", &cone.subidaH2, 256);
	createTrackbar( "H2 degrau subida", "H", &cone.step1_H2, 100);
	createTrackbar( "H2 topo", "H", &cone.altoH2, 256);
	createTrackbar( "H2 descida", "H", &cone.descidaH2, 256);
	createTrackbar( "H2 degrau descida", "H", &cone.step2_H2, 100);
	createTrackbar( "H2 baixo", "H", &cone.baixoH2, 256);




	
}

void Painel3(){


	namedWindow( "SV", WINDOW_NORMAL );
	resizeWindow("SV", 250, 1);
	
	createTrackbar( "S subida", "SV", &cone.subidaS, 256);
	createTrackbar( "S degrau subida", "SV", &cone.step1_S, 100);
	createTrackbar( "S topo", "SV", &cone.altoS, 256);
	createTrackbar( "S descida", "SV", &cone.descidaS, 256);
	createTrackbar( "S degrau descida", "SV", &cone.step2_S, 100);
	createTrackbar( "S baixo", "SV", &cone.baixoS, 256);

	createTrackbar( "V subida", "SV", &cone.subidaV, 256);
	createTrackbar( "V degrau subida", "SV", &cone.step1_V, 100);
	createTrackbar( "V topo", "SV", &cone.altoV, 256);
	createTrackbar( "V descida", "SV", &cone.descidaV, 256);
	createTrackbar( "V degrau descida", "SV", &cone.step2_V, 100);
	createTrackbar( "V baixo", "SV", &cone.baixoV, 256);


	
}



#endif



bool Comando(Mat source, VideoCapture* cap, bool aberta){

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
			case('s'):	
				while( comando == 's'){
					while( (pontos != 2) &&  (comando == 's') ) {
						setMouseCallback("SOURCE", on_mouse, NULL);
						comando = waitKey(1);
						switch(comando){
							case(-1):
								comando = 's';
								break;
							case(27):
								aberta = false;
								break;	
							default:
								comando = 1;
								break;
						}
					}
					if (pontos == 2)
						sonda(source);
					pontos = 0;
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
		#ifdef Rastreia9
			case(49):
				if(p1){
					p1 = false;
					destroyWindow("H");
				}
				else{
					Painel1();
					p1 = true;
				}
				break;
			case(51):
				if(p3){
					p3 = false;
					destroyWindow("SV");
				}
				else{
					Painel3();
					p3 = true;
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
		#endif				

		#ifndef Rastreia9 		
			case(49):
				if(p1){
					p1 = false;
					destroyWindow("Aceita HSV");
				}
				else{
					Painel1();
					p1 = true;
				}
				break;
			case(51):
				if(p3){
					p3 = false;
					destroyWindow("ZOOM2");
				}
				else{
					Painel3();
					p3 = true;
				}
				break;
			case(52):
				if(p4){
					p4 = false;
					destroyWindow("ZOOM");
				}
				else{
					Painel4();
					p4 = true;
				}
				break;
			
			#ifdef novo_codigo
			
			case(53):
				if(p5){
					p5 = false;
					destroyWindow("HUE");
				}
				else{
					Painel5();
					p5 = true;
				}
				break;
			case(54):
				if(p6){
					p6 = false;
					destroyWindow("SATURATION");
				}
				else{
					Painel6();
					p6 = true;
				}
				break;
			case(55):
				if(p7){
					p7 = false;
					destroyWindow("VALUE");
				}
				else{
					Painel7();
					p7 = true;
				}
				break;		
			
			#endif	

			#ifdef codigo_continuo
			
			case(53):
				if(p5){
					p5 = false;
					destroyWindow("CorLuz");
				}
				else{
					Painel5();
					p5 = true;
				}
				break;		
			#endif	

		#endif		
			
			case( 27 ):  //Sair
				aberta = false;
				break;
			default:
				break;
		}

	return aberta;
}

#endif


int main(int argc, char **argv){

	ros::init(argc, argv, "vision");
	ros::NodeHandle n;
	ros::Publisher chatter_pub = n.advertise<geometry_msgs::Point32>("cone_position", 1000);
	ros::Rate loop_rate(100);
	geometry_msgs::Point32 msg;

	struct timeval novo, velho;

	int tempo;

	Mat img;//imagem da câmera
	VideoCapture cap; //Captura da câmera
	bool aberta;
	if(!cap.open(1))
        aberta = false;
    else 
    	aberta = true;



	while( (aberta == true)&&(ros::ok() ) ){



			#ifdef ve_tempo
			gettimeofday(&tempo1, NULL);
			#endif

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
			
			#ifdef ve_tempo
			gettimeofday(&tempo2, NULL);
			tempo = (int) (1000000 * (tempo2.tv_sec - tempo1.tv_sec) + (tempo2.tv_usec - tempo1.tv_usec));
			if(cone.atualiza){
				cout<<"camera: "<<tempo;
			}
			gettimeofday(&velho, NULL);
			#endif

			//imshow("SOURCE", img);
			cone.rastreia(img);

			if(cone.encontrou_cone){
				msg.y = cone.pub_angulo;
				msg.x = cone.pub_distancia;
				msg.z = 1;
			}
			else{
				msg.z = 0;
			}

			chatter_pub.publish(msg);




				#ifdef ve_tempo				
				gettimeofday(&novo, NULL);
				tempo = (int) (1000000 * (novo.tv_sec - velho.tv_sec) + (novo.tv_usec - velho.tv_usec));
				if(cone.atualiza){
					cout<<"  deteccao: "<<tempo;
				}
				tempo = (int) (1000000 * (novo.tv_sec - tempo1.tv_sec) + (novo.tv_usec - tempo1.tv_usec));
				if(cone.atualiza){
					cout<<"   total: "<<tempo<<endl;
				}
				#endif
									
				#ifdef usuario
				aberta = Comando(img, &cap, aberta);
				#endif


		loop_rate.sleep();
		
	}

	msg.x = -999;
	msg.y = -999;
	msg.z = 1;
	chatter_pub.publish(msg);

	return 0;	
}