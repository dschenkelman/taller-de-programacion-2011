#pragma once
#include "Escenario.h"

class EscenarioTests
{
public:
	EscenarioTests(void);
	~EscenarioTests(void);
	void printLeaks(int);
	void run(void);
	void printResult(std::string testName, bool result);
	bool testCrearEscenarioCreaCorrectamente(void);
	bool testNonValidAttributeMakesHasErrorTrue(void);
	bool testCorrectlyPopulatesTexturas(void);
};
