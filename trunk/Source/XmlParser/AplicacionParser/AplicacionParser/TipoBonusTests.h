#pragma once
#include "TipoBonus.h"

class TipoBonusTests
{
public:
	TipoBonusTests(void);
	~TipoBonusTests(void);
	void printLeaks(int);
	void run(void);
	void printResult(std::string testName, bool result);
	bool testAtributoTexturaDeMasDeUnCaracterLoggeaWarning();
	bool testNonValidAttributeMakesHasErrorTrue(void);
	bool testAtributoTexturaCorrectoGuardaCorrectamente();
};
