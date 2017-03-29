#include "ros/ros.h"
#include "std_msgs/String.h"
#include "robo_virtual/Posicao.h"
#include "geometry_msgs/Twist.h"
#include "nav_msgs/Odometry.h"
#include "nav_msgs/Path.h"
#include "geometry_msgs/Quaternion.h"
#include "tf/transform_datatypes.h"
#include "geometry_msgs/PoseStamped.h"

#include <math.h>

#define PI 3.14159265


//Variaveis ----------------------------------------------------------------------------------------------------------

//valores Robo virtual
struct RoboVirtual{
  float x,y,theta;
  float velocidade;
};

std::vector<geometry_msgs::PoseStamped> pose;
geometry_msgs::PoseStamped auxPose;
geometry_msgs::Twist msg;

RoboVirtual roboAtual, roboDestino, roboReferencia;

int trajetoriaAtual = 0;

bool parar = true;

float velocidadeLinear = 0, velocidadeAngular = 0;

//Funcoes ---------------------------------------------------------------------------------------------------------------

void trajetoCallback(const nav_msgs::Path::ConstPtr& msg)
{
  
  static int flag = 0;
  
  if(flag == 0){
    pose = msg->poses;
    flag++;
  }

}

//Posicao atual lida do gazebo
void posicaoAtualCallback(const nav_msgs::Odometry::ConstPtr& msg)
{
  geometry_msgs::Quaternion orientacao;
  double roll, pitch, yaw;
  tf::Quaternion quat;

  orientacao = msg->pose.pose.orientation;  
  tf::quaternionMsgToTF(orientacao, quat);
  tf::Matrix3x3(quat).getRPY(roll, pitch, yaw);

  //ROS_INFO("Posicao atual lida: x:%f y:%f theta: %f, vel: %f", msg->x, msg->y, msg->theta, msg->velocidade);
  roboAtual.x = msg->pose.pose.position.x;
  roboAtual.y = msg->pose.pose.position.y;
  roboAtual.theta = yaw;
  //ROS_INFO("Posicao atual lida: x:%f y:%f theta: %f", roboAtual.x, roboAtual.y, roboAtual.theta);
}

/**as coordenadas x e y do robo estao em relacao ao mapa do mundo, nao em relacao aos eixos do robo*/
void cinematicaRoboReferencia(const ros::TimerEvent&){

  static float vx = 0, vy = 0;
  static float x_aux = 0, y_aux = 0, vx_aux = 0, vy_aux = 0;

  ROS_INFO("robo destino: x: %f y: %f ", roboDestino.x, roboDestino.y);
  ROS_INFO("robo referencia: x: %f y: %f theta: %f", roboReferencia.x, roboReferencia.y, roboReferencia.theta);
  ROS_INFO("robo simulado: x: %f y: %f theta: %f", roboAtual.x, roboAtual.y, roboAtual.theta);

  /*velocidade em x e y em relacao ao mundo*/
  vx = (roboDestino.x - roboReferencia.x)/0.1;
  vy = (roboDestino.y - roboReferencia.y)/0.1;
  
  /*velocidades lineares e angulares a serem aplicadas no robo de referencia*/
  velocidadeLinear = cos(roboReferencia.theta)*vx + sin(roboReferencia.theta)*vy;
  velocidadeAngular = -sin(roboReferencia.theta)*vx+ cos(roboReferencia.theta)*vy;

  if (velocidadeLinear > 0.8){
    velocidadeLinear = 0.8;
  }
  else if (velocidadeLinear < -0.8){
    velocidadeLinear = -0.8;
  }
  if (velocidadeAngular > 0.8){
    velocidadeAngular = 0.8;
  }
  else if (velocidadeAngular < -0.8){
    velocidadeAngular = -0.8;
  }

  if (pose.size() > 0){

    if ((velocidadeLinear < 0.3) && (velocidadeLinear>0)){
      velocidadeLinear = 0.3;
    }
    else if ((velocidadeLinear < (-0.3)) && (velocidadeLinear < 0)){
      velocidadeLinear = -0.3;
    }
  
  }
  ROS_INFO("vl: %f va: %f", velocidadeLinear, velocidadeAngular);
  
  roboReferencia.x = roboReferencia.x + (cos(roboReferencia.theta)*velocidadeLinear - sin(roboReferencia.theta)*velocidadeAngular)*0.1;
  roboReferencia.y = roboReferencia.y + (sin(roboReferencia.theta)*velocidadeLinear + cos(roboReferencia.theta)*velocidadeAngular)*0.1;
  roboReferencia.theta = roboReferencia.theta + (velocidadeAngular*0.1);

  if (abs(roboReferencia.theta) > PI){
    while (abs(roboReferencia.theta) > PI) {
      roboReferencia.theta -= PI;
    }

  }

}


/*void velocidadeRobo(const ros::TimerEvent&){

  static float x_aux = 0, y_aux = 0;

  ROS_INFO("Mandando velocidades");
  ROS_INFO("X atual: %f destino: %f", roboAtual.x,roboDestino.x);
  ROS_INFO("y atual: %f destino: %f", roboAtual.y,roboDestino.y);

  ROS_INFO("theta atual: %f ", roboAtual.theta);

  ROS_INFO("robo referencia: x: %f y: %f theta: %f", roboReferencia.x, roboReferencia.y, roboReferencia.theta);

  float vx = (roboDestino.x - roboAtual.x)/0.1;
  float vy = (roboDestino.y - roboAtual.y)/0.1;


  /*if (abs(roboDestino.x - roboAtual.x) < 0.001){
    vx = 0;  
  }
  if (abs(roboDestino.y - roboAtual.y) < 0.001){
    vy = 0;  
  }*/
  /*roboReferencia.x = roboReferencia.x + vx*0.1;
  roboReferencia.y = roboReferencia.y + vy*0.1;

  //float velocidadeLinear = cos(roboAtual.theta)*vx + sin(roboAtual.theta)*vy;
  //float velocidadeAngular = -sin(roboAtual.theta)*vx+ cos(roboAtual.theta)*vy;

  roboReferencia.theta = roboReferencia.theta + velocidadeAngular*0.1;

  if (velocidadeLinear > 0.8){
    velocidadeLinear = 0.8;
  }
  else if (velocidadeLinear < -0.8){
    velocidadeLinear = -0.8;
  }
  if (velocidadeAngular > 0.8){
    velocidadeAngular = 0.8;
  }
  else if (velocidadeAngular < -0.8){
    velocidadeAngular = -0.8;
  }

  if (pose.size() > 0){

    if ((velocidadeLinear < 0.3) && (velocidadeLinear>0)){
      velocidadeLinear = 0.3;
    }
    else if ((velocidadeLinear < (-0.3)) && (velocidadeLinear < 0)){
      velocidadeLinear = -0.3;
    }
  
  }
  ROS_INFO("vl: %f va: %f", velocidadeLinear, velocidadeAngular);
  
  if (!parar) {
    msg.linear.x = velocidadeLinear;
    msg.angular.z = velocidadeAngular;
  }
  else {
    msg.linear.x = 0;
    msg.angular.z = 0;
  }
  
}*/

void calculaSegmento (void) {

  static float gama = 0; /*angulo de inclinacao da reta de segmento de trajetoria*/

  //Indica que ele passou da regiao do seguimeto atual e ira prossegir para o proximo segmento ou que irá comecar o primeiro segmento  
  if (((cos(gama)*(roboAtual.x - roboDestino.x))+(sin(gama)*(roboAtual.y - roboDestino.y)) > 0) || (trajetoriaAtual == 0)){
    if (!pose.empty()){
      parar = false,
      auxPose = pose.front();
      pose.erase(pose.begin());

      roboDestino.x = auxPose.pose.position.x;
      roboDestino.y = auxPose.pose.position.y;
      
      gama = atan2((roboDestino.y - roboAtual.y),(roboDestino.x - roboAtual.x));
      trajetoriaAtual++;

      roboReferencia = roboAtual;

      ROS_INFO("Segmento atual %d:  x:%f y:%f",trajetoriaAtual, auxPose.pose.position.x,auxPose.pose.position.y);  
    }
    else{
      parar = true;
    }
  }

}

void controladorTrajetoriaSimulador(const ros::TimerEvent&) {
  
  static float a1 =0, a2 = 0;
  //const float gama1 = ?;
  //const float gammaK2 = ?;
  const int k1=1.2, k2=1.2,k3=1.2;
  static float erro1 = 0, erro2 = 0, erro3=0;
  static float vf=0, wf=0;

  erro1 = cos(roboAtual.theta)*(roboReferencia.x - roboAtual.x) + sin(roboAtual.theta)*(roboReferencia.y - roboAtual.y);
  erro2 = -sin(roboAtual.theta)*(roboReferencia.x - roboAtual.x) + cos(roboAtual.theta)*(roboReferencia.y - roboAtual.y);
  erro3 = roboReferencia.theta - roboAtual.theta;

  vf = (velocidadeLinear * cos(erro3)) + (k1 *erro1);
  wf = velocidadeAngular + (velocidadeLinear * k2 * erro2)  + (k3 * sin(erro3));

  if (!parar) {
    msg.linear.x = vf;
    msg.angular.z = wf;
  }
  else {
    msg.linear.x = 0;
    msg.angular.z = 0;
    velocidadeLinear = 0;
    velocidadeAngular = 0;
  }

}

void controladorTrajetoriaReal(const ros::TimerEvent&) {
  
  static float lambda = 1.47;
  static float a1 =0, a2 = 0; /*Parametros de adaptacao do controlador*/
  const float gama1 = 1.2;
  const float gama2 = 1.2;
  const int k1=1.2, k2=1.2,k3=1.2;
  static float erro1 = 0, erro2 = 0, erro3=0;
  static float vf=0, wf=0; /*velocidades dadas para o robo virtual*/
  static float velocidadeEsquerda = 0, velocidadeDireita = 0; /*velocidades dadas às rodas do robo real*/
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

  if (!parar) {
    msg.linear.x = vf;
    msg.angular.z = wf;
  }
  else {
    msg.linear.x = 0;
    msg.angular.z = 0;
    velocidadeLinear = 0;
    velocidadeAngular = 0;
  }

}

int main(int argc, char **argv)
{

  ros::init(argc, argv, "robo_virtual");

  ros::NodeHandle n;
 
  ros::Subscriber subTrajeto = n.subscribe("trajeto", 1000, trajetoCallback);
  ros::Subscriber subAtual = n.subscribe("odom", 1000, posicaoAtualCallback);
  ros::Publisher pubVelocidade = n.advertise<geometry_msgs::Twist>("cmd_vel", 1000);
  //ros::Timer temporizador = n.createTimer(ros::Duration(0.1),velocidadeRobo, false);
  ros::Timer temporizador = n.createTimer(ros::Duration(0.1),cinematicaRoboReferencia, false);
  ros::Timer controlador = n.createTimer(ros::Duration(0.1),controladorTrajetoriaSimulador, false);

  ros::Rate loop_rate(10);
  
  int segmentoTrajetoria = 0;

  while (ros::ok()){

    calculaSegmento();
    pubVelocidade.publish(msg);
    loop_rate.sleep();
    ros::spinOnce();
  
  }

  return 0;
}
