#include "ros/ros.h"
#include "std_msgs/String.h"
#include "robo_virtual/Posicao.h"

#include <sstream>


int main(int argc, char **argv)
{

  ros::init(argc, argv, "posicaoAtual");

  ros::NodeHandle n;

  ros::Publisher posicaoAtualPub = n.advertise<robo_virtual::Posicao>("posicaoAtual", 1000);

  ros::Rate loop_rate(0.9);

  float aux_x = 0, aux_y = 0, aux_theta = 20, aux_velocidade = 2.5;
  int count = 0;
  robo_virtual::Posicao msg;

  while (ros::ok())
  {  
    msg.x = aux_x;
    msg.y = aux_y;
    msg.theta = aux_theta;
    msg.velocidade = aux_velocidade;    
    
    /*aux_x ++;
    aux_y ++;
    aux_theta = 0;  
    */
    posicaoAtualPub.publish(msg);

    ROS_INFO("Enviando : x: %f y: %f theta: %f, vel: %f", msg.x, msg.y, msg.theta, msg.velocidade);
    ros::spinOnce();

    loop_rate.sleep();
    ++count;
  }


  return 0;
}
