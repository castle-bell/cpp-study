#include <iostream>
#include <string>

class CopyTracer
{
public:
	CopyTracer(const std::string& name)
		: Name{name}
	{
		std::cout << "This is Original: " << name << '\n';
	}

	CopyTracer(const CopyTracer& other)
		: Name{other.Name}
	{
		std::cout << "Copy constructed from: " << other.Name << '\n';
	}

	CopyTracer& operator=(const CopyTracer& other)
	{
		Name = other.Name;
		std::cout << "Copy assigned from: " << other.Name << '\n';

		return *this;
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
	CopyTracer original{"Original"};
	CopyTracer copied{original};

	std::cout << std::boolalpha
		<< "Copied object is distinct: " << (&copied != &original) << '\n'
		<< "Copied value matches: " << (copied.GetName() == original.GetName()) << '\n';

	CopyTracer target{"Target"};
	const CopyTracer* targetAddress = &target;
	CopyTracer& assignmentResult = (target = original);

	std::cout
		<< "Target address unchanged: " << (targetAddress == &target) << '\n'
		<< "operator= returned target: " << (&assignmentResult == &target) << '\n'
		<< "Assigned value matches: " << (target.GetName() == original.GetName()) << '\n';
}
