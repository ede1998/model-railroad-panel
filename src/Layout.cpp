#include "Layout.h"

void Layout::CreateTurnouts()
{
    auto turnout = Turnout(1);
    turnout.SetPanelSwitch(this->_reader0x20.RequestPin(7));
    turnout.SetPanelLed(this->_writer0x23.RequestPin(2));
    this->_turnouts.push_back(turnout);

    turnout = Turnout(2);
    turnout.SetPanelSwitch(this->_reader0x20.RequestPin(2));
    turnout.SetPanelLed(this->_writer0x22.RequestPin(2));
    this->_turnouts.push_back(turnout);

    turnout = Turnout(3);
    turnout.SetPanelSwitch(this->_reader0x21.RequestPin(2));
    turnout.SetPanelLed(this->_writer0x23.RequestPin(6));
    this->_turnouts.push_back(turnout);

    turnout = Turnout(4);
    turnout.SetPanelSwitch(this->_reader0x20.RequestPin(3));
    turnout.SetPanelLed(this->_writer0x23.RequestPin(5));
    this->_turnouts.push_back(turnout);

    turnout = Turnout(5);
    turnout.SetPanelSwitch(this->_reader0x20.RequestPin(5));
    turnout.SetPanelLed(this->_writer0x22.RequestPin(3));
    this->_turnouts.push_back(turnout);

    turnout = Turnout(6);
    turnout.SetPanelSwitch(this->_reader0x21.RequestPin(6));
    turnout.SetPanelLed(this->_writer0x22.RequestPin(4));
    this->_turnouts.push_back(turnout);

    turnout = Turnout(7);
    turnout.SetPanelSwitch(this->_reader0x21.RequestPin(5));
    turnout.SetPanelLed(this->_writer0x23.RequestPin(3));
    this->_turnouts.push_back(turnout);

    turnout = Turnout(8);
    turnout.SetPanelSwitch(this->_reader0x21.RequestPin(4));
    turnout.SetPanelLed(this->_writer0x23.RequestPin(7));
    this->_turnouts.push_back(turnout);

    turnout = Turnout(9);
    turnout.SetPanelSwitch(this->_reader0x20.RequestPin(6));
    turnout.SetPanelLed(this->_writer0x22.RequestPin(0));
    this->_turnouts.push_back(turnout);

    turnout = Turnout(10);
    turnout.SetPanelSwitch(this->_reader0x21.RequestPin(3));
    turnout.SetPanelLed(this->_writer0x23.RequestPin(4));
    this->_turnouts.push_back(turnout);

    turnout = Turnout(11);
    turnout.SetPanelSwitch(this->_reader0x21.RequestPin(7));
    turnout.SetPanelLed(this->_writer0x22.RequestPin(6));
    this->_turnouts.push_back(turnout);

    turnout = Turnout(12);
    turnout.SetPanelSwitch(this->_reader0x20.RequestPin(4));
    turnout.SetPanelLed(this->_writer0x22.RequestPin(1));
    this->_turnouts.push_back(turnout);

    turnout = Turnout(13);
    turnout.SetPanelSwitch(this->_reader0x20.RequestPin(1));
    turnout.SetPanelLed(this->_writer0x22.RequestPin(7));
    this->_turnouts.push_back(turnout);

    turnout = Turnout(14);
    turnout.SetPanelSwitch(this->_reader0x20.RequestPin(0));
    turnout.SetPanelLed(this->_writer0x22.RequestPin(5));
    this->_turnouts.push_back(turnout);
}