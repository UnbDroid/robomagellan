#include <stdlib.h>
#include <string.h>
#include "fsm.h"

int fsm_init(struct fsm_object *obj)
{
    obj->fsm_base = NULL;
    obj->fsm_cur_state_name = std::string();
    obj->fsm_arg_num = 0;
    obj->fsm_arg_value = NULL;
    obj->fsm_last_state = NULL;
    obj->info = NULL;
    return 0;
}

int fsm_next_state(struct fsm_object *obj)
{
    struct fsm_state *tmp = obj->fsm_base;
    if ((obj->fsm_base==NULL)||(obj->fsm_cur_state_name.empty()))
    {        
        return -1;
    }
    while ((tmp->name != obj->fsm_cur_state_name)&&(tmp!=NULL))
        tmp = tmp->next;
    if (tmp == NULL)
        return -1;
    tmp->function(obj,obj->fsm_arg_num,obj->fsm_arg_value);

    
    return 0;
}

int fsm_main(struct fsm_object *obj)
{
     return fsm_next_state(obj);
    
}

int fsm_add(struct fsm_object *obj, std::string state, void (*fun)(struct fsm_object *, int ,void **) )
{
    struct fsm_state *tmp = obj->fsm_base;
    struct fsm_state *new_state = new fsm_state;
    while(tmp->next)
        tmp = tmp->next;
    new_state->name = state;
    new_state->function = fun;
    new_state->next=NULL;
    tmp->next=new_state;
    return 0;
}

int fsm_remove(struct fsm_object *obj,std::string state)
{
    if (state == "default")
        return -1;
    struct fsm_state *to_del;
    struct fsm_state *tmp=obj->fsm_base;
    while((tmp->next!=NULL)&&(tmp->next->name != state))
        tmp=tmp->next;
    if (tmp == NULL)
        return -1;
    to_del = tmp->next;
    tmp->next = tmp->next->next;
    free(to_del);
    return 0;
}

int fsm_return_last_state(struct fsm_object *obj){
    if(obj->fsm_last_state == NULL){
        return 0;
    }     
    struct fsm_state *tmp = obj->fsm_cur_state;
    obj->fsm_cur_state = obj->fsm_last_state;
    obj->fsm_cur_state_name = obj->fsm_last_state->name;
    obj->fsm_arg_num = obj->fsm_last_state->num;
    obj->fsm_arg_value= obj->fsm_last_state->arg;
    obj->fsm_last_state = tmp;
    return 0;
}

int fsm_to_state(struct fsm_object *obj, std::string state, int num, void** arg)
{
    struct fsm_state *tmp=obj->fsm_base;
    while((tmp!=NULL)&&(tmp->name != state))
        tmp=tmp->next;
    if (tmp == NULL)
        return -1;
    obj->fsm_last_state = obj->fsm_cur_state;
    obj->fsm_cur_state = tmp;
    obj->fsm_cur_state_name = tmp->name;
    obj->fsm_arg_num = num;
    obj->fsm_arg_value=arg;
    return 0;
}

int fsm_to_state(struct fsm_object *obj, std::string state)
{
    if(state == "terminate"){
        fsm_terminate(obj);
    }else{
        struct fsm_state *tmp=obj->fsm_base;
        while((tmp!=NULL)&&(tmp->name != state))
            tmp=tmp->next;
        if (tmp == NULL)
            return -1;
        obj->fsm_last_state = obj->fsm_cur_state;
        obj->fsm_cur_state = tmp;
        obj->fsm_cur_state_name = tmp->name;
        obj->fsm_arg_num = tmp->num;
        obj->fsm_arg_value=tmp->arg;
    }
    return 0;
}

int fsm_add_arg(struct fsm_object *obj, std::string state, int num, void** arg)
{
    struct fsm_state *tmp=obj->fsm_base;
    while((tmp!=NULL)&&(tmp->name != state))
        tmp=tmp->next;
    if (tmp == NULL)
        return -1;
    tmp->num = num;
    tmp->arg = arg;
    if(state=="default"){
        obj->fsm_arg_num = tmp->num;
        obj->fsm_arg_value=tmp->arg;       
    }
    return 0;
}

int fsm_default(struct fsm_object *obj, void (*fun)(struct fsm_object *, int ,void **) )
{
    obj->fsm_base = new fsm_state;
    obj->fsm_base->name="default";
    obj->fsm_base->function = fun;
    obj->fsm_base->next = NULL;
    obj->fsm_cur_state = obj->fsm_base;
    obj->fsm_cur_state_name = obj->fsm_base->name;
    return 0;
}

void fsm_terminate(struct fsm_object *obj)
{
    struct fsm_state *tmp = obj->fsm_base;
    struct fsm_state *to_del=tmp;
    while(tmp)
    {
        to_del = tmp;
        tmp=tmp->next;
        free(to_del);
    }

    obj->fsm_cur_state = NULL;
    obj->fsm_cur_state_name = std::string();
    obj->fsm_base = NULL;
}
