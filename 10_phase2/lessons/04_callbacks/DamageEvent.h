#pragma once

#include <functional>
#include <vector>

namespace phase2::callbacks
{
	class DamageEvent
	{
	public:
		void Subscribe(std::function<void(int)> callback);
		void Broadcast(int damage) const;

	private:
		std::vector<std::function<void(int)>> Callbacks;
	};
}
