#include <string>
#include <vector>
using namespace std;

#pragma once
class xmlValidator
{
public:
	xmlValidator(void);
	~xmlValidator(void);
	bool validate(string);
private:
	string getOpeningElementName(string xml, size_t* index);
	string getClosingElementName(string xml, size_t* index);
};

