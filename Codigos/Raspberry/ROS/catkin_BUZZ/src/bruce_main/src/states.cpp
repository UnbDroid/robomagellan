#include "states.h"

void startStates(std::vector<fsm_parser_state>& fsm_states){
	fsm_parser_state setup_state = {{"",setup,NULL},"setup"};
	setup_state.function_param_names.push_back("map_bottom_left_lat");
	setup_state.function_param_names.push_back("map_bottom_left_lng");
	setup_state.function_param_names.push_back("next_state");

	fsm_parser_state calcular_rota_state = {{"",calcular_rota,NULL},"calcular_rota"};
	calcular_rota_state.function_param_names.push_back("x_coordinate");
	calcular_rota_state.function_param_names.push_back("y_coordinate");
	calcular_rota_state.function_param_names.push_back("next_state");

	fsm_parser_state aproximar_cruzeiro_state = {{"",aproximar_cruzeiro,NULL},"aproximar_cruzeiro"};
	aproximar_cruzeiro_state.function_param_names.push_back("obstacle_range");
	aproximar_cruzeiro_state.function_param_names.push_back("max_dist_from_route");
	aproximar_cruzeiro_state.function_param_names.push_back("wait_recalculate_time");
	aproximar_cruzeiro_state.function_param_names.push_back("recalculate_state");
	aproximar_cruzeiro_state.function_param_names.push_back("avoid_obstacle_state");
	aproximar_cruzeiro_state.function_param_names.push_back("next_state");	

	fsm_parser_state recalcular_rota_state = {{"",recalcular_rota,NULL},"recalcular_rota"};

	fsm_parser_state desviar_obstaculos_moveis_state = {{"",desviar_obstaculos_moveis,NULL},"desviar_obstaculos_moveis"};
	desviar_obstaculos_moveis_state.function_param_names.push_back("obstacle_inflation");

   	fsm_parser_state parser_states[NUM_STATES] = {setup_state,
	                      		                                  	calcular_rota_state,
		 		                                  	aproximar_cruzeiro_state,
	                      		                                   	recalcular_rota_state,
		                      		                                  desviar_obstaculos_moveis_state};
           for(unsigned i = 0; i < NUM_STATES; ++i) {
           		fsm_states.push_back(parser_states[i]);
           }
}

fsm_state * getFSMState(std::vector<fsm_parser_state>& fsm_states, std::string name){
	for(unsigned i = 0; i < fsm_states.size(); ++i) {
		if(fsm_states[i].function_name == name){
			return & fsm_states[i].state;
		}
	}
	return NULL;
}

fsm_parser_state * getFSMParserState(std::vector<fsm_parser_state>& fsm_states, std::string name){
	for(unsigned i = 0; i < fsm_states.size(); ++i) {
		if(fsm_states[i].state.name == name){
			return & fsm_states[i];
		}
	}
	return NULL;	
}

void processArgs(std::vector<arg_type> & newArgs, int val,void **arg){
	arg_type ** argsRaw = (arg_type**) arg;
	for(unsigned i = 0; i < val; ++i) {
		newArgs.push_back(*(argsRaw[i]));
	}
}
