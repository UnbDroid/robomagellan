#include "conditions/conditions.h"
#include "ros/ros.h"
#include "fsm.h"
#include <cstdlib>
#include "parser/base_functions.h"

bool compare(Fsm *fsm, std::vector<std::string>args){
	float f_aux1,f_aux2;
	int i_aux1,i_aux2;
	bool b_aux1, b_aux2;
	trim(args[0]); // arg1
	trim(args[1]); // arg2
	trim(args[2]); // arg1Type
	trim(args[3]); // arg2Type
	trim(args[4]); // comparation
	std::string arg1Type = args[2];
	std::string arg2Type = args[3];
	std::string comparation = args[4];

	if(arg1Type == "float"){
		f_aux1 = std::atof(args[0].c_str());
	}else if(arg1Type == "int"){
		i_aux1 = std::atoi(args[0].c_str());
	}else if(arg1Type == "bool"){
		b_aux1 = std::atoi(args[0].c_str());
	}else if(arg1Type == "v_int"){
		int * aux =(int*)getMember(fsm->info,args[0]);
		if(aux){
			i_aux1 = *aux;
		}
	}else if(arg1Type == "v_bool"){
		bool * aux =(bool*)getMember(fsm->info,args[0]);
		if(aux){
			b_aux1 = *aux;
		}
	}else if(arg1Type == "v_float"){
		float * aux =(float*)getMember(fsm->info,args[0]);
		if(aux){
			f_aux1 = *aux;
		}
	}

	if(arg2Type == "float"){
		f_aux2 = std::atof(args[1].c_str());
	}else if(arg2Type == "int"){
		i_aux2 = std::atoi(args[1].c_str());
	}else if(arg2Type == "bool"){
		b_aux2 = std::atoi(args[1].c_str());
	}else if(arg2Type == "v_int"){
		int * aux =(int*)getMember(fsm->info,args[1]);
		if(aux){
			i_aux2 = *aux;
		}
	}else if(arg2Type == "v_bool"){
		bool * aux =(bool*)getMember(fsm->info,args[1]);
		if(aux){
			b_aux2 = *aux;
		}
	}else if(arg2Type == "v_float"){
		float * aux =(float*)getMember(fsm->info,args[1]); 
		if(aux){
			f_aux2 = *aux;
		}
	}

	if(comparation == "e"){
		if(arg1Type == "int"){
			return i_aux1 == i_aux2;
		}else if(arg1Type == "float"){
			return f_aux1 == f_aux2;
		}else if(arg1Type == "bool"){
			return b_aux1 == b_aux2;
		}
	}else if(comparation == "g"){
		if(arg1Type == "int"){
			return i_aux1 > i_aux2;
		}else if(arg1Type == "float"){
			return f_aux1 > f_aux2;
		}else if(arg1Type == "bool"){
			return b_aux1 > b_aux2;
		}
	}else if(comparation == "s"){
		if(arg1Type == "int"){
			return i_aux1 < i_aux2;
		}else if(arg1Type == "float"){
			return f_aux1 < f_aux2;
		}else if(arg1Type == "bool"){
			return b_aux1 < b_aux2;
		}
	}else if(comparation == "ge"){
		if(arg1Type == "int"){
			return i_aux1 >= i_aux2;
		}else if(arg1Type == "float"){
			return f_aux1 >= f_aux2;
		}else if(arg1Type == "bool"){
			return b_aux1 >= b_aux2;
		}
	}else if(comparation == "se"){
		if(arg1Type == "int"){
			return i_aux1 <= i_aux2;
		}else if(arg1Type == "float"){
			return f_aux1 <= f_aux2;
		}else if(arg1Type == "bool"){
			return b_aux1 <= b_aux2;
		}
	}else if(comparation == "d"){
		if(arg1Type == "int"){
			return i_aux1 != i_aux2;
		}else if(arg1Type == "float"){
			return f_aux1 != f_aux2;
		}else if(arg1Type == "bool"){
			return b_aux1 != b_aux2;
		}
	}

	return false;
}
