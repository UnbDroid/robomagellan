#include "conditions/conditions.h"
#include "ros/ros.h"
#include "fsm.h"
#include <cstdlib>

bool route_calculated(Fsm *fsm, std::vector<std::string>args){
	if(fsm->info->route_calculated){
		fsm->info->route_calculated = false;
		return true;
	}else{
		return false;
	}
}
