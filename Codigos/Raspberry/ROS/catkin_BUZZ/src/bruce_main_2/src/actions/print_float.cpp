#include "actions/actions.h"
#include "ros/ros.h"
#include "fsm.h"
#include "parser/base_functions.h"

void print_float(Fsm *fsm, std::vector<std::string> args){
	float * value = (float *	)getMember(fsm->info,trim(args[0]));
	if(value){
		#ifdef PRINT_ENABLED
			ROS_INFO("%f",*value);
		#endif		
	}
}