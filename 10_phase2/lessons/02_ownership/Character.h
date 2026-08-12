#pragma once

#include <memory>
#include <string>

#include "Weapon.h"

namespace phase2::ownership
{
	class Character
	{
	public:
		explicit Character(std::string name);

		void Equip(std::unique_ptr<Weapon> weapon);
		const Weapon* GetEquippedWeapon() const noexcept;

	private:
		std::string Name;
		std::unique_ptr<Weapon> EquippedWeapon;
	};
}

