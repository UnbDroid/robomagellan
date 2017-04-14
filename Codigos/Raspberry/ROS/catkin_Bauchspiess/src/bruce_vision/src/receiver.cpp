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


using namespace std;

/*
void chatterCallback(const std_msgs::String::ConstPtr& msg)
{
  //ROS_INFO("I heard: [%s]", msg->data.c_str());
  cout<<msg->data.c_str()<<endl;
}
*/

void cone_positionCallback(const geometry_msgs::Point32::ConstPtr& msg)
{
  //ROS_INFO("I heard: [%s]", msg->data.c_str());
  cout<<msg->x<<"m   "<<msg->y<<"graus"<<endl;
}

int main(int argc, char **argv)
{
  ros::init(argc, argv, "receiver");


  ros::NodeHandle n;

  ros::Subscriber sub = n.subscribe("cone_position", 1000, cone_positionCallback);

  ros::spin();

  return 0;
}