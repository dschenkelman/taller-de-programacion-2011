#include "QueryResult.h"

QueryResult::QueryResult(void)
{
}

std::string QueryResult::getValue(std::string colName)
{
	return this->resultMap[colName];
}

void QueryResult::setValue(std::string colName, std::string colValue)
{
	this->resultMap[colName] = colValue;
}

QueryResult::~QueryResult(void)
{
}
