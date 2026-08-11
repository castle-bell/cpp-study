#include "Warrior.h"
#include "Mage.h"
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

void TestPolymorphism()
{
	std::unique_ptr<Character> mage = std::make_unique<Mage>("Mage", 100);
	std::unique_ptr<Character> warrior = std::make_unique<Warrior>("Warrior", 10);

	mage->Attack();
	warrior->Attack();
}

int main()
{
	TestWarrior();
	TestWarriorAttack();
	TestPolymorphism();
	return 0;
}