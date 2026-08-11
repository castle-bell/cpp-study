#pragma once

#include <cstdio>

class ScopedFile
{
public:
    explicit ScopedFile(const char* path);
    ~ScopedFile();

    void Write(const char* text);
    [[nodiscard]] bool IsOpen() const noexcept;

    ScopedFile(const ScopedFile&) = delete;
    ScopedFile& operator=(const ScopedFile&) = delete;

private:
    std::FILE* File{};
};
