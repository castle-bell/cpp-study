#include <vector>
#include <algorithm>
#include <iostream>
#include <string>
#include <unordered_map>

void UseStlMethod()
{
	auto levels = std::vector<int>{ 5, 10, 3, 20, 8 };
	std::sort(levels.begin(), levels.end());

	for (int level : levels)
	{
		std::cout
			<< "Level: "
			<< level
			<< '\n';
	}

	const auto found = std::find(levels.begin(), levels.end(), 10);

	if (found != levels.end())
	{
		std::cout << "Found: " << *found << '\n';
	}
}

void RemoveDeadMonsters()
{
	auto monsterHPs = std::vector<int>{100, 0, 80, 0, 120};
	const auto removedCount = std::erase(monsterHPs, 0);

	std::cout << "Removed: " << removedCount << '\n';

	for (int hp : monsterHPs)
	{
		std::cout << "HP: " << hp << '\n';
	}
}

void FindMonsterByName()
{
	auto monsterHPs = std::unordered_map<std::string, int>{
		{"Slime", 100},
		{"Orc", 250},
		{"Goblin", 80}
	};

	const auto found = monsterHPs.find("Orc");

	if (found != monsterHPs.end())
	{
		std::cout
			<< "Orc HP is "
			<< found->second
			<< '\n';
	}

	else
	{
		std::cout
			<< "Not Found";
	}


}

int main()
{
	UseStlMethod();
	RemoveDeadMonsters();
	FindMonsterByName();
	return 0;
}
