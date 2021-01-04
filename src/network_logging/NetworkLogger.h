#pragma once

#include <ESP8266WebServer.h>
#include <Print.h>
#include <RingBuf.h>
#include <memory>

class NetworkLogger : public Print
{
public:
    static constexpr size_t BUFFER_SIZE = 3000;

private:
    std::unique_ptr<ESP8266WebServer> _server;

    void HandleNotFound();
    void HandleRoot();
    void HandleUpdate();

    RingBuf<char, BUFFER_SIZE> _log_buffer;

public:
    void Start(uint16_t port);

    inline void Handle();

    void Idle(int duration_ms);

    size_t write(uint8_t data) override;
};