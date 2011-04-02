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
	std::cout << "XmlElement Tests: Hubo " << leaks << " memory leaks." << endl << endl;
}

void XmlElementTests::run(void) {
	printResult("initialConstructionTest",initialConstructionTest());
	printResult("testGetChildrenWithoutAnyChildThrowsException", testGetChildrenWithoutAnyChildThrowsException());
	printResult("testGetChildren", testGetChildren());
	printResult("testGetNameGetStartLineAndEndLineWorkCorrectly", testGetNameGetStartLineAndEndLineWorkCorrectly());
	printResult("testCopyConstructorWorksCorrectlyWithNoChildElements",testCopyConstructorWorksCorrectlyWithNoChildElements());
	printResult("testAssignmentOperatorWorkCorrectlyWithNoChildElements", testAssignmentOperatorWorkCorrectlyWithNoChildElements());
	printResult("testAssignmentOperatorWorkCorrectlyWithChildElements", testAssignmentOperatorWorkCorrectlyWithChildElements());
	printResult("testAssignmentOperatorWorkCorrectlyWithAttributes", testAssignmentOperatorWorkCorrectlyWithAttributes());

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

bool XmlElementTests::testGetNameGetStartLineAndEndLineWorkCorrectly(void)
{
	XmlElement element1("TestName", 1, 2);
	
	bool successCondition1 = element1.getName() == "TestName";
	bool successCondition2 = element1.getEndLine() == 2;
	bool successCondition3 = element1.getStartLine() == 1;

	return successCondition1 && successCondition2 && successCondition3;
}

bool XmlElementTests::testCopyConstructorWorksCorrectlyWithNoChildElements(void)
{
	XmlElement element1("TestName", 1, 2);
	XmlElement element2(element1);

	bool successCondition1 = element2.getName() == "TestName";
	bool successCondition2 = element2.getEndLine() == 2;
	bool successCondition3 = element2.getStartLine() == 1;

	return successCondition1 && successCondition2 && successCondition3;
}

bool XmlElementTests::testAssignmentOperatorWorkCorrectlyWithNoChildElements(void)
{
	XmlElement element1("TestName", 1, 2);
	XmlElement element2("t", 5, 6);
	element2 = element1;

	bool successCondition1 = element2.getName() == "TestName";
	bool successCondition2 = element2.getEndLine() == 2;
	bool successCondition3 = element2.getStartLine() == 1;

	return successCondition1 && successCondition2 && successCondition3;
}

bool XmlElementTests::testAssignmentOperatorWorkCorrectlyWithChildElements(void)
{
	XmlElement element1("TestName", 1, 2);
	XmlElement child("TestChild", 3, 4);
	XmlElement element2("t", 5, 6);
	element1.addChild(child);
	element2 = element1;

	bool successCondition1 = element2.getChildren().at(0).getName() == "TestChild";
	bool successCondition2 = element2.getChildren().at(0).getEndLine() == 4;
	bool successCondition3 = element2.getChildren().at(0).getStartLine() == 3;

	return successCondition1 && successCondition2 && successCondition3;
}

bool XmlElementTests::testAssignmentOperatorWorkCorrectlyWithAttributes(void)
{
	XmlElement element1("TestName", 1, 2);
	XmlAttribute attribute("Key", "Value");
	XmlElement element2("t", 5, 6);
	element1.addAttribute(attribute);
	element2 = element1;

	element2.getValue("Key") == "Value";
	
	bool successCondition1 = element2.getValue("Key") == "Value";

	return successCondition1;
}

XmlElementTests::~XmlElementTests(void)
{
}
