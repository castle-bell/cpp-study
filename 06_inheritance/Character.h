#pragma once

#include <string>

class Character
{
public:
    explicit Character(std::string name);
    ~Character();

protected:
    std::string Name;
};