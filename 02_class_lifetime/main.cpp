#include <iostream>

class LifetimeTracer {
public: 
	LifetimeTracer()
	{
		std::cout << "Constructed" << '\n';
	}

	~LifetimeTracer()
	{
		std::cout << "Destroyed" << '\n';
	}
};

class Equipment {
public:
	Equipment()
	{
		std::cout << "Equip Constructed" << '\n';
	}

	~Equipment()
	{
		std::cout << "Equip Destroyed" << '\n';
	}
};

class Player {
public:
	Player()
	{
		std::cout << "Player Constructed" << '\n';
	}

	~Player()
	{
		std::cout << "Player Destroyed" << '\n';
	}

private:
	Equipment Equip;
};

int main()
{
	std::cout << "Before scope" << '\n';
	{
		LifetimeTracer tracer{};
	}
	std::cout << "After scope" << '\n';

	{
		Player player{};
	}

	return 0;
}