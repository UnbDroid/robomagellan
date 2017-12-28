#include "ros/ros.h"
#include "std_msgs/String.h"

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <highgui.h>
#include <sys/time.h>

#include <unistd.h>

#include <sstream>

#include <geometry_msgs/Point32.h>
#include "geometry_msgs/PoseStamped.h"


#include "RastreiaCone.hpp"
#include "Kalman.hpp"



#include "ros/serialization.h"
#include "ros/builtin_message_traits.h"
#include "ros/message_operations.h"
#include "ros/message.h"
#include "ros/time.h"



using namespace std;
using namespace cv;


#define TAXA_AMOSTRAGEM 0.1f

#define DRODAS 0.1f //distancia entre rodas
#define DCAMERA 0.1f //distancia entre camera e centro do robo

float f10, f12, f30, f32;
float b10, b11, b30, b31;
float vel_e = 0, vel_d = 0;



float z_x = 0, z_y = 0; 

bool enable = false, init = false, enable_visao = false, enable_encoder = false;
int miss_cont = 0;


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
  numeral->clear();
  int val = valor;
  string aux;
  int_to_string(val,&aux);
  (*numeral) = aux + ".";
  valor -= val;
  valor *= pow(10,casas);
  val = valor;
  aux.clear();
  int_to_string(val,&aux);
  (*numeral) = (*numeral)+aux;
}


#define GRAPH_SIZE 50
#define HOR 500/GRAPH_SIZE

void grafico(float dist, float angulo, int tempo, float dist_dado=-1, float angulo_dado = -1)
{
  static float t[GRAPH_SIZE];
  static int kalman_dist[GRAPH_SIZE];
  static int kalman_angulo[GRAPH_SIZE];
  static int data_dist[GRAPH_SIZE];
  static int data_angulo[GRAPH_SIZE];
  static int q_pontos = 0;
  static int index = -1;


  int i,j,k;
  float max = 0;
  float passo;
  string num,num2;

  //preenche vetor de dados
  if(q_pontos<GRAPH_SIZE)
  {
    q_pontos++;
  }
  index++;
  if(index> 49)
  {
    index = 0;
  }

  kalman_dist[index] = (int)100*dist;
  kalman_angulo[index] = angulo;
  t[index] = tempo/100000;

  data_dist[index] = (int)100*dist_dado;
  data_angulo[index] = angulo_dado;

  //estaticos
  Mat grafico(500,600,CV_8UC3);
  grafico = Scalar(255,255,255);
  arrowedLine( grafico, Point(40, 440), Point(40,10), Scalar(0,0,0), 1, 8, 0, 0.01);
  arrowedLine( grafico, Point(40, 440), Point(550,440), Scalar(0,0,0), 1, 8, 0, 0.01);
  arrowedLine( grafico, Point(540, 440), Point(540,10), Scalar(0,0,0), 1, 8, 0, 0.01);
  putText(grafico, "Distancia (cm)", Point(50,20), FONT_HERSHEY_SIMPLEX, 0.5, Scalar(180,0,0), 1, 8, false );
  putText(grafico, "Angulo (graus)", Point(415,20), FONT_HERSHEY_SIMPLEX, 0.5, Scalar(0,180,0), 1, 8, false );
  putText(grafico, "Tempo (s)", Point(250,480), FONT_HERSHEY_SIMPLEX, 0.5, Scalar(0,0,0), 1, 8, false );
  putText(grafico, "30", Point(550,40), FONT_HERSHEY_SIMPLEX, 0.5, Scalar(0,180,0), 1, 8, false );
  putText(grafico, "0", Point(550,240), FONT_HERSHEY_SIMPLEX, 0.5, Scalar(0,180,0), 1, 8, false );
  putText(grafico, "-30", Point(550,440), FONT_HERSHEY_SIMPLEX, 0.5, Scalar(0,180,0), 1, 8, false );


  //dinamico
  for(i=0;i<q_pontos;i++)
  {
    if(data_dist[i] > max)
    {
      max = data_dist[i];
    }
    if(kalman_dist[i] > max)
    {
      max = kalman_dist[i];
    }
  }

  passo = 400/max;
  num.clear();
  int_to_string(max,&num);

  putText(grafico, num, Point(5,40), FONT_HERSHEY_SIMPLEX, 0.5, Scalar(180,0,0), 1, 8, false );
  putText(grafico, "0", Point(5,440), FONT_HERSHEY_SIMPLEX, 0.5, Scalar(180,0,0), 1, 8, false );

  j=index;
  for(i=0;i<q_pontos;i++)
  {
    j++;
    if(j>=q_pontos)
    {
      j=0;
    }
    if(data_dist[j]>0)
    {
      circle(grafico, Point(40+i*10,440-passo*data_dist[j]),4, Scalar(180,0,0));
    }
    if(i>0)
    {
      k=j-1;
      if(k<0)
      {
        k=q_pontos-1;
      }
      line(grafico,Point(30+i*10,440-passo*kalman_dist[k]),Point(40+i*10,440-passo*kalman_dist[j]),Scalar(255,0,0));
    }

    if(i%10==9 || i==0)
    {
      num.clear();
      num2.clear();
      int_to_string((int)(t[j]/10),&num);
      int_to_string( (int)((t[j])-( ((int)(t[j]/10)) * 10) ) ,&num2);
      putText(grafico, num+"."+num2, Point(40+i*10,460), FONT_HERSHEY_SIMPLEX, 0.5, Scalar(0,0,0), 1, 8, false );
    }
  }


  imshow("Grafico",grafico);
}



void velocidade_atualCallback(const geometry_msgs::Point32::ConstPtr& msg)
{
  vel_d = 2.0*CV_PI*0.06*msg->x;
  vel_e = 2.0*CV_PI*0.06*msg->y;  
}

void init_Kalman(Kalman* filtro)
{
  //inicialização do filtro de Kalman
  float dataX[4] = {z_x,0,z_y,0};
  Mat x(4,1,CV_32F, dataX);

  float dataF[16] = {1,TAXA_AMOSTRAGEM,0,0, 0,0,0,0, 0,0,1,TAXA_AMOSTRAGEM, 0,0,0,0};
  Mat F(4,4,CV_32F,dataF);

  float dataB[8] = {0,0, 0,0, 0,0, 0,0};
  Mat B(4,2,CV_32F,dataB);

  float dataP[16] = {100,0,0,0, 0,100,0,0,  0,0,100,0, 0,0,0,100};
  Mat P(4,4,CV_32F,dataP);
  float dataQ[16] = {10*TAXA_AMOSTRAGEM,0,0,0, 0,10*TAXA_AMOSTRAGEM,0,0, 0,0,10*TAXA_AMOSTRAGEM,0,  0,0,0,10*TAXA_AMOSTRAGEM};
  Mat Q(4,4,CV_32F,dataQ);
  float dataH[8] = {1,0,0,0, 0,0,1,0};
  Mat H (2,4,CV_32F,dataH);

  float dataR[4] = {10,0, 0,10};
  Mat R(2,2,CV_32F,dataR);
  filtro->init(x,F,P,Q,H,R,B);
}

void Predicao(Kalman* filtro)
{
  float aux, alpha, seno, cosseno;
  aux = (vel_e-vel_d)/(2.0*DRODAS);
  alpha = aux*TAXA_AMOSTRAGEM;
  seno = sin(alpha);
  cosseno = cos(alpha);

  const float dividendo = (4*DRODAS*DRODAS);


  float X = filtro->x.at<float>(Point(0,0));
  float Y = filtro->x.at<float>(Point(2,0));



  
  filtro->F.at<float>(Point(0,1)) = -seno*aux;
  filtro->F.at<float>(Point(2,1)) = -cosseno*aux;
  filtro->F.at<float>(Point(0,3)) = cosseno*aux;
  filtro->F.at<float>(Point(2,3)) = -seno*aux;


  aux = cosseno*( (X+DCAMERA)*(vel_e-vel_d)*TAXA_AMOSTRAGEM+2*DRODAS*(Y-DRODAS) );
  aux += seno*( 2*DRODAS*(X+DCAMERA) - TAXA_AMOSTRAGEM*(Y*(vel_e-vel_d)+DRODAS*(vel_e+vel_d)) );
  aux /= dividendo;
  filtro->B.at<float>(Point(1,0)) = aux;

  aux = -cosseno*( (X+DCAMERA)*(vel_e-vel_d)*TAXA_AMOSTRAGEM+2*DRODAS*(Y+DRODAS) );
  aux -= seno*( 2*DRODAS*(X+DCAMERA)-TAXA_AMOSTRAGEM*(Y*(vel_e-vel_d)+DRODAS*(vel_e+vel_d)) );
  aux /= dividendo;
  filtro->B.at<float>(Point(1,1)) = aux;

  aux = seno*(TAXA_AMOSTRAGEM*(vel_e-vel_d)*(X+DCAMERA) + 2*DRODAS*(Y-DRODAS));
  aux += cosseno*(-2*DRODAS*(X+DCAMERA)+TAXA_AMOSTRAGEM*(Y*(vel_e-vel_d)+DRODAS*(vel_e+vel_d)) );
  aux/dividendo;
  filtro->B.at<float>(Point(3,0)) = aux;
  
  aux = -seno*(TAXA_AMOSTRAGEM*(vel_e-vel_d)*(X+DCAMERA) + 2*DRODAS*(Y+DRODAS));
  aux -= cosseno*(-2*DRODAS*(X+DCAMERA)+TAXA_AMOSTRAGEM*(Y*(vel_e-vel_d)+DRODAS*(vel_e+vel_d)) );
  aux/dividendo;
  filtro->B.at<float>(Point(3,1)) = aux;

  float dataU[2] = {vel_d,vel_e};
  Mat u(2,1,CV_32F,dataU);

  filtro->predict(u);

}

void Atualizacao(Kalman* filtro)
{
  float dataZ[2] = {z_x,z_y};
  Mat z(2,1,CV_32F,dataZ);
  filtro->update(z);
}





int main(int argc, char **argv)
{

  ros::init(argc, argv, "receiver");


  ros::NodeHandle n;

  ros::Subscriber sub2 = n.subscribe("velocidade_atual", 1000, velocidade_atualCallback);
  //ros::Timer temporizador = n.createTimer(ros::Duration(TEMPO_AMOSTRAGEM),CalculaAngulo, false);
  sleep(1);

  Kalman filtro;



  int comando = -1;

  RastreiaCone cone;

  Mat img;//imagem da câmera
  VideoCapture cap; //Captura da câmera
  bool aberta;
  if(!cap.open(1))
        aberta = false;
    else 
      aberta = true;



  while(ros::ok() && comando!=27  )
  {

    if(enable)
    {
      Predicao(&filtro);
    }
    cone.rastreia(img);
    if(enable)
    {
      if(cone.encontrou_cone)
      {
        z_x = cone.pubx;
        z_y = cone.puby;
        Atualizacao(&filtro);
      }
      else
      {

      }
    }
    else
    {
      if(cone.encontrou_cone)
      {
        z_x = cone.pubx;
        z_y = cone.puby;
        init_Kalman(&filtro);
        enable = true;
      }
    }
   
    comando = waitKey(1);
    ros::spinOnce();
  }

  //ros::spin();

  return 0;
}