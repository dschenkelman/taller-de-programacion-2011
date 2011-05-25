#include <map>
#include <string>
#pragma once

class QueryResult
{
private:
	std::map<std::string, std::string> resultMap;
public:
	QueryResult(void);
	std::string getValue(std::string colName);
	void setValue(std::string colName, std::string colValue);
	~QueryResult(void);
};
