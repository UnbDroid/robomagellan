#include <stdlib.h>
#include <string.h>
#include "fsm.h"

int fsm_init(Fsm *fsm){
    fsm->states = std::vector<State>();
    fsm->cur_state = NULL;
    fsm->last_state = NULL;
    fsm->cur_state_name = std::string();
    fsm->info = NULL;
    return 0;
}

int fsm_add_states(Fsm * fsm, std::vector<State> & states){
    fsm->states = states;
}

int fsm_next_state(Fsm * fsm){
    if(fsm->cur_state == NULL){
        if(fsm->states.size() < 1){
            return -1;
        }else{
            fsm->cur_state_name = fsm->states[0].name;
        }
    }
    State * state = NULL;
    for(int i=0; i < fsm->states.size(); i++){     
        if( fsm->cur_state_name == fsm->states[i].name){
            state = & fsm->states[i];
        }
    }
    if (state == NULL)
        return -1;
    if(state && fsm->cur_state){
        if(state->name != fsm->cur_state->name)
            fsm->last_state = fsm->cur_state;
    }
    // if(fsm->last_state){

    //     std::cout << "Last state: "<< fsm->last_state->name << std::endl;
    // }
    // if(fsm->cur_state){
    //     std::cout << "Cur state: "<< fsm->cur_state->name<< std::endl;
    // }
    fsm->cur_state = state;

    return 0;
}

int fsm_main(Fsm *fsm){
    if(fsm->cur_state != NULL){
        for (int i = 0; i < fsm->cur_state->actions.size(); ++i){
            fsm->cur_state->actions[i]->function(fsm, fsm->cur_state->actions[i]->action_param);
        }
        for (int i = 0; i < fsm->cur_state->conditions.size(); ++i){
            Condition * condition = fsm->cur_state->conditions[i];
            bool result = true;
            while(condition != NULL){
                result &= condition->function(fsm, condition->condition_param);
                condition = condition->next;
            }
            condition = fsm->cur_state->conditions[i];
            if(result){
                for (int i = 0; i < condition->actions.size(); ++i){
                    condition->actions[i]->function(fsm, condition->actions[i]->action_param);
                }
            }
        }
    }

     return fsm_next_state(fsm);
    
}

int fsm_to_state(Fsm *fsm, std::string state)
{
    if(state == "terminate"){
        fsm_terminate(fsm);
    }else if(state == "last_state"){
        std::cout << fsm->last_state->name << std::endl;
        fsm->cur_state_name = fsm->last_state->name;
    }else{
        fsm->cur_state_name = state;
    }
    return 0;
}

void fsm_terminate(Fsm *fsm){
    fsm->states.clear();
    fsm->cur_state = NULL;
    fsm->last_state = NULL;
}
