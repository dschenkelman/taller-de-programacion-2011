#pragma once
#include <string>

class Parameter{
private:
	std::string key;
	void* value;
public:
	std::string getKey();
	void* getValue();
	void setKey(std::string k);
	void setValue(void* v);
};