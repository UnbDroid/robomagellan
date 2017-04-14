#include "conditions/conditions.h"
#include "ros/ros.h"
#include "fsm.h"
#include <cstdlib>

bool cone_found(Fsm *fsm, std::vector<std::string>args){
	if(fsm->info->cone_encontrado){
		fsm->info->cone_encontrado = false;
		return true;
	}else{
		return false;
	}
}
