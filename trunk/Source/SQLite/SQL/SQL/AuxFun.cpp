#include "AuxFun.h"

using namespace std;

int processResult(void* qr, int numCols, char** valCol, char** nomCol)
{
	QueryResult queryResult;

	for(int i = 0; i < numCols; i++)
	{
		std::string nC = nomCol[i];
		std::string vC = valCol[i];
		queryResult.setValue(nC, vC);
	}
	((List<QueryResult>*)qr)->add(queryResult);

	return 0;
}