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

void TestSharedPointer()
{
	auto first = std::make_shared<Monster>("Goblin");
	assert(first.use_count() == 1);

	{
		auto second = first;
		assert(first.use_count() == 2);
		assert(second.use_count() == 2);

		second->PrintName();
	}

	assert(first.use_count() == 1);
}

void TestWeakPointer()
{
	std::weak_ptr<Monster> observer;

	{
		auto owner = std::make_shared<Monster>("Skeleton");
		observer = owner;
		assert(!observer.expired());

		auto locked = observer.lock();
		assert(locked);
		locked->PrintName();
	}

	assert(observer.expired());
	assert(!observer.lock());
}

int main()
{
	TestUniquePointer();
	TestUniquePointerMove();
	TestSharedPointer();
	TestWeakPointer();
	return 0;
}
