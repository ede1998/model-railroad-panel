#pragma once

#include <assert.h>
#include "Pins.h"
#include "PinUpdater.h"
#include <array>
#include <algorithm>
#include <cstddef>
#include <bitset>
#include <Adafruit_I2CDevice.h>

class Pcf8574Writer : public Updater<Operation::Write>
{
public:
    static constexpr size_t MAX_PINS = 8;

private:
    class Pcf8574WritePin : public WritePin
    {
    public:
        bool GetValue() const
        {
            if (this->_valueChanged)
            {
                Log.trace("Write value for [%s] changed to [%T].\n", this->CName(), this->_value);
            }
            return this->_value;
        }

        bool GetValueChanged() const
        {
            return this->_valueChanged;
        }

        void SetName(const std::string& name)
        {
            this->_name = name;
        }
    };

    std::array<Pcf8574WritePin, MAX_PINS> _pins;

    void Update() override
    {
        bool noValueChanged = std::none_of(this->_pins.begin(), this->_pins.end(), [](const Pcf8574WritePin &pin) { return pin.GetValueChanged(); });

        if (noValueChanged)
        {
            Log.trace("No value for the writer changed. Not updating any pins.\n");
            return;
        }

        Log.trace("At least one value for the writer changed. Updating all pins.\n");
        std::bitset<MAX_PINS> data;
        for (size_t i = 0; i < MAX_PINS; ++i)
        {
            data[i] = this->_pins[i].GetValue();
            this->_pins[i].Update();
        }

        this->DoUpdate(data);
    }

protected:
    virtual void DoUpdate(const std::bitset<MAX_PINS> &data) = 0;

    void UpdatePinNames()
    {
        auto i = 0;
        for (auto& pin : this->_pins)
        {
            char buffer[2];
            snprintf(buffer, 2, "%d", i);
            pin.SetName(this->_name + "_P" + buffer);
            ++i;
        }
    }
public:
    WritePin& RequestPin(size_t pin_number)
    {
        assert(pin_number < MAX_PINS);
        return this->_pins[pin_number];
    }
};

class LocalPcf8574Writer : public Pcf8574Writer
{
private:
    Adafruit_I2CDevice _i2c_dev;

protected:
    void DoUpdate(const std::bitset<MAX_PINS> &data) override
    {
        uint8_t buffer = data.to_ulong();
        this->_i2c_dev.write(&buffer, sizeof(buffer));
        Log.verbose("Wrote [%d] to address [%x].\n", buffer, this->_i2c_dev.address());
    }

public:
    LocalPcf8574Writer(uint8_t address) : _i2c_dev(address)
    {
        char buffer[5];
        snprintf(buffer, 5, "%x", address);
        this->_name = "LocalPcf8574Writer" + std::string(buffer);
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