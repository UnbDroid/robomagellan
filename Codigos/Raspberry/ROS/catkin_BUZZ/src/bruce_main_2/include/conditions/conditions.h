#pragma once
#include <string>
#include <vector>
#include <actions/actions.h>

struct Condition{
	std::string name;
	bool (*function)(Fsm* ,std::vector<std::string>);
	Condition * next;
	std::vector<std::string> condition_param;
	std::vector<Action*> actions;
}; 

struct ConditionParser{
	std::string name;
	std::string func_name;
	bool (*function)(Fsm* ,std::vector<std::string>);
	std::vector<std::string> condition_param_names;	
};


void startConditionsParser(std::vector<ConditionParser> & conditions);

bool getConditionByFunctionName(ConditionParser & condition, std::string funcName, std::vector<ConditionParser> & conditions);

Condition * createCondition(std::string & name, std::string & args , std::vector<ConditionParser> & conditions);

bool is_bigger(Fsm *obj, std::vector<std::string>);

bool odom_ok(Fsm *obj, std::vector<std::string>);

bool route_calculated(Fsm *obj, std::vector<std::string>);

bool distant_from_route(Fsm *obj, std::vector<std::string>);

bool distant_from_route(Fsm *obj, std::vector<std::string>);

bool cone_found(Fsm *obj, std::vector<std::string>);

bool us_reading_smaller(Fsm *obj, std::vector<std::string>);

bool check_timer(Fsm *obj, std::vector<std::string>);

bool check_touch_sensor(Fsm *obj, std::vector<std::string>);

bool check_counter_bigger(Fsm *obj, std::vector<std::string>);

bool check_counter_smaller(Fsm *obj, std::vector<std::string>);

bool check_green_button(Fsm *obj, std::vector<std::string>);

bool check_black_button(Fsm *obj, std::vector<std::string>);

bool check_origin_received(Fsm *obj, std::vector<std::string>);
