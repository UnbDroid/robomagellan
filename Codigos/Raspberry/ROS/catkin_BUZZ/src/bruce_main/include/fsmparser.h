#pragma once 
#include "fsm.h"
#include <vector>

#define SINGLE 0
#define MULTIPLE 1

struct arg_type{
	std::string single;
	std::vector<std::string> multiple;
	int type;
};

struct fsm_parser_state{
	fsm_state state;
	std::string function_name;
	std::vector<std::string> function_param_names;
	std::vector<std::string> function_param;
};

void parseFile(std::string file,std::vector<fsm_parser_state>& fsm_states,fsm_object & fsm);
void processFileText(std::string text,std::vector<fsm_parser_state>& fsm_states, fsm_object & fsm);
void processDeclaration(std::vector<std::string> & elements, std::vector<fsm_parser_state>& fsm_states, std::vector<fsm_parser_state>& fsm_added_states, fsm_object & fsm);
void processFSM(std::vector<std::string> & elements, std::vector<fsm_parser_state>& fsm_states, std::vector<fsm_parser_state>& fsm_added_states, fsm_object & fsm);
