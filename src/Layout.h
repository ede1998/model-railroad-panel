#pragma once

#include "pins/Pcf8574Reader.h"
#include "pins/Pcf8574Writer.h"
#include "pins/PinUpdater.h"
#include "pins/PinConnector.h"
#include <vector>

class Layout
{
private:
    PinUpdater _updater;
    std::vector<OneToOnePinConnector> _oneToOneConnectors;
    LocalPcf8574Reader _reader0x20 = LocalPcf8574Reader(0x20);
    LocalPcf8574Reader _reader0x21 = LocalPcf8574Reader(0x21);
    LocalPcf8574Writer _writer0x22 = LocalPcf8574Writer(0x22);
    LocalPcf8574Writer _writer0x23 = LocalPcf8574Writer(0x23);

    void OneToOneWire(ReadPin& r, WritePin& w)
    {
        this->_oneToOneConnectors.push_back(OneToOnePinConnector(r,w));
    }

    void Wire()
    {
        this->OneToOneWire(this->_reader0x20.RequestPin(7), this->_writer0x23.RequestPin(2)); // W 1
        this->OneToOneWire(this->_reader0x20.RequestPin(2), this->_writer0x22.RequestPin(2)); // W 2
        this->OneToOneWire(this->_reader0x21.RequestPin(2), this->_writer0x23.RequestPin(6)); // W 3
        this->OneToOneWire(this->_reader0x20.RequestPin(3), this->_writer0x23.RequestPin(5)); // W 4
        this->OneToOneWire(this->_reader0x20.RequestPin(5), this->_writer0x22.RequestPin(3)); // W 5
        this->OneToOneWire(this->_reader0x21.RequestPin(6), this->_writer0x22.RequestPin(4)); // W 6
        this->OneToOneWire(this->_reader0x21.RequestPin(5), this->_writer0x23.RequestPin(3)); // W 7
        this->OneToOneWire(this->_reader0x21.RequestPin(4), this->_writer0x23.RequestPin(7)); // W 8
        this->OneToOneWire(this->_reader0x20.RequestPin(6), this->_writer0x22.RequestPin(0)); // W 9
        this->OneToOneWire(this->_reader0x21.RequestPin(3), this->_writer0x23.RequestPin(4)); // W 10
        this->OneToOneWire(this->_reader0x21.RequestPin(7), this->_writer0x22.RequestPin(6)); // W 11
        this->OneToOneWire(this->_reader0x20.RequestPin(4), this->_writer0x22.RequestPin(1)); // W 12
        // this->OneToOneWire(not there); // W 13
        this->OneToOneWire(this->_reader0x20.RequestPin(1), this->_writer0x22.RequestPin(7)); // W 14
        this->OneToOneWire(this->_reader0x20.RequestPin(0), this->_writer0x22.RequestPin(5)); // W 15
    }

    void Register()
    {
        for (auto &connector : this->_oneToOneConnectors)
        {
            this->_updater.Register(connector);
        }

        this->_updater.Register(this->_reader0x20);
        this->_updater.Register(this->_reader0x21);
        this->_updater.Register(this->_writer0x22);
        this->_updater.Register(this->_writer0x23);
    }

public:
    Layout()
    {
        this->Wire();
        this->Register();
    }

    void Run()
    {
        this->_updater.Update();
    }
};