#include "Weapon.h"

#include <iostream>

namespace phase2::ownership
{
	Weapon::~Weapon()
	{
		std::cout << "Weapon destroyed: " << Name << '\n';
	}
}
