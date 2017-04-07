#include "conditions/conditions.h"
#include "ros/ros.h"
#include "fsm.h"
#include <cstdlib>

bool odom_ok(Fsm *fsm, std::vector<std::string>args){
	return fsm->info->position_is_valid;
}
