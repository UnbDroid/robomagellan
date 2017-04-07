#pragma once 

#include <string>
#include "actions/actions.h"
#include "conditions/conditions.h"
#include "states/states.h"
#include "bruce_main_2/vitals.h"

struct Fsm{
    std::vector<State> states;
    State * cur_state;
    State * last_state;
    std::string cur_state_name;
    robot_information * info;
};

int fsm_init(Fsm *fsm);

int fsm_add_states(Fsm * fsm, std::vector<State> & states);

int fsm_next_state(Fsm * fsm);

int fsm_main(Fsm *fsm);

int fsm_to_state(Fsm *obj, std::string state);

void fsm_terminate(Fsm *obj);
