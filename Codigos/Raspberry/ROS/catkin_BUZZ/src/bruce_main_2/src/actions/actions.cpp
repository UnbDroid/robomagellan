#include "actions/actions.h"
#include "parser/base_functions.h"

void startActionsParser(std::vector<ActionParser> & actions){
	/* Change state action */
	ActionParser change_state_action = {"","change_state",change_state};
	change_state_action.action_param_names.push_back("next_state");
	actions.push_back(change_state_action);
	/* Print action */
	ActionParser print_action = {"","print",print};
	print_action.action_param_names.push_back("message");
	actions.push_back(print_action);
	/* Publish Map Bottom Left Corner action */
	ActionParser publish_map_bottom_left_corner_action = {"","publish_map_bottom_left_corner",publish_map_bottom_left_corner};
	publish_map_bottom_left_corner_action.action_param_names.push_back("latitude");
	publish_map_bottom_left_corner_action.action_param_names.push_back("longitude");
	actions.push_back(publish_map_bottom_left_corner_action);
	/* Calculate route gps action */
	ActionParser request_route_calculation_action = {"","request_route_calculation",request_route_calculation};	
	actions.push_back(request_route_calculation_action);
	/* Send Enable Path Follow action */
	ActionParser send_enable_path_follow_action = {"","send_enable_path_follow",send_enable_path_follow};
	send_enable_path_follow_action.action_param_names.push_back("value");
	actions.push_back(send_enable_path_follow_action);
	/* Set Calculating Route action */
	ActionParser set_calculating_route_action = {"","set_calculating_route",set_calculating_route};
	set_calculating_route_action.action_param_names.push_back("value");
	actions.push_back(set_calculating_route_action);
	/* set_map_path_goal_pgs action */
	ActionParser set_map_path_goal_gps_action = {"","set_map_path_goal_gps",set_map_path_goal_gps};
	set_map_path_goal_gps_action.action_param_names.push_back("latitude");
	set_map_path_goal_gps_action.action_param_names.push_back("longitude");
	actions.push_back(set_map_path_goal_gps_action);
	/* add_timer action */
	ActionParser add_timer_action = {"","add_timer",add_timer};
	add_timer_action.action_param_names.push_back("name");
	actions.push_back(add_timer_action);
	/* reset_timer action */
	ActionParser reset_timer_action = {"","reset_timer",reset_timer};
	reset_timer_action.action_param_names.push_back("name");
	actions.push_back(reset_timer_action);
	/* insert_us_obstacles_in_map action */
	ActionParser insert_us_obstacles_in_map_action = {"","insert_us_obstacles_in_map",insert_us_obstacles_in_map};
	insert_us_obstacles_in_map_action.action_param_names.push_back("obstacle_inflation");
	actions.push_back(insert_us_obstacles_in_map_action);
	/* insert_us_obstacles_in_map action */
	ActionParser insert_camera_readings_in_map_action = {"","insert_camera_readings_in_map",insert_camera_readings_in_map};
	actions.push_back(insert_camera_readings_in_map_action);
	/* add_counter action */
	ActionParser add_counter_action = {"","add_counter",add_counter};
	add_counter_action.action_param_names.push_back("name");
	actions.push_back(add_counter_action);
	/* increment_counter action */
	ActionParser increment_counter_action = {"","increment_counter",increment_counter};
	increment_counter_action.action_param_names.push_back("name");
	actions.push_back(increment_counter_action);
	/* reset_counter action */
	ActionParser reset_counter_action = {"","reset_counter",reset_counter};
	reset_counter_action.action_param_names.push_back("name");
	actions.push_back(reset_counter_action);
	/* request_set_origin action */
	ActionParser request_set_origin_action = {"","request_set_origin",request_set_origin};
	actions.push_back(request_set_origin_action);
	/* set_velocity action */
	ActionParser set_velocity_action = {"","set_velocity",set_velocity};
	set_velocity_action.action_param_names.push_back("linear");
	set_velocity_action.action_param_names.push_back("angular");
	actions.push_back(set_velocity_action);
	/* send_enable_follow_camera action */
	ActionParser send_enable_follow_camera_action = {"","send_enable_follow_camera",send_enable_follow_camera};
	send_enable_follow_camera_action.action_param_names.push_back("value");
	actions.push_back(send_enable_follow_camera_action);
}

bool getActionByFunctionName(ActionParser & action, std::string funcName, std::vector<ActionParser> & actions){
	for(unsigned i = 0; i < actions.size(); ++i) {
		if(actions[i].func_name == funcName){
			action = actions[i];
			return true;
		}
	}
	return false;
}

Action * createAction(std::string & name, std::string & args , std::vector<ActionParser> & actions){
	for(unsigned i = 0; i < actions.size(); ++i) {
		if(actions[i].name == name){
			Action * action= new Action;
			action->name = name;
			action->function = actions[i].function;
			std::vector<std::string> arguments = split(args,",",true);
			if(arguments.size() != actions[i].action_param_names.size()){
				throw("Action with incorrect number of arguments");
			}
			std::string * auxArgs = new std::string[arguments.size()];
			for(unsigned k = 0; k < arguments.size(); ++k) {
				std::vector<std::string> arg_parts = split(arguments[k],":",true);
				if(arg_parts.size()!=2){
					std::string aux = name + std::string(" action missing or with too many :");
					throw(aux.c_str());				
				}
				trim(arg_parts[0]);
				trim(arg_parts[1]);
				bool found = false;
				for(unsigned j=0; j < arguments.size(); ++j){
					if(arg_parts[0] == actions[i].action_param_names[j]){
						found = true;
						auxArgs[j] = arg_parts[1];
						break;
					}
				}				
				if(!found){
					std::string aux = name + std::string(" action doesn't have ") + arg_parts[0] +std::string(" argument");
					throw(aux.c_str());				
				}
			}
			for(unsigned j=0; j < arguments.size(); ++j){
				action->action_param.push_back(auxArgs[j]);
			}			
			if(action->action_param.size()!=arguments.size()){
				std::string aux = name + std::string(" action missing arguments");
				throw(aux.c_str());	
			}
			return action;
		}
	}
	return NULL;
}
