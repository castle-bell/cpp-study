#include "Warrior.h"

#include <iostream>
#include <utility>

Warrior::Warrior(std::string name, int strength)
	: Character{std::move(name)}
	, Strength {strength}
{
	std::cout
		<< "Warrior: "
		<< Name
		<< " Spawned\n";
}

Warrior::~Warrior()
{
	std::cout
		<< "Warrior: "
		<< Name
		<< " Destroyed\n";
}

void Warrior::PrintStatus() const
{
	std::cout
		<< "Name: "
		<< Name
		<< '\n'
		<< "Strength: "
		<< Strength
		<< '\n';
}
