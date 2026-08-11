#include "ScopedFile.h"

#include <iostream>

int main()
{
	{
		ScopedFile file{"raii_test.txt"};
		if (!file.IsOpen())
		{
			return 1;
		}

		file.Write("RAII closes this file automatically.\n");
		std::cout << "Leaving inner scope\n";
	}

	std::cout << "Inner scope ended\n";
}
