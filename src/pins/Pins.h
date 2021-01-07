#pragma once

#include "Component.h"

class ReadPin : public virtual Component
{
protected:
    bool _value = false;

public:
    bool GetValue() const
    {
        return this->_value;
    }
};

class WritePin : public virtual Component
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