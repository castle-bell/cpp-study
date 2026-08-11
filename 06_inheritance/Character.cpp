#include "Character.h"

#include <iostream>
#include <utility>

Character::Character(std::string name)
	: Name{ std::move(name) }
{
	std::cout << "Character: " << Name << " Spawned\n";
}

Character::~Character()
{
	std::cout
		<< "Character: "
		<< Name
		<< " Destroyed\n";
}

void Character::Attack() const
{
	std::cout
		<< "Character Attacked";
}