#pragma once

#include <string>

#include "ECharacterState.h"

namespace phase2::data_model
{
	struct FCharacterData
	{
		std::string Name;
		int Level{ 1 };
		float Health{ 100.0f };
		ECharacterState State{ ECharacterState::Idle };
	};
}
