#pragma once

#include "pigpio-remote/PiConnection.h"
#include "pins/Pcf8574Reader.h"
#include "pins/Pcf8574Writer.h"
#include "pins/PinUpdater.h"
#include "pins/PigpioPins.h"
#include <vector>
#include "Turnout.h"

class Layout
{
private:
    PinUpdater _updater;
    std::vector<Turnout> _turnouts;

    LocalPcf8574Reader _reader0x20 = LocalPcf8574Reader(0x20);
    LocalPcf8574Reader _reader0x21 = LocalPcf8574Reader(0x21);
    LocalPcf8574Writer _writer0x22 = LocalPcf8574Writer(0x22);
    LocalPcf8574Writer _writer0x23 = LocalPcf8574Writer(0x23);

    PigpioPcf8574Writer _writer_remote0x20;
    PigpioPinSet<PigpioReadPin> _remote_read_pins;
    PigpioPinSet<PigpioWritePin> _remote_write_pins;

    void CreateTurnouts();

    void Wire()
    {
        for (auto &turnout : this->_turnouts)
        {
            auto success = turnout.Wire();
            if (!success)
            {
                Log.fatal("Invalid configuration for turnout [%d].", turnout.GetTurnoutNumber());
                while (true)
                {
                    delay(1000);
                }
            }
        }
    }

    void Register()
    {
        Turnout::RegisterTurnoutMaster(this->_updater);
        for (auto &turnout : this->_turnouts)
        {
            turnout.Register(this->_updater);
        }

        this->_updater.Register(this->_reader0x20);
        this->_updater.Register(this->_reader0x21);
        this->_updater.Register(this->_writer0x22);
        this->_updater.Register(this->_writer0x23);

        this->_updater.Register(this->_writer_remote0x20);
        this->_remote_read_pins.Register(this->_updater);
        this->_remote_write_pins.Register(this->_updater);
    }

public:
    Layout(pigpio_remote::PiConnection &connection)
        : _writer_remote0x20(connection, 0x20),
          _remote_read_pins(connection),
          _remote_write_pins(connection)
    {
        this->_remote_read_pins.Add({4, 10, 12, 14, 15, 16, 17, 18, 20, 21, 22, 23, 24, 27});
        this->_remote_write_pins.Add({5, 6, 8, 9, 11, 13, 19, 26});
        Turnout::SetTurnoutMasterWritePin(this->_remote_write_pins[26]);
        this->CreateTurnouts();
        this->Wire();
        this->Register();
    }

    void Run()
    {
        this->_updater.Update();
    }
};