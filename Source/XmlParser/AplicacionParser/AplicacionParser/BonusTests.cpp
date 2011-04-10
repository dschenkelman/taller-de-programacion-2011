#include "StdAfx.h"
#include "BonusTests.h"
#include <iostream>
#include "XmlElement.h"
#include "Bonus.h"
#include "Logger.h"
//useful to detect memory leaks
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
using namespace std;

BonusTests::BonusTests(void)
{
}

BonusTests::~BonusTests(void)
{
}

void BonusTests::printLeaks(int leaks)
{
	std::cout << "Bonus Tests: Hubo " << leaks << " memory leaks." << endl << endl;
}

void BonusTests::run(void)
{
	printResult("testNonValidAttributeMakesHasErrorTrue", testNonValidAttributeMakesHasErrorTrue());
	int leaks = _CrtDumpMemoryLeaks();
	printLeaks(leaks);
}

void BonusTests::printResult(std::string testName, bool result)
{
	std::cout << (testName.append(result ? ": Passed\n" : ": Failed!!!\n"));
}

bool BonusTests::testNonValidAttributeMakesHasErrorTrue(void)
{
	XmlElement element("Bonus", 1, 2);
	XmlAttribute att1("tipo", "Pizza");
	XmlAttribute att2("invalido", "invalido");

	element.addAttribute(att1);
	element.addAttribute(att2);

	Bonus bonus(element);

	bool successCondition = bonus.hasError();

	Logger::closeLog();

	return successCondition;
}