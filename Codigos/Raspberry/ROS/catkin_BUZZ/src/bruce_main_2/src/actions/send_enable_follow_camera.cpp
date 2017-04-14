#include "actions/actions.h"
#include "ros/ros.h"
#include "fsm.h"
#include "parser/base_functions.h"

void send_enable_follow_camera(Fsm *fsm, std::vector<std::string> args){
	std_msgs::Int16 msg;
	std_msgs::Bool boolMsg;
	trim(args[0]);
	if(args[0] == "true"){
		msg.data =3;
		boolMsg.data = true;
	}else{
		msg.data = 0;
		boolMsg.data = false;
	}
	fsm->info->pubEnableFollowPath->publish(msg);
	fsm->info->pubFollowCamera->publish(boolMsg);
}
