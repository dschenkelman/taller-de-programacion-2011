#include "StdAfx.h"
#include "XmlElementTests.h"
#include "XmlElement.h"
#include <string>
#include <iostream>
#include <exception>

//useful to detect memory leaks
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

using namespace std;

XmlElementTests::XmlElementTests(void)
{
}

void XmlElementTests::printResult(std::string testName, bool result)
{
	std::cout << (testName.append(result ? ": Passed\n" : ": Failed!!!\n"));
}

void XmlElementTests::printLeaks(int leaks)
{
	std::cout << "List Tests: Hubo " << leaks << " memory leaks." << endl << endl;
}

void XmlElementTests::run(void) {
	printResult("initialConstructionTest",initialConstructionTest());

	/*int leaks = _CrtDumpMemoryLeaks();
	printLeaks(leaks);*/
}

bool XmlElementTests::initialConstructionTest(void) {
	XmlElement my_test("my_testing_element",123456,789012);
	if (my_test.getName()!="my_testing_element") {
		return false;
	}
	return true;
}

XmlElementTests::~XmlElementTests(void)
{
}
