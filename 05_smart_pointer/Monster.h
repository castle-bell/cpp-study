#pragma once

#include <string>
class Monster
{
public:
	explicit Monster(std::string name);
	~Monster();

	void PrintName() const;

private:
	std::string Name;
};

