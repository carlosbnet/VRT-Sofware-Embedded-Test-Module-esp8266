#include "Arduino.h"
#include "SDModule.h"
#include <ArduinoJson.h>
#include <SPI.h>
#include <SD.h>

SDModule::SDModule(uint8_t cs_pin_number){
    pin_cs = cs_pin_number;
}

boolean SDModule::begin()
{

   return SD.begin(pin_cs);

}


void SDModule::dataSave(DynamicJsonDocument data)
{

     File dataFile = SD.open("datalog.txt", FILE_WRITE);

  // if the file is available, write to it:
  if (dataFile) {
    serializeJson(data,dataFile);
    dataFile.println();
    dataFile.close();
    Serial.println("Save..");
    
  }
  // if the file isn't open, pop up an error:
  else {
    Serial.println("error opening datalog.txt");
  }

}

void SDModule::headerSD(){

Serial.println("==============================================================================================================");
Serial.println("==============================================================================================================");
Serial.println("=========================                                                      ===============================");
Serial.println("=========================              Management System VRT  1.0              ===============================");
Serial.println("=========================                    SD Module  1.0                   ===============================");
Serial.println("=========================                                                      ===============================");
Serial.println("==============================================================================================================");
Serial.println("==============================================================================================================");


 }