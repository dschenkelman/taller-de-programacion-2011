#include "stdafx.h"
#include "ParameterHolder.h"
#include <sstream>

/** string parameters */
void ParameterHolder::addParameter(std::string key, std::string value){
	Parameter* newParameter = new Parameter(key, value);
	this->parameters.add(newParameter);
}

std::string ParameterHolder::getParameter(std::string key){
	std::string toReturn = NULL;
	bool found = false;
	size_t pos = 0;
	while(!found && pos < this->parameters.length()){
		if(this->parameters.at(pos)->getKey() == key){
			toReturn = this->parameters.at(pos)->getValue();
			found = true;
		}
	}
	return toReturn;
}


/** int parameters */
void ParameterHolder::addIntParameter(std::string key, int value){
	std::string s;
	std::stringstream out;
	out << value;
	s = out.str();
	Parameter* newParameter = new Parameter(key, s);
	this->parameters.add(newParameter);
}
int ParameterHolder::getIntParameter(std::string key){
	std::string toReturn = NULL;
	bool found = false;
	size_t pos = 0;
	while(!found && pos < this->parameters.length()){
		if(this->parameters.at(pos)->getKey() == key){
			toReturn = this->parameters.at(pos)->getValue();
			found = true;
		}
	}

	return atoi(toReturn.c_str());;
}


ParameterHolder::~ParameterHolder()
{
	for (int i = 0; i < this->parameters.length(); i++)
	{
		delete this->parameters.at(i);
	}
}
