#include "ros/ros.h"
#include "std_msgs/String.h"
#include "robo_virtual/Posicao.h"
#include "geometry_msgs/Twist.h"
#include "nav_msgs/Odometry.h"
#include "nav_msgs/Path.h"
#include "geometry_msgs/Quaternion.h"
#include "tf/transform_datatypes.h"
#include "geometry_msgs/PoseStamped.h"
#include "std_msgs/Bool.h"

#include <math.h>
#include <stdio.h>

#define PI 3.14159265f


#define TEMPO_AMOSTRAGEM 0.1f
#define VELOCIDADE_MAXIMA 0.9f
#define VELOCIDADE_MINIMA 0.15f
#define VELOCIDADE_MINIMA_ANGULAR 0.05f

//Variaveis Globais-------------------------------------------------------------------------------------------------------

//valores Robo
struct Robo{
  float x,y,theta;
};

std::vector<geometry_msgs::PoseStamped> pose;
geometry_msgs::PoseStamped auxPose;
geometry_msgs::Twist velocidadeRobo;

Robo roboAtual, roboDestino,roboReferencia, roboInicial;

bool parar = true;
bool novoSegmento = false;

static float velocidadeLinear = 0, velocidadeAngular = 0;

static int trajetoriaAtual = 0;
/*Parametros de adaptacao do controlador*/
static float a1 =0, a2 = 0; 
/*Parametros de erro*/
static float erro1 = 0, erro2 = 0, erro3=0;

static bool inicio = false;

static bool enable = false;

FILE *arq, *arq2;

//Funcoes ---------------------------------------------------------------------------------------------------------------

void controladorTrajetoriaReal(void);

//-----------------------------------------------------------------------------------------------------------------------

/**Funcao do subscriber que recebe os pontos a serem seguidos*/
void trajetoCallback(const nav_msgs::Path::ConstPtr& msg)
{
  
  if(enable){
    pose = msg->poses;
    trajetoriaAtual = 0;
    ROS_INFO("Posicao recebida");
  }
}

void enablePathCallback(const std_msgs::Bool::ConstPtr& msg)
{
  enable = msg->data;
  if(enable){
    ROS_INFO("enable enable");
  }
}
/**Posicao atual lida do siimulador gazebo*/
void posicaoAtualCallback(const nav_msgs::Odometry::ConstPtr& msg)
{
  geometry_msgs::Quaternion orientacao;

  double roll, pitch, yaw;
  
  tf::Quaternion quat;

  orientacao = msg->pose.pose.orientation;  
  
  //Tranforma a orientacao dada em quaternions para radianos 
  tf::quaternionMsgToTF(orientacao, quat);
  tf::Matrix3x3(quat).getRPY(roll, pitch, yaw);

  //ROS_INFO("quaternions: x: %f y: %f z:%f w: %f", orientacao.x,orientacao.y,orientacao.z,orientacao.w);
  //ROS_INFO("yaw: %f pitch: %f roll: %f", yaw,pitch,roll);
  
  roboAtual.x = msg->pose.pose.position.x;
  roboAtual.y = msg->pose.pose.position.y;
  roboAtual.theta = yaw;

  //ROS_INFO("Posicao atual lida: x:%f y:%f theta: %f", roboAtual.x, roboAtual.y, roboAtual.theta);
}

/**Funcao que atualiza o segmento atual a ser realizado*/
void calculaSegmento (void) {

  static float aux_x = 0, aux_y = 0;
  static float gama = 0; /*angulo de inclinacao da reta de segmento de trajetoria*/

  //Indica que ele passou da regiao do seguimeto atual e ira prossegir para o proximo segmento ou que irá comecar o primeiro segmento  
  if (!enable){
    parar = true;
    inicio = false;
    return;
  }
  if ((((cos(gama)*(roboAtual.x - roboDestino.x))+(sin(gama)*(roboAtual.y - roboDestino.y))) > 0) || (trajetoriaAtual == 0)){
    if (!pose.empty()){
      auxPose = pose.front();
      pose.erase(pose.begin());

      aux_x = roboDestino.x;
      aux_y = roboDestino.y;

      roboDestino.x = auxPose.pose.position.x;
      roboDestino.y = auxPose.pose.position.y;
      
      if (trajetoriaAtual == 0){
        gama = atan2((roboDestino.y - roboAtual.y),(roboDestino.x - roboAtual.x));  
      }
      else {
        gama = atan2((roboDestino.y - aux_y),(roboDestino.x - aux_x));
      }
      
      trajetoriaAtual++;

      ROS_INFO("Segmento atual %d:  x:%f y:%f",trajetoriaAtual, auxPose.pose.position.x,auxPose.pose.position.y);

      fprintf(arq,"Segmento atual %d:  x:%f y:%f",trajetoriaAtual, auxPose.pose.position.x,auxPose.pose.position.y);
      
      roboReferencia = roboAtual;
      roboInicial = roboReferencia;
      a1 =0, a2 = 0; 
      erro1 = 0, erro2 = 0, erro3=0;
      parar = false;

      inicio = true;
    }
    else{
      parar=true;
      inicio = false;
      //ROS_INFO("Parei - segmento: %d", trajetoriaAtual);
    }
  }

}

// Fazendo a trajetoria de referencia por meio de interpolacao
// Dando errado - velocidade linear nao pode ser constante (nao pode andar reto)
void RoboReferencia(const ros::TimerEvent&){

  static float vx = 0, vy = 0 , w = 0;
  static float periodo = 0, amostras = 0, incremento = 0;
  static float t =0; 
  float anguloReta = 0;
  static float x,y,theta;
  static int flag = 0;
  static ros::Time tempo = ros::Time::now();  
  float tempo_aux = ros::Time::now().toSec() - tempo.toSec();
  tempo = ros::Time::now();

  if (inicio) {

    x = roboDestino.x - roboInicial.x;
    y = roboDestino.y - roboInicial.y;
    
    anguloReta = atan2(y,x);

    theta = anguloReta - roboReferencia.theta;

    if ((abs(x) >= abs(y)) && (abs(x) >= abs(theta))) {
      periodo = x/0.9;
      if(periodo < 0){
        periodo = -periodo;
      }

      vx = x/periodo;
      vy = y/periodo;
      w = theta/periodo;
    }
    else if ((abs(y) > abs(x)) && (abs(y) >= abs(theta))){
      periodo = y/0.9;
      if(periodo < 0){
        periodo = -periodo;
      }
      vx = x/periodo;
      w = theta/periodo;
      vy = y/periodo;
    }
    else if ((abs(theta) > abs(x))&&(abs(theta) > abs(y))) {
      periodo = theta/0.9;
      if(periodo < 0){
        periodo = -periodo;
      }
      vx = x/periodo;
      vy = y/periodo;
      w = theta/periodo;
    }

    amostras = periodo/TEMPO_AMOSTRAGEM;
    t = 0;
    incremento = 1/amostras;

    ROS_INFO("periodo: %f amostras: %f t = %f", periodo, amostras, t);
    fprintf(arq,"x: %f y: %f t = %f \n", x, y, theta);
    fprintf(arq,"periodo: %f amostras: %f incremento = %f\n", periodo, amostras, incremento);
    fprintf(arq,"velocidades: x: %f y :%f theta: %f \n", vx, vy, w);
    inicio = false;
  }

  if (t < 1){ 
    roboReferencia.x = roboInicial.x + t*x;
    roboReferencia.y = roboInicial.y + t*y;
    roboReferencia.theta = roboInicial.theta + t*theta;
    
    t += incremento;
    flag = 1;
  }else if (flag == 1){
    flag = 0;
    roboReferencia.x = roboInicial.x + x;
    roboReferencia.y = roboInicial.y + y;
    roboReferencia.theta = roboInicial.theta + theta;
  }
  
  //ROS_INFO("roboReferencia: x: %f y: %f theta: %f", roboReferencia.x, roboReferencia.y, roboReferencia.theta);

  //velocidades lineares e angulares a serem aplicadas no robo de referencia
  velocidadeLinear = cos(roboReferencia.theta)*vx + sin(roboReferencia.theta)*vy;
  velocidadeAngular = w;

  if (parar) {
    velocidadeLinear = 0;
    velocidadeAngular = 0;
    vx = 0;
    vy = 0;
  }
  
  controladorTrajetoriaReal();  
  
}

/**Funcao do controlador de trajetoria para o robo real*/
void controladorTrajetoriaReal(void /*const ros::TimerEvent&*/) {

  const float lambda = 1.47;
  /*Parametros de ganho do controlador*/
  const float gama1 = 1.2;
  const float gama2 = 1.2;
  const float k1=1.2, k2=1.3, k3=1.2;

  /*velocidades dadas para o robo simulado*/
  static float vf=0, wf=0; 
  /*velocidades dadas às rodas do robo real*/
  static float velocidadeEsquerda = 0, velocidadeDireita = 0; 
  static float funcaoAuxiliar = 0;

  erro1 = cos(roboAtual.theta)*(roboReferencia.x - roboAtual.x) + sin(roboAtual.theta)*(roboReferencia.y - roboAtual.y);
  erro2 = -sin(roboAtual.theta)*(roboReferencia.x - roboAtual.x) + cos(roboAtual.theta)*(roboReferencia.y - roboAtual.y);
  erro3 = roboReferencia.theta - roboAtual.theta;

  vf = (velocidadeLinear * cos(erro3)) + (k1 *erro1);
  wf = velocidadeAngular + (velocidadeLinear * k2 * erro2)  + (k3 * sin(erro3));

  if (a2 > lambda){
    funcaoAuxiliar = 0; 
  }
  else {
    float fo = (gama2*wf*sin(erro3))/k2;

    funcaoAuxiliar = ((1 - (a2/lambda))*(1 - (a2/lambda))) + ((fo*fo) + 1 );

  }

  a1 = a1 + (gama1*erro1*vf);
  a2 = a2 + ((lambda/k2)*wf*sin(erro3)) + funcaoAuxiliar; 

  velocidadeEsquerda = a1*vf + a2*wf;
  velocidadeDireita = a1*vf - a2*wf;

  //ROS_INFO("Velocidades para o robo simulado: vf:%f wf:%f",vf,wf);
  //ROS_INFO("Velocidades para o robo real: vd:%f ve:%f",velocidadeDireita, velocidadeEsquerda);

  if (!parar) {

    if (vf > VELOCIDADE_MAXIMA){
      vf = VELOCIDADE_MAXIMA;
    }
    else if (vf < -VELOCIDADE_MAXIMA){
      vf = -VELOCIDADE_MAXIMA;
    }
    if (wf > VELOCIDADE_MAXIMA){
      wf = VELOCIDADE_MAXIMA;
    }
    else if (wf < -VELOCIDADE_MAXIMA){
      wf = -VELOCIDADE_MAXIMA;
    }

    /*if ((!pose.empty()) && abs(velocidadeAngular) < 0.2){

      if ((vf < VELOCIDADE_MINIMA) && (vf>0)){
        vf = VELOCIDADE_MINIMA;
      }
      else if ((vf > (-VELOCIDADE_MINIMA)) && (vf < 0)){
        vf = -VELOCIDADE_MINIMA;
      }*/
      /*if ((wf < VELOCIDADE_MINIMA_ANGULAR) && (wf > 0)){
        wf = VELOCIDADE_MINIMA_ANGULAR;
      }
      else if ((wf > (-VELOCIDADE_MINIMA_ANGULAR)) && (wf < 0)){
        wf = -VELOCIDADE_MINIMA_ANGULAR;
      }*/
    
    //}

    velocidadeRobo.linear.x = vf;
    velocidadeRobo.angular.z = wf;
  }
  else {
    vf = 0;
    wf = 0;
    velocidadeRobo.linear.x = 0;
    velocidadeRobo.angular.z = 0;
  }

  fprintf(arq2, "%f  %f \n", vf,wf);
}

int main(int argc, char **argv)
{

  arq = fopen("feedback.txt", "w");
  arq2 = fopen("feedbackvel.txt", "w");

  ros::init(argc, argv, "robo_virtual");

  ros::NodeHandle n;
 
  ros::Subscriber subTrajeto = n.subscribe("path_planned", 1000, trajetoCallback);
  ros::Subscriber subAtual = n.subscribe("odom", 1000, posicaoAtualCallback);
  ros::Subscriber subEnable = n.subscribe("enable_follow_path", 1000, enablePathCallback);

  ros::Publisher pubVelocidade = n.advertise<geometry_msgs::Twist>("cmd_vel", 1000);

  ros::Timer temporizador = n.createTimer(ros::Duration(TEMPO_AMOSTRAGEM),RoboReferencia, false);
  //ros::Timer controlador = n.createTimer(ros::Duration(TEMPO_AMOSTRAGEM),controladorTrajetoriaReal, false);

  ros::Rate loop_rate(10);
  
  float tempo = 0;

  while (ros::ok()){

    tempo += 0.1;
    calculaSegmento();
    pubVelocidade.publish(velocidadeRobo);

    ROS_INFO("%f %f %f %f %f %f %f",tempo, roboReferencia.x, roboReferencia.y, roboReferencia.theta,roboAtual.x, roboAtual.y, roboAtual.theta);
    
    fprintf(arq,"%f %f %f %f %f %f %f\n",tempo, roboReferencia.x, roboReferencia.y, roboReferencia.theta,roboAtual.x, roboAtual.y, roboAtual.theta); 
    loop_rate.sleep();
    ros::spinOnce();
  
  }

  fclose(arq);

  return 0;
}





//-----------------------------Backup -----------------------------------------------------------------------------
/**As coordenadas x e y do robo estao em relacao ao mapa do mundo, nao em relacao aos eixos do robo*/
/**Funcao que calcula a cinematica do robo de referencia*/
// void cinematicaRoboReferenciaErrada(const ros::TimerEvent&){

//   static float vx = 0, vy = 0;

//   static ros::Time tempo = ros::Time::now();  
//   float tempo_aux = ros::Time::now().toSec() - tempo.toSec();
//   float erro_x = 0, erro_y = 0;

//   tempo = ros::Time::now();

//   //Atualizando a posicao do robo de referencia
//   roboReferencia.x = roboReferencia.x + (cos(roboReferencia.theta)*velocidadeLinear - sin(roboReferencia.theta)*velocidadeAngular)*tempo_aux;
//   roboReferencia.y = roboReferencia.y + (sin(roboReferencia.theta)*velocidadeLinear + cos(roboReferencia.theta)*velocidadeAngular)*tempo_aux;
//   roboReferencia.theta = roboReferencia.theta + (2*PI*velocidadeAngular*tempo_aux);

//   // Angulo do robo fica entre -PI e PI
//   while (abs(roboReferencia.theta) > PI){
//     if ((roboReferencia.theta > PI) && (roboReferencia.theta > 0)) {
//       roboReferencia.theta -= PI;
//     }
//     if ((roboReferencia.theta < -PI) && (roboReferencia.theta < 0)) {
//       roboReferencia.theta += PI;
//     }
//   }

//   //velocidade em x e y do robo de referencia em relacao ao mundo
//   if (!parar) {
//     erro_x = (roboDestino.x - roboReferencia.x);
//     erro_y = (roboDestino.y - roboReferencia.y);

//     vx = erro_x/TEMPO_AMOSTRAGEM; 
//     vy = erro_y/TEMPO_AMOSTRAGEM;

//   }
  
//   /*velocidades lineares e angulares a serem aplicadas no robo de referencia*/
//   velocidadeLinear = cos(roboReferencia.theta)*vx + sin(roboReferencia.theta)*vy;
//   velocidadeAngular = -sin(roboReferencia.theta)*vx+ cos(roboReferencia.theta)*vy;

//   if (velocidadeLinear > VELOCIDADE_MAXIMA){
//     velocidadeLinear = VELOCIDADE_MAXIMA;
//   }
//   else if (velocidadeLinear < -VELOCIDADE_MAXIMA){
//     velocidadeLinear = -VELOCIDADE_MAXIMA;
//   }
//   if (velocidadeAngular > VELOCIDADE_MAXIMA){
//     velocidadeAngular = VELOCIDADE_MAXIMA;
//   }
//   else if (velocidadeAngular < -VELOCIDADE_MAXIMA){
//     velocidadeAngular = -VELOCIDADE_MAXIMA;
//   }

//   /*if ((!pose.empty()) && abs(velocidadeAngular) < 0.2){

//     if ((velocidadeLinear < VELOCIDADE_MINIMA) && (velocidadeLinear> 0)){
//       velocidadeLinear = VELOCIDADE_MINIMA;
//     }
//     else if ((velocidadeLinear > (-VELOCIDADE_MINIMA)) && (velocidadeLinear < 0)){
//       velocidadeLinear = -VELOCIDADE_MINIMA;
//     }
  
//   }*/

//   if (parar) {
//     velocidadeLinear = 0;
//     velocidadeAngular = 0;
//     vx = 0;
//     vy = 0;
//   }
  
//   controladorTrajetoriaReal();  
  
// }
// void RoboReferenciaAntigo(const ros::TimerEvent&){

//   static float vx = 0, vy = 0;

//   static float incremento = 0, incrementoangulo = 0, t =0 , amostras = 0; 
//   float distancia = 0, anguloReta = 0;
//   float x,y;

//   static ros::Time tempo = ros::Time::now();  
//   float tempo_aux = ros::Time::now().toSec() - tempo.toSec();
//   tempo = ros::Time::now();

//   if (inicio) {

//     x = roboDestino.x - roboInicial.x;
//     y = roboDestino.y - roboInicial.y;
    
//     anguloReta = atan2(y,x);

//     x  = pow(x , 2);
//     y  = pow(y , 2);

//     distancia = sqrt(x+y);

//     roboReferencia.theta = roboReferencia.theta + (2*PI*velocidadeAngular*tempo_aux);

//     if (pose.size() > 0) {

//       vx = 0.8*cos(roboReferencia.theta);
//       vy = 0.8*sin(roboReferencia.theta);
      
//       if (distancia < 0.08/*0.173*/){
//         incremento = 1;
//         t = 1;
//         amostras = 1;
//       }
//       else {
//         amostras = distancia/0.08;
//         incremento = 1/amostras;
//         t = 0;
//       }

//     }
//     else {
      
//       vx = 0.5*cos(roboReferencia.theta);
//       vy = 0.5*sin(roboReferencia.theta);

//       if (distancia < 0.05){
//         incremento = 1;
//         t = 1;
//         amostras = 1;
//       }
//       else {
//         amostras = (distancia/0.05);
//         incremento = 1/amostras;
//       }

//     }

//     incrementoangulo = (anguloReta - roboReferencia.theta)/amostras;

//     inicio = false;
    
//   }

//   if ((t+incremento) <= 1){
//     t = t+incremento;  
//     roboReferencia.x = roboInicial.x + t*(roboDestino.x - roboInicial.x);
//     roboReferencia.y = roboInicial.y + t*(roboDestino.y - roboInicial.y);
//     roboReferencia.theta = roboReferencia.theta + (2*PI*velocidadeAngular*tempo_aux);
//   }
//   else {
//     roboReferencia.theta = atan2((roboDestino.y - roboReferencia.y), (roboDestino.x - roboReferencia.x));
//     roboReferencia.x = roboDestino.x;
//     roboReferencia.y = roboDestino.y;
//   }
  
//   //ROS_INFO("roboReferencia: x: %f y: %f theta: %f", roboReferencia.x, roboReferencia.y, roboReferencia.theta);

//   //velocidades lineares e angulares a serem aplicadas no robo de referencia
//   velocidadeLinear = cos(roboReferencia.theta - anguloReta)*vx + sin(roboReferencia.theta - anguloReta)*vy;
//   velocidadeAngular = -sin(roboReferencia.theta - anguloReta)*vx+ cos(roboReferencia.theta - anguloReta)*vy;

//   if (velocidadeAngular > VELOCIDADE_MAXIMA){
//     velocidadeAngular = VELOCIDADE_MAXIMA;
//   }
//   else if (velocidadeAngular < -VELOCIDADE_MAXIMA){
//     velocidadeAngular = -VELOCIDADE_MAXIMA;
//   }

//   if (parar) {
//     velocidadeLinear = 0;
//     velocidadeAngular = 0;
//     vx = 0;
//     vy = 0;
//   }
  
//   controladorTrajetoriaReal();  
  
// }


// /**As coordenadas x e y do robo estao em relacao ao mapa do mundo, nao em relacao aos eixos do robo*/
// /**Funcao que calcula a cinematica do robo de referencia*/
// void cinematicaRoboReferencia(const ros::TimerEvent&){

//   static float vx = 0, vy = 0, vTheta = 0;

//   static ros::Time tempo = ros::Time::now();  
//   float tempo_aux = ros::Time::now().toSec() - tempo.toSec();
//   float erro_x = 0, erro_y = 0, erro_theta = 0;

//   tempo = ros::Time::now();

//   //Atualizando a posicao do robo de referencia
//   roboReferencia.x = roboReferencia.x + (cos(roboReferencia.theta)*velocidadeLinear)*tempo_aux;
//   roboReferencia.y = roboReferencia.y + (sin(roboReferencia.theta)*velocidadeLinear)*tempo_aux;
//   roboReferencia.theta = roboReferencia.theta + (2*PI*velocidadeAngular*tempo_aux);

//   // Angulo do robo fica entre -PI e PI
//   while (abs(roboReferencia.theta) > PI){
//     if ((roboReferencia.theta > PI) && (roboReferencia.theta > 0)) {
//       roboReferencia.theta -= PI;
//     }
//     if ((roboReferencia.theta < -PI) && (roboReferencia.theta < 0)) {
//       roboReferencia.theta += PI;
//     }
//   }

//   //velocidade em x e y do robo de referencia em relacao ao mundo
//   if (!parar) {
//     erro_x = (roboDestino.x - roboReferencia.x);
//     erro_y = (roboDestino.y - roboReferencia.y);
//     erro_theta = (roboDestino.theta - roboReferencia.theta);

//     vx = erro_x/TEMPO_AMOSTRAGEM; 
//     vy = erro_y/TEMPO_AMOSTRAGEM;
//     vTheta = erro_theta/2*PI/TEMPO_AMOSTRAGEM;

//   }
  
//   /*velocidades lineares e angulares a serem aplicadas no robo de referencia*/
//   velocidadeLinear = cos(roboReferencia.theta)*vx + sin(roboReferencia.theta)*vy;
//   velocidadeAngular = vTheta;

//   if (velocidadeLinear > VELOCIDADE_MAXIMA){
//     velocidadeLinear = VELOCIDADE_MAXIMA;
//   }
//   else if (velocidadeLinear < -VELOCIDADE_MAXIMA){
//     velocidadeLinear = -VELOCIDADE_MAXIMA;
//   }
//   if (velocidadeAngular > VELOCIDADE_MAXIMA){
//     velocidadeAngular = VELOCIDADE_MAXIMA;
//   }
//   else if (velocidadeAngular < -VELOCIDADE_MAXIMA){
//     velocidadeAngular = -VELOCIDADE_MAXIMA;
//   }

//   /*if ((!pose.empty()) && abs(velocidadeAngular) < 0.2){

//     if ((velocidadeLinear < VELOCIDADE_MINIMA) && (velocidadeLinear> 0)){
//       velocidadeLinear = VELOCIDADE_MINIMA;
//     }
//     else if ((velocidadeLinear > (-VELOCIDADE_MINIMA)) && (velocidadeLinear < 0)){
//       velocidadeLinear = -VELOCIDADE_MINIMA;
//     }
  
//   }*/

//   if (parar) {
//     velocidadeLinear = 0;
//     velocidadeAngular = 0;
//     vx = 0;
//     vy = 0;
//   }
  
//   controladorTrajetoriaReal();  
  
// }