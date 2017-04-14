#include "conditions/conditions.h"
#include "ros/ros.h"
#include "fsm.h"
#include <cstdlib>

bool is_bigger(Fsm *fsm, std::vector<std::string>args){
	float first = std::atof(args[0].c_str());
	float second = std::atof(args[1].c_str());
	return first > second;
}
