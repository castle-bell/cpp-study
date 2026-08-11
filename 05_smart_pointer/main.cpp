#include <iostream>
#include <memory>
#include <cassert>
#include <utility>

#include "Monster.h"

void TestUniquePointer()
{
	auto monster = std::make_unique<Monster>("Slime");
	monster->PrintName();
	std::cout << "Leaving scope\n";
}

void TestUniquePointerMove()
{
	auto first = std::make_unique<Monster>("Slime");
	auto moved = std::move(first);

	assert(!first);
	assert(moved);

	moved->PrintName();
}

int main()
{
	TestUniquePointer();
	TestUniquePointerMove();
	return 0;
}
