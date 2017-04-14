#include "ros/ros.h"
#include "geometry_msgs/Point32.h"
#include "std_msgs/Bool.h"
#include <stdio.h>

#define PI 3.14159265f

#define DEBUG 1

#define DISTANCIA_MAXIMA 2.0f
#define DISTANCIA_MINIMA 1.0f
#define VELOCIDADE_LINEAR 1.2f
#define VELOCIDADE_LINEAR_APROX 1.0f

//Variaveis Globais-------------------------------------------------------------------------------------------------------

geometry_msgs::Point32 DistanciaCamera;
//geometry_msgs::Point32 DistanciaInicialCamera;

geometry_msgs::Point32 velocidadeRobo;

static bool enable = false;

#if defined(DEBUG)
  FILE *arq;
#endif

//Funcoes ---------------------------------------------------------------------------------------------------------------

void distanciaCallback(const geometry_msgs::Point32::ConstPtr& msg);
void enableCallback(const std_msgs::Bool::ConstPtr& msg);
void calcularVelocidades(void );

//-----------------------------------------------------------------------------------------------------------------------
void distanciaCallback(const geometry_msgs::Point32::ConstPtr& msg){

  DistanciaCamera.x = msg->x;
  DistanciaCamera.y = msg->y;
  DistanciaCamera.z = msg->z;

}
void enableCallback(const std_msgs::Bool::ConstPtr& msg){

  enable = msg -> data;
}

/**Funcao que calcula as velocidades para alcancar o ponto da camera*/
// void calculaVelocidades (const ros::TimerEvent&){

//   static float x = 0, y = 0, theta = 0;
//   static float vx = 0, vy = 0, w = 0;
//   static float periodo = 0;
//   static float amostras = 0, incremento = 0;
//   static float t =0;
//   static float erro1 = 0, erro2 = 0, erro3 = 0;
//   const float k1 = 1.2, k2 = 1.2, k3 = 1.2;
//   static int flag = 0;
//   static float distanciaRestantex = 0, distanciaRestantey = 0, distanciaRestantetheta = 0;

//   if (!enable){
//     vx = 0;
//     vy = 0;
//     w  = 0;
//     erro1 = 0;
//     erro2 = 0;
//     erro3 = 0;
//     return;
//   }
//   if (inicio){

//     x = (DistanciaCamera.x)*cos(DistanciaCamera.z *PI/180);
//     y = (DistanciaCamera.x)*sin(DistanciaCamera.z *PI/180);
    
//     theta = DistanciaCamera.z * PI/180;

//     if ((abs(x) >= abs(y)) && (abs(x) >= abs(theta))) {
//       periodo = x/VEL_VIRTUAL;
    
//       if(periodo < 0){
//         periodo = -periodo;
//       }

//       vx = x/periodo;
//       vy = y/periodo;
//       w = theta/periodo;
//     }
//     else if ((abs(y) > abs(x)) && (abs(y) >= abs(theta))){
//       periodo = y/VEL_VIRTUAL;
//       if(periodo < 0){
//         periodo = -periodo;
//       }
//       vx = x/periodo;
//       w = theta/periodo;
//       vy = y/periodo;
//     }
//     else if ((abs(theta) > abs(x))&&(abs(theta) > abs(y))) {
//       periodo = theta/VEL_VIRTUAL;
//       if(periodo < 0){
//         periodo = -periodo;
//       }
//       vx = x/periodo;
//       vy = y/periodo;
//       w = theta/periodo;
//     }

//     amostras = periodo/TEMPO_AMOSTRAGEM;
//     t = 0;
//     incremento = 1/amostras;

//     inicio = false;

//   }

//   if (t < 1){ 
      
//     distanciaRestantex = ((DistanciaInicialCamera.x)*cos(DistanciaInicialCamera.z *PI/180)) - t*vx;
//     distanciaRestantey = ((DistanciaInicialCamera.x)*sin(DistanciaInicialCamera.z *PI/180)) - t*vy;
//     distanciaRestantetheta = (DistanciaInicialCamera.z * PI/180) - t*w;
//     t += incremento;
//     flag = 1;
  
//   }else if (flag == 1){
  
//     flag = 0;
//     distanciaRestantex = 0;
//     distanciaRestantey = 0;
//     distanciaRestantetheta = 0;
      
//   }  

//   erro1 = DistanciaCamera.x - distanciaRestantex;
//   erro2 = DistanciaCamera.y - distanciaRestantey;
//   erro3 = DistanciaCamera.z*PI/180 - distanciaRestantetheta;

//   velocidadeRobo.x = (vx*cos(erro3)) + k1*erro1;
//   velocidadeRobo.z = w + (vx * k2 * erro2) + (k3 * sin(erro3));

// }

void calculaVelocidades2 (void) {
  
  float k_linear = 2;

  if (!enable){
    velocidadeRobo.x = 0;
    velocidadeRobo.z = 0;
    return;
  }
  if (DistanciaCamera.x > DISTANCIA_MAXIMA) {
    velocidadeRobo.x = VELOCIDADE_LINEAR;
    velocidadeRobo.z = PI/180*(DistanciaCamera.y);
  }  
  else if (DistanciaCamera.x > DISTANCIA_MINIMA){
    velocidadeRobo.x = k_linear*(DistanciaCamera.x - DISTANCIA_MINIMA);
    velocidadeRobo.z = PI/180*(DistanciaCamera.y);
  }
  else if (DistanciaCamera.x < DISTANCIA_MINIMA){
    velocidadeRobo.x = VELOCIDADE_LINEAR_APROX;
    velocidadeRobo.z = PI/180*(DistanciaCamera.y);
  }

#if defined(DEBUG)
  fprintf(arq,"%f %f \n",velocidadeRobo.x,velocidadeRobo.z);
#endif

}

int main(int argc, char **argv)
{

#if defined(DEBUG)
  arq = fopen("feedback_controle_camera.txt", "w");
#endif

  ros::init(argc, argv, "controle_camera");

  ros::NodeHandle n;
 
  ros::Subscriber subDistancia = n.subscribe("cone_position", 1000, distanciaCallback);
  ros::Subscriber subEnable = n.subscribe("follow_camera", 1000, enableCallback);

  ros::Publisher pubVelocidade = n.advertise<geometry_msgs::Point32>("velocity", 1000);

  ros::Rate loop_rate(5);
  
  float tempo = 0;

  while (ros::ok()){

    //Se estiver no modo seguir trajetoria
    if (enable){
      calculaVelocidades2();
      pubVelocidade.publish(velocidadeRobo);
    
    }
    else {
      velocidadeRobo.x = 0;
      velocidadeRobo.z = 0;
      pubVelocidade.publish(velocidadeRobo);
    }

    loop_rate.sleep();
    ros::spinOnce();
  
  }
#if defined(DEBUG)
  fclose(arq);
#endif
  return 0;
}
