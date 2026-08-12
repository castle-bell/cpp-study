#include "Character.h"

#include <utility>

namespace phase2::ownership
{
	Character::Character(std::string name)
		: Name{ std::move(name) }
	{
	}

	void Character::Equip(std::unique_ptr<Weapon> weapon)
	{
		EquippedWeapon = std::move(weapon);
	}

	const Weapon* Character::GetEquippedWeapon() const noexcept
	{
		return EquippedWeapon.get();
	}
}
