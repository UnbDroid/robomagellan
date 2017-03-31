#include "fsm.h"
#include "states.h"
#include "ros/ros.h"

void calcular_rota(struct fsm_object *obj, int val,void **arg){
	static std::vector<arg_type> args;
	static std::vector<float> x_coordinates;
	static std::vector<float> y_coordinates;
	static std::vector<std::string> next_states;
	static int run_iterator = 0;
	static bool first_time =true;
	static bool new_iteration = true;
	if(first_time){
		processArgs(args,val,arg);
		first_time = false;
		if(args[0].type != args[1].type ||  args[1].type != args[2].type){
			throw("Calcular rotas arguments incompatible");
		}
		if(args[0].type == SINGLE){
			x_coordinates.push_back(std::atof(args[0].single.c_str()));
			y_coordinates.push_back(std::atof(args[1].single.c_str()));
			next_states.push_back(args[2].single);
		}else{
			if(args[0].multiple.size() != args[1].multiple.size() ||args[1].multiple.size() != args[2].multiple.size())
				throw("Calcular rotas arguments incompatible");
			for (int i = 0; i < args[0].multiple.size(); ++i){
				x_coordinates.push_back(std::atof(args[0].multiple[i].c_str()));
				y_coordinates.push_back(std::atof(args[1].multiple[i].c_str()));
				next_states.push_back(args[2].multiple[i]);
			}
		}
	}

	if(new_iteration){
		new_iteration = false;
		geometry_msgs::Point32 msg;

		GPSCoord gpsGoal ={x_coordinates[run_iterator], y_coordinates[run_iterator]};
		NEDCoord nedGoal = GPS2NED(gpsGoal,obj->info->bottomLeft);
		NEDCoord originInMap = GPS2NED(obj->info->origin,obj->info->bottomLeft);
		obj->info->originInMap.x = originInMap.y;
		obj->info->originInMap.y = originInMap.x;
		float map_x = nedGoal.y;
		float map_y = nedGoal.x;
		msg.x = map_x;
		msg.y = map_y;		
		obj->info->pubRequestPath->publish(msg);
		obj->info->currentMapGoal.x = map_x;
		obj->info->currentMapGoal.y = map_y;
		ROS_INFO("Requesting (%f,%f) ",map_x,map_y);	
	}
	//ROS_INFO("(%f, %f), %s\n",x_coordinates[run_iterator],y_coordinates[run_iterator],next_states[run_iterator].c_str());
	if(obj->info->route_calculated){
		fsm_to_state(obj,next_states[run_iterator]);
		obj->info->route_calculated = false;
		new_iteration = true;
		run_iterator++;
	}
}
