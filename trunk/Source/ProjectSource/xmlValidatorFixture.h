#include <string>
using namespace std;

#pragma once
class xmlValidatorFixture
{
public:
	xmlValidatorFixture(void);
	~xmlValidatorFixture(void);
	void run (void);
	void printResult(string testName, bool result);
	bool testValidatorReturnsTrueWithValidXml(void);
	bool testValidatorReturnsFalseWithNotClosingFinalElement(void);
	bool testValidatorReturnsFalseWithNotOpeningInitialElement(void);
	bool testValidatorReturnsFalseWithNotClosingElementInTheMiddle(void);
	bool testValidatorReturnsFalseWithNoClosingQuote(void);
	bool testValidatorReturnsFalseWithNoOpeningQuote(void);
	bool testValidatorReturnsFalseWithNotOpeningElementInTheMiddle(void);
	bool testValidatorReturnsFalseWithTwoConsecutiveClosingElements(void);
	bool testValidatorReturnsFalseWithTwoConsecutiveOpeningElements(void);
	bool testValidatorReturnsFalseWhenElementNameHasSpacesWhenOpeningTag(void);
	bool testValidatorReturnsFalseWhenElementNameHasNumericalCharacterWhenOpeningTag(void);
	bool testValidatorReturnsFalseWhenElementNameHasNonAlphabeticalCharacterOtherThanUnderscoreWhenOpeningTag(void);
	bool testValidatorReturnsTrueWhenElementNameHasUnderscoreAsFirstCharacter(void);
	bool testValidatorReturnsFalseWhenClosingElementDoesNotMatchOpeningElement(void);
	bool testValidatorReturnsFalseWhenClosingElementIsMissing(void);
	bool testValidatorReturnsFalseWhenOpeningElementIsMissing(void);
};