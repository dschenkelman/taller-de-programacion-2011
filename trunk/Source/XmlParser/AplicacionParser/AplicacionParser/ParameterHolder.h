#pragma once
#include "List.h"
#include "Parameter.h"

class ParameterHolder{
private:
	List<Parameter*> parameters;
public:
	// string parameters
	std::string getParameter(std::string key);
	void addParameter(std::string key, std::string value);
	
	// int parameters
	int getIntParameter(std::string key);
	void addIntParameter(std::string key, int value);
	
	~ParameterHolder();
};