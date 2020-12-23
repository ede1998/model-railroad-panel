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

// Set LED_BUILTIN if it is not defined by Arduino framework
// #define LED_BUILTIN 13

PiConnection pi;
BasicIo io(pi);

void setup()
{
  // initialize LED digital pin as an output.
  pinMode(LED_BUILTIN, OUTPUT);
  // put your setup code here, to run once:
  Serial.begin(115200);

  //WiFiManager
  //Local intialization. Once its business is done, there is no need to keep it around
  WiFiManager wifiManager;
  //reset saved settings
  //wifiManager.resetSettings();

  //set custom ip for portal
  //wifiManager.setAPStaticIPConfig(IPAddress(10,0,1,1), IPAddress(10,0,1,1), IPAddress(255,255,255,0));

  //fetches ssid and pass from eeprom and tries to connect
  //if it does not connect it starts an access point with the specified name
  //here  "AutoConnectAP"
  //and goes into a blocking loop awaiting configuration
  wifiManager.autoConnect("AutoConnectAP");
  //or use this for auto generated name ESP + ChipID
  //wifiManager.autoConnect();

  //if you get here you have connected to the WiFi
  Serial.println("connected...yeey :)");

  auto connection_result = pi.connect("192.168.140.80");
  Serial.printf("Connection result = %d\n", connection_result);
  auto result = io.set_mode(17, GpioMode::PI_OUTPUT);
  Serial.printf("Set mode result = %d\n", static_cast<int>(result));
}

void loop()
{
  for (auto delay_duration = 1000;; delay_duration += 1000)
  {
    // turn the LED on (HIGH is the voltage level)
    // digitalWrite(LED_BUILTIN, HIGH);
    auto result = io.gpio_write(17, GpioLevel::PI_ON);
    Serial.printf("gpio write result = %d\n", static_cast<int>(result));

    // wait for a second
    delay(delay_duration);

    // turn the LED off by making the voltage LOW
    //digitalWrite(LED_BUILTIN, LOW);
    auto result1 = io.gpio_write(17, GpioLevel::PI_OFF);
    Serial.printf("gpio write result = %d\n", static_cast<int>(result1));

    // wait for a second
    delay(delay_duration);
    if (delay_duration >= 30000)
    {
      delay_duration = 1000;
    }
  }
}