#include "conditions/conditions.h"
#include "ros/ros.h"
#include "fsm.h"
#include <cstdlib>

bool us_reading_smaller(Fsm *fsm, std::vector<std::string>args){
	int i = std::atoi(args[0].c_str());
	float obstacle_range = std::atof(args[1].c_str());

	return fsm->info->US[i] > 0 && fsm->info->US[i] < obstacle_range;
}
