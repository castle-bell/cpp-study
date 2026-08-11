#include "Warrior.h"

void TestWarrior()
{
	Warrior warrior{ "Warrior", 10 };
	warrior.PrintStatus();
}

int main()
{
	TestWarrior();
	return 0;
}