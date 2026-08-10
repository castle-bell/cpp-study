#include <iostream>
#include <string>

class Player
{
public:
	Player(
		const std::string& name,
		int level,
		int hp,
		float attack,
		bool alive)
		: Name{name},
		Level{level},
		HP{ hp },
		Attack{attack},
		Alive{alive}
	{
	}

	void Print() const
	{
		std::cout
			<< "Name: " << Name << '\n'
			<< "Level: " << Level << '\n'
			<< "HP: " << HP << '\n'
			<< "Attack: " << Attack << '\n'
			<< "Alive: " << std::boolalpha << Alive << '\n';
	}

private:
	std::string Name;
	int Level;
	int HP;
	float Attack;
	bool Alive;
};

Player CreatePlayer(const std::string& name, int level)
{
	return Player(
		name,
		level,
		100,
		25.5f,
		true
	);
}

int main()
{
	std::cout << "Hello, C++!" << std::endl;

	std::string name;
	int level{};

	if (!(std::cin >> name >> level))
	{
		std::cerr << "Invalid input\n";
		return 1;
	}

	Player player = CreatePlayer(name, level);
	player.Print();

	return 0;
}
