#include "actions/actions.h"
#include "ros/ros.h"
#include "fsm.h"
#include "parser/base_functions.h"

void reset_counter(Fsm *fsm, std::vector<std::string> args){
	trim(args[0]);
	for (int i = 0; i < fsm->info->counters.size(); ++i){
		if(fsm->info->counters[i].name == args[0]){
			fsm->info->counters[i].counter = 0;
		}
	}
}
