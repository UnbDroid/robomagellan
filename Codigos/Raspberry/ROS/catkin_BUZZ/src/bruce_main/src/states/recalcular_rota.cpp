#include "fsm.h"
#include "states.h"
#include "ros/ros.h"

void recalcular_rota(struct fsm_object *obj, int val,void **arg){
	static bool new_iteration = true;
	
	if(new_iteration){
		new_iteration = false;
		geometry_msgs::Point32 msg;

		msg.x = obj->info->currentMapGoal.x;
		msg.y = obj->info->currentMapGoal.y;		
		obj->info->pubRequestPath->publish(msg);
		ROS_INFO("Requesting (%f,%f) ",obj->info->currentMapGoal.x,obj->info->currentMapGoal.y);
		ROS_INFO("Origin in map (%f,%f)",obj->info->originInMap.x,obj->info->originInMap.y);
	}
	//ROS_INFO("(%f, %f), %s\n",x_coordinates[run_iterator],y_coordinates[run_iterator],next_states[run_iterator].c_str());
	if(obj->info->route_calculated){
		fsm_return_last_state(obj);
		obj->info->route_calculated = false;
		new_iteration = true;
	}
}
