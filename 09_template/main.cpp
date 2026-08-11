#include "Box.h"

#include <string>
#include <iostream>

template <typename T>
T GetMax(T T1, T T2)
{
	return T1 > T2 ? T1 : T2;
}

void TestBox()
{
	Box<int> levelBox{ 10 };
	Box<std::string> nameBox{ "Slime" };

	std::cout
		<< "Level: "
		<< levelBox.Get()
		<< '\n'
		<< "Name: "
		<< nameBox.Get()
		<< '\n';
}

int main()
{
	auto max1 = GetMax(1, 2);
	auto max2 = GetMax(1.0f, 2.0f);
	TestBox();
	return 0;
}
