#pragma once
#include "Obstaculo.h"

class ObstaculoTests
{
public:
	ObstaculoTests(void);
	~ObstaculoTests(void);
	void printLeaks(int);
	void run(void);
	void printResult(std::string testName, bool result);
	bool testAtributoFilaConValorNegativoTiraExcepcion();
	bool testAtributoColumnaConValorNegativoTiraExcepcion();
	bool testAtributoFilaCorrectoGuardaCorrectamente();
	bool testAtributoColumnaCorrectoGuardaCorrectamente();
};
