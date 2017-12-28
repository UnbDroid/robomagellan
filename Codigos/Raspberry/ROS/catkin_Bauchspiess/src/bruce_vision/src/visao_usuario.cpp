#define USEBAG
#define usuario
//#define ve_tempo
//#define novo_codigo
//#define codigo_continuo
#define Rastreia9

#include "RastreiaCone.hpp"
#include "Kalman.hpp"


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
#ifdef encontrar_arvore
	AchaArvore detector_de_arvore;
#endif

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
	//cvtColor(temp, gray, CV_BGR2GRAY);


	cvtColor(temp, hsv, CV_BGR2HSV);

	Mat matriz_ponderada;

	vector<Mat> channels; 
	vector<Mat> canais(3);

	/*
	split(hsv, channels);
	equalizeHist(channels[1], canais[1]);
	float S_hist = (float)cone.S_pondera/100;
	float S_regular = 1-S_hist;
	add(S_regular*channels[1], S_hist*canais[1], channels[1]);	
	equalizeHist(channels[2], canais[2]);
	float V_hist = (float)cone.V_pondera/100;
	float V_regular = 1-V_hist;
	add(V_regular*channels[2], V_hist*canais[2], channels[2]);
    
	merge(channels, matriz_ponderada);
	*/

	/*
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


	*/

	float H = 0;
	float S = 0;
	float V = 0;
	int aux;



	for(int i = min_x; i<= max_x; i++){
		for(int j = min_y; j<= max_y; j++){
			/*
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
			*/
			aux = hsv.at<Vec3b>(Point(i, j))[0];
			H += aux;
			aux = hsv.at<Vec3b>(Point(i, j))[1];
			S += aux;
			aux = hsv.at<Vec3b>(Point(i, j))[2];
			V += aux;

		}
		cout<<endl;

	}
	float comprimento = max_x-min_x+1;
	float altura =  max_y - min_y + 1; 

	H = H/(comprimento*altura);
	S = S/(comprimento*altura);
	V = V/(comprimento*altura);
	cout<<"Media HSV = ("<<H<<","<<S<<","<<V<<")"<<endl;

	/*
	H2 = H2/(comprimento*altura);
	S2 = S2/(comprimento*altura);
	V2 = V2/(comprimento*altura);
	cout<<"Media HSV = ("<<H2<<","<<S2<<","<<V2<<")"<<endl;
	//imshow("HSV EQUALIZADA", hsv2);
	*/


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


#ifndef segmentacao

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

void Painel2(){
	namedWindow( "PAINEL 2", WINDOW_NORMAL );
	resizeWindow("PAINEL 2", 250, 1);


	createTrackbar( "Janela final", "PAINEL 2", &cone.tamanho_final, 1000);
	createTrackbar( "Janela 0", "PAINEL 2", &cone.tamanho0, 1000);
	createTrackbar( "Janela 1", "PAINEL 2", &cone.tamanho_mat, 1000);
	createTrackbar( "Minimo pontos", "PAINEL 2", &cone.min_pontos, 1000);
	createTrackbar( "Percentual pontos", "PAINEL 2", &cone.perc_pontosi, 1000);




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

void Painel4(){
	namedWindow( "Auxiliar", WINDOW_NORMAL );
	resizeWindow("Auxiliar", 250, 1);
	

	//createTrackbar( "H hist ponderado", "PAINEL 2", &cone.H_pondera, 100);
	createTrackbar( "S hist ponderado", "Auxiliar", &cone.S_pondera, 100);
	createTrackbar( "V hist ponderado", "Auxiliar", &cone.V_pondera, 100);

	//createTrackbar( "Peso Original", "PAINEL 2", &cone.Peso_original, 100);
	createTrackbar( "Aceita Longe", "Auxiliar", &cone.min_aceita, 256);
	createTrackbar( "Blur Interesse Longe", "Auxiliar", &cone.size_blur, 100);
	createTrackbar( "Aceita blur Longe", "Auxiliar", &cone.aceita_blur, 256);
	createTrackbar( "Aceita2 Longe", "Auxiliar", &cone.aceita_final, 256);


	createTrackbar( "Aceita Perto", "Auxiliar", &cone.min_aceitaz, 256);
	//createTrackbar( "H hist ponderado", "PAINEL 2", &cone.H_pondera, 100);
	//createTrackbar( "S hist ponderado", "PAINEL 2", &cone.S_pondera, 100);
	//createTrackbar( "V hist ponderado", "PAINEL 2", &cone.V_pondera, 100);

	//createTrackbar( "Peso Original", "PAINEL 2", &cone.Peso_original, 100);
	createTrackbar( "Blur Interesse Perto", "Auxiliar", &cone.size_blurz, 100);
	createTrackbar( "Aceita blur Perto", "Auxiliar", &cone.aceita_blurz, 256);
	createTrackbar( "Aceita2 Perto", "Auxiliar", &cone.aceita_finalz, 256);

	createTrackbar( "Pot H", "Auxiliar", &cone.potH, 10);
	createTrackbar( "Pot S", "Auxiliar", &cone.potS, 10);
	createTrackbar( "Pot V", "Auxiliar", &cone.potV, 10);


}


void Painel5(){
	namedWindow( "SVZoom", WINDOW_NORMAL );
	resizeWindow("SVZoom", 250, 1);
	
	createTrackbar( "S subida Perto", "SVZoom", &cone.subidaSz, 256);
	createTrackbar( "S degrau subida Perto", "SVZoom", &cone.step1_Sz, 100);
	createTrackbar( "S topo Perto", "SVZoom", &cone.altoSz, 256);
	createTrackbar( "S descida Perto", "SVZoom", &cone.descidaSz, 256);
	createTrackbar( "S degrau descida Perto", "SVZoom", &cone.step2_Sz, 100);
	createTrackbar( "S baixo Perto", "SVZoom", &cone.baixoSz, 256);

	createTrackbar( "V subida Perto", "SVZoom", &cone.subidaVz, 256);
	createTrackbar( "V degrau subida Perto", "SVZoom", &cone.step1_Vz, 100);
	createTrackbar( "V topo Perto", "SVZoom", &cone.altoVz, 256);
	createTrackbar( "V descida Perto", "SVZoom", &cone.descidaVz, 256);
	createTrackbar( "V degrau descida Perto", "SVZoom", &cone.step2_Vz, 100);
	createTrackbar( "V baixo Perto", "SVZoom", &cone.baixoVz, 256);	
}

void Painel6(){
	namedWindow( "HZoom", WINDOW_NORMAL );
	resizeWindow("HZoom", 250, 1);
	createTrackbar( "H1 subida Perto", "HZoom", &cone.subidaH1z, 256);
	createTrackbar( "H1 degrau subida Perto", "HZoom", &cone.step1_H1z, 100);
	createTrackbar( "H1 topo Perto", "HZoom", &cone.altoH1z, 256);
	createTrackbar( "H1 descida Perto", "HZoom", &cone.descidaH1z, 256);
	createTrackbar( "H1 degrau descida Perto", "HZoom", &cone.step2_H1z, 100);
	createTrackbar( "H1 baixo Perto", "HZoom", &cone.baixoH1z, 256);

	createTrackbar( "H2 subida Perto", "HZoom", &cone.subidaH2z, 256);
	createTrackbar( "H2 degrau subida Perto", "HZoom", &cone.step1_H2z, 100);
	createTrackbar( "H2 topo Perto", "HZoom", &cone.altoH2z, 256);
	createTrackbar( "H2 descida Perto", "HZoom", &cone.descidaH2z, 256);
	createTrackbar( "H2 degrau descida Perto", "HZoom", &cone.step2_H2z, 100);
	createTrackbar( "H2 baixo Perto", "HZoom", &cone.baixoH2z, 256);	
}


#endif

#ifdef encontrar_arvore

	void Painel7(){
		namedWindow( "ARVORE", WINDOW_NORMAL );
		resizeWindow("ARVORE", 250, 1);
		createTrackbar( "verde baixo", "ARVORE", &detector_de_arvore.verde_baixo, 256);
		createTrackbar( "verde alto", "ARVORE", &detector_de_arvore.verde_alto, 256);	
		createTrackbar( "sat baixo", "ARVORE", &detector_de_arvore.saturacao_baixa, 256);
		createTrackbar( "sat alto", "ARVORE", &detector_de_arvore.saturacao_alta, 256);
		createTrackbar( "value baixo", "ARVORE", &detector_de_arvore.value_baixo, 256);
		createTrackbar( "value alto", "ARVORE", &detector_de_arvore.value_alto, 256);
		createTrackbar( "size blur", "ARVORE", &detector_de_arvore.blur_size, 100);
		createTrackbar( "passa blur", "ARVORE", &detector_de_arvore.min_blur, 100);



	}

#endif

#else

void Painel2(){
	namedWindow( "PAINEL 2", WINDOW_NORMAL );
	resizeWindow("PAINEL 2", 250, 1);
	createTrackbar( "minL", "PAINEL 2", &cone.minL, 256);
	createTrackbar( "maxL", "PAINEL 2", &cone.maxL, 256);
	createTrackbar( "minB", "PAINEL 2", &cone.minB, 256);
	createTrackbar( "maxB", "PAINEL 2", &cone.maxB, 256);
	createTrackbar( "minG", "PAINEL 2", &cone.minG, 256);
	createTrackbar( "maxG", "PAINEL 2", &cone.maxG, 256);
	createTrackbar( "minR", "PAINEL 2", &cone.minR, 256);
	createTrackbar( "maxR", "PAINEL 2", &cone.maxR, 256);
	createTrackbar( "minaceita", "PAINEL 2", &cone.min_aceita, 256);
	createTrackbar( "aceitafinal", "PAINEL 2", &cone.aceita_final, 256);

	/*
	createTrackbar( "sizeCanny", "PAINEL 2", &cone.sizeCanny, 5);

	createTrackbar( "minCanny", "PAINEL 2", &cone.minCanny, 1000);
	createTrackbar( "maxCanny", "PAINEL 2", &cone.maxCanny, 1000);
	*/
	//createTrackbar( "difpixel", "PAINEL 2", &cone.dif_pixel, 256);
	//createTrackbar( "difcentroide", "PAINEL 2", &cone.dif_centroide, 256);


	/*
	namedWindow( "PAINEL 2", WINDOW_NORMAL );
	resizeWindow("PAINEL 2", 250, 1);
	createTrackbar( "L subida", "PAINEL 2", &cone.subidaL, 256);
	createTrackbar( "L degrau subida", "PAINEL 2", &cone.step1_L, 100);
	createTrackbar( "L topo", "PAINEL 2", &cone.altoL, 256);
	createTrackbar( "L descida", "PAINEL 2", &cone.descidaL, 256);
	createTrackbar( "L degrau descida", "PAINEL 2", &cone.step2_L, 100);
	createTrackbar( "L baixo", "PAINEL 2", &cone.baixoL, 256);

	createTrackbar( "Janela final", "PAINEL 2", &cone.tamanho_final, 1000);
	createTrackbar( "Janela 0", "PAINEL 2", &cone.tamanho0, 1000);
	//createTrackbar( "Janela 1", "PAINEL 2", &cone.tamanho_mat, 1000);
	*/

}

void Painel3(){


	namedWindow( "PAINEL 3", WINDOW_NORMAL );
	resizeWindow("PAINEL 3", 250, 1);
	createTrackbar( "minLo", "PAINEL 3", &cone.minLo, 256);
	createTrackbar( "maxLo", "PAINEL 3", &cone.maxLo, 256);
	createTrackbar( "minBo", "PAINEL 3", &cone.minBo, 256);
	createTrackbar( "maxBo", "PAINEL 3", &cone.maxBo, 256);
	createTrackbar( "minGo", "PAINEL 3", &cone.minGo, 256);
	createTrackbar( "maxGo", "PAINEL 3", &cone.maxGo, 256);
	createTrackbar( "minRo", "PAINEL 3", &cone.minRo, 256);
	createTrackbar( "maxRo", "PAINEL 3", &cone.maxRo, 256);

	/*
	namedWindow( "ab", WINDOW_NORMAL );
	resizeWindow("ab", 250, 1);
	
	createTrackbar( "a subida", "ab", &cone.subidaA, 256);
	createTrackbar( "a degrau subida", "ab", &cone.step1_A, 100);
	createTrackbar( "a topo", "ab", &cone.altoA, 256);
	createTrackbar( "a descida", "ab", &cone.descidaA, 256);
	createTrackbar( "a degrau descida", "ab", &cone.step2_A, 100);
	createTrackbar( "a baixo", "ab", &cone.baixoA, 256);

	createTrackbar( "b subida", "ab", &cone.subidaB, 256);
	createTrackbar( "b degrau subida", "ab", &cone.step1_B, 100);
	createTrackbar( "b topo", "ab", &cone.altoB, 256);
	createTrackbar( "b descida", "ab", &cone.descidaB, 256);
	createTrackbar( "b degrau descida", "ab", &cone.step2_B, 100);
	createTrackbar( "b baixo", "ab", &cone.baixoB, 256);	
	*/
}

void Painel4(){


	namedWindow( "PAINEL 4", WINDOW_NORMAL );
	resizeWindow("PAINEL 4", 250, 1);
	createTrackbar( "difLo", "PAINEL 4", &cone.difLo, 50);
	createTrackbar( "difLb", "PAINEL 4", &cone.difLb, 50);
	createTrackbar( "difAo", "PAINEL 4", &cone.difAo, 50);
	createTrackbar( "difAb", "PAINEL 4", &cone.difAb, 50);
	createTrackbar( "difBo", "PAINEL 4", &cone.difBo, 50);
	createTrackbar( "difBb", "PAINEL 4", &cone.difBb, 50);
	createTrackbar( "maxdif", "PAINEL 4", &cone.max_dif, 100);
	createTrackbar( "min_seg", "PAINEL 4", &cone.min_segment_size, 100);

}


void Painel5(){


	namedWindow( "PAINEL 5", WINDOW_NORMAL );
	resizeWindow("PAINEL 5", 250, 1);
	createTrackbar( "minLB", "PAINEL 5", &cone.minLB, 255);
	createTrackbar( "maxLB", "PAINEL 5", &cone.maxLB, 255);
	createTrackbar( "minAB", "PAINEL 5", &cone.minAB, 255);
	createTrackbar( "maxAB", "PAINEL 5", &cone.maxAB, 255);
	createTrackbar( "minBB", "PAINEL 5", &cone.minBB, 255);
	createTrackbar( "maxBB", "PAINEL 5", &cone.maxBB, 255);


}


/*
void Painel4(){


	namedWindow( "PAINEL 4", WINDOW_NORMAL );
	resizeWindow("PAINEL 4", 250, 1);

	createTrackbar( "difpixel", "PAINEL 4", &cone.dif_pixel, 750);
	createTrackbar( "maxdifpixel", "PAINEL 4", &cone.max_dif_pixel, 256);
	createTrackbar( "difcentroide", "PAINEL 4", &cone.dif_centroide, 750);
	createTrackbar( "maxdifcentroide", "PAINEL 4", &cone.max_dif_centroide, 256);
	createTrackbar( "maxdifpixelL", "PAINEL 4", &cone.max_dif_pixelL, 256);
	createTrackbar( "maxdifcentroideL", "PAINEL 4", &cone.max_dif_centroideL, 256);
	createTrackbar( "minSegmentSize", "PAINEL 4", &cone.min_segment_size, 1000);

	createTrackbar( "minCanny", "PAINEL 4", &cone.minCanny, 2000);
	createTrackbar( "maxCanny", "PAINEL 4", &cone.maxCanny, 2000);
	createTrackbar( "CannySize", "PAINEL 4", &cone.sizeCanny, 3);
}
*/

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
			case(53):
				if(p5){
					p5 = false;
					destroyWindow("PAINEL 5");
				}
				else{
					Painel5();
					p5 = true;
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
		#ifndef segmentacao		
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
			case(52):
				if(p4){
					p4 = false;
					destroyWindow("Auxiliar");
				}
				else{
					Painel4();
					p4 = true;
				}
				break;
			case(53):
				if(p5){
					p5 = false;
					destroyWindow("SVZoom");
				}
				else{
					Painel5();
					p5 = true;
				}
				break;
			case(54):
				if(p6){
					p6 = false;
					destroyWindow("HZoom");
				}
				else{
					Painel6();
					p6 = true;
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
		#ifdef encontrar_arvore
			case(55):
				if(p7){
					p7 = false;
					destroyWindow("ARVORE");
				}
				else{
					Painel7();
					p7 = true;
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

		#else

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





/*
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
*/



int main(int argc, char **argv){

	
	//-----ROS---------------
	ros::init(argc, argv, "vision");
	ros::NodeHandle n;
	ros::Publisher chatter_pub = n.advertise<geometry_msgs::Point32>("cone_position", 1000);
	ros::Rate loop_rate(10);
	geometry_msgs::Point32 msg;

	struct timeval novo, velho, T;


	struct timeval t1, t2, t3, t4;

	int tempo,t,dt;

	Mat img;//imagem da câmera
	VideoCapture cap; //Captura da câmera
	bool aberta;
	if(!cap.open(1))
        aberta = false;
    else 
    	aberta = true;


    gettimeofday(&t1,NULL);


    #ifdef USEBAG
    rosbag::Bag bag;
    bag.open("cam.bag", rosbag::bagmode::Write);
    #endif
    

	while( (aberta == true)&&(ros::ok() ) ){


			gettimeofday(&t3,NULL);	
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

			gettimeofday(&t4,NULL);
			tempo = (int) (1000000 * (t4.tv_sec - t3.tv_sec) + (t4.tv_usec - t3.tv_usec));
			//cout<<"camera:  "<<tempo<<endl;


			//imshow("SOURCE", img);
			
			gettimeofday(&t3,NULL);	
			cone.rastreia(img,false,0,0,0,0,0);
			gettimeofday(&t4,NULL);
			tempo = (int) (1000000 * (t4.tv_sec - t3.tv_sec) + (t4.tv_usec - t3.tv_usec));
			//cout<<"rastreia:  "<<tempo<<endl;
		


		    if(cone.encontrou_cone){
		    	msg.x = cone.pubx;
		    	msg.y = cone.puby;
				msg.z = 1; 
			}
			else
			{
				msg.x = 0;
		    	msg.y = 0;
				msg.z = 0;
			}
		  	
			//cout<<msg.x<<"   "<<msg.y<<endl;

			chatter_pub.publish(msg);
			#ifdef USEBAG
			bag.write("Camera", ros::Time::now(), msg);
			#endif

			
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


		gettimeofday(&t2,NULL);
		tempo = (int) (1000000 * (t2.tv_sec - t1.tv_sec) + (t2.tv_usec - t1.tv_usec));
		//cout<<tempo<<endl;
		gettimeofday(&t1,NULL);
		
	}

	msg.x = 0;
	msg.y = 0;
	msg.z = 0;
	chatter_pub.publish(msg);
	#ifdef USEBAG
	bag.close();
	#endif

	return 0;	
}