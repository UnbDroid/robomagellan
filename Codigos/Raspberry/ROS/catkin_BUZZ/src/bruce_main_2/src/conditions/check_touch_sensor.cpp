#include "conditions/conditions.h"
#include "ros/ros.h"
#include "fsm.h"
#include <cstdlib>

bool check_touch_sensor(Fsm *fsm, std::vector<std::string>args){
	int min_times = std::atof(args[0].c_str());
	static int times_pressed = 0;
	if(fsm->info->sensor_toque){
		times_pressed++;
		if(times_pressed >= min_times){
			return true;
		}
	}else{
		times_pressed = 0;
	}
}
