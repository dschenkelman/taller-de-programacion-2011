#pragma once
#include "List.h"
#include "Parameter.h"

class ParameterHolder{
private:
	List<Parameter*>* parameters;
public:
	std::string getParameter(std::string key);
	void addParameter(std::string key, std::string value);
	~ParameterHolder();
};