#include <unistd.h>
#include <sstream>
#include "ros/ros.h"
#include "std_msgs/String.h"
#include <rosbag/bag.h>
#include <rosbag/view.h>
#include <geometry_msgs/Point32.h>
#include "geometry_msgs/PoseStamped.h"
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <sys/time.h>
#include <boost/foreach.hpp>



using namespace std;


int main(int argc, char **argv)
{

	ros::init(argc, argv, "vision");
	ros::NodeHandle n;
	ros::Publisher chatter_pub = n.advertise<geometry_msgs::Point32>("cone_position", 1000);
	ros::Rate loop_rate(10);
	geometry_msgs::Point32 msg;


	
	rosbag::Bag bag;
    bag.open("cam.bag", rosbag::bagmode::Read);
    

    std::vector<std::string> topics;
    topics.push_back(std::string("Camera"));

    rosbag::View view(bag, rosbag::TopicQuery(topics));

	BOOST_FOREACH(rosbag::MessageInstance const m, view)
	{
	   	if (m.getTopic() == "Camera") 
		{
		    geometry_msgs::Point32::ConstPtr cam_pos = m.instantiate<geometry_msgs::Point32>();
		    if (cam_pos != NULL)
		        chatter_pub.publish(*cam_pos);
		}
		if(!ros::ok())
			break;
		loop_rate.sleep();
	}
	
	bag.close();
	


}