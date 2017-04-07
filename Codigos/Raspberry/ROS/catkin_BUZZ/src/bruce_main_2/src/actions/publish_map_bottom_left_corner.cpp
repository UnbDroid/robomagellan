#include "actions/actions.h"
#include "ros/ros.h"
#include "fsm.h"

void publish_map_bottom_left_corner(Fsm *fsm, std::vector<std::string> args){
	geometry_msgs::Point32 msg;
	msg.x = std::atof(args[0].c_str());
	msg.y = std::atof(args[1].c_str());
	fsm->info->bottomLeft.lat = msg.x;
	fsm->info->bottomLeft.lng = msg.y;
	fsm->info->pubMapBLCoordinate->publish(msg);
	#ifdef PRINT_ENABLED
		ROS_INFO("(%f, %f)\n",fsm->info->pose.position.x,fsm->info->pose.position.y);
	#endif				
}
