#include "actions/actions.h"
#include "ros/ros.h"
#include "fsm.h"

void print(Fsm *fsm, std::vector<std::string> args){
	ROS_INFO("%s",args[0].c_str());
}
