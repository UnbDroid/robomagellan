#pragma once
#include <fstream>
#include <iostream>
#include <algorithm> 
#include <functional> 
#include <cctype>
#include <locale>
#include <string>
#include <cstring>

// trim from start
std::string &ltrim(std::string &s);

// trim from end
std::string &rtrim(std::string &s);

// trim from both ends
std::string &trim(std::string &s);

std::vector<std::string> split(std::string text, std::string delimiter,bool includeEmpty = false);
