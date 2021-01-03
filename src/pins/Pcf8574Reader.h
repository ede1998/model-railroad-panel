#pragma once

#include <assert.h>
#include "Pins.h"
#include "PinUpdater.h"
#include <array>
#include <cstddef>
#include <bitset>
#include <Adafruit_I2CDevice.h>

class Pcf8574Reader : public Updater<Operation::Read>
{
public:
    static constexpr size_t MAX_PINS = 8;

private:
    class Pcf8574ReadPin : public ReadPin
    {
    public:
        void SetValue(bool value)
        {
            if (value != _value)
            {
                Log.trace("Value of [%s] changed to [%T].\n", this->CName(), value);
            }
            this->_value = value;
        }

        void SetName(const std::string &name)
        {
            this->_name = name;
        }
    };

    std::array<Pcf8574ReadPin, MAX_PINS> _pins;

    void Update()
    {
        std::bitset<MAX_PINS> result = this->DoUpdate();

        for (size_t i = 0; i < MAX_PINS; ++i)
        {
            this->_pins[i].SetValue(result[i]);
        }
    }

protected:
    virtual std::bitset<MAX_PINS> DoUpdate() = 0;

    void UpdatePinNames()
    {
        auto i = 0;
        for (auto &pin : this->_pins)
        {
            char buffer[2];
            snprintf(buffer, 2, "%d", i);
            pin.SetName(this->_name + "_P" + buffer);
            ++i;
        }
    }

public:
    ReadPin &RequestPin(size_t pin_number)
    {
        assert(pin_number < MAX_PINS);
        return this->_pins[pin_number];
    }
};

class LocalPcf8574Reader : public Pcf8574Reader
{
private:
    Adafruit_I2CDevice _i2c_dev;

protected:
    std::bitset<Pcf8574Reader::MAX_PINS> DoUpdate() override
    {
        uint8_t buffer;
        this->_i2c_dev.read(&buffer, sizeof(buffer));
        Log.verbose("Read [%d] from I2C address [%x].\n", buffer, this->_i2c_dev.address());
        return {buffer};
    }

public:
    LocalPcf8574Reader(uint8_t address) : _i2c_dev(address)
    {
        char buffer[5];
        snprintf(buffer, 5, "%x", const_cast<Adafruit_I2CDevice &>(this->_i2c_dev).address());
        this->_name = "LocalPcf8574Reader" + std::string(buffer);
        this->UpdatePinNames();

        if (!this->_i2c_dev.begin())
        {
            Log.fatal("Did not find device at [%x].\n", this->_i2c_dev.address());
            while (true)
                ;
        }
        Log.notice("Device found at address [%x].\n", this->_i2c_dev.address());
    }
};