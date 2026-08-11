#include "ScopedFile.h"

#include <iostream>

void WriteReport(const char* path, bool stopEarly)
{
	ScopedFile file{path};
	if (!file.IsOpen())
	{
		return;
	}

	file.Write("Report started\n");

	if (stopEarly)
	{
		return;
	}

	file.Write("Report completed\n");
}

void TestEarlyReturn()
{
	WriteReport("early_report.txt", true);
	WriteReport("complete_report.txt", false);
}

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

	TestEarlyReturn();
}
