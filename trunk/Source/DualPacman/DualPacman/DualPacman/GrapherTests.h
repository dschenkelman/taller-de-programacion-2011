#pragma once
#include "Grapher.h"

class GrapherTests
{
public:
	GrapherTests(void);
	~GrapherTests(void);
	void printLeaks(int);
	void run(void);
	void printResult(std::string testName, bool result);
	bool testGraficarEscenario(void);
	bool testGraficarEscenario800x600(void);
	bool testGraficarEscenario1024x768(void);
	
};
