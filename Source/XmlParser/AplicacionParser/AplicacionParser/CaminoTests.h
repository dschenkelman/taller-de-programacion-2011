#pragma once
#include "Camino.h"
#include "Bonus.h"

class CaminoTests
{
public:
	CaminoTests(void);
	~CaminoTests(void);
	void run(void);
	void printLeaks(int leaks);
	void printResult(std::string testName, bool result);
	bool testAtributoFilaConValorNegativoTiraExcepcion();
	bool testAtributoColumnaConValorNegativoTiraExcepcion();
	bool testAtributoFilaCorrectoGuardaCorrectamente();
	bool testAtributoColumnaCorrectoGuardaCorrectamente();
	bool testCaminoConBonusCreaCorrectamente();
	bool testCaminoConDosBonusTiraExcepcion();
};