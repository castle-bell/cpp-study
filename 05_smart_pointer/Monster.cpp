#include "Monster.h"

#include <iostream>
#include <utility>

Monster::Monster(std::string name)
	: Name{std::move(name)}
{
	std::cout << Name << " constructed\n";
}

Monster::~Monster()
{
	std::cout << Name << " destroyed\n";
}

void Monster::PrintName() const
{
	std::cout << "This Monster name is " << Name << '\n';
}
