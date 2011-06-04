#pragma once
#include <string>

class Parameter{
private:
	std::string key;
	std::string value;
public:
	Parameter(std::string key, std::string value);
	std::string getKey();
	std::string getValue();
};