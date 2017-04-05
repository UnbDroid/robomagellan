#pragma once 
#include "fsm.h"
#include <vector>

#define SINGLE 0
#define MULTIPLE 1




void parseFile(std::string file,Fsm & fsm);
void processFileText(std::string text,Fsm & fsm);
void processActions(std::vector<std::string> & elements, std::vector<ActionParser> & actions, std::vector<ActionParser> & added_actions);
void processConditions(std::vector<std::string> & elements, std::vector<ConditionParser> & conditions, std::vector<ConditionParser> & added_conditions);
void processStates(std::vector<std::string> & elements, std::vector<State> & added_states);
void processFSM(std::vector<std::string> & elements, std::vector<ActionParser> & added_actions, std::vector<ConditionParser> & added_conditions,std::vector<State> & added_states);
Action * processSingleAction(std::string part,  std::vector<ActionParser> & added_actions);
Condition * processSingleCondition(std::string part,  std::vector<ConditionParser> & added_conditions);
void processConditions(std::vector<std::string> conditions, std::vector<std::string> actions, std::vector<ConditionParser> & added_conditions,  std::vector<ActionParser> & added_actions, State * state);
