#include "OwnershipLesson.h"
#include "Character.h"

#include <iostream>
#include <memory>
#include <utility>

namespace phase2::ownership
{
	void Test1()
	{
		auto sword{ std::make_unique<Weapon>() };
		sword->Name = "Sword";
		sword->AttackPower = 25;
		Character knight{ "Knight" };

		knight.Equip(std::move(sword));

		std::cout << std::boolalpha;
		std::cout << "Sword ownership moved: " << (sword == nullptr) << '\n';

		const Weapon* equippedWeapon{ knight.GetEquippedWeapon() };
		if (equippedWeapon != nullptr)
		{
			std::cout
				<< "Equipped weapon: " << equippedWeapon->Name << '\n'
				<< "Attack power: " << equippedWeapon->AttackPower << '\n';
		}
	}

	void Test2()
	{
		auto sword{ std::make_unique<Weapon>() };
		sword->Name = "Sword";
		sword->AttackPower = 25;
		Character knight{ "Knight" };

		knight.Equip(std::move(sword));

		const Weapon* oldWeapon{ knight.GetEquippedWeapon() };
		std::cout << "Old observer captured: " << (oldWeapon != nullptr) << '\n';

		auto axe{ std::make_unique<Weapon>() };
		axe->Name = "Axe";
		axe->AttackPower = 50;
		knight.Equip(std::move(axe));

		const Weapon* newWeapon{ knight.GetEquippedWeapon() };

		std::cout
			<< "Current Weapon: "
			<< newWeapon->Name
			<< '\n';
	}

	template <typename TCallable>
	void TestWrapper(TCallable&& test)
	{
		std::cout << "New Test Started\n";

		test();

		std::cout << "Test Finished\n\n";
	}

	void Run()
	{
		TestWrapper(Test1);
		TestWrapper(Test2);
	}
}
