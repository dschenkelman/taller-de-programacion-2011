#include <string>
#include <vector>
#include <iostream>
#include <istream>
#include <ostream>
#include <iterator>
#include <sstream>
#include <algorithm>
#include <map>

using namespace std;
#pragma once


class xmlTagUtils
{
public:
	xmlTagUtils(void);
	~xmlTagUtils(void);
	void parseElementAttribute(string element, std::map<std::string, std::string> & myMap);
};
