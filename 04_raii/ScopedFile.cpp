#include "ScopedFile.h"

#include <iostream>

ScopedFile::ScopedFile(const char* path)
{
	const errno_t result = fopen_s(
		&File,
		path,
		"w"
	);

	if (result != 0)
	{
		File = nullptr;
		std::cout << "File open failed\n";
		return;
	}

	std::cout << "File opened\n";
}

ScopedFile::ScopedFile(ScopedFile&& other) noexcept
	: File{other.File}
{
	other.File = nullptr;
}

ScopedFile::~ScopedFile()
{
	if (File != nullptr)
	{
		std::fclose(File);
		File = nullptr;
		std::cout << "File closed\n";
	}
}

void ScopedFile::Write(const char* text)
{
	if (File != nullptr)
	{
		std::fputs(text, File);
	}
}

bool ScopedFile::IsOpen() const noexcept
{
	return File != nullptr;
}

