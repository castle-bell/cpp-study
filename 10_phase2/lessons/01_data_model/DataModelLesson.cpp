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

	void ApplyDamage(FCharacterData& character, float damage)
	{
		if (damage <= 0.0f)
		{
			return;
		}

		const float remainingHealth{ character.Health - damage };
		if (remainingHealth <= 0.0f)
		{
			character.Health = 0.0f;
			character.State = ECharacterState::Dead;
		}
		else
		{
			character.Health = remainingHealth;
		}
	}

	[[nodiscard]] bool TryApplyDamage(FCharacterData* target, float damage)
	{
		if (target == nullptr)
			return false;

		ApplyDamage(*target, damage);
		return true;
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

		if (TryApplyDamage(&newCharacter, 20.0f))
		{
			PrintCharacter(newCharacter);
		}

		FCharacterData* missingTarget{ nullptr };
		if (!TryApplyDamage(missingTarget, 20.0f))
		{
			std::cout << "No target to damage.\n\n";
		}

		ApplyDamage(knight, 200.0f);
		PrintCharacter(knight);
	}
}
