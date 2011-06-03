#include "stdafx.h"
#include "ParameterHolder.h"

void ParameterHolder::addParameter(std::string key, std::string value){
	Parameter* newParameter = new Parameter(key, value);
	this->parameters->add(newParameter);
}

std::string ParameterHolder::getParameter(std::string key){
	std::string toReturn = "";
	bool found = false;
	size_t pos = 0;
	while(!found && pos < this->parameters->length()){
		if(this->parameters->at(pos)->getKey() == key){
			toReturn = this->parameters->at(pos)->getValue();
			found = true;
		}
		pos++;
	}
	return toReturn;
}

ParameterHolder::ParameterHolder(){
	this->parameters = new List<Parameter*>();
}

ParameterHolder::~ParameterHolder()
{
	for (int i = 0; i < this->parameters->length(); i++)
	{
		delete this->parameters->at(i);
	}
}
