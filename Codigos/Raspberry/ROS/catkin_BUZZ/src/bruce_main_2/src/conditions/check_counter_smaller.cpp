#include "conditions/conditions.h"
#include "ros/ros.h"
#include "fsm.h"
#include "parser/base_functions.h"
#include <cstdlib>

bool check_counter_smaller(Fsm *fsm, std::vector<std::string>args){
	trim(args[0]);
	int value = std::atoi(args[1].c_str());
	bool found = false;
	int counter;
	for (int i = 0; i < fsm->info->counters.size(); ++i){
		if(fsm->info->counters[i].name == args[0]){
			found = true;
			counter = fsm->info->counters[i].counter;
		}
	}
	if(!found){
		return false;
	}	
	return counter < value;
}
