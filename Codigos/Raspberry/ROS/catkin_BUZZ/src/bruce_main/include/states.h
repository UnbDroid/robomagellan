#pragma once 

#include "fsm.h"
#include "fsmparser.h"
#include <vector>

#define NUM_STATES 5

void setup(struct fsm_object *obj, int val,void **arg);

void calcular_rota(struct fsm_object *obj, int val,void **arg);

void aproximar_cruzeiro(struct fsm_object *obj, int val,void **arg);

void recalcular_rota(struct fsm_object *obj, int val,void **arg);

void desviar_obstaculos_moveis(struct fsm_object *obj, int val,void **arg);

void startStates(std::vector<fsm_parser_state>& fsm_states);

fsm_state * getFSMState(std::vector<fsm_parser_state>& fsm_states, std::string name);
fsm_parser_state * getFSMParserState(std::vector<fsm_parser_state>& fsm_states, std::string name);
void processArgs(std::vector<arg_type> & newArgs, int val,void **arg);
