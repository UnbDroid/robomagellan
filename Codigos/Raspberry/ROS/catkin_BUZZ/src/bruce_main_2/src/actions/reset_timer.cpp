#include "actions/actions.h"
#include "ros/ros.h"
#include "fsm.h"
#include "parser/base_functions.h"

void reset_timer(Fsm *fsm, std::vector<std::string> args){
	trim(args[0]);
	for (int i = 0; i < fsm->info->timers.size(); ++i){
		if(fsm->info->timers[i].name == args[0]){
			fsm->info->timers[i].t = std::chrono::high_resolution_clock::now();
		}
	}
}
