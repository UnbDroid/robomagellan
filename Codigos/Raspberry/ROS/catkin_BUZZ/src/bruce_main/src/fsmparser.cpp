#include "fsmparser.h"
#include "states.h"
#include <fstream>
#include <iostream>
#include <algorithm> 
#include <functional> 
#include <cctype>
#include <locale>
#include <string>
#include <cstring>

// trim from start
static inline std::string &ltrim(std::string &s) {
    s.erase(s.begin(), std::find_if(s.begin(), s.end(),
            std::not1(std::ptr_fun<int, int>(std::isspace))));
    return s;
}

// trim from end
static inline std::string &rtrim(std::string &s) {
    s.erase(std::find_if(s.rbegin(), s.rend(),
            std::not1(std::ptr_fun<int, int>(std::isspace))).base(), s.end());
    return s;
}

// trim from both ends
static inline std::string &trim(std::string &s) {
    return ltrim(rtrim(s));
}

std::vector<std::string> split(std::string text, std::string delimiter,bool includeEmpty = false){
	std::string token;
	std::vector<std::string> parts;
	while(token != text){
		token = text.substr(0,text.find_first_of(delimiter));
		text = text.substr(text.find_first_of(delimiter) + 1);
		if(!token.empty() || includeEmpty){
			parts.push_back(token);
		}
	}
	return parts;
}

void parseFile(std::string filename,std::vector<fsm_parser_state>& fsm_states, fsm_object & fsm){
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
	processFileText(fileText,fsm_states,fsm);
	file.close();
}

void processFileText(std::string text,std::vector<fsm_parser_state>& fsm_states, fsm_object & fsm){
	// = StringSplitter::split("\n",text);
	std::vector<std::string> sections = split(text,"@",true);
	std::vector<fsm_parser_state> fsm_added_states;
	if(sections.size()!=3){
		throw("Incorrect number of section");
	}
	for (std::vector<std::string>::iterator section = sections.begin()+1; section != sections.end(); ++section){
		// std::cout << *section << std::endl;
		// std::cout << "------------------------" << std::endl;		
		std::vector<std::string> elements = split(*section,"+");
		if(trim(elements[0]) == "Declarations"){
			// std::cout << "Na declaracao" << std::endl;
			// std::cout << "------------------------" << std::endl;
			processDeclaration(elements,fsm_states,fsm_added_states,fsm);
		}else if(trim(elements[0]) == "FSM"){
			// std::cout << "No corpo" << std::endl;
			// std::cout << "------------------------" << std::endl;
			processFSM(elements,fsm_states,fsm_added_states,fsm);
		}else{
			throw("Section doesn't exist");
		}
	}
	
}

void processDeclaration(std::vector<std::string> & elements, std::vector<fsm_parser_state>& fsm_states, std::vector<fsm_parser_state>& fsm_added_states, fsm_object & fsm){
	bool hasDefault = false;
	for (std::vector<std::string>::iterator element = elements.begin()+1; element != elements.end(); ++element){
		std::vector<std::string> properties = split(*element,"\t");
		if(properties.size() != 2){
			throw("Declarations: element has too many arguments");
		}
		std::vector<std::string> property_parts = split(properties[1],":");
		if(trim(property_parts[0])!="function_name"){
			std::string msg = std::string("Declarations: \"")+std::string(property_parts[0])+ std::string("\" Property doesn't exist");
			throw(msg.c_str());
		}
		fsm_state * state = getFSMState(fsm_states,trim(property_parts[1]));

		if(state == NULL){
			std::string msg = std::string("Declarations: \"")+std::string(property_parts[1])+ std::string("\" is not a valid state function");
			throw(msg.c_str());
		}else{
			state->name = trim(properties[0]);
		}

		if(trim(properties[0]) == "default"){
			if(!hasDefault){
				hasDefault = true;
				fsm_default(&fsm,state->function);
				fsm_parser_state * added_state = getFSMParserState(fsm_states,properties[0]);
				fsm_added_states.push_back(*added_state);
			}else{
				throw("Declarations: Default already defined");
			}
		}else{
			fsm_add(&fsm,trim(properties[0]),state->function);
			fsm_parser_state * added_state = getFSMParserState(fsm_states,properties[0]);
			fsm_added_states.push_back(*added_state);			
		}
	}
	if(!hasDefault){
		throw("Declarations: Default state is missing");
	}
}

void processFSM(std::vector<std::string> & elements, std::vector<fsm_parser_state>& fsm_states, std::vector<fsm_parser_state>& fsm_added_states, fsm_object & fsm){
	for (std::vector<std::string>::iterator element = elements.begin()+1; element != elements.end(); ++element){
		std::vector<std::string> properties = split(*element,"\t");
		if(properties.size() < 1){
			throw("FSM: state with no name");
		}

		fsm_parser_state * current_parser_state = getFSMParserState(fsm_added_states,trim(properties[0]));
		if(current_parser_state == NULL){
			std::string msg = std::string("FSM: \"")+std::string(properties[0])+ std::string("\" is not a declared state name");
			throw(msg.c_str());
		}
		if(current_parser_state->function_param_names.size() != properties.size()-1){
			std::string msg = std::string("FSM: \"")+std::string(properties[0])+ std::string("\" state expects ")+std::to_string(current_parser_state->function_param_names.size())+std::string(" arguments. ")+std::to_string(properties.size()-1)+std::string(" were given. ");
			throw(msg.c_str());
		}
		arg_type ** arguments = new arg_type*[current_parser_state->function_param_names.size()];
		for (std::vector<std::string>::iterator property = properties.begin()+1; property != properties.end(); ++property){
			trim(*property);
			std::vector<std::string> property_parts = split(*property,":",true);
			if(property_parts.size()!=2){
				std::string msg = std::string("FSM: \"")+std::string(*property)+ std::string("\" has too many \":\" ");
				throw(msg.c_str());
			}
			trim(property_parts[0]);
			trim(property_parts[1]);
			bool hasMatch = false;
			for(unsigned i = 0; i < current_parser_state->function_param_names.size(); ++i) {
				if(current_parser_state->function_param_names[i] == property_parts[0]){
					hasMatch = true;
					arguments[i] = new arg_type;
					if(property_parts[1].find(",")!=std::string::npos){
						arguments[i]->type = 1;
						std::vector<std::string> arg_parts = split(property_parts[1],",");
						for (std::vector<std::string>::iterator arg_part = arg_parts.begin(); arg_part != arg_parts.end(); ++arg_part){
							arguments[i]->multiple.push_back(trim(*arg_part));	
						}			
					}else{
						arguments[i]->type = 0;
						arguments[i]->single = property_parts[1];
					}
				}
			}
			if(!hasMatch){
				std::string msg = std::string("FSM: \"")+std::string(properties[0])+ std::string("\" state doesn't have \"")+std::string(property_parts[0])+std::string("\" argument. ");
				throw(msg.c_str());				
			}
		}
		fsm_add_arg(&fsm,properties[0],current_parser_state->function_param_names.size(),(void**)arguments);
	}
}
