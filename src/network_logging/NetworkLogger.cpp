#include "NetworkLogger.h"

#include <functional>
#include <sstream>

#include "logging-frame.h"

void NetworkLogger::HandleNotFound()
{
    this->_server->send(404, "text/plain", "Not found");
}

void NetworkLogger::HandleRoot()
{
    this->_server->send(200, "text/html", HTML_FILE);
}

void NetworkLogger::HandleUpdate()
{
    std::ostringstream stream;
    char data;

    while (this->_log_buffer.pop(data))
    {
        stream << data;
    }

    this->_server->sendHeader("Access-Control-Allow-Origin", "*");
    this->_server->sendHeader("Access-Control-Allow-Origin", "*");
    this->_server->send(200, "text/plain; charset=utf-8", stream.str().c_str());
}

void NetworkLogger::Start(uint16_t port)
{
    this->_server.reset(new ESP8266WebServer(port));

    this->_server->on("/", std::bind(&NetworkLogger::HandleRoot, this));
    this->_server->on("/update", std::bind(&NetworkLogger::HandleUpdate, this));
    this->_server->onNotFound(std::bind(&NetworkLogger::HandleNotFound, this));

    this->_server->begin();
}

void NetworkLogger::Idle(int duration_ms)
{
  auto wait_start = millis();

  while (millis() < wait_start + duration_ms)
  {
    this->Handle();
    delay(5);
  }
}

size_t NetworkLogger::write(uint8_t data) 
{
    if (this->_log_buffer.isFull())
    {
        char dummy;
        do
        {
            dummy = '\n';
            this->_log_buffer.pop(dummy);
        } while (dummy != '\n');
    }

    // Serial.printf("Received data [%d] = [%c].\n", data, data);

    this->_log_buffer.push(data);
    return sizeof(data);
}

void NetworkLogger::Handle()
{
    this->_server->handleClient();
}