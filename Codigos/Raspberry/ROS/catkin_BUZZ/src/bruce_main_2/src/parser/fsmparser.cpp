#include "parser/fsmparser.h"
#include "states/states.h"
#include "parser/base_functions.h"

void parseFile(std::string filename,Fsm & fsm){
	std::ifstream file;
	std::string line, fileText;
	file.open((filename).c_str());
	while(file.is_open() && !file.eof()){
		std::getline(file,line);
		if(!line.empty() && line.c_str()!=NULL){
			fileText.append(line);
			fileText.append("\n");
		}
	}
	processFileText(fileText,fsm);
	file.close();
}

void processFileText(std::string text, Fsm & fsm){
	// = StringSplitter::split("\n",text);
	std::vector<std::string> sections = split(text,"@",true);
	//std::vector<fsm_parser_state> fsm_added_states;

	std::vector<ActionParser> actions;
	startActionsParser(actions);
	std::vector<ActionParser> added_actions;

	std::vector<ConditionParser> conditions;
	startConditionsParser(conditions);
	std::vector<ConditionParser> added_conditions;

	std::vector<State> added_states;

	if(sections.size()!=5){
		throw("Incorrect number of section");
	}
	for (std::vector<std::string>::iterator section = sections.begin()+1; section != sections.end(); ++section){
		// std::cout << *section << std::endl;
		// std::cout << "------------------------" << std::endl;		
		std::vector<std::string> elements = split(*section,"+");
		if(trim(elements[0]) == "Actions"){
			// std::cout << "Nas Acoes" << std::endl;
			// std::cout << "------------------------" << std::endl;
			processActions(elements, actions, added_actions);
		}else if(trim(elements[0]) == "Conditions"){
			// std::cout << "Nas condicoes" << std::endl;
			// std::cout << "------------------------" << std::endl;
			processConditions(elements, conditions, added_conditions);
		}else if(trim(elements[0]) == "States"){
			// std::cout << "Nos estados" << std::endl;
			// std::cout << "------------------------" << std::endl;
			processStates(elements,added_states);
		}else if(trim(elements[0]) == "FSM"){
			// std::cout << "No corpo" << std::endl;
			// std::cout << "------------------------" << std::endl;
			processFSM(elements,added_actions,added_conditions,added_states);
		}else{
			throw("Section doesn't exist");
		}
	}
	fsm_add_states(&fsm,added_states);
	/*for(unsigned i = 0; i < added_states.size(); ++i) {
		std::cout<< added_states[i].name <<std::endl;
		std::cout<< added_states[i].actions.size() <<std::endl;
		for(unsigned j = 0; j < added_states[i].actions.size(); ++j) {
			std::cout<< "\t" <<added_states[i].actions[j]->name <<std::endl;
			for (int k = 0; k < added_states[i].actions[j]->action_param.size(); ++k){
				std::cout<< "\t\t" <<added_states[i].actions[j]->action_param[k] <<std::endl;
			}
		}
		std::cout<< added_states[i].conditions.size() <<std::endl;
		for(unsigned j = 0; j < added_states[i].conditions.size(); ++j) {
			std::cout<< "\t" <<added_states[i].conditions[j]->name <<std::endl;
			Condition * aux = added_states[i].conditions[j]->next;
			for (int k = 0; k < added_states[i].conditions[j]->condition_param.size(); ++k){
				std::cout<< "\t\t" <<added_states[i].conditions[j]->condition_param[k] <<std::endl;
			}
			while(aux != NULL){
				std::cout<< "\t-Extra: " <<added_states[i].conditions[j]->name <<std::endl;
				for (int k = 0; k < aux->condition_param.size(); ++k){
					std::cout<< "\t\t-" <<aux->condition_param[k] <<std::endl;
				}
				aux = aux->next;
			}
			for (int k = 0; k < added_states[i].conditions[j]->actions.size(); ++k){
				std::cout<< "\t\t\t" <<added_states[i].conditions[j]->actions[k]->name <<std::endl;
				for (int l = 0; l < added_states[i].conditions[j]->actions[k]->action_param.size(); ++l){
					std::cout<< "\t\t\t\t" <<added_states[i].conditions[j]->actions[k]->action_param[l] <<std::endl;
				}
			}
		}
	}*/
}

void processActions(std::vector<std::string> & elements, std::vector<ActionParser> & actions, std::vector<ActionParser> & added_actions){
	for (std::vector<std::string>::iterator element = elements.begin()+1; element != elements.end(); ++element){
		std::vector<std::string> properties = split(*element,":");
		if(properties.size() != 2){
			throw("Actions: action has the wrong number of arguments, it should be two");
		}
		trim(properties[0]);
		trim(properties[1]);

		ActionParser action;
		bool exists = getActionByFunctionName(action,properties[1],actions);
		if(!exists){
			std::string aux = std::string("Actions: ")+properties[1]+std::string(" is not a valid action");
			throw(aux.c_str());	
		}
		action.name = properties[0];
		added_actions.push_back(action);
	}
}

void processConditions(std::vector<std::string> & elements, std::vector<ConditionParser> & conditions, std::vector<ConditionParser> & added_conditions){
	for (std::vector<std::string>::iterator element = elements.begin()+1; element != elements.end(); ++element){
		std::vector<std::string> properties = split(*element,":");
		if(properties.size() != 2){
			throw("Conditions: condition has the wrong number of arguments, it should be two");
		}
		trim(properties[0]);
		trim(properties[1]);

		ConditionParser condition;
		bool exists = getConditionByFunctionName(condition,properties[1],conditions);
		if(!exists){
			std::string aux = std::string("Conditions: ")+properties[1]+std::string(" is not a valid condition");
			throw(aux.c_str());	
		}
		condition.name = properties[0];
		added_conditions.push_back(condition);
	}
}

void processStates(std::vector<std::string> & elements, std::vector<State> & added_states){
	for (std::vector<std::string>::iterator element = elements.begin()+1; element != elements.end(); ++element){
		trim(*element);
		State state;
		state.name = *element;
		added_states.push_back(state);
	}
}

void getArgument(std::string & name, std::string & arg, std::string & str){
	int searchStart = str.find("(");
	int searchEnd = str.find(")");
	int argStart = searchStart+1;
	int argEnd = searchEnd - argStart;
	//std::cout << "Recebi: " << str <<std::endl;
	if(searchStart == std::string::npos || searchEnd == std::string::npos){
		throw("FSM: Missing ()");
	}
	arg =  str.substr(argStart,argEnd);
	trim(arg);
	name = str.substr(0,argStart-1);
	trim(name);
}


void processFSM(std::vector<std::string> & elements, std::vector<ActionParser> & added_actions, std::vector<ConditionParser> & added_conditions,std::vector<State> & added_states){
	for (std::vector<std::string>::iterator element = elements.begin()+1; element != elements.end(); ++element){
		std::vector<std::string> stateDescriptions = split(*element,"\t");
		trim(stateDescriptions[0]);
		//std::cout << stateDescriptions[0] << std::endl;
		State * state = getState(stateDescriptions[0],added_states);
		if(state == NULL){
			throw("FSM: Inexistent state");
		}
		for(unsigned i = 1; i < stateDescriptions.size(); ++i) {
			std::vector<std::string> parts = split(stateDescriptions[i],">>");
			if(parts.size() == 1){
				Action * action = processSingleAction(parts[0],added_actions);
				state->actions.push_back(action);
			}else if(parts.size() == 2){
				std::vector<std::string> conditions = split(parts[0],"&");
				std::vector<std::string> actions = split(parts[1],"&");
				processConditions(conditions, actions,added_conditions,added_actions,state);				
			}
			// std::cout << "State description: " << stateDescriptions[i] <<" "<<parts.size() << std::endl;
		}
		
	}
}

Action * processSingleAction(std::string part,  std::vector<ActionParser> & added_actions){
	trim(part);
	std::string args;
	std::string actionName;
	getArgument(actionName,args,part);
	Action * action = createAction(actionName,args,added_actions);
	if(action == NULL){
		throw("FSM: Inexistent action");
	}
	return action;
}
Condition * processSingleCondition(std::string part,  std::vector<ConditionParser> & added_conditions){
	trim(part);
	std::string args;
	std::string conditionName;
	getArgument(conditionName,args,part);
	Condition * condition = createCondition(conditionName,args,added_conditions);
	if(condition == NULL){
		throw("FSM: Inexistent condition");
	}
	return condition;
}


void processConditions(std::vector<std::string> conditions, std::vector<std::string> actions, std::vector<ConditionParser> & added_conditions,  std::vector<ActionParser> & added_actions, State * state){
	Condition * base_condition = processSingleCondition(conditions[0],added_conditions);
	Condition * aux = base_condition;
	for(unsigned i = 1; i < conditions.size(); ++i) {
		aux->next = processSingleCondition(conditions[i],added_conditions);
		aux = aux->next;
	}
	aux->next = NULL;
	for(unsigned i = 0; i < actions.size(); ++i) {
		Action * action = processSingleAction(actions[i],added_actions);
		base_condition->actions.push_back(action);
	}
	state->conditions.push_back(base_condition);
}

double toRadian(double degree){
  return (degree*PI/180.0);
}


ECEFCoord GPS2ECEF(GPSCoord gpoint){
  float a = 6378137;
  float b = 6356752.31424518;
  float f = (a-b)/a;
  float e = std::sqrt(f*(2.0-f));
  float sinLat = std::sin(toRadian(gpoint.lat));
  float cosLat = std::cos(toRadian(gpoint.lat));
  float sinLng = std::sin(toRadian(gpoint.lng));
  float cosLng = std::cos(toRadian(gpoint.lng));
  float N = a/(std::sqrt(1-(e*e*sinLat*sinLat))); 

  ECEFCoord ecefPoint;

  ecefPoint.x = (N+gpoint.alt)*cosLat*cosLng;
  ecefPoint.y = (N+gpoint.alt)*cosLat*sinLng;
  ecefPoint.z = (N*(1-e*e)+gpoint.alt)*sinLat; 
  return ecefPoint;
}

NEDCoord GPS2NED(GPSCoord gpoint ,GPSCoord ref){
  
  
  ECEFCoord ecefPoint = GPS2ECEF(gpoint);
  ECEFCoord refEcefPoint = GPS2ECEF(ref);
  
  NEDCoord nedPoint,aux;
  
  double sLaR = std::sin(toRadian(ref.lat));
  double cLaR = std::cos(toRadian(ref.lat));
  double sLoR = std::sin(toRadian(ref.lng));
  double cLoR = std::cos(toRadian(ref.lng));

  aux.x = ecefPoint.x-refEcefPoint.x;
  aux.y = ecefPoint.y-refEcefPoint.y;
  aux.z = ecefPoint.z-refEcefPoint.z;

  nedPoint.x = -sLaR*cLoR*aux.x  - sLaR*sLoR*aux.y + cLaR*aux.z;
  nedPoint.y = -sLoR*aux.x          + cLoR*aux.y;
  nedPoint.z = -cLaR*cLoR*aux.x  - cLaR*sLoR*aux.y - sLaR*aux.z;

  return nedPoint;
}
