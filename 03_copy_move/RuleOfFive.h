#pragma once

#include <cstddef>

namespace rule_of_five
{
class IntBuffer
{
public:
    explicit IntBuffer(std::size_t size);
    IntBuffer(const IntBuffer& other);
    IntBuffer& operator=(const IntBuffer& other);
    IntBuffer(IntBuffer&& other) noexcept;
    IntBuffer& operator=(IntBuffer&& other) noexcept;
    ~IntBuffer();

    void Set(std::size_t index, int value);
    [[nodiscard]] int Get(std::size_t index) const;
    [[nodiscard]] std::size_t GetSize() const;

private:
    std::size_t Size{};
    int* Data{};
};
}
