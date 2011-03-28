#pragma once
#include "Camino.h"

class CaminoTests
{
public:
	CaminoTests(void);
	~CaminoTests(void);
	void run(void);
	void printResult(std::string testName, bool result);
	bool testAtributoFilaConValorNegativoTiraExcepcion();
	bool testAtributoColumnaConValorNegativoTiraExcepcion();
	bool testAtributoFilaCorrectoGuardaCorrectamente();
	bool testAtributoColumnaCorrectoGuardaCorrectamente();
};
