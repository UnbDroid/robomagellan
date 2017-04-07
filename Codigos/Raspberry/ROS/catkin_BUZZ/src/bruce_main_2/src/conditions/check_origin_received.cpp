#include "conditions/conditions.h"
#include "ros/ros.h"
#include "fsm.h"
#include <cstdlib>

bool check_origin_received(Fsm *fsm, std::vector<std::string>args){
	if(fsm->info->origin_received){
		fsm->info->origin_received = false;
		return true;
	}else{
		return false;
	}
}
