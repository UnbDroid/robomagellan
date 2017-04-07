#pragma once 

#include <string>
#include "bruce_main/vitals.h"

struct fsm_object;

struct fsm_state{
    std::string name;
    void (*function)(struct fsm_object* ,int,void**);
    struct fsm_state *next;
    int num;
    void** arg;
}; 

struct fsm_object{
    struct fsm_state * fsm_base;
    struct fsm_state * fsm_cur_state;
    struct fsm_state * fsm_last_state;
    std::string fsm_cur_state_name;
    int fsm_arg_num;
    void ** fsm_arg_value;
    robot_information * info;
};

int fsm_init(struct fsm_object *obj);

int fsm_main(struct fsm_object *obj);

int fsm_next_state(struct fsm_object *obj);

int fsm_add(struct fsm_object *obj, std::string state, void (*fun)(struct fsm_object *, int, void **) );

int fsm_return_last_state(struct fsm_object *obj);

int fsm_default(struct fsm_object *obj, void (*fun)(struct fsm_object *, int, void **) );

int fsm_remove(struct fsm_object *obj, std::string state);

int fsm_to_state(struct fsm_object *obj, std::string state, int num, void** arg);
int fsm_to_state(struct fsm_object *obj, std::string state);

int fsm_add_arg(struct fsm_object *obj, std::string state, int num, void** arg);

void fsm_terminate(struct fsm_object *obj);
