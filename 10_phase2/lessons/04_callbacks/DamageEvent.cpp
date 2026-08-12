#include "DamageEvent.h"

#include <utility>

namespace phase2::callbacks
{
	void DamageEvent::Subscribe(std::function<void(int)> callback)
	{
		Callbacks.push_back(std::move(callback));
	}

	void DamageEvent::Broadcast(int damage) const
	{
		for (const auto& callback : Callbacks)
		{
			callback(damage);
		}
	}
}
