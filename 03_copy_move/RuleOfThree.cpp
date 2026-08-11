#include <cstddef>

class IntBuffer
{
public:
    IntBuffer(std::size_t size)
        : Size{ size }
        , Data{ new int[size] {} }
    {
    }

    IntBuffer(const IntBuffer& other)
        : Size{ other.Size }
        , Data{ new int[other.Size] }
    {
        for (std::size_t i = 0; i < Size; ++i)
        {
            Data[i] = other.Data[i];
        }
    }

    ~IntBuffer()
    {
        delete[] Data;
    }

private:
    std::size_t Size{};
    int* Data{};
};
