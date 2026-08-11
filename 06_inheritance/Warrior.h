#pragma once

#include "Character.h"
#include <string>

class Warrior : public Character
{
public:
	Warrior(std::string name, int strength);
	~Warrior();

	void PrintStatus() const;

private:
	int Strength;
};

