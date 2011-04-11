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
	bool testAtributoAnchoConValorNegativoTomaValorPorDefecto();
	bool testAtributoAltoConValorNegativoTomaValorPorDefecto();
	bool testAtributoAltoCorrectoGuardaCorrectamente();
	bool testAtributoAnchoCorrectoGuardaCorrectamente();
	bool testGenerarMatrizGeneraCorrectamente();
	bool testTipoBonusInvalidoNoSeAgregaALaMatriz();
	bool testColocarDosObjetosEnMismaPosicionGuardaElPrimero();
	bool testNonValidAttributeMakesHasErrorTrue(void);
};
