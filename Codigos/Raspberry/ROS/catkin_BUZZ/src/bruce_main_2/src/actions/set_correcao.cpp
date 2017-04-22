
#include "actions/actions.h"
#include "ros/ros.h"
#include "fsm.h"
#include "parser/base_functions.h"

void set_correcao(Fsm *fsm, std::vector<std::string> args){
	trim(args[0]);
	if(args[0] == "true"){
		fsm->info->correcao = true;
	}else{
		fsm->info->correcao = false;
	}
}
