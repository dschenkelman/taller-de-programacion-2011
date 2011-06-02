#include "StdAfx.h"
#include "Parameter.h"

std::string Parameter::getKey(){
	return this->key;
}

void* Parameter::getValue(){
	return this->value;
}