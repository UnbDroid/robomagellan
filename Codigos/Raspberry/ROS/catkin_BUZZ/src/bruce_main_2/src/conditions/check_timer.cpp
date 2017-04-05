#include "conditions/conditions.h"
#include "ros/ros.h"
#include "fsm.h"
#include "parser/base_functions.h"
#include <cstdlib>

bool check_timer(Fsm *fsm, std::vector<std::string>args){
	trim(args[0]);
	double time = std::atof(args[1].c_str());
	bool found = false;
	std::chrono::high_resolution_clock::time_point t1;
	for (int i = 0; i < fsm->info->timers.size(); ++i){
		if(fsm->info->timers[i].name == args[0]){
			found = true;
			t1 = fsm->info->timers[i].t;
		}
	}
	if(!found){
		return false;
	}

	std::chrono::high_resolution_clock::time_point t2 = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double> time_span = std::chrono::duration_cast<std::chrono::duration<double>>(t2 - t1);
	//ROS_INFO("%f",time_span.count());
	return time_span.count() > time;
}
