#pragma once 

#include <vector>
#include <string>

#include <actions/actions.h>
#include <conditions/conditions.h>

struct State{
	std::string name;
	std::vector<Action*> actions;
	std::vector<Condition*> conditions;
}; 

State * getState(std::string,std::vector<State>&);
