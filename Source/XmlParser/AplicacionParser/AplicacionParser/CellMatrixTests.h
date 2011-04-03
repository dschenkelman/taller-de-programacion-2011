#include <string>
#include "CellMatrix.h"

#pragma once

class CellMatrixTests
{
public:
	CellMatrixTests(void);
	~CellMatrixTests(void);
	void run (void);
	void printResult(std::string testName, bool result);
	void printLeaks(int leaks);
};