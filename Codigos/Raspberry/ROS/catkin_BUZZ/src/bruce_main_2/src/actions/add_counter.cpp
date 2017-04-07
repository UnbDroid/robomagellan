#include "actions/actions.h"
#include "ros/ros.h"
#include "fsm.h"
#include "parser/base_functions.h"

void add_counter(Fsm *fsm, std::vector<std::string> args){
	trim(args[0]);
	for (int i = 0; i < fsm->info->counters.size(); ++i){
		if(fsm->info->counters[i].name == args[0]){
			return;
		}
	}	
	BasicCounter counter = {args[0],0};
	fsm->info->counters.push_back(counter);
}
