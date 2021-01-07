#pragma once

#include "Component.h"
#include <ArduinoLog.h>

enum class Operation
{
    Read,
    Write,
    Connect
};

template <Operation updater>
class Updater : public virtual Component
{
public:
    virtual ~Updater() = default;
    virtual void Update() = 0;
};

class PinUpdater
{
private:
    std::vector<Updater<Operation::Read> *> _readers;
    std::vector<Updater<Operation::Write> *> _writers;
    std::vector<Updater<Operation::Connect> *> _connectors;

public:
    void Register(Updater<Operation::Read> &updater)
    {
        Log.notice("Adding read updater [%s].", updater.CName());
        this->_readers.push_back(&updater);
    }

    void Register(Updater<Operation::Write> &updater)
    {
        Log.notice("Adding write updater [%s].", updater.CName());
        this->_writers.push_back(&updater);
    }

    void Register(Updater<Operation::Connect> &updater)
    {
        Log.notice("Adding connect updater [%s].", updater.CName());
        this->_connectors.push_back(&updater);
    }

    void Update()
    {
        Log.notice("Updating readers.");
        for (auto reader : this->_readers)
        {
            reader->Update();
        }

        Log.notice("Updating connectors.");
        for (auto connector : this->_connectors)
        {
            connector->Update();
        }

        Log.notice("Updating writers.");
        for (auto writer : this->_writers)
        {
            writer->Update();
        }
    }
};