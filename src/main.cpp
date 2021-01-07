#include <Arduino.h>
#include <WiFiManager.h>
#include "pigpio-remote/BasicIo.h"
#include "pigpio-remote/PiConnection.h"
#include <ArduinoLog.h>
#include "Layout.h"
#include "network_logging/NetworkLogger.h"

Layout *layout;
NetworkLogger logger;
pigpio_remote::PiConnection pigpio_connection;

void printTimestamp(Print *_logOutput)
{
  char c[12];
  sprintf(c, "%10lu ", millis());
  _logOutput->print(c);
}

void printNewline(Print* _logOutput) {
  _logOutput->print('\n');
}

void setup()
{
  Serial.begin(115200);

  WiFiManager wifiManager;
  wifiManager.autoConnect("AutoConnectAP");

  logger.Start(80);

  Log.begin(LOG_LEVEL_NOTICE, &logger);
  Log.setPrefix(printTimestamp);
  Log.setSuffix(printNewline);

  Log.notice("connected...yeey :).");

  auto result = pigpio_connection.Connect("modellbahn");
  if (result != pigpio_remote::ConnectionError::SUCCESS)
  {
    Log.fatal("Could not connect to pigpio remote. Error code = [%d].", result);
    while (true)
    {
      delay(10);
    }
  }

  layout = new Layout(pigpio_connection);
}

void loop()
{
  layout->Run();
  logger.Idle(2000);
}