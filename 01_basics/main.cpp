#include <iostream>
#include <string>
#include <vector>

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
		HP{hp},
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

void TakeDamage(int& hp, int damage)
{
	hp -= damage;

	if (hp < 0)
	{
		hp = 0;
	}
}

void TestVector()
{
	std::vector<int> monsterHps{ 100, 80, 120, 50 };
	std::cout << "Count of Monsters: " << monsterHps.size() << "\n"
		<< "Hp of Second Monster: " << monsterHps[1] << "\n";
}

void TestForLoop()
{
	const std::vector<int> monsterHps{ 100, 80, 120, 50 };

	for (const int monsterHp : monsterHps)
	{
		std::cout << "Monster HP: " << monsterHp << '\n';
	}
}

int main()
{
	std::cout << "Hello, C++!\n";

	std::string name;
	int level{};

	if (!(std::cin >> name >> level))
	{
		std::cerr << "Invalid input\n";
		return 1;
	}

	Player player = CreatePlayer(name, level);
	player.Print();

	int currentHp{100};
	TakeDamage(currentHp, 30);
	std::cout << "Remaining HP: " << currentHp << '\n';

	TestVector();
	TestForLoop();

	return 0;
}
