#include "conditions/conditions.h"
#include "parser/base_functions.h"

void startConditionsParser(std::vector<ConditionParser> & conditions){
	/* is_bigger condition */
	ConditionParser is_bigger_condition = {"","is_bigger",is_bigger};
	is_bigger_condition.condition_param_names.push_back("first");
	is_bigger_condition.condition_param_names.push_back("second");
	conditions.push_back(is_bigger_condition);
	/* odom_ok condition */
	ConditionParser odom_ok_condition = {"","odom_ok",odom_ok};
	conditions.push_back(odom_ok_condition);
	/* route_calculated condition */
	ConditionParser route_calculated_condition = {"","route_calculated",route_calculated};
	conditions.push_back(route_calculated_condition);
	/* distant_from_route condition */
	ConditionParser distant_from_route_condition = {"","distant_from_route",distant_from_route};
	distant_from_route_condition.condition_param_names.push_back("distance");
	conditions.push_back(distant_from_route_condition);	
	/* distant_from_route condition */
	ConditionParser cone_found_condition = {"","cone_found",cone_found};
	conditions.push_back(cone_found_condition);	
	/* any_us_reading_smaller condition */
	ConditionParser us_reading_smaller_condition = {"","us_reading_smaller",us_reading_smaller};
	us_reading_smaller_condition.condition_param_names.push_back("us_number");
	us_reading_smaller_condition.condition_param_names.push_back("distance");
	conditions.push_back(us_reading_smaller_condition);	
	/* check_timer condition */
	ConditionParser check_timer_condition = {"","check_timer",check_timer};
	check_timer_condition.condition_param_names.push_back("name");
	check_timer_condition.condition_param_names.push_back("time");
	conditions.push_back(check_timer_condition);		
}

bool getConditionByFunctionName(ConditionParser & condition, std::string funcName, std::vector<ConditionParser> & conditions){
	for(unsigned i = 0; i < conditions.size(); ++i) {
		if(conditions[i].func_name == funcName){
			condition = conditions[i];
			return true;
		}
	}
	return false;
}

Condition * createCondition(std::string & name, std::string & args , std::vector<ConditionParser> & conditions){
	for(unsigned i = 0; i < conditions.size(); ++i) {
		if(conditions[i].name == name){
			Condition * condition= new Condition;
			condition->name = name;
			condition->function = conditions[i].function;
			std::vector<std::string> arguments = split(args,",",true);
			if(arguments.size() != conditions[i].condition_param_names.size()){
				throw("Condition with incorrect number of arguments");
			}
			std::string * auxArgs = new std::string[arguments.size()];
			for(unsigned k = 0; k < arguments.size(); ++k) {
				std::vector<std::string> arg_parts = split(arguments[k],":",true);
				if(arg_parts.size()!=2){
					std::string aux = name + std::string(" condition missing or with too many :");
					throw(aux.c_str());				
				}
				trim(arg_parts[0]);
				trim(arg_parts[1]);
				bool found = false;
				for(unsigned j=0; j < arguments.size(); ++j){
					if(arg_parts[0] == conditions[i].condition_param_names[j]){
						found = true;
						auxArgs[j] = arg_parts[1];
						break;
					}
				}
				if(!found){
					std::string aux = name + std::string(" condition doesn't have ") + arg_parts[0] +std::string(" argument");
					throw(aux.c_str());				
				}
			}
			for(unsigned j=0; j < arguments.size(); ++j){
				condition->condition_param.push_back(auxArgs[j]);
			}
			if(condition->condition_param.size()!=arguments.size()){
				std::string aux = name + std::string(" condition missing arguments");
				throw(aux.c_str());	
			}
			return condition;
		}
	}	
	return NULL;
}
