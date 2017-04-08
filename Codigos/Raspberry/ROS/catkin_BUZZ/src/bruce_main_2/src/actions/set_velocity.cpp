
#include "actions/actions.h"
#include "ros/ros.h"
#include "fsm.h"

void set_velocity(Fsm *fsm, std::vector<std::string> args){
	geometry_msgs::Point32 msg;
	msg.x = std::atof(args[0].c_str());
	msg.z = std::atof(args[1].c_str());
	fsm->info->pubVelocity->publish(msg);
}
