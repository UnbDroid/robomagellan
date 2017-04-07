#include "actions/actions.h"
#include "ros/ros.h"
#include "fsm.h"

void request_route_calculation(Fsm *fsm, std::vector<std::string> args){
	if(!fsm->info->calculating_route){
		geometry_msgs::Point32 msg;
		float map_x = fsm->info->currentMapGoal.x;
		float map_y = fsm->info->currentMapGoal.y;
		msg.x = map_x;
		msg.y = map_y;
		fsm->info->pubRequestPath->publish(msg);
		#ifdef PRINT_ENABLED
			ROS_INFO("Requesting (%f,%f) ",map_x,map_y);
		#endif					
	}
}
