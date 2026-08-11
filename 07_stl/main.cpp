#include <vector>
#include <algorithm>
#include <iostream>

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

int main()
{
	UseStlMethod();
	return 0;
}