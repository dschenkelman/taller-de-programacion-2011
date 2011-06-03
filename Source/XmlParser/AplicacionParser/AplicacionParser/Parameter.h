#pragma once
#include <string>

class Parameter{
private:
	std::string key;
	std::string value;
public:
	std::string getKey();
	std::string getValue();
	void setKey(std::string k);
	void setValue(std::string v);
};