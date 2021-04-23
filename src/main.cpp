

//----------------------VRT APP------------------------

/*
App com a função de gerenciar todos os perifericos do computador de bordo dentro do foguete

São eles:
 - Modulo GPS
 - Modulo GSM
 - Modulo WIFI
 - Modulo ALTIMETRO
 - Modulo ACELEROMENTRO
*/
#include <Arduino.h>
#include <SoftwareSerial.h>
#include <SPI.h>
#include <ArduinoJson.h>
#include <ESP8266WiFi.h>

//Add Modules
#include "GPSModule.h"
#include "BMPModule.h"
#include "MPUModule.h"
#include "SDModule.h"
#include "WIFIModule.h"

GPSModule moduleGPS(D3, D0);
BMPModule moduleBMP;
MPUModule moduleMPU;
SDModule moduleSD(D0);
WIFIModule moduleWifi;

void setup()
{

  Serial.begin(115200);

  moduleGPS.begin();
  moduleBMP.begin();
  moduleMPU.begin();

  if (!moduleSD.begin())
  {
    Serial.println("Card failed, or not present");
    // don't do anything more:
    while (1)
      ;
  }
  Serial.println("card initialized.");

  if (moduleWifi.connect() != WL_CONNECTED)
  {
    Serial.print("A conexão não foi estabelecida, por favor apertar botão reset ou aguardar...\n");
    return;
  }
}

void loop()
{

  StaticJsonDocument<1024> doc;

  JsonObject infor = doc.createNestedObject("modules");

  infor["gps"] = moduleGPS.createJson();

  infor["bmp"] = moduleBMP.createJson();

  infor["mpu"] = moduleMPU.createJson();

  infor["wifi"] = moduleWifi.createJson();

  serializeJsonPretty(doc, Serial);

  moduleSD.dataSave(doc);

  delay(1000);

  moduleWifi.checkConnection();
}
