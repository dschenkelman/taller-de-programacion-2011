#pragma once
#include "TipoBonus.h"

class SpecialBonusManager
{
	int totalProbability;
	TipoBonus selectedBonus;
	List<TipoBonus> bonusTypes;
	bool validBonus;
public:
	SpecialBonusManager(void);
	void addBonusType(TipoBonus& tipoBonus);
	void selectBonus(void);
	bool isSelectedBonusValid(void);
	TipoBonus& getSelectedBonus(void);
	~SpecialBonusManager(void);
};
