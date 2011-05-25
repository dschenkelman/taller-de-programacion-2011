#include "Query.h"
#include "AuxFun.h"

Query::Query(sqlite3* db, std::string q)
{
	this->db = db;
	this->query = q;
}

void Query::execute()
{
	List<QueryResult>* qr = new List<QueryResult>();
	sqlite3_exec(this->db, this->query.c_str(), processResult, qr, NULL);
	
	this->queryResult = *qr;
	delete qr;
}

List<QueryResult> Query::getQueryResults()
{
	return this->queryResult;
}

Query::~Query(void)
{
}
