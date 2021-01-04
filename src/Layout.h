#pragma once

#include "pins/Pcf8574Reader.h"
#include "pins/Pcf8574Writer.h"
#include "pins/PinUpdater.h"
#include "pins/PinConnector.h"
#include <vector>

class Turnout
{
private:
    ReadPin *_panel_switch;
    ReadPin *_remote_feedback;
    WritePin *_panel_led;
    WritePin *_remote_motor;

    // OneToOnePinConnector _feedback_connector;
    OneToOnePinConnector _switch_connector;

    int _turnout_number;

public:
    Turnout(int number) : _turnout_number(number) {}

    inline void SetPanelSwitch(ReadPin &pin) { this->_panel_switch = &pin; }
    inline void SetPanelLed(WritePin &pin) { this->_panel_led = &pin; }
    inline void SetRemoteFeedback(ReadPin &pin) { this->_remote_feedback = &pin; }
    inline void SetRemoteMotor(WritePin &pin) { this->_remote_motor = &pin; }

    inline int GetTurnoutNumber() const { return this->_turnout_number; }

    bool Wire()
    {
        Log.notice("Wiring turnout [%d].", this->_turnout_number);

        if (this->_panel_switch == nullptr || this->_panel_led == nullptr
            // || this->_remote_feedback == nullptr || this->_remote_motor == nullptr
            )
        {
            Log.error("Not all I/O configured.");
            return false;
        }

        // this->_feedback_connector.Wire(*this->_remote_feedback, *this->_panel_led);
        this->_switch_connector.Wire(*this->_panel_switch, *this->_panel_led);

        return true;
    }

    void Register(PinUpdater &updater)
    {
        updater.Register(this->_switch_connector);
        // updater.Register(this->_feedback_connector);
    }
};

class Layout
{
private:
    PinUpdater _updater;
    std::vector<Turnout> _turnouts;
    LocalPcf8574Reader _reader0x20 = LocalPcf8574Reader(0x20);
    LocalPcf8574Reader _reader0x21 = LocalPcf8574Reader(0x21);
    LocalPcf8574Writer _writer0x22 = LocalPcf8574Writer(0x22);
    LocalPcf8574Writer _writer0x23 = LocalPcf8574Writer(0x23);

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
        for (auto &turnout : this->_turnouts)
        {
            turnout.Register(this->_updater);
        }

        this->_updater.Register(this->_reader0x20);
        this->_updater.Register(this->_reader0x21);
        this->_updater.Register(this->_writer0x22);
        this->_updater.Register(this->_writer0x23);
    }

public:
    Layout()
    {
        this->CreateTurnouts();
        this->Wire();
        this->Register();
    }

    void Run()
    {
        this->_updater.Update();
    }
};