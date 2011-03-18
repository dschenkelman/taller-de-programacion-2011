#include "StdAfx.h"
#include "xmlValidator.h"
#include "xmlValidatorFixture.h"
#include <stack>
#include <iostream>


xmlValidatorFixture::xmlValidatorFixture(void)
{
}


xmlValidatorFixture::~xmlValidatorFixture(void)
{
}

void xmlValidatorFixture :: run (void)
{
	printResult("testValidatorReturnsTrueWithValidXml", testValidatorReturnsTrueWithValidXml());
	printResult("testValidatorReturnsFalseWithNotClosingFinalElement", testValidatorReturnsFalseWithNotClosingFinalElement());
	printResult("testValidatorReturnsFalseWithNotOpeningInitialElement", testValidatorReturnsFalseWithNotOpeningInitialElement());
	printResult("testValidatorReturnsFalseWithNotClosingElementInTheMiddle", testValidatorReturnsFalseWithNotClosingElementInTheMiddle());
	printResult("testValidatorReturnsFalseWithNotOpeningElementInTheMiddle", testValidatorReturnsFalseWithNotOpeningElementInTheMiddle());
	printResult("testValidatorReturnsFalseWithNoClosingQuote", testValidatorReturnsFalseWithNoClosingQuote());
	printResult("testValidatorReturnsFalseWithNoOpeningQuote", testValidatorReturnsFalseWithNoOpeningQuote());
	printResult("testValidatorReturnsFalseWithTwoConsecutiveClosingElements", testValidatorReturnsFalseWithTwoConsecutiveClosingElements());
	printResult("testValidatorReturnsFalseWithTwoConsecutiveOpeningElements", testValidatorReturnsFalseWithTwoConsecutiveOpeningElements());
	printResult("testValidatorReturnsFalseWhenElementNameHasSpacesWhenOpeningTag", testValidatorReturnsFalseWhenElementNameHasSpacesWhenOpeningTag());
	printResult("testValidatorReturnsFalseWhenElementNameHasNumericalCharacterWhenOpeningTag", testValidatorReturnsFalseWhenElementNameHasNumericalCharacterWhenOpeningTag());
	printResult("testValidatorReturnsFalseWhenElementNameHasNonAlphabeticalCharacterOtherThanUnderscoreWhenOpeningTag", testValidatorReturnsFalseWhenElementNameHasNonAlphabeticalCharacterOtherThanUnderscoreWhenOpeningTag());
	printResult("testValidatorReturnsTrueWhenElementNameHasUnderscoreAsFirstCharacter", testValidatorReturnsTrueWhenElementNameHasUnderscoreAsFirstCharacter());
	printResult("testValidatorReturnsFalseWhenClosingElementDoesNotMatchOpeningElement", testValidatorReturnsFalseWhenClosingElementDoesNotMatchOpeningElement());
}

void xmlValidatorFixture :: printResult(string testName, bool result)
{
	cout << (testName.append(result ? ": Passed\n" : ": Failed\n"));
}

bool xmlValidatorFixture :: testValidatorReturnsTrueWithValidXml(void)
{
	string xml = "<?xml version='1.0'?><note><to>Tove</to><from>Jani</from><heading>Reminder</heading><body>Don&quot;t forget me this weekend!</body></note>";
	xmlValidator* validator = new xmlValidator();
	bool isValid = validator->validate(xml);
	delete validator;
	return isValid;
}

bool xmlValidatorFixture :: testValidatorReturnsFalseWithNotClosingFinalElement(void)
{
	string xml = "<?xml version='1.0'?><note><to>Tove</to><from>Jani</from><heading>Reminder</heading><body>Don&quot;t forget me this weekend!</body></note";
	xmlValidator* validator = new xmlValidator();
	bool isValid = validator->validate(xml);
	delete validator;
	return !isValid;
}

bool xmlValidatorFixture :: testValidatorReturnsFalseWithNotOpeningInitialElement()
{
	string xml = "?xml version='1.0'?><note><to>Tove</to><from>Jani</from><heading>Reminder</heading><body>Don&quot;t forget me this weekend!</body></note";
	xmlValidator* validator = new xmlValidator();
	bool isValid = validator->validate(xml);
	delete validator;
	return !isValid;
}

bool xmlValidatorFixture :: testValidatorReturnsFalseWithNotClosingElementInTheMiddle()
{
	string xml = "<?xml version='1.0'?><note><to>Tove</to<from>Jani</from><heading>Reminder</heading><body>Don&quot;t forget me this weekend!</body></note>";
	xmlValidator* validator = new xmlValidator();
	bool isValid = validator->validate(xml);
	delete validator;
	return !isValid;
}

bool xmlValidatorFixture :: testValidatorReturnsFalseWithNotOpeningElementInTheMiddle()
{
	string xml = "<?xml version='1.0'?><note>to>Tove</to><from>Jani</from><heading>Reminder</heading><body>Don&quot;t forget me this weekend!</body></note>";
	xmlValidator* validator = new xmlValidator();
	bool isValid = validator->validate(xml);
	delete validator;
	return !isValid;
}

bool xmlValidatorFixture :: testValidatorReturnsFalseWithNoClosingQuote()
{
	string xml = "<?xml version=\"1.0?><note><to>Tove</to><from>Jani</from><heading>Reminder</heading><body>Don&quot;t forget me this weekend!</body></note>";
	xmlValidator* validator = new xmlValidator();
	bool isValid = validator->validate(xml);
	delete validator;
	return !isValid;
}

bool xmlValidatorFixture :: testValidatorReturnsFalseWithNoOpeningQuote()
{
	string xml = "<?xml version=1.0\"?><note><to>Tove</to><from>Jani</from><heading>Reminder</heading><body>Don&quot;t forget me this weekend!</body></note>";
	xmlValidator* validator = new xmlValidator();
	bool isValid = validator->validate(xml);
	delete validator;
	return !isValid;
}

bool xmlValidatorFixture :: testValidatorReturnsFalseWithTwoConsecutiveClosingElements()
{
	string xml = "<?xml version=\"1.0\"?><note><to>Tove</to>><from>Jani</from><heading>Reminder</heading><body>Don&quot;t forget me this weekend!</body></note>";
	xmlValidator* validator = new xmlValidator();
	bool isValid = validator->validate(xml);
	delete validator;
	return !isValid;
}

bool xmlValidatorFixture :: testValidatorReturnsFalseWithTwoConsecutiveOpeningElements()
{
	string xml = "<?xml version=\"1.0\"?><note><<to>Tove</to><from>Jani</from><heading>Reminder</heading><body>Don&quot;t forget me this weekend!</body></note>";
	xmlValidator* validator = new xmlValidator();
	bool isValid = validator->validate(xml);
	delete validator;
	return !isValid;
}

bool xmlValidatorFixture :: testValidatorReturnsFalseWhenElementNameHasSpacesWhenOpeningTag()
{
	string xml = "<?xml version=\"1.0\"?>< note><to>Tove</to><from>Jani</from><heading>Reminder</heading><body>Don&quot;t forget me this weekend!</body></note>";
	xmlValidator* validator = new xmlValidator();
	bool isValid = validator->validate(xml);
	delete validator;
	return !isValid;
}

bool xmlValidatorFixture :: testValidatorReturnsFalseWhenElementNameHasNumericalCharacterWhenOpeningTag()
{
	//source:http://www.w3.org/TR/xml/#NT-NameStartChar
	string xml = "<?xml version=\"1.0\"?><2note><to>Tove</to><from>Jani</from><heading>Reminder</heading><body>Don&quot;t forget me this weekend!</body></2note>";
	xmlValidator* validator = new xmlValidator();
	bool isValid = validator->validate(xml);
	delete validator;
	return !isValid;
}

bool xmlValidatorFixture :: testValidatorReturnsFalseWhenElementNameHasNonAlphabeticalCharacterOtherThanUnderscoreWhenOpeningTag()
{
	//source:http://www.w3.org/TR/xml/#NT-NameStartChar
	string xml = "<?xml version=\"1.0\"?><!note><to>Tove</to><from>Jani</from><heading>Reminder</heading><body>Don&quot;t forget me this weekend!</body></!note>";
	xmlValidator* validator = new xmlValidator();
	bool isValid = validator->validate(xml);
	delete validator;
	return !isValid;
}

bool xmlValidatorFixture :: testValidatorReturnsTrueWhenElementNameHasUnderscoreAsFirstCharacter()
{
	//source:http://www.w3.org/TR/xml/#NT-NameStartChar
	string xml = "<?xml version=\"1.0\"?><_note><to>Tove</to><from>Jani</from><heading>Reminder</heading><body>Don&quot;t forget me this weekend!</body></_note>";
	xmlValidator* validator = new xmlValidator();
	bool isValid = validator->validate(xml);
	delete validator;
	return isValid;
}

bool xmlValidatorFixture :: testValidatorReturnsFalseWhenClosingElementDoesNotMatchOpeningElement()
{
	string xml = "<?xml version=\"1.0\"?><note><to>Tove</to><from>Jani</from><heading>Reminder</heading><body>Don&quot;t forget me this weekend!</bodies></note>";
	xmlValidator* validator = new xmlValidator();
	bool isValid = validator->validate(xml);
	delete validator;
	return !isValid;
}

bool  xmlValidatorFixture :: testValidatorReturnsFalseWhenClosingElementIsMissing(void)
{
	string xml = "<?xml version=\"1.0\"?><note><to>Tove</to><from>Jani</from><heading>Reminder<body>Don&quot;t forget me this weekend!</body></note>";
	xmlValidator* validator = new xmlValidator();
	bool isValid = validator->validate(xml);
	delete validator;
	return !isValid;
}

bool xmlValidatorFixture::testValidatorReturnsFalseWhenOpeningElementIsMissing(void)
{
	string xml = "<?xml version=\"1.0\"?><note><to>Tove</to><from>Jani</from>Reminder</heading><body>Don&quot;t forget me this weekend!</body></note>";
	xmlValidator* validator = new xmlValidator();
	bool isValid = validator->validate(xml);
	delete validator;
	return !isValid;
}