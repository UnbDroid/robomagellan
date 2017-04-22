#pragma once
#include <string>
#include <vector>

struct Action{
	std::string name;
	void (*function)(struct Fsm* ,std::vector<std::string>);
	std::vector<std::string> action_param;
}; 

struct ActionParser{
	std::string name;
	std::string func_name;
	void (*function)(struct Fsm* ,std::vector<std::string>);
	std::vector<std::string> action_param_names;	
};


void startActionsParser(std::vector<ActionParser> & actions);

bool getActionByFunctionName(ActionParser & action, std::string funcName, std::vector<ActionParser> & actions);

Action * createAction(std::string & name, std::string & args , std::vector<ActionParser> & actions);

void change_state(struct Fsm *obj, std::vector<std::string>);
void print(struct Fsm *obj, std::vector<std::string>);
void print_bool(struct Fsm *obj, std::vector<std::string>);
void print_int(struct Fsm *obj, std::vector<std::string>);
void print_float(struct Fsm *obj, std::vector<std::string>);
void publish_map_bottom_left_corner(struct Fsm *obj, std::vector<std::string>);
void request_route_calculation(struct Fsm *obj, std::vector<std::string>);
void send_enable_path_follow(struct Fsm *obj, std::vector<std::string>);
void send_enable_follow_camera(struct Fsm *obj, std::vector<std::string>);
void set_calculating_route(struct Fsm *obj, std::vector<std::string>);
void set_map_path_goal_gps(struct Fsm *obj, std::vector<std::string>);
void insert_us_obstacles_in_map(struct Fsm *obj, std::vector<std::string>);
void add_timer(struct Fsm *obj, std::vector<std::string>);
void reset_timer(struct Fsm *obj, std::vector<std::string>);
void insert_camera_readings_in_map(struct Fsm *obj, std::vector<std::string>);
void add_counter(struct Fsm *obj, std::vector<std::string>);
void increment_counter(struct Fsm *obj, std::vector<std::string>);
void reset_counter(struct Fsm *obj, std::vector<std::string>);
void request_set_origin(struct Fsm *obj, std::vector<std::string>);
void set_velocity(struct Fsm *obj, std::vector<std::string>);
void requisitar_uma_paradinha(struct Fsm *obj, std::vector<std::string>);
