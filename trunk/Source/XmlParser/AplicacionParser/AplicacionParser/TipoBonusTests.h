#pragma once
#include "TipoBonus.h"

class TipoBonusTests
{
public:
	TipoBonusTests(void);
	~TipoBonusTests(void);
	void run(void);
	void printResult(std::string testName, bool result);
	bool testAtributoTexturaDeMasDeUnCaracterTiraExcepcion();
	bool testAtributoTexturaCorrectoGuardaCorrectamente();
};
