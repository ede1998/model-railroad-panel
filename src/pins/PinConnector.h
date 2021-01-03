#pragma once

#include "PinUpdater.h"
#include "Pins.h"
#include <ArduinoLog.h>

class OneToOnePinConnector : public Updater<Operation::Connect>
{
private:
    ReadPin &_read;
    WritePin &_write;

public:
    OneToOnePinConnector(ReadPin &readPin, WritePin &writePin) : _read(readPin), _write(writePin)
    {
        Log.notice("Wired read pin [%s] to write pin [%s].\n", readPin.CName(), writePin.CName());
        this->_name = "OneToOneConnector(" + readPin.Name() + "," + writePin.Name() + ")";
    }

    void Update() override
    {
        auto value = this->_read.GetValue();
        Log.verbose("Updating value [%T] from reader [%s] to writer [%s].\n", value, this->_read.CName(), this->_write.CName());
        this->_write.SetValue(value);
    }
};