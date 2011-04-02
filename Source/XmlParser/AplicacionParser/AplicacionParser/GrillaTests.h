#pragma once
#include "Grilla.h"
#include "Camino.h"
#include "Obstaculo.h"

class GrillaTests
{
public:
	GrillaTests(void);
	~GrillaTests(void);
	void printLeaks(int);
	void run(void);
	void printResult(std::string testName, bool result);
	bool testAtributoAnchoConValorNegativoTiraExcepcion();
	bool testAtributoAltoConValorNegativoTiraExcepcion();
	bool testAtributoAltoCorrectoGuardaCorrectamente();
	bool testAtributoAnchoCorrectoGuardaCorrectamente();
	bool testGenerarMatrizGeneraCorrectamente();
	bool testTipoBonusInvalidoNoSeAgregaALaMatriz();
	
};
