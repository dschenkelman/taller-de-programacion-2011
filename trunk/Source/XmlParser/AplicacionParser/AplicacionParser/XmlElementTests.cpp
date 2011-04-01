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
	printResult("testGetChildrenWithoutAnyChildThrowsException", testGetChildrenWithoutAnyChildThrowsException());
	printResult("testGetChildren", testGetChildren());
	printResult("testHasChildrenWithoutAnyChildReturnsFalse", testHasChildrenWithoutAnyChildReturnsFalse());
	printResult("testHasChildrenWithChildReturnsTrue", testHasChildrenWithChildReturnsTrue());

	int leaks = _CrtDumpMemoryLeaks();
	printLeaks(leaks);
}

bool XmlElementTests::initialConstructionTest(void) {
	XmlElement my_test("my_testing_element",123456,789012);
	if (my_test.getName()!="my_testing_element") {
		return false;
	}
	return true;
}

bool XmlElementTests::testGetChildren(void) {
	XmlElement xmlElement("Name", 1, 100);
	
	XmlElement child1("Child 1", 2, 99);
	XmlElement child2("Child 2", 3, 98);
	XmlElement child3("Child 3", 4, 97);

	xmlElement.addChild(child1);
	xmlElement.addChild(child2);
	xmlElement.addChild(child3);

	List<XmlElement> xmlElementChildren = xmlElement.getChildren();

	for(size_t i = 0; i < xmlElementChildren.length(); i++) {
	
		if(!(xmlElementChildren.at(i).getName() == "Child 1" ||
			xmlElementChildren.at(i).getName() == "Child 2" ||
			xmlElementChildren.at(i).getName() == "Child 3")) {

				return false;
		}
	}	

	return true;
}

bool XmlElementTests::testGetChildrenWithoutAnyChildThrowsException(void) {
	XmlElement xmlElement("Name", 1, 100);

	try {
		xmlElement.getChildren();
	}
	catch(exception& e) {
		return true;
	}

	return false;
}

bool XmlElementTests::testHasChildrenWithoutAnyChildReturnsFalse()
{
	XmlElement xmlElement("Name", 1, 20);

	bool result = xmlElement.hasChildren();

	if (!result)
	{
		return true;
	}

	return false;
}

bool XmlElementTests::testHasChildrenWithChildReturnsTrue()
{
	XmlElement xmlElement("Name", 1, 30);
	XmlElement xmlElementChild("Child", 1, 29);

	xmlElement.addChild(xmlElementChild);

	bool result = xmlElement.hasChildren();

	if(result)
	{
		return true;
	}

	return false;
}

XmlElementTests::~XmlElementTests(void)
{
}
