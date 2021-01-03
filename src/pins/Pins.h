#pragma once

#include <string>

class NamedPin
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

class ReadPin : public NamedPin
{
protected:
    bool _value = false;

public:
    bool GetValue() const
    {
        return this->_value;
    }
};

class WritePin : public NamedPin
{
protected:
    bool _value = false;
    bool _valueChanged = false;

public:
    void SetValue(bool value)
    {
        if (value == this->_value)
        {
            return;
        }
        this->_value = value;
        this->_valueChanged = true;
    }

    void Update()
    {
        this->_valueChanged = false;
    }
};