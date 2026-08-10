#include <iostream>
#include <string>

class CopyTracer
{
public:
	CopyTracer(const std::string& name)
		: Name{ name }
	{
		std::cout << "This is Original: " << name << '\n';
	}

	CopyTracer(const CopyTracer& other)
		: Name{ other.Name + " Copy" }
	{
		std::cout << "This is Copy From: " << other.Name << '\n';
	}

	~CopyTracer()
	{
		std::cout << "Destroyed: " << Name << '\n';
	}

	const std::string& GetName() const
	{
		return Name;
	}

private:
	std::string Name;
};

int main()
{
	CopyTracer original{ "Original" };
	CopyTracer copy = original;
}