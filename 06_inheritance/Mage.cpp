#include "Mage.h"

#include <iostream>
#include <utility>

Mage::Mage(std::string name, int mana)
	: Character{std::move(name)}
	, Mana{ mana }
{
}

void Mage::Attack() const
{
	std::cout
		<< "Mage attacks with mana: "
		<< Mana
		<< '\n';
}
