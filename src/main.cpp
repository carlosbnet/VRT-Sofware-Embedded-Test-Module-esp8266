

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
#include <ESP8266HTTPClient.h>

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

long firstTime = 0;
long lastTime = 0;
long firstTimeMPU = 0;
long lastTimeMPU = 0;
long firstTimeGPS = 0;
long lastTimeGPS = 0;
long firstTimeBMP = 0;
long lastTimeBMP = 0;
long firstTimeWifi = 0;
long lastTimeWifi = 0;
long lastTimePost = 0;
long firstTimePost = 0;
long lastTimeSD = 0;
long firstTimeSD = 0;

void setup()
{

  Serial.begin(115200);

  moduleGPS.begin();
  moduleBMP.begin();
  moduleMPU.begin();
  moduleWifi.begin();

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

  firstTime = millis();

  StaticJsonDocument<1024> doc;

  firstTimeGPS = millis();
  doc["moduleGps"] = moduleGPS.createJson();
  lastTimeGPS = millis();

  firstTimeBMP = millis();
  doc["moduleBmp"] = moduleBMP.createJson();
  lastTimeBMP = millis();

  firstTimeMPU = millis();
  doc["moduleMpu"] = moduleMPU.createJson();
  lastTimeMPU = millis();

  firstTimeWifi = millis();
  doc["moduleWifi"] = moduleWifi.createJson();
  lastTimeWifi = millis();

  firstTimeSD = millis();
  moduleSD.dataSave(doc);
  lastTimeSD = millis();

  firstTimePost = millis();
  moduleWifi.sendData(doc);
  lastTimePost = millis();

  moduleWifi.checkConnection();

  lastTime = millis();

  Serial.println("--------------------------------------------------------------");
  Serial.print("Tempo de execução geral: ");
  Serial.println(lastTime - firstTime);
  Serial.print("Tempo de execução GPS: ");
  Serial.println(lastTimeGPS - firstTimeGPS);
  Serial.print("Tempo de execução BMP: ");
  Serial.println(lastTimeBMP - firstTimeBMP);
  Serial.print("Tempo de execução MPU: ");
  Serial.println(lastTimeMPU - firstTimeMPU);
  Serial.print("Tempo de execução WIFI: ");
  Serial.println(lastTimeWifi - firstTimeWifi);
  Serial.print("Tempo de execução Post: ");
  Serial.println(lastTimePost - firstTimePost);
  Serial.print("Tempo de execução SD: ");
  Serial.println(lastTimeSD - firstTimeSD);
  Serial.println("--------------------------------------------------------------");

  
}
