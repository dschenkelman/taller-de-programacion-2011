#include "StdAfx.h"
#include "Parameter.h"

Parameter::Parameter(std::string key, std::string value){
	this->key = key;
	this->value = value;
}

std::string Parameter::getKey(){
	return this->key;
}

std::string Parameter::getValue(){
	return this->value;
}