#pragma once

#include <utility>

template <typename T>
class Box
{
public:
	explicit Box(T value)
		: Value{std::move(value)}
	{
	}

	const T& Get() const
	{
		return Value;
	}

private:
	T Value;
};

