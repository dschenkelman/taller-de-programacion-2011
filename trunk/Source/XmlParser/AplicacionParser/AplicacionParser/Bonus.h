#pragma once
#include "XmlElement.h"

class Bonus
{
	std::string tipo;
public:
	Bonus(XmlElement e);
	Bonus(std::string tipo);
	Bonus(void);
	std::string getTipo();
	~Bonus(void);
};
