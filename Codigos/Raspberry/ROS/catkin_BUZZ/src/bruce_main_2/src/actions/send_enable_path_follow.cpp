#include "actions/actions.h"
#include "ros/ros.h"
#include "fsm.h"
#include "parser/base_functions.h"

void send_enable_path_follow(Fsm *fsm, std::vector<std::string> args){
	std_msgs::Int16 msg;
	trim(args[0]);
	msg.data = std::atof(args[0].c_str());
	fsm->info->pubEnableFollowPath->publish(msg);
}
