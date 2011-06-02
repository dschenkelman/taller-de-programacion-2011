#pragma once
#include "List.h"
#include "Parameter.h"

class ParameterHolder{
private:
	List<Parameter*>* parameters;
public:
	void* getParameter(std::string key);
	void addParameter(std::string key, void* value);
	~ParameterHolder();
};