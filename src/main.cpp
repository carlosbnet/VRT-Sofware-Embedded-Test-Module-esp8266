

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

//Add Modules
#include "GPSModule.h"
#include "BMPModule.h"
#include "MPUModule.h"
#include "SDModule.h"

GPSModule moduleGPS(D3,D0);
BMPModule moduleBMP;
MPUModule moduleMPU;
SDModule  moduleSD(D0);

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

}

void loop()
{

  const size_t capacity = 4 * JSON_OBJECT_SIZE(1) + JSON_OBJECT_SIZE(2) + 9 * JSON_OBJECT_SIZE(3) + JSON_OBJECT_SIZE(4) + JSON_OBJECT_SIZE(6);
  DynamicJsonDocument doc(capacity);

  JsonObject infor = doc.createNestedObject("modules");

  infor["gps"] = moduleGPS.createJson();

  infor["bmp"] = moduleBMP.createJson();

  infor["mpu"] = moduleMPU.createJson();

  serializeJsonPretty(doc, Serial);

  moduleSD.dataSave(doc);

  delay(1000);
  
}