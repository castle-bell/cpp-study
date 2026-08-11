#include "DataModelLesson.h"
#include "FCharacterData.h"

#include <iostream>

namespace phase2::data_model
{
	const char* ToString(ECharacterState state)
	{
		switch (state)
		{
		case ECharacterState::Idle:
			return "Idle";

		case ECharacterState::Attacking:
			return "Attacking";

		case ECharacterState::Dead:
			return "Dead";
		}

		return "Unknown";
	}

	void PrintCharacter(const FCharacterData& data)
	{
		std::cout
			<< "Name: " << data.Name << '\n'
			<< "Level: " << data.Level << '\n'
			<< "Health: " << data.Health << '\n'
			<< "State: " << ToString(data.State) << "\n\n";
	}

	void Run()
	{
		std::cout << "01_data_model is ready.\n";

		FCharacterData newCharacter{};
		newCharacter.Name = "New Recruit";

		FCharacterData knight{
			"Knight",
			10,
			150.0f,
			ECharacterState::Attacking
		};

		PrintCharacter(newCharacter);
		PrintCharacter(knight);
	}
}
