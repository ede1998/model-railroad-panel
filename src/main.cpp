/**
 * Blink
 *
 * Turns on an LED on for one second,
 * then off for one second, repeatedly.
 */
#include "Arduino.h"
#include <ESP8266WiFi.h> //https://github.com/esp8266/Arduino

//needed for library
#include <DNSServer.h>
#include <ESP8266WebServer.h>
#include <WiFiManager.h> //https://github.com/tzapu/WiFiManager
#include <string>
#include "pigpio-remote/BasicIo.h"
#include "pigpio-remote/PiConnection.h"
#include <ArduinoLog.h>
#include "Layout.h"


Layout* layout;

void printTimestamp(Print* _logOutput) {
  char c[12];
  sprintf(c, "%10lu ", millis());
  _logOutput->print(c);
}

void setup()
{
  Serial.begin(115200);

  Log.begin(LOG_LEVEL_TRACE, &Serial);
  Log.setPrefix(printTimestamp);

  WiFiManager wifiManager;
  wifiManager.autoConnect("AutoConnectAP");
  Log.notice("connected...yeey :)");

  layout = new Layout();
}

void loop()
{
  layout->Run();
  delay(2000);
}