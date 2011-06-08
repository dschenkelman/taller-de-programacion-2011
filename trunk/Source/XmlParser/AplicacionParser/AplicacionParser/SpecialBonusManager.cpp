#include "StdAfx.h"
#include "SpecialBonusManager.h"
#include <stdlib.h>
#include <time.h>

SpecialBonusManager::SpecialBonusManager(void) : totalProbability(0), validBonus(false)
{
}

void SpecialBonusManager::addBonusType(TipoBonus& tipoBonus)
{
	if (tipoBonus.getNombre() == "alimento" || tipoBonus.getNombre() == "alimentoEspecial")
	{
		return;
	}

	this->totalProbability += tipoBonus.getProbabilidad();
	this->bonusTypes.add(tipoBonus);
}

void SpecialBonusManager::selectBonus(void)
{
	srand(time(NULL));
	int number = rand() % this->totalProbability;
	int sum = 0;
	int i = 0;

	while(sum <= number)
	{
		sum += this->bonusTypes.at(i).getProbabilidad();
		i++;
	}

	if (this->bonusTypes.at(i - 1).getApariciones() > 0)
	{
		this->bonusTypes.at(i - 1).decreaseApariciones();
		this->selectedBonus = this->bonusTypes.at(i - 1);
		this->validBonus = true;
	}
	else
	{
		this->validBonus = false;
	}
}

TipoBonus& SpecialBonusManager::getSelectedBonus(void)
{
	return this->selectedBonus;
}

bool SpecialBonusManager::isSelectedBonusValid()
{
	return this->validBonus;
}

SpecialBonusManager::~SpecialBonusManager(void)
{
}
