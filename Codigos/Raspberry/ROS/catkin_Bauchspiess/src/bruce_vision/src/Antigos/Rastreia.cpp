//#define BAGWRITE
//#define BAGREAD


#include "Kalman.hpp"
#include "ros/ros.h"
#include "std_msgs/String.h"
#include <unistd.h>
#include <sstream>
#include <rosbag/bag.h>
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
#include "gqueue.h"
#include "gmatlabdatafile.h"
#include "gdatalogger.h"

#include "RastreiaCone.hpp"




using namespace std;
using namespace cv;


#define TAXA_AMOSTRAGEM 0.1f

#define DRODAS 0.1f //distancia entre rodas
#define DCAMERA 0.1f //distancia entre camera e centro do robo

#define CHISQUARE 5.991

float vel_e = 0, vel_d = 0;
float vel_e_anterior = 0,vel_d_anterior = 0;


#ifdef BAGWRITE
rosbag::Bag bag;
#endif
    
GDATALOGGER gDataLogger;

RastreiaCone cone;



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




void velocidade_atualCallback(const geometry_msgs::Point32::ConstPtr& msg)
{
  float ve,vd;
  vd = 2.0*CV_PI*0.06*msg->x;
  ve = 2.0*CV_PI*0.06*msg->y;

  vel_e = (ve+vel_e_anterior)/2.0;
  vel_d = (vd+vel_d_anterior)/2.0;

  vel_e_anterior = ve;
  vel_d_anterior = vd;

  #ifdef BAGWRITE
  bag.write("Encoder", ros::Time::now(), msg);  
  #endif
}





void init_Kalman(Kalman* filtro, Kalman* odometria, double z_x, double z_y)
{
  //inicialização do filtro de Kalman
  float dataX[4] = {z_x,0,z_y,0};
  Mat x(4,1,CV_32F, dataX);

  float dataF[16] = {1,TAXA_AMOSTRAGEM,0,0, 0,0,0,0, 0,0,1,TAXA_AMOSTRAGEM, 0,0,0,0};
  Mat F(4,4,CV_32F,dataF);

  float dataB[8] = {0,0, 0,0, 0,0, 0,0};
  Mat B(4,2,CV_32F,dataB);

  float dataP[16] = {0.04,0,0,0, 0,0.01,0,0,  0,0,0.04,0, 0,0,0,0.01};
  Mat P(4,4,CV_32F,dataP);
  float dataQ[16] = {0.01,0,0,0, 0,0.01,0,0, 0,0,0.01,0,  0,0,0,0.01};
  Mat Q(4,4,CV_32F,dataQ);
  float dataH[8] = {1,0,0,0, 0,0,1,0};
  Mat H (2,4,CV_32F,dataH);

  float dataR[4] = {0.01,0, 0,0.01};
  Mat R(2,2,CV_32F,dataR);
  filtro->init(x,F,P,Q,H,R,B);

  odometria->init(x,F,P,Q,H,R,B);

}

void Predicao(Kalman* filtro, Kalman* odometria, float DeltaT)
{
  float aux, alpha, seno, cosseno;
  aux = (vel_e-vel_d)/(2.0*DRODAS);
  alpha = aux*DeltaT;
  seno = sin(alpha);
  cosseno = cos(alpha);


  //Kalman
  float X = filtro->x.at<float>(Point(0,0));
  float Y = filtro->x.at<float>(Point(0,2));
  float VX = filtro->x.at<float>(Point(0,1));
  float VY = filtro->x.at<float>(Point(0,3));

  filtro->F.at<float>(Point(1,0)) = DeltaT; 
  filtro->F.at<float>(Point(0,1)) = -seno*aux;
  filtro->F.at<float>(Point(2,1)) = -cosseno*aux;
  filtro->F.at<float>(Point(3,2)) = DeltaT;
  filtro->F.at<float>(Point(0,3)) = cosseno*aux;
  filtro->F.at<float>(Point(2,3)) = -seno*aux;

  filtro->x.at<float>(Point(0,0)) = X+DeltaT*VX;
  filtro->x.at<float>(Point(0,1)) = -seno*aux*X-cosseno*aux*Y-seno*aux*DCAMERA-cosseno*((vel_e+vel_d)/2);
  filtro->x.at<float>(Point(0,2)) = Y+DeltaT*VY;
  filtro->x.at<float>(Point(0,3)) = cosseno*aux*X-seno*aux*Y+cosseno*aux*DCAMERA-seno*((vel_e+vel_d)/2);

  filtro->predict(false);

  //odometria
  X = odometria->x.at<float>(Point(0,0));
  Y = odometria->x.at<float>(Point(0,2));
  VX = odometria->x.at<float>(Point(0,1));
  VY = odometria->x.at<float>(Point(0,3));

  odometria->x.at<float>(Point(0,0)) = X+DeltaT*VX;
  odometria->x.at<float>(Point(0,1)) = -seno*aux*X-cosseno*aux*Y-seno*aux*DCAMERA-cosseno*((vel_e+vel_d)/2);
  odometria->x.at<float>(Point(0,2)) = Y+DeltaT*VY;
  odometria->x.at<float>(Point(0,3)) = cosseno*aux*X-seno*aux*Y+cosseno*aux*DCAMERA-seno*((vel_e+vel_d)/2);

}

void Atualizacao(Kalman* filtro, float z_x, float z_y)
{
  float dist = sqrt(z_x*z_x+z_y*z_y);
  float dataZ[2] = {z_x,z_y};
  Mat z(2,1,CV_32F,dataZ);
  filtro->update(z);
}





int main(int argc, char **argv)
{

  double T,x,y;


  int comando = -1;
  int cont;

  //ROS
  ros::init(argc, argv, "receiver");
  ros::NodeHandle n;
  ros::Subscriber sub = n.subscribe("velocidade_atual", 1000, velocidade_atualCallback);
  ros::Publisher chatter_pub = n.advertise<geometry_msgs::Point32>("cone_position", 1000);
  ros::Rate loop_rate(10);
  geometry_msgs::Point32 coneMsg;


  ros::Time t_inicial, t_atual, t_anterior;
  float DeltaT;


  //Kalman
  Kalman filtro, odometria;
  bool enable = false;


  Mat dist_Mahalanobis(1,1,CV_32F);
  double dist;
  double recentDist[5] = {0,0,0,0,0};
  int index = 0;

  Mat Z(2,1,CV_32F);


  //Visao
  
  Mat img;//imagem da câmera
  VideoCapture cap; //Captura da câmera
  bool aberta;
  if(!cap.open(1))
        aberta = false;
    else 
      aberta = true;

  int k;

    
  // Data logger:
  if(!gDataLogger_Init(&gDataLogger,"src/bruce_vision/src/matlabdatafiles/matlabdatafile.mat",NULL)){
    printf("\nErro em gDataLogger_Init\n\n");
    return EXIT_FAILURE;
  }
  gDataLogger_DeclareVariable(&gDataLogger,"T_encoder","s",1,1,1000);
  gDataLogger_DeclareVariable(&gDataLogger,"vel_e","m/s",1,1,1000);
  gDataLogger_DeclareVariable(&gDataLogger,"vel_d","m/s",1,1,1000);

  gDataLogger_DeclareVariable(&gDataLogger,"T_odom","s",1,1,1000);
  gDataLogger_DeclareVariable(&gDataLogger,"odom_x","m",1,1,1000);
  gDataLogger_DeclareVariable(&gDataLogger,"odom_y","m",1,1,1000);
  
  gDataLogger_DeclareVariable(&gDataLogger,"T_pred","s",1,1,1000);
  gDataLogger_DeclareVariable(&gDataLogger,"pred_x","m",1,1,1000);
  gDataLogger_DeclareVariable(&gDataLogger,"pred_y","m",1,1,1000);
  
  gDataLogger_DeclareVariable(&gDataLogger,"T_cam","s",1,1,1000);
  gDataLogger_DeclareVariable(&gDataLogger,"cam_x","m",1,1,1000);
  gDataLogger_DeclareVariable(&gDataLogger,"cam_y","m",1,1,1000);
  
  gDataLogger_DeclareVariable(&gDataLogger,"T_kalman","s",1,1,1000);
  gDataLogger_DeclareVariable(&gDataLogger,"kalman_x","m",1,1,1000);
  gDataLogger_DeclareVariable(&gDataLogger,"kalman_y","m",1,1,1000);


  gDataLogger_DeclareVariable(&gDataLogger,"T_dist","s",1,1,1000);
  gDataLogger_DeclareVariable(&gDataLogger,"distM","",1,1,1000);

  
  while(ros::ok() && aberta  )
  {

    comando = waitKey(1);
    if(comando == 27)
      aberta = false;


    //obtenção de dados
    ros::spinOnce();


    if(cone.atualiza)
        cap >> img;
    if( img.empty() ){
      aberta = false;
        break;
    }
    else
      aberta = true;
    if(aberta == false)
    {
      break;
    }

    t_atual = ros::Time::now();
    //Predição
    if(enable)
    {
      T = t_atual.toSec() - t_inicial.toSec();
      DeltaT = t_atual.toSec() - t_anterior.toSec(); 
      Predicao(&filtro,&odometria, DeltaT);
      t_anterior = t_atual;

      x = odometria.x.at<float>(Point(0,0));
      y = odometria.x.at<float>(Point(0,2));
      gDataLogger_InsertVariable(&gDataLogger,"T_odom",&T);
      gDataLogger_InsertVariable(&gDataLogger,"odom_x",&x);
      gDataLogger_InsertVariable(&gDataLogger,"odom_y",&y);


      x = filtro.x.at<float>(Point(0,0));
      y = filtro.x.at<float>(Point(0,2));
      gDataLogger_InsertVariable(&gDataLogger,"T_pred",&T);
      gDataLogger_InsertVariable(&gDataLogger,"pred_x",&x);
      gDataLogger_InsertVariable(&gDataLogger,"pred_y",&y);

      cone.rastreia(img,true,(float)x,(float)y);

    }
    else{
      cone.rastreia(img,false,0,0);
    }

    if(cone.encontrou_cone)
    {
        Z.at<float>(Point(0,0)) = x;
        Z.at<float>(Point(0,1)) = y;
    }

    if(enable)
    {
      filtro.y = Z-filtro.H*filtro.x;
      dist_Mahalanobis =filtro.y.t()*(filtro.R+filtro.H*filtro.P*filtro.H.t())*filtro.y;
      dist = (double) dist_Mahalanobis.at<float>(Point(0,0));
      gDataLogger_InsertVariable(&gDataLogger,"T_dist",&T);
      gDataLogger_InsertVariable(&gDataLogger,"distM",&dist);
      recentDist[index] = dist;
      index++;
      if(index>=5)
        index = 0;
    }



    if(cone.encontrou_cone)
    {
      x = cone.pubx;
      y = cone.puby;
      gDataLogger_InsertVariable(&gDataLogger,"T_cam",&T);
      gDataLogger_InsertVariable(&gDataLogger,"cam_x",&x);
      gDataLogger_InsertVariable(&gDataLogger,"cam_y",&y);
      if(enable && dist < CHISQUARE)
      {
        Atualizacao(&filtro,x,y);
      }
      else
      {
        t_inicial = ros::Time::now();
        t_anterior = t_inicial;
        init_Kalman(&filtro,&odometria, cone.pubx, cone.puby);
        enable = true;
        T = 0;
        x = filtro.x.at<float>(Point(0,0));
        y = filtro.x.at<float>(Point(0,2));
        gDataLogger_InsertVariable(&gDataLogger,"T_pred",&T);
        gDataLogger_InsertVariable(&gDataLogger,"pred_x",&x);
        gDataLogger_InsertVariable(&gDataLogger,"pred_y",&y);
        gDataLogger_InsertVariable(&gDataLogger,"T_odom",&T);
        gDataLogger_InsertVariable(&gDataLogger,"odom_x",&x);
        gDataLogger_InsertVariable(&gDataLogger,"odom_y",&y);


        for(k=0;k<5;k++)
        {
          recentDist[k] = 0;
          index = 0;
        }
      }

    }

    if(enable)
    {
      cont = 0;
      for(k=0;k<5;k++)
      {
        if(recentDist[k] > CHISQUARE)
          cont++;
      }
      if(cont>4)
        enable = false;

      x = filtro.x.at<float>(Point(0,0));
      y = filtro.x.at<float>(Point(0,2));
      gDataLogger_InsertVariable(&gDataLogger,"T_kalman",&T);
      gDataLogger_InsertVariable(&gDataLogger,"kalman_x",&x);
      gDataLogger_InsertVariable(&gDataLogger,"kalman_y",&y);
 
      coneMsg.x = (float) x;
      coneMsg.y = (float) y;
      coneMsg.z = 1;
    }
    else
    {
      coneMsg.x = 0;
      coneMsg.y = 0;
      coneMsg.z = 0;
    }





    chatter_pub.publish(coneMsg);
    
    loop_rate.sleep();
  }

  for(k=1;k<=10;++k){
    usleep(200000); 
    gDataLogger_MatfileUpdate(&gDataLogger); // esvazia os buffers no arquivo de log
    
    //printf("\n [%i] Atualizado arquivo Matlab",k);
  }
  
  gDataLogger_Close(&gDataLogger);
  #ifdef BAGWRITE
  bag.close();
  #endif
  

  return 0;
}