#include "actions/actions.h"
#include "ros/ros.h"
#include "fsm.h"

void request_set_origin(Fsm *fsm, std::vector<std::string> args){
	std_msgs::Bool msg;
	msg.data = true;
	fsm->info->pubOriginRequest->publish(msg);
	#ifdef PRINT_ENABLED
		ROS_INFO("Requesting origin");
	#endif					

}
