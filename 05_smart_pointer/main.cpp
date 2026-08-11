#include <iostream>
#include <memory>

#include "Monster.h"

void TestUniquePointer()
{
	auto monster = std::make_unique<Monster>("Slime");
	monster->PrintName();
	std::cout << "Leaving scope\n";
}

int main()
{
	TestUniquePointer();
	return 0;
}
