#include "Warrior.h"
#include <memory>

void TestWarrior()
{
	Warrior warrior{ "Warrior", 10 };
	warrior.PrintStatus();
}

void TestWarriorAttack()
{
	std::unique_ptr<Character> character = std::make_unique<Warrior>("Warrior", 10);
	character->Attack();
}

int main()
{
	TestWarrior();
	TestWarriorAttack();
	return 0;
}