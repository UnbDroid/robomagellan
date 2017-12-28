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

#include "gqueue.hpp"
#include "gmatlabdatafile.hpp"
#include "gdatalogger.hpp"




using namespace std;
using namespace cv;


#define TAXA_AMOSTRAGEM 0.1f

#define DRODAS 0.1f //distancia entre rodas
#define DCAMERA 0.1f //distancia entre camera e centro do robo

float f10, f12, f30, f32;
float b10, b11, b30, b31;
float vel_e = 0, vel_d = 0;



float z_x = 0, z_y = 0;
float e_x = 0, e_y = 0;
float k_x = 0, k_y = 0;


bool enable = false, init = false, enable_visao = false, enable_encoder = false;
int miss_cont = 0;

bool miss = false;


rosbag::Bag bag;
    
GDATALOGGER gDataLogger;

PGDATALOGGER pgDataLogger;


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

void mostra_pos(int quant)
{
  static float K_x[50];
  static float K_y[50];
  static float E_x[50];
  static float E_y[50];
  static float Z_x[50];
  static float Z_y[50];
  static bool visao[50];
  static int indexE = 0;
  static int indexZ = 0;
  static bool maximoE = false;
  static bool maximoZ = false;

  int i,j,max;

  if(quant == 1 || quant == 3 || quant == 6)
  {
    E_x[indexE] = e_x;
    E_y[indexE] = e_y;
    indexE++;
  }

  if(quant>4)
  {
    visao[indexZ] = false;
    indexZ++;
  }
  else if(quant > 1)
  {
    visao[indexZ] = true;
    K_x[indexZ] = k_x;
    K_y[indexZ] = k_y;
    Z_x[indexZ] = z_x;
    Z_y[indexZ] = z_y;
    indexZ++;
  }
  if(indexZ >= 50)
  {
    maximoZ = true;
    indexZ = 0;
  }

  if(indexE >= 50)
  {
    maximoE = true;
    indexE = 0;
  }


  if(maximoE)
  {
    max = 50;
  }
  else
  {
    max = indexE;
  }

  float maxX = -1;
  float maxY = -1;

  for(i=0;i<max;i++)
  {
    if(E_x[i]>maxX)
      maxX = E_x[i];
    if(fabs(E_y[i])>maxY )
      maxY = fabs(E_y[i]);
  }
  
  if(maximoZ)
  {
    max = 50;
  }
  else
  {
    max = indexZ;
  }

  for(i=0;i<max;i++)
  {
    if(Z_x[i]>maxX)
      maxX = Z_x[i];
    if(fabs(Z_y[i])>maxY )
      maxY = fabs(Z_y[i]);
    if(K_x[i]>maxX)
      maxX = K_x[i];
    if(fabs(K_y[i])>maxY )
      maxY = fabs(K_y[i]);
  }

  Mat Posicao(500,500,CV_8UC3);
  Posicao = Scalar(255,255,255);
  arrowedLine(Posicao,Point(10,500),Point(10,0),Scalar(0,0,0),1,8,0,0.01);
  arrowedLine(Posicao,Point(10,250),Point(500,250),Scalar(0,0,0),1,8,0,0.01);

  if(maximoE)
  {
    max = 50;
    j=indexE;
  }
  else
  {
    max = indexE;
    j=0;
  }


  int x,y,x_ant,y_ant;
  
  for(i=0;i<max;i++)
  {
    x = 480*(E_x[j]/maxX) + 10;
    y = 250 - 240*(E_y[j]/maxY);
    if(i>0)
    {
      line(Posicao,Point(x_ant,y_ant),Point(x,y),Scalar(255,0,0));
      //circle(Posicao,Point(x,y),3,Scalar(255,0,0));
    }
    x_ant = x;
    y_ant = y;
    j++;
    if(j>=50)
      j=0;
  }
  
  if(maximoZ)
  {
    max = 50;
    j=indexZ;
  }
  else
  {
    max = indexZ;
    j=0;
  }

  int x2,y2,x2_ant,y2_ant;
  for(i=0;i<max;i++)
  {
    if(visao[j])
    {
      x = 480*(Z_x[j]/maxX) + 10;
      y = 250 - 240*(Z_y[j]/maxY);
      if(i>0)
      {
        line(Posicao,Point(x_ant,y_ant),Point(x,y),Scalar(0,255,0) );
      }
      x_ant = x;
      y_ant = y;

      x = 480*(K_x[j]/maxX) + 10;
      y = 250 - 240*(K_y[j]/maxY);
      if(i>0)
      {
        line(Posicao,Point(x2_ant,y2_ant),Point(x,y),Scalar(0,0,255) );
      }
      x2_ant = x;
      y2_ant = y;
    }
    j++;
    if(j>=50)
      j=0;
  }



  imshow("Posicao",Posicao);



}

void cone_positionCallback(const geometry_msgs::Point32::ConstPtr& msg)
{

  float dist, angulo;
  double xv, yv;

  if(msg->z == 1)
  {
    if(!enable)
    {
      init = true;
    }
    //posicao do cone para a camera
    z_x = msg->x;
    z_y = msg->y;
    xv = z_x;
    yv = z_y;
    enable_visao = true;
    cout<<z_x<<"  "<<z_y<<endl;
    gDataLogger_InsertVariable(&gDataLogger,"x_v",&xv,1);
    gDataLogger_InsertVariable(&gDataLogger,"y_v",&yv,1);

  }
  else
  {
    miss = true;
    if(enable)
    {
      enable_visao = false;
      miss_cont++;
      if(miss_cont>=5)
      {
        enable = false;
      }
    }
  }


  


  bag.write("Camera", ros::Time::now(), msg);


}


void velocidade_atualCallback(const geometry_msgs::Point32::ConstPtr& msg)
{
  enable_encoder = true;
  vel_d = 2.0*CV_PI*0.06*msg->x;
  vel_e = 2.0*CV_PI*0.06*msg->y;
  bag.write("Encoder", ros::Time::now(), msg);  
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

  float dataP[16] = {0.04,0,0,0, 0,0.01,0,0,  0,0,0.04,0, 0,0,0,0.01};
  Mat P(4,4,CV_32F,dataP);
  float dataQ[16] = {0.04,0,0,0, 0,0.04,0,0, 0,0,0.04,0,  0,0,0,0.04};
  Mat Q(4,4,CV_32F,dataQ);
  float dataH[8] = {1,0,0,0, 0,0,1,0};
  Mat H (2,4,CV_32F,dataH);

  float dataR[4] = {0.01,0, 0,0.01};
  Mat R(2,2,CV_32F,dataR);
  filtro->init(x,F,P,Q,H,R,B);
  e_x = z_x;
  k_x = z_x;
  e_y = z_y;
  k_y = z_y;
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
  float Y = filtro->x.at<float>(Point(0,2));



  
  filtro->F.at<float>(Point(0,1)) = -seno*aux;
  filtro->F.at<float>(Point(2,1)) = -cosseno*aux;
  filtro->F.at<float>(Point(0,3)) = cosseno*aux;
  filtro->F.at<float>(Point(2,3)) = -seno*aux;


  aux = cosseno*( (X+DCAMERA)*(vel_e-vel_d)*TAXA_AMOSTRAGEM+2*DRODAS*(Y-DRODAS) );
  aux += seno*( 2*DRODAS*(X+DCAMERA) - TAXA_AMOSTRAGEM*(Y*(vel_e-vel_d)+DRODAS*(vel_e+vel_d)) );
  aux /= dividendo;
  filtro->B.at<float>(Point(0,1)) = aux;

  aux = -cosseno*( (X+DCAMERA)*(vel_e-vel_d)*TAXA_AMOSTRAGEM+2*DRODAS*(Y+DRODAS) );
  aux -= seno*( 2*DRODAS*(X+DCAMERA)-TAXA_AMOSTRAGEM*(Y*(vel_e-vel_d)+DRODAS*(vel_e+vel_d)) );
  aux /= dividendo;
  filtro->B.at<float>(Point(1,1)) = aux;

  aux = seno*(TAXA_AMOSTRAGEM*(vel_e-vel_d)*(X+DCAMERA) + 2*DRODAS*(Y-DRODAS));
  aux += cosseno*(-2*DRODAS*(X+DCAMERA)+TAXA_AMOSTRAGEM*(Y*(vel_e-vel_d)+DRODAS*(vel_e+vel_d)) );
  aux/dividendo;
  filtro->B.at<float>(Point(0,3)) = aux;
  
  aux = -seno*(TAXA_AMOSTRAGEM*(vel_e-vel_d)*(X+DCAMERA) + 2*DRODAS*(Y+DRODAS));
  aux -= cosseno*(-2*DRODAS*(X+DCAMERA)+TAXA_AMOSTRAGEM*(Y*(vel_e-vel_d)+DRODAS*(vel_e+vel_d)) );
  aux/dividendo;
  filtro->B.at<float>(Point(1,3)) = aux;

  float dataU[2] = {vel_d,vel_e};
  Mat u(2,1,CV_32F,dataU);

  filtro->predict(u);
  e_x = filtro->x.at<float>(Point(0,0));
  e_y = filtro->x.at<float>(Point(0,2));

}

void Atualizacao(Kalman* filtro)
{
  float dataZ[2] = {z_x,z_y};
  Mat z(2,1,CV_32F,dataZ);
  filtro->update(z);
  k_x = filtro->x.at<float>(Point(0,0));
  k_y = filtro->x.at<float>(Point(0,2));

}





int main(int argc, char **argv)
{

  ros::init(argc, argv, "receiver");


  ros::NodeHandle n;

  ros::Subscriber sub = n.subscribe("cone_position", 1000, cone_positionCallback);
  ros::Subscriber sub2 = n.subscribe("velocidade_atual", 1000, velocidade_atualCallback);
  //ros::Timer temporizador = n.createTimer(ros::Duration(TEMPO_AMOSTRAGEM),CalculaAngulo, false);
  sleep(1);

  Kalman filtro;


  Mat aux;

  int comando = -1;

  //pgDataLogger = &gDataLogger;

  bag.open("test.bag", rosbag::bagmode::Read);
  

  // Data logger:
  if(!gDataLogger_Init(&gDataLogger,"src/bruce_vision/src/matlabdatafiles/matlabdatafile.mat",NULL)){
    printf("\nErro em gDataLogger_Init\n\n");
    return EXIT_FAILURE;
  }

  gDataLogger_DeclareVariable(&gDataLogger,"t","s",1000);
  gDataLogger_DeclareVariable(&gDataLogger,"x_v","m",1000);
  gDataLogger_DeclareVariable(&gDataLogger,"y_v","m",1000);

  
  int cont = 0;

  while(ros::ok() && comando!=27  )
  {

    cont = 0;
    if(enable)
    {
      if(enable_encoder)
      {
        Predicao(&filtro);
        enable_encoder = false;
        cont++;
      }
      if(enable_visao)
      {
        cont+=2;
        Atualizacao(&filtro);
        enable_visao = false;
      }
      else
      {
        if(miss)
        {
          miss = false;
          cont+=5;
        }
      }
    }
    else if(init)
    {
      init = false;
      init_Kalman(&filtro);
      enable = true;
      cont = 3;
    }

    if(cont>0){
      mostra_pos(cont);
    }

    comando = waitKey(1);
    ros::spinOnce();
  }

  int k;
  for(k=1;k<=10;++k){
    usleep(200000); 
    gDataLogger_MatfileUpdate(&gDataLogger); // esvazia os buffers no arquivo de log
    
    printf("\n [%i] Atualizado arquivo Matlab",k);
  }
  gDataLogger_Close(&gDataLogger);
  bag.close();


  return 0;
}