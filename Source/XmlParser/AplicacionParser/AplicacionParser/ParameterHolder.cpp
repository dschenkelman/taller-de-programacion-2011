#include "stdafx.h"
#include "ParameterHolder.h"

void ParameterHolder::addParameter(std::string key, void *value){
	Parameter* newParameter = new Parameter();
	this->parameters->add(newParameter);
}

void* ParameterHolder::getParameter(std::string key){
	void* toReturn = NULL;
	bool found = false;
	size_t pos = 0;
	while(!found && pos < this->parameters->length()){
		if(this->parameters->at(pos)->getKey() == key){
			toReturn = this->parameters->at(pos)->getValue();
			found = true;
		}
	}
	return toReturn;
}

ParameterHolder::~ParameterHolder()
{
	for (int i = 0; i < this->parameters->length(); i++)
	{
		delete this->parameters->at(i);
	}
}
