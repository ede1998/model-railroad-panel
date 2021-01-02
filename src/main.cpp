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
#include <Adafruit_I2CDevice.h>

Adafruit_I2CDevice i2c_dev = Adafruit_I2CDevice(0x21);
Adafruit_I2CDevice i2c_dev_20 = Adafruit_I2CDevice(0x20);

void setup()
{
  Serial.begin(115200);

  WiFiManager wifiManager;
  wifiManager.autoConnect("AutoConnectAP");
  Serial.println("connected...yeey :)");

  if (!i2c_dev.begin())
  {
    Serial.print("Did not find device at 0x");
    Serial.println(i2c_dev.address(), HEX);
    while (1)
      ;
  }
  Serial.print("Device found on address 0x");
  Serial.println(i2c_dev.address(), HEX);

  uint8_t buffer[32];
  // Try to read 32 bytes
  i2c_dev.read(buffer, 32);
  Serial.print("Read: ");
  for (uint8_t i = 0; i < 32; i++)
  {
    Serial.print("0x");
    Serial.print(buffer[i], HEX);
    Serial.print(", ");
  }
  Serial.println();

}

static uint8_t buffer = 0xFF;

void loop()
{
  buffer ^= 0xFF;

  if (i2c_dev.write(&buffer, 1))
  {
    Serial.printf("Write %d successful.", buffer);
  }
  else
  {
    Serial.print("Error writing.");
  }


  i2c_dev.read(&buffer, 1);
  Serial.print("Read 21: 0x");
  Serial.print(buffer, HEX);
  Serial.println();

  uint8_t buffer2 = 0;
  i2c_dev_20.read(&buffer2, 1);
  Serial.print("Read 20: 0x");
  Serial.print(buffer2, HEX);
  Serial.println();

  delay(200);
}