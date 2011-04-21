#pragma once
#include <string>

class TexturaTests
{
public:
	TexturaTests(void);
	void printLeaks(int);
	void run(void);
	void printResult(std::string testName, bool result);
	bool testIsCreatedFromElementWithNameTextura(void);
	bool testHasErrorIfAttributeNameIsNotValid(void);
	bool testHasErrorIfItDoesNotHaveArchivoAttribute(void);
	bool testHasErrorIfItDoesNotHaveNombreAttribute(void);
	bool testBoundsAreZeroAndMaxIntWhenNotSpecified(void);
	bool testBoundsAreCorrectWhenSpecified(void);
	bool testBoundStringValuesAreNotConsidered(void);
	bool testBoundNegativeValuesAreNotConsidered(void);
	bool testRightOrBottomLowerThanLeftOrTopUseDefaults(void);
	bool testDefaultAlfaIsFF00FF(void);
	bool testGetsAlphaFromElementCorrectly(void);
	bool testAlphaWithoutSharpUsesDefaultDueToInvalidFormat(void);
	bool testAlphaWithInvalidHexCharacterUsesDefaultDueToInvalidFormat(void);
	bool testDefaultDeltaIsZero(void);
	bool testGetsDeltaFromAttribute(void);
	bool testNegativeDeltaUsesZeroAsDefault(void);
	bool testAlphabeticDeltaUsesZeroAsDefault(void);
	bool testDefaultRotarionIsZero(void);
	bool testGetsRotationFromAttribute(void);
	bool testNegativeRotationUsesZeroAsDefault(void);
	bool testRotationBiggerThan359UsesZeroAsDefault(void);
	bool testAlphabeticRotationUsesZeroAsDefault(void);
	~TexturaTests(void);
};
