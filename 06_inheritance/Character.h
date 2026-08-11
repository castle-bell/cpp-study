#pragma once

#include <string>

class Character
{
public:
    explicit Character(std::string name);
    virtual ~Character();

    virtual void Attack() const;

protected:
    std::string Name;
};