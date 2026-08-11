#include "RuleOfFive.h"

namespace rule_of_five
{
IntBuffer::IntBuffer(std::size_t size)
    : Size{size}
    , Data{new int[size]{}}
{
}

IntBuffer::IntBuffer(const IntBuffer& other)
    : Size{other.Size}
    , Data{new int[other.Size]}
{
    for (std::size_t i = 0; i < Size; ++i)
    {
        Data[i] = other.Data[i];
    }
}

IntBuffer& IntBuffer::operator=(const IntBuffer& other)
{
    int* newData = new int[other.Size];
    for (std::size_t i = 0; i < other.Size; ++i)
    {
        newData[i] = other.Data[i];
    }

    delete[] Data;

    Size = other.Size;
    Data = newData;

    return *this;
}

IntBuffer::IntBuffer(IntBuffer&& other) noexcept
    : Size{other.Size}
    , Data{other.Data}
{
    other.Size = 0;
    other.Data = nullptr;
}

IntBuffer& IntBuffer::operator=(IntBuffer&& other) noexcept
{
    if (this == &other)
    {
        return *this;
    }

    int* oldData = Data;

    Size = other.Size;
    Data = other.Data;

    other.Size = 0;
    other.Data = nullptr;

    delete[] oldData;

    return *this;
}

IntBuffer::~IntBuffer()
{
    delete[] Data;
}

void IntBuffer::Set(std::size_t index, int value)
{
    Data[index] = value;
}

int IntBuffer::Get(std::size_t index) const
{
    return Data[index];
}

std::size_t IntBuffer::GetSize() const
{
    return Size;
}
}
