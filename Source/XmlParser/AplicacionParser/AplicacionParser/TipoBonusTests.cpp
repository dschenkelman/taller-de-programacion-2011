#include "StdAfx.h"
#include "TipoBonusTests.h"
#include <exception>
#include <iostream>
using namespace std;

TipoBonusTests::TipoBonusTests(void)
{
}

TipoBonusTests::~TipoBonusTests(void)
{
}

void TipoBonusTests::run(void)
{
	printResult("testAtributoTexturaDeMasDeUnCaracterTiraExcepcion", testAtributoTexturaDeMasDeUnCaracterTiraExcepcion());
	printResult("testAtributoTexturaCorrectoGuardaCorrectamente", testAtributoTexturaCorrectoGuardaCorrectamente());
}

void TipoBonusTests::printResult(std::string testName, bool result)
{
	std::cout << (testName.append(result ? ": Passed\n" : ": Failed!!!\n"));
}

bool TipoBonusTests::testAtributoTexturaDeMasDeUnCaracterTiraExcepcion()
{
	XmlElement elemento("Nombre", 1, 100);
	XmlAttribute atributo("textura", "*+");
	elemento.addAttribute(atributo);

	try
	{
		TipoBonus tipoBonus(elemento);
	}
	catch (exception& e)
	{
		return true;
	}

	return false;
}

bool TipoBonusTests::testAtributoTexturaCorrectoGuardaCorrectamente()
{
	XmlElement elemento("Nombre", 1, 100);
	XmlAttribute atributo("textura", "+");
	elemento.addAttribute(atributo);

	TipoBonus tipoBonus(elemento);
	
	char textura = tipoBonus.getTextura();

	if (textura != '+')
	{
		return false;
	}

	return true;
}