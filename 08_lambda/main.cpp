#include <iostream>
#include <vector>
#include <algorithm>

void TestLambda1()
{
	auto monsterHPs = std::vector<int>{ 100, 80, 0, 120 };
	auto condition = [](int hp)
		{
			return hp <= 0;
		};
	
	auto found = std::find_if(monsterHPs.begin(), monsterHPs.end(), condition);

	if (found != monsterHPs.end())
	{
		std::cout << *found << '\n';
	}
}

void TestLambda2()
{
	const int minimumHP = 100;

	auto monsterHPs = std::vector<int>{ 100, 80, 0, 120 };
	auto condition = [minimumHP](int hp)
		{
			return hp < minimumHP;
		};

	auto found = std::find_if(monsterHPs.begin(), monsterHPs.end(), condition);

	if (found != monsterHPs.end())
	{
		std::cout << *found << '\n';
	}
}

int main()
{
	TestLambda1();
	TestLambda2();
	return 0;
}