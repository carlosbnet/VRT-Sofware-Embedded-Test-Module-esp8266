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

const size_t capacity = JSON_OBJECT_SIZE(1) + JSON_OBJECT_SIZE(2) + 4*JSON_OBJECT_SIZE(3) + JSON_OBJECT_SIZE(4) + JSON_OBJECT_SIZE(6);
DynamicJsonDocument doc(capacity);
        
//Cria o PAI 
JsonObject infor_bmp280 = doc.createNestedObject("infor_bmp280");

//Criar os Filhos

this->createJsonChild(infor_bmp280);

//For debug
//serializeJsonPretty(doc, Serial);

return doc;

}


void BMPModule::createJsonChild(JsonObject jsonObject){
         
        //Criar os Filhos
        jsonObject["temperature"] = this->Adafruit_BMP280::readTemperature();
        jsonObject["pressure"] = this->Adafruit_BMP280::readPressure();                          
        jsonObject["altitude"] = this->Adafruit_BMP280::readAltitude(1013.25);

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

