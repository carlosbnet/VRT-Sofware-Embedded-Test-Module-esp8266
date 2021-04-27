#include "Arduino.h"
#include "BMPModule.h"
#include <SoftwareSerial.h>
#include <ArduinoJson.h>
#include <Adafruit_BMP280.h>
#include <Adafruit_Sensor.h>

BMPModule::BMPModule(void)
{
    _port = DEFAULT_ADDRESS_BMP;
}

BMPModule::BMPModule(byte port)
{
    _port = port;
}


void BMPModule::begin(){

    this->Adafruit_BMP280::begin(_port);


}


DynamicJsonDocument BMPModule::createJson(){

  DynamicJsonDocument build = this->buildJson();

    return build;
}


DynamicJsonDocument BMPModule::buildJson(){

StaticJsonDocument<64> doc;
        
        
        doc["temperature"] = this->Adafruit_BMP280::readTemperature();
        doc["pressure"] = this->Adafruit_BMP280::readPressure();                          
        doc["altitude"] = this->Adafruit_BMP280::readAltitude(1013.25);


//For debug
//serializeJsonPretty(doc, Serial);

return doc;

}

void BMPModule::header(){

Serial.println("==============================================================================================================");
Serial.println("==============================================================================================================");
Serial.println("=========================                                                      ===============================");
Serial.println("=========================              Management System VRT  1.0              ===============================");
Serial.println("=========================                    BMP Module  1.0                   ===============================");
Serial.println("=========================                                                      ===============================");
Serial.println("==============================================================================================================");
Serial.println("==============================================================================================================");

}

