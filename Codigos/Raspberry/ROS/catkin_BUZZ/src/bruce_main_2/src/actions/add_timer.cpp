#include "actions/actions.h"
#include "ros/ros.h"
#include "fsm.h"
#include "parser/base_functions.h"

void add_timer(Fsm *fsm, std::vector<std::string> args){
	trim(args[0]);
	for (int i = 0; i < fsm->info->timers.size(); ++i){
		if(fsm->info->timers[i].name == args[0]){
			return;
		}
	}
	BasicTimer timer = {args[0],std::chrono::high_resolution_clock::now()};
	fsm->info->timers.push_back(timer);
}
