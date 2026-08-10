#include <iostream>
#include <string>

class Player
{
public:
	Player(
		std::string name,
		int level,
		int hp,
		float attack,
		bool alive)
	{
		Name = name;
		Level = level;
		HP = hp;
		Attack = attack;
		Alive = alive;
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

void PrintPlayer()
{
	Player player1{
		"Player",
		10,
		100,
		25.5f,
		true
	};

	player1.Print();
}


int main()
{
	std::cout << "Hello, C++!" << std::endl;
	PrintPlayer();
	return 0;
}
