#include "conditions/conditions.h"
#include "ros/ros.h"
#include "fsm.h"
#include <cstdlib>

bool check_black_button(Fsm *fsm, std::vector<std::string>args){
	return fsm->info->botao_preto;
}
