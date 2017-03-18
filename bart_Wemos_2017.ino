/**************************************************************
D7 - 13 ds18
D1 - 5 przek1
V1 - tempval
V1 - tempval2
 **************************************************************/

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <SimpleTimer.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#include <ArduinoOTA.h>
#include <ESP8266mDNS.h>

#define ONE_WIRE_BUS_PIN 13
OneWire oneWire(ONE_WIRE_BUS_PIN);
DallasTemperature sensors(&oneWire);
DeviceAddress zew01 = { 0x28, 0xFF, 0x61, 0x75, 0x90, 0x15, 0x03, 0x64 };
DeviceAddress wew02 = { 0x28, 0xFF, 0xDC, 0x8E, 0x50, 0x15, 0x01, 0xCD };

SimpleTimer timer;
int przek1 = 5;
float tempval, tempval2;
char auth[] = "bc0e485e0bfd433084309ae0cb999c3f";

char ssid[] = "_";
char pass[] = "chuck1234";

void stx() {
  sensors.requestTemperatures();
  tempval = sensors.getTempC(zew01);
  tempval2 = sensors.getTempC(wew02);
  Blynk.virtualWrite(V0, tempval);
  Blynk.virtualWrite(V1, tempval2);
}

void setup()
{
  Serial.begin(115200);
  pinMode(przek1,OUTPUT);
  digitalWrite(przek1,HIGH);
  sensors.begin();
  sensors.setResolution(wew02, 10);
  sensors.setResolution(zew01, 10);
  Blynk.begin(auth, ssid, pass, "hc.karolak-k.com");
  timer.setInterval(10000L, stx);

    /* ----------- OTA ------------- */
  ArduinoOTA.setHostname("WemosD1Mini");
  ArduinoOTA.onStart([]() {
    Blynk.disconnect();
  });
  ArduinoOTA.begin();
  //stx();
}

void loop()
{
  Blynk.run();
  ArduinoOTA.handle();
  timer.run();
}

