#pragma once
#include "TipoObstaculo.h"

class TipoObstaculoTests
{
public:
	TipoObstaculoTests(void);
	~TipoObstaculoTests(void);
	void printLeaks(int leaks);
	void run(void);
	void printResult(std::string testName, bool result);
	bool testAtributoTexturaCorrectoGuardaCorrectamente();
	bool testNonValidAttributeMakesHasErrorTrue(void);
	bool testCanUseStringAsTextura(void);
};
