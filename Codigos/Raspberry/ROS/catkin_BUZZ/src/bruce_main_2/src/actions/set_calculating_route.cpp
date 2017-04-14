#include "actions/actions.h"
#include "ros/ros.h"
#include "fsm.h"
#include "parser/base_functions.h"

void set_calculating_route(Fsm *fsm, std::vector<std::string> args){
	trim(args[0]);
	if(args[0] == "true"){
		fsm->info->calculating_route = true;
	}else{
		fsm->info->calculating_route = false;
	}
}
