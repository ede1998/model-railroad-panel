#pragma once

#include <string>

class Component
{
protected:
    std::string _name;

public:
    const std::string &Name() const
    {
        return this->_name;
    }

    const char *CName() const
    {
        return this->_name.c_str();
    }
};
