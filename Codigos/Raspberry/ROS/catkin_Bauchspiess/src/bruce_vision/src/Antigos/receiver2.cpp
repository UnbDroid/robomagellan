#include "Kalman.hpp"
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


#include "opencv2/opencv.hpp"
#include "opencv2/calib3d/calib3d.hpp"
#include "opencv2/core/core.hpp"
#include <cv.h>
#include <highgui.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>

#include <sys/time.h>


using namespace std;
using namespace cv;


#define TEMPO_AMOSTRAGEM 0.01f


float vel_e = 0, vel_d = 0;
float dist, angulo;
bool enable_encoder = false, enable_visao = false, enable = false, init = false;
int miss_cont = 0;


float xcam, ycam, vel_angular; 
float z_x = 0, z_y = 0, z_velx = 0, z_vely = 0;

float Xc = 4, Yc = 4;


geometry_msgs::PoseStamped PosicaoAtual, PosicaoAnterior;

float drc = 0.1; //10cm

int tempo_encoder, tempo_visao;

struct timeval t_inicial, t_encoder, t_visao;


struct timeval t1, t2;




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



void cone_positionCallback(const geometry_msgs::Point32::ConstPtr& msg)
{

  struct timeval tempo;
  if(msg->z == 1)
  {
    dist = msg->x;
    angulo = msg->y;
    enable_visao = true;
    miss_cont = 0;
    if(!enable)
    {
      gettimeofday(&t_inicial, NULL);
      enable = true;
      init = true;
    }
    gettimeofday(&t_visao, NULL);
    tempo_visao = (int) (1000000 * (t_visao.tv_sec - t_inicial.tv_sec) + (t_visao.tv_usec - t_inicial.tv_usec));

    //posicao do cone para a camera
    xcam = dist*cos( (CV_PI/180)*angulo );
    ycam = dist*sin( (CV_PI/180)*angulo );

    //ajuste para o ponto central do robô
    xcam+=drc;

    //rotação: referencia paralela a global
    z_x = xcam*cos(PosicaoAtual.pose.orientation.z) - ycam*sin(PosicaoAtual.pose.orientation.z);
    z_y = xcam*sin(PosicaoAtual.pose.orientation.z) + ycam*cos(PosicaoAtual.pose.orientation.z);

    //calculo da posicao do robô = posicao_cone_global - posicao_cone_robo;
    z_x = Xc - z_x;
    z_y = Yc - z_y;

  }
  else
  {
    if(enable)
    {
      miss_cont++;
      if(miss_cont>=5)
      {
        enable = false;
      }
    }
  }



}


void velocidade_atualCallback(const geometry_msgs::Point32::ConstPtr& msg)
{

  if(enable)
  {
    gettimeofday(&t_encoder, NULL);
    tempo_encoder = (int) (1000000 * (t_encoder.tv_sec - t_inicial.tv_sec) + (t_encoder.tv_usec - t_inicial.tv_usec));
  }

  vel_d = 2*CV_PI*0.06*msg->x;
  vel_e = 2*CV_PI*0.06*msg->y;

  z_velx = 0.5*(vel_d+vel_e)*cos(PosicaoAtual.pose.orientation.z);
  z_vely = 0.5*(vel_d+vel_e)*sin(PosicaoAtual.pose.orientation.z);
  vel_angular = (0.06/0.075)*(vel_d-vel_e);

}



void CalculaAngulo(const ros::TimerEvent&){


    PosicaoAtual.pose.orientation.z += vel_angular*TEMPO_AMOSTRAGEM;

    float abs_theta = abs(PosicaoAtual.pose.orientation.z);

    while (abs_theta > CV_PI){
      abs_theta = abs(PosicaoAtual.pose.orientation.z);
      if (abs_theta > 2*CV_PI) {
        if (PosicaoAtual.pose.orientation.z > 0) {
         PosicaoAtual.pose.orientation.z -= 2*CV_PI;
        }
        else if (PosicaoAtual.pose.orientation.z < 0) {
          PosicaoAtual.pose.orientation.z += 2*CV_PI;
        }
      }
      else if (abs_theta > CV_PI){
        if (PosicaoAtual.pose.orientation.z > 0) {
          PosicaoAtual.pose.orientation.z = 2*CV_PI - PosicaoAtual.pose.orientation.z;

        }
        else if (PosicaoAtual.pose.orientation.z < 0) {
          PosicaoAtual.pose.orientation.z = 2*CV_PI + PosicaoAtual.pose.orientation.z;
        } 
      }
    }

}


float Q0 = 50;
float Q1 = 50;
float Q2 = 50; 
float Q3 = 50;
void init_Kalman(Kalman* filtro)
{
  gettimeofday(&t1,NULL);
  //inicialização do filtro de Kalman
  float dataX[4] = {0,0,0,0};
  Mat x(4,1,CV_32F, dataX);

  float dataF[16] = {1,0,1,0, 0,1,0,1, 0,0,1,0, 0,0,0,1};
  Mat F(4,4,CV_32F,dataF);

  float dataP[16] = {100,0,0,0, 0,100,0,0,  0,0,100,0, 0,0,0,100};
  Mat P(4,4,CV_32F,dataP);
  float dataQ[16] = {Q0,0,0,0, 0,Q1,0,0, 0,0,Q2,0,  0,0,0,Q3};
  Mat Q(4,4,CV_32F,dataQ);
  Mat H = Mat::eye(4,4,CV_32F);
  cout<<H<<endl;
  float dataR[16] = {10,0,0,0, 0,10,0,0,  0,0,10,0, 0,0,0,10};
  Mat R(4,4,CV_32F,dataR);
  filtro->init(x,F,P,Q,H,R);
}

void Predicao(Kalman* filtro)
{
  float deltaT;
  gettimeofday(&t2,NULL);
  deltaT =  ((float)( 1000000*(t2.tv_sec - t1.tv_sec) + (t2.tv_usec - t1.tv_usec) ))/1000000;
  gettimeofday(&t1,NULL);//tempo inicial para proxima predicao
  
  filtro->Q.at<float>( Point(0,0) ) = Q0*deltaT;
  filtro->Q.at<float>( Point(1,1) ) = Q1*deltaT;
  filtro->Q.at<float>( Point(2,2) ) = Q2*deltaT;
  filtro->Q.at<float>( Point(3,3) ) = Q3*deltaT;

  filtro->predict();

}

void Atualizacao(Kalman* filtro)
{
  float dataZ[4] = {z_x,z_y,z_velx,z_vely};
  Mat z(4,1,CV_32F,dataZ);
  filtro->update(z);
  PosicaoAtual.pose.position.x = filtro->x.at<float>(0);
  PosicaoAtual.pose.position.y = filtro->x.at<float>(1);

}





int main(int argc, char **argv)
{

  ros::init(argc, argv, "receiver");


  ros::NodeHandle n;

  ros::Subscriber sub = n.subscribe("cone_position", 1000, cone_positionCallback);
  ros::Subscriber sub2 = n.subscribe("velocidade_atual", 1000, velocidade_atualCallback);
  ros::Timer temporizador = n.createTimer(ros::Duration(TEMPO_AMOSTRAGEM),CalculaAngulo, false);
  sleep(1);

  Kalman filtro;


  Mat aux;

  int comando = -1;



  PosicaoAtual.pose.position.x = 0;
  PosicaoAtual.pose.position.y = 0;
  PosicaoAtual.pose.orientation.z = 0;

  while(ros::ok() && comando!=27  )
  {
    if(init)
    {
      init = false;
      init_Kalman(&filtro);
    }
    if(enable)
    {
      Predicao(&filtro);
      if(enable_visao)
      {
        Atualizacao(&filtro);
        //grafico(filtro.x.at<float>( Point(0,0) ),filtro.x.at<float>( Point(0,1) ),tempo_visao,dist,angulo);
      }
      enable_encoder = false;
      enable_visao = false;

      
    }
    comando = waitKey(1);
    ros::spinOnce();
  }

  //ros::spin();

  return 0;
}