#pragma once

#include <assert.h>
#include "Pins.h"
#include "PinUpdater.h"
#include <array>
#include <cstddef>
#include <bitset>

template <class ParentPin, Operation operation>
class Pcf8574 : public Updater<operation>
{
public:
    static constexpr size_t MAX_PINS = 8;

protected:
    class Pcf8574Pin : public ParentPin
    {
    public:
        void SetName(const std::string &name)
        {
            this->_name = name;
        }
    };

    template <class Pin>
    void UpdatePinNames(std::array<Pin, MAX_PINS> &pins)
    {
        auto i = 0;
        for (auto &pin : pins)
        {
            char buffer[2];
            snprintf(buffer, 2, "%d", i);
            pin.SetName(this->_name + "_P" + buffer);
            ++i;
        }
    }

public:
    virtual ParentPin &RequestPin(size_t pin_number) = 0;
    virtual ~Pcf8574() = default;
};