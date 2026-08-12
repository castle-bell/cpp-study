#include "OwnershipLesson.h"
#include "Character.h"

#include <iostream>
#include <memory>
#include <utility>

namespace phase2::ownership
{
	void Run()
	{
		auto sword{ std::make_unique<Weapon>(Weapon{ "Sword", 25 }) };
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
}
