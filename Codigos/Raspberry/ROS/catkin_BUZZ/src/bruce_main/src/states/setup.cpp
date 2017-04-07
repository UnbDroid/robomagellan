#include "fsm.h"
#include "states.h"
#include "ros/ros.h"

void setup(struct fsm_object *obj, int val,void **arg){
	static std::vector<arg_type> args;
	static bool first_time =true;
	static bool new_iteration = true;
	if(first_time){
		processArgs(args,val,arg);
		if(args[0].type != SINGLE || args[1].type != SINGLE || args[2].type != SINGLE)
			throw("Setup next_state must be a single argument!");
		first_time = false;
	}
	if(new_iteration){
		new_iteration = false;
	}
	geometry_msgs::Point32 msg;
	msg.x = std::atof(args[0].single.c_str());
	msg.y = std::atof(args[1].single.c_str());
	obj->info->bottomLeft.lat = msg.x;
	obj->info->bottomLeft.lng = msg.y;
	obj->info->pubMapBLCoordinate->publish(msg);	
	ROS_INFO("(%f, %f)\n",obj->info->pose.position.x,obj->info->pose.position.y);

	if(obj->info->position_is_valid){
		fsm_to_state(obj,args[2].single);
		new_iteration = true;
	}
}
