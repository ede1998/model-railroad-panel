#include "Layout.h"

void Layout::CreateTurnouts()
{
    auto turnout = Turnout(1);
    turnout.SetPanelSwitch(this->_reader0x20.RequestPin(7));
    turnout.SetPanelLed(this->_writer0x23.RequestPin(2));
    turnout.SetRemoteFeedback(this->_remote_read_pins[10]);
    turnout.SetRemoteMotor(this->_remote_write_pins[26]);
    this->_turnouts.push_back(turnout);

    turnout = Turnout(2);
    turnout.SetPanelSwitch(this->_reader0x20.RequestPin(2));
    turnout.SetPanelLed(this->_writer0x22.RequestPin(2));
    turnout.SetRemoteFeedback(this->_remote_read_pins[24]);
    turnout.SetRemoteMotor(this->_remote_write_pins[19]);
    this->_turnouts.push_back(turnout);

    turnout = Turnout(3);
    turnout.SetPanelSwitch(this->_reader0x21.RequestPin(2));
    turnout.SetPanelLed(this->_writer0x23.RequestPin(6));
    turnout.SetRemoteFeedback(this->_remote_read_pins[27]);
    turnout.SetRemoteMotor(this->_remote_write_pins[13]);
    this->_turnouts.push_back(turnout);

    turnout = Turnout(4);
    turnout.SetPanelSwitch(this->_reader0x20.RequestPin(3));
    turnout.SetPanelLed(this->_writer0x23.RequestPin(5));
    turnout.SetRemoteFeedback(this->_remote_read_pins[20]);
    turnout.SetRemoteMotor(this->_remote_write_pins[6]);
    this->_turnouts.push_back(turnout);

    turnout = Turnout(5);
    turnout.SetPanelSwitch(this->_reader0x20.RequestPin(5));
    turnout.SetPanelLed(this->_writer0x22.RequestPin(3));
    turnout.SetRemoteFeedback(this->_remote_read_pins[18]);
    turnout.SetRemoteMotor(this->_remote_write_pins[5]);
    this->_turnouts.push_back(turnout);

    turnout = Turnout(6);
    turnout.SetPanelSwitch(this->_reader0x21.RequestPin(6));
    turnout.SetPanelLed(this->_writer0x22.RequestPin(4));
    turnout.SetRemoteFeedback(this->_remote_read_pins[14]);
    turnout.SetRemoteMotor(this->_remote_write_pins[8]);
    this->_turnouts.push_back(turnout);

    turnout = Turnout(7);
    turnout.SetPanelSwitch(this->_reader0x21.RequestPin(5));
    turnout.SetPanelLed(this->_writer0x23.RequestPin(3));
    turnout.SetRemoteFeedback(this->_remote_read_pins[15]);
    turnout.SetRemoteMotor(this->_remote_write_pins[11]);
    this->_turnouts.push_back(turnout);

    turnout = Turnout(8);
    turnout.SetPanelSwitch(this->_reader0x21.RequestPin(4));
    turnout.SetPanelLed(this->_writer0x23.RequestPin(7));
    turnout.SetRemoteFeedback(this->_remote_read_pins[22]);
    turnout.SetRemoteMotor(this->_remote_write_pins[9]);
    this->_turnouts.push_back(turnout);

    turnout = Turnout(9);
    turnout.SetPanelSwitch(this->_reader0x20.RequestPin(6));
    turnout.SetPanelLed(this->_writer0x22.RequestPin(0));
    turnout.SetRemoteFeedback(this->_remote_read_pins[16]);
    turnout.SetRemoteMotor(this->_writer_remote0x20.RequestPin(0));
    this->_turnouts.push_back(turnout);

    turnout = Turnout(10);
    turnout.SetPanelSwitch(this->_reader0x21.RequestPin(3));
    turnout.SetPanelLed(this->_writer0x23.RequestPin(4));
    turnout.SetRemoteFeedback(this->_remote_read_pins[21]);
    turnout.SetRemoteMotor(this->_writer_remote0x20.RequestPin(1));
    this->_turnouts.push_back(turnout);

    turnout = Turnout(11);
    turnout.SetPanelSwitch(this->_reader0x21.RequestPin(7));
    turnout.SetPanelLed(this->_writer0x22.RequestPin(6));
    turnout.SetRemoteFeedback(this->_remote_read_pins[4]);
    turnout.SetRemoteMotor(this->_writer_remote0x20.RequestPin(2));
    this->_turnouts.push_back(turnout);

    turnout = Turnout(12);
    turnout.SetPanelSwitch(this->_reader0x20.RequestPin(4));
    turnout.SetPanelLed(this->_writer0x22.RequestPin(1));
    turnout.SetRemoteFeedback(this->_remote_read_pins[12]);
    turnout.SetRemoteMotor(this->_writer_remote0x20.RequestPin(3));
    this->_turnouts.push_back(turnout);

    turnout = Turnout(14);
    turnout.SetPanelSwitch(this->_reader0x20.RequestPin(1));
    turnout.SetPanelLed(this->_writer0x22.RequestPin(7));
    turnout.SetRemoteFeedback(this->_remote_read_pins[17]);
    turnout.SetRemoteMotor(this->_writer_remote0x20.RequestPin(4));
    this->_turnouts.push_back(turnout);

    turnout = Turnout(15);
    turnout.SetPanelSwitch(this->_reader0x20.RequestPin(0));
    turnout.SetPanelLed(this->_writer0x22.RequestPin(5));
    turnout.SetRemoteFeedback(this->_remote_read_pins[23]);
    turnout.SetRemoteMotor(this->_writer_remote0x20.RequestPin(5));
    this->_turnouts.push_back(turnout);
}
