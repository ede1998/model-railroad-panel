#pragma once

#include "PinUpdater.h"
#include "Pins.h"
#include <ArduinoLog.h>
#include <vector>
#include <algorithm>
#include <Arduino.h>

class OneToOnePinConnector : public Updater<Operation::Connect>
{
private:
    ReadPin *_read;
    WritePin *_write;
    bool _negate = false;

public:
    void Wire(ReadPin &read_pin, WritePin &write_pin, bool negate)
    {
        this->_read = &read_pin;
        this->_write = &write_pin;
        this->_negate = negate;
        Log.trace("Wired read pin [%s] to write pin [%s].", read_pin.CName(), write_pin.CName());
        this->_name = "OneToOneConnector(" + read_pin.Name() + "," + write_pin.Name() + ")";
    }

    void Update() override
    {
        auto read_value = this->_read->GetValue();
        auto value = this->_negate ? !read_value : read_value;
        Log.verbose("Updating value [%T] from reader [%s] to writer [%s].", value, this->_read->CName(), this->_write->CName());
        this->_write->SetValue(value);
    }
};

class ChangeObserverConnector : public Updater<Operation::Connect>
{
private:
    std::vector<bool> _previous_states;
    std::vector<ReadPin *> _read_pins;
    WritePin *_write_pin;
    unsigned long _on_duration_start = 0;
    static constexpr unsigned long TOTAL_ON_DURATION = 2000;
    static constexpr bool WRITE_PIN_VALUE_ENABLED = false;

    bool AnyStateChanged() const
    {
        size_t i = 0;
        auto pin_changed = [&i, this](const ReadPin *pin) {
            return pin->GetValue() != this->_previous_states[i++];
        };
        return std::any_of(this->_read_pins.begin(), this->_read_pins.end(), pin_changed);
    }

    void UpdateStates()
    {
        for (size_t i = 0; i < _read_pins.size(); ++i)
        {
            this->_previous_states[i] = this->_read_pins[i]->GetValue();
        }
    }

    void EnablePin()
    {
        Log.verbose("Trying to enable pin.");
        if (this->_on_duration_start == 0)
        {
            Log.notice("Enabling write pin for [%s].", this->CName());
            this->_on_duration_start = millis();
            this->_write_pin->SetValue(WRITE_PIN_VALUE_ENABLED);
        }
    }

    void DisablePin()
    {
        Log.verbose("Trying to disable pin.");
        auto time = millis();
        if (this->_on_duration_start + TOTAL_ON_DURATION <= time)
        {
            Log.notice("Disabling write pin for [%s].", this->CName());
            this->_write_pin->SetValue(!WRITE_PIN_VALUE_ENABLED);
            this->_on_duration_start = 0;
        }
    }

public:
    ChangeObserverConnector()
    {
        this->_name = "ChangeObserverConnector";
    }

    void AddReadPin(ReadPin &read_pin)
    {
        this->_read_pins.push_back(&read_pin);
        this->_previous_states.push_back(read_pin.GetValue());
        Log.trace("Added read pin [%s].", read_pin.CName());
    }

    void SetWritePin(WritePin &write_pin)
    {
        this->_write_pin = &write_pin;
        Log.trace("Set write pin [%s].", write_pin.CName());
    }

    void Update() override
    {
        Log.error("on_duration_start = [%l]", this->_on_duration_start);
        if (this->AnyStateChanged())
        {
            Log.notice("An observed state changed. Trying to enable write pin.");
            this->EnablePin();
        }
        else
        {
            DisablePin();
        }
        
        UpdateStates();
    }
};