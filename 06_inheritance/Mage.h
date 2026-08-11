#pragma once

#include "Character.h"
#include <string>

class Mage : public Character
{
public:
	Mage(std::string name, int mana);
	void Attack() const override;

private:
	int Mana;
};

