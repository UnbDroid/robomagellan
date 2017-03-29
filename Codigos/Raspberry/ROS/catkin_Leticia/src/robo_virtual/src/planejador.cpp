#include "ros/ros.h"
#include "nav_msgs/Path.h"
#include "geometry_msgs/PoseStamped.h"
#include "geometry_msgs/Pose.h"
#include "geometry_msgs/Vector3.h"
#include "geometry_msgs/Quaternion.h"

#include <sstream>
#include <vector>


int main(int argc, char **argv)
{

  ros::init(argc, argv, "planejador");

  ros::NodeHandle n;

  ros::Publisher trajetoriaPub = n.advertise<nav_msgs::Path>("trajeto", 1000);

  nav_msgs::Path trajeto;
  std::vector<geometry_msgs::PoseStamped> pose;
  geometry_msgs::PoseStamped auxPosition;

  float contador = 0.5;
  float aux_x = 0.1, aux_y = 0.1, aux_theta = 0.1, aux_velocidade = 2.5;

  ros::Rate loop_rate(1);

  /*auxPosition.header.seq = (int)contador;
  auxPosition.pose.position.x = 0;
  auxPosition.pose.position.y = 0;
  auxPosition.pose.position.z = 0;
  trajeto.poses.push_back(auxPosition);
  contador += 0.5;*/


  auxPosition.header.seq = (int)contador;
  auxPosition.pose.position.x = 5;
  auxPosition.pose.position.y = 4;
  auxPosition.pose.position.z = 0;
  trajeto.poses.push_back(auxPosition);


  auxPosition.header.seq = (int)contador;
  auxPosition.pose.position.x = -5;
  auxPosition.pose.position.y = 6;
  auxPosition.pose.position.z = 0;
  trajeto.poses.push_back(auxPosition);
  

  /*auxPosition.header.seq = (int)contador;
  auxPosition.pose.position.x = 6;
  auxPosition.pose.position.y = -5;
  auxPosition.pose.position.z = 0;
  trajeto.poses.push_back(auxPosition);*/

  /*auxPosition.header.seq = (int)contador;
  auxPosition.pose.position.x = -4;
  auxPosition.pose.position.y = 3;
  auxPosition.pose.position.z = 0;
  trajeto.poses.push_back(auxPosition);

  auxPosition.header.seq = (int)contador;
  auxPosition.pose.position.x = -1;
  auxPosition.pose.position.y = -3;
  auxPosition.pose.position.z = 0;
  trajeto.poses.push_back(auxPosition);

  auxPosition.header.seq = (int)contador;
  auxPosition.pose.position.x = -6;
  auxPosition.pose.position.y = -3;
  auxPosition.pose.position.z = 0;
  trajeto.poses.push_back(auxPosition);*/

  auxPosition.header.seq = (int)contador;
  auxPosition.pose.position.x = 0;
  auxPosition.pose.position.y = 0;
  auxPosition.pose.position.z = 0;
  trajeto.poses.push_back(auxPosition);
  
  while (ros::ok())
  {
    trajetoriaPub.publish(trajeto);

    ROS_INFO("Enviando trajeto ");
    
    ros::spinOnce();

    loop_rate.sleep();

  }


  return 0;
}
