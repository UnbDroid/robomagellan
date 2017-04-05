#include "actions/actions.h"
#include "ros/ros.h"
#include "fsm.h"
#include "parser/base_functions.h"

void change_state(Fsm *fsm, std::vector<std::string> args){
	trim(args[0]);
	fsm_to_state(fsm,args[0]);
}
