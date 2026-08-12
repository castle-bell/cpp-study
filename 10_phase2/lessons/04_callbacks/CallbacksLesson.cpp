#include "CallbacksLesson.h"
#include "DamageEvent.h"

#include <iostream>

namespace phase2::callbacks
{
	void Run()
	{
		std::cout << "04_callbacks is ready.\n";

		auto printDamage = [](int damage)
			{
				std::cout
					<< "Damage: "
					<< damage
					<< '\n';
			};

		auto printTwiceDamage = [](int damage)
			{
				std::cout
					<< "Twice Damage: "
					<< damage * 2
					<< '\n';
			};

		DamageEvent events{};

		events.Subscribe(printDamage);
		events.Subscribe(printTwiceDamage);

		events.Broadcast(10);
	}
}
