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

/*
void chatterCallback(const std_msgs::String::ConstPtr& msg)
{
  //ROS_INFO("I heard: [%s]", msg->data.c_str());
  cout<<msg->data.c_str()<<endl;
}
*/



float vel_e = 0, vel_d = 0;
float dist, angulo;
bool enable_encoder = false, enable_visao = false, enable = false, init = false;
int miss_cont = 0;

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

  /*
  arrowedLine( graficodist, Point(40, 480), Point(40,10), Scalar(0,0,0), 1, 8, 0, 0.01);
  arrowedLine( graficodist, Point(40, 480), Point(610,480), Scalar(0,0,0), 1, 8, 0, 0.01);
  arrowedLine( graficodist, Point(600, 480), Point(600,10), Scalar(0,0,0), 1, 8, 0, 0.01);

  putText(graficodist, "30", Point(605,30), FONT_HERSHEY_SIMPLEX, 0.5, Scalar(0,255,0), 1, 8, false );
  putText(graficodist, "0", Point(605,255), FONT_HERSHEY_SIMPLEX, 0.5, Scalar(0,255,0), 1, 8, false );
  putText(graficodist, "-30", Point(605,480), FONT_HERSHEY_SIMPLEX, 0.5, Scalar(0,255,0), 1, 8, false );

  putText(graficodist, "0", Point(20,480), FONT_HERSHEY_SIMPLEX, 0.5, Scalar(255,0,0), 1, 8, false );
  float max = 0;
  int i;
  string num;
  for(i=0;i<q_pontos;i++)
  {
    if(data_dist[i] > max)
    {
      max = data_dist[i];
    }
    if(kalm_dist[i] > max)
    {
      max = kalm_dist[i];
    }
  }
  int_to_string((int)max,&num);
  putText(graficodist, num, Point(10,30), FONT_HERSHEY_SIMPLEX, 0.5, Scalar(255,0,0), 1, 8, false );
  num.clear();
  int_to_string(max/2,&num);
  putText(graficodist, num, Point(10,255), FONT_HERSHEY_SIMPLEX, 0.5, Scalar(255,0,0), 1, 8, false );
  float parte = 450.0/max;
  float parte2 = 225.0/30; 
  int ind_ant;
  for(i=0;i<q_pontos;i++)
  {
    ind++;
    if(ind==q_pontos)
    {
      ind = 0;
    }
    if(data_dist[ind] > 0)
    {
      circle(graficodist,Point(50+i*11,480-data_dist[ind]*parte),5,Scalar(255,0,0) );
      rectangle(graficodist,Point(45+i*11,250-data_angulo[ind]*parte2),Point(55+i*11,260-data_angulo[ind]*parte2),Scalar(0,255,0));
    }
    else
    {
      circle(graficodist,Point(50+i*11,480),5,Scalar(0,0,255) );
    }
    if(i>0)
    {
      line(graficodist,Point(39+i*11,480-kalm_dist[ind_ant]*parte),Point(50+i*11,480-kalm_dist[ind]*parte),Scalar(255,0,0) );
      line(graficodist,Point(39+i*11,255-kalm_angulo[ind_ant]*parte2),Point(50+i*11,255-kalm_angulo[ind]*parte2),Scalar(0,255,0) );
    }
    ind_ant = ind;
  }
  imshow("grafico dist",graficodist);
  */
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
    tempo_encoder = tempo_visao;
    printf("tempo visao: %d  \n",tempo_visao);
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
  struct timeval tempo;
  static int iniciou = 0;
  float t_anterior;
  if(iniciou!=0){
    t_anterior = tempo_encoder;
  }
  gettimeofday(&t_encoder, NULL);
  
  tempo_encoder = (int) (1000000 * (t_encoder.tv_sec - t_inicial.tv_sec) + (t_encoder.tv_usec - t_inicial.tv_usec));

  if(iniciou !=0)
  {
    //teste de tempo
    printf("encoder call back: %f \n", tempo_encoder-t_anterior);
  }
  else
  {
    iniciou = 1;
  }

  vel_d = 2*CV_PI*0.06*msg->x;
  vel_e = 2*CV_PI*0.06*msg->y;
  enable_encoder = true;
}


float Q0 = 70;
float Q1 = 0;
float Q2 = 0; 
float Q3 = 70;
void init_Kalman(Kalman* filtro)
{
  //inicialização do filtro de Kalman
  float dataX[2] = {0,0};
  Mat x(2,1,CV_32F, dataX);

  float dataF[4] = {1,0, 0,1};
  Mat F(2,2,CV_32F,dataF);
  float dataB[4] = {0,0, 0,0};
  Mat B(2,2,CV_32F,dataB);
  float dataP[4] = {0,0, 0,0};
  Mat P(2,2,CV_32F,dataP);
  float dataQ[4] = {Q0,Q1, Q2,Q3};
  Mat Q(2,2,CV_32F,dataQ);
  float dataH[4] = {1,0, 0,1};
  Mat H(2,2,CV_32F,dataH);
  float dataR[4] = {10,0, 0,10};
  Mat R(2,2,CV_32F,dataR);
  filtro->init(x,F,B,P,Q,H,R);
}

void Predicao(Kalman* filtro)
{
  float deltaT;
  static float D = 0.075*2*CV_PI;
  gettimeofday(&t2,NULL);
  deltaT =  ((float)( 1000000*(t2.tv_sec - t1.tv_sec) + (t2.tv_usec - t1.tv_usec) ))/1000000;
  gettimeofday(&t1,NULL);//tempo inicial para proxima predicao
  


  float dataU[2] = {vel_e,vel_d};
  Mat u(2,1,CV_32F,dataU);

  filtro->B.at<float>( Point(0,0) ) = -deltaT/2;
  filtro->B.at<float>( Point(1,0) ) = -deltaT/2;
  filtro->B.at<float>( Point(0,1) ) = -deltaT*D;
  filtro->B.at<float>( Point(1,1) ) = deltaT*D;


  filtro->Q.at<float>( Point(0,0) ) = Q0*deltaT;
  filtro->Q.at<float>( Point(1,0) ) = Q1*deltaT;
  filtro->Q.at<float>( Point(0,1) ) = Q2*deltaT;
  filtro->Q.at<float>( Point(1,1) ) = Q3*deltaT;

  filtro->predict(u);

}

void Atualizacao(Kalman* filtro)
{
  float dataZ[2] = {dist,angulo};
  Mat z(2,1,CV_32F,dataZ);
  filtro->update(z);
}


int main(int argc, char **argv)
{

  ros::init(argc, argv, "receiver");


  ros::NodeHandle n;

  ros::Subscriber sub = n.subscribe("cone_position", 1000, cone_positionCallback);
  ros::Subscriber sub2 = n.subscribe("velocidade_atual", 1000, velocidade_atualCallback);

  Kalman filtro;


  Mat aux;

  int comando = -1;

  gettimeofday(&t1,NULL);

  Mat teste;

  if(teste.data==NULL)
  {
    cout<<"funciona"<<endl;
  }

  while(ros::ok() && comando!=27  )
  {
    if(init)
    {
      init = false;
      init_Kalman(&filtro);
      cout<<filtro.x<<endl;
    }
    if(enable)
    {
      Predicao(&filtro);
      //cout<<filtro.x<<endl;
      if(enable_visao)
      {
        printf("tempo visao2: %d  \n",tempo_visao);
        Atualizacao(&filtro);
        grafico(filtro.x.at<float>( Point(0,0) ),filtro.x.at<float>( Point(0,1) ),tempo_visao,dist,angulo);
      }
      else if(enable_encoder)
      {
        //grafico(filtro.x.at<float>(0),filtro.x.at<float>(1),tempo_encoder);
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