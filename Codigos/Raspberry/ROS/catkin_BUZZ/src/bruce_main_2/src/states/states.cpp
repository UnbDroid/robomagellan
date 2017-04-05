#include <states/states.h>

State * getState(std::string name,std::vector<State> & states){
	for(unsigned i = 0; i < states.size(); ++i) {
		if(name == states[i].name){
			return & states[i];
		}
	}
	return NULL;
}
