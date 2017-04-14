#include "parser/base_functions.h"

// trim from start
std::string &ltrim(std::string &s) {
    s.erase(s.begin(), std::find_if(s.begin(), s.end(),
            std::not1(std::ptr_fun<int, int>(std::isspace))));
    return s;
}

// trim from end
std::string &rtrim(std::string &s) {
    s.erase(std::find_if(s.rbegin(), s.rend(),
            std::not1(std::ptr_fun<int, int>(std::isspace))).base(), s.end());
    return s;
}

// trim from both ends
std::string &trim(std::string &s) {
    return ltrim(rtrim(s));
}

std::vector<std::string> split(std::string text, std::string delimiter,bool includeEmpty){
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
