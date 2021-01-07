#pragma once

#include "pins/Pins.h"
#include "pins/PinConnector.h"

class Turnout
{
private:
    ReadPin *_panel_switch;
    ReadPin *_remote_feedback;
    WritePin *_panel_led;
    WritePin *_remote_motor;

    OneToOnePinConnector _feedback_connector;
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
            || this->_remote_feedback == nullptr || this->_remote_motor == nullptr
            )
        {
            Log.error("Not all I/O configured.");
            return false;
        }

        this->_feedback_connector.Wire(*this->_remote_feedback, *this->_panel_led);
        this->_switch_connector.Wire(*this->_panel_switch, *this->_remote_motor);

        return true;
    }

    void Register(PinUpdater &updater)
    {
        updater.Register(this->_switch_connector);
        updater.Register(this->_feedback_connector);
    }
};
