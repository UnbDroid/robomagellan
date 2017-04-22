#include "actions/actions.h"
#include "ros/ros.h"
#include "fsm.h"

void requisitar_uma_paradinha(Fsm *fsm, std::vector<std::string> args){
	std_msgs::Bool msg;
	trim(args[0]);
	if(args[0] == "true"){
		msg.data = true;
	}else{
		msg.data = false;
	}
	fsm->info->pubParadinha->publish(msg);
	#ifdef PRINT_ENABLED
		ROS_INFO("Requesting paradinha");
	#endif					

}
