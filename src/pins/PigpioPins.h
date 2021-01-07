#pragma once

#include "pigpio-remote/PiConnection.h"
#include "pigpio-remote/BasicIo.h"
#include "Pins.h"
#include <ArduinoLog.h>
#include "PinUpdater.h"

class PigpioPin
{
protected:
    const unsigned int _pin_number;
    pigpio_remote::BasicIo _basic_io;

    PigpioPin(pigpio_remote::PiConnection &connection, unsigned int pin_number, bool is_reader) : _pin_number(pin_number), _basic_io(connection)
    {
        using namespace pigpio_remote;
        auto mode = is_reader ? GpioMode::PI_INPUT : GpioMode::PI_OUTPUT;
        auto result = this->_basic_io.SetMode(this->_pin_number, mode);
        if (result != PigpioError::PI_OK)
        {
            Log.error("Set mode failed with error code [%d].", static_cast<pigpio_remote::PigpioError>(result));
            while (true)
            {
                delay(10);
            }
        }

        if (is_reader)
        {
            Log.verbose("Configuring pull up for reader.");
            auto result = this->_basic_io.SetPullUpDown(this->_pin_number, GpioPullUpDown::PI_PUD_UP);
            if (result != PigpioError::PI_OK)
            {
                Log.error("Setting pull up failed with error code [%d].", static_cast<pigpio_remote::PigpioError>(result));
                while (true)
                {
                    delay(10);
                }
            }
        }
    }

public:
    unsigned int GetPinNumber() const
    {
        return this->_pin_number;
    }
};

class PigpioWritePin : public WritePin, public Updater<Operation::Write>, public PigpioPin
{
public:
    PigpioWritePin(pigpio_remote::PiConnection &connection, unsigned int pin_number)
        : PigpioPin(connection, pin_number, false)
    {
        char buffer[3];
        snprintf(buffer, sizeof(buffer), "%d", pin_number);
        this->_name = "PigpioWritePin" + std::string(buffer);
    }

    void Update() override
    {
        if (!this->_valueChanged)
        {
            Log.verbose("Value of pin [%s] not changed. No need to update.", this->CName());
            return;
        }

        auto level = this->_value ? pigpio_remote::GpioLevel::PI_HIGH : pigpio_remote::GpioLevel::PI_LOW;
        auto result = this->_basic_io.Write(this->_pin_number, level);
        if (result != pigpio_remote::PigpioError::PI_OK)
        {
            Log.warning("Could not update pin [%s] to level [%d]. Error code [%d].", this->CName(), level, static_cast<pigpio_remote::PigpioError>(result));
        }
    }
};

class PigpioReadPin : public ReadPin, public Updater<Operation::Read>, public PigpioPin
{
public:
    PigpioReadPin(pigpio_remote::PiConnection &connection, unsigned int pin_number)
        : PigpioPin(connection, pin_number, true)
    {
        char buffer[3];
        snprintf(buffer, sizeof(buffer), "%d", pin_number);
        this->_name = "PigpioReadPin" + std::string(buffer);
    }

    void Update() override
    {
        auto result = this->_basic_io.Read(this->_pin_number);
        if (result.Error != pigpio_remote::PigpioError::PI_OK)
        {
            Log.warning("Could not read pin [%s]. Error code [%d].", this->CName(), static_cast<pigpio_remote::PigpioError>(result.Error));
            return;
        }

        auto level = (*result.Value) == pigpio_remote::GpioLevel::PI_LOW ? false : true;
        Log.notice("Read level [%T] for pin [%s].", level, this->CName());
        this->_value = level;
    }
};

template <class Pin>
class PigpioPinSet
{
    static_assert(std::is_same<Pin, PigpioReadPin>::value || std::is_same<Pin, PigpioWritePin>::value,
                  "Template argument pin must be PigpioWritePin or PigpioReadPin.");

private:
    std::vector<Pin> _pins;
    pigpio_remote::PiConnection &_connection;

public:
    PigpioPinSet(pigpio_remote::PiConnection &connection)
        : _connection(connection)
    {
    }

    void Add(std::initializer_list<unsigned int> pins)
    {
        this->_pins.reserve(this->_pins.size() + pins.size());
        for (auto pin : pins)
        {
            this->_pins.emplace_back(this->_connection, pin);
        }
    }

    void Register(PinUpdater &updater)
    {
        for (auto &pin : this->_pins)
        {
            updater.Register(pin);
        }
    }

    Pin &operator[](unsigned int pin_number)
    {
        for (auto &pin : this->_pins)
        {
            if (pin.GetPinNumber() == pin_number)
            {
                return pin;
            }
        }

        Log.error("No pin with number [%d].", pin_number);
        return this->_pins[0];
    }

    Pin *GetPin(unsigned int pin_number)
    {
        for (auto &pin : this->_pins)
        {
            if (pin.GetPinNumber() == pin_number)
            {
                return pin;
            }
        }

        Log.warning("No pin with number [%d].", pin_number);
        return nullptr;
    }
};