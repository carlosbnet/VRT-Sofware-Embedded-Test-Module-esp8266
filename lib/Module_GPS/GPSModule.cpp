#include "Arduino.h"
#include "GPSModule.h"
#include <SoftwareSerial.h>
#include <ArduinoJson.h>
#include <TinyGPS++.h>



GPSModule::GPSModule(void) : SoftwareSerial(DEFAULT_RX_PIN,DEFAULT_TX_PIN), TinyGPSPlus()
{
    rx_pin = DEFAULT_RX_PIN;
    tx_pin = DEFAULT_TX_PIN;
    
}

GPSModule::GPSModule(uint8_t rx, uint8_t tx): SoftwareSerial(rx, tx), TinyGPSPlus()
{
    rx_pin = rx;
    tx_pin = tx;

}





void GPSModule::begin(){

    this->baud = DEFAULT_BAUD_RATE;
    this->SoftwareSerial::begin(baud);
    

}


void GPSModule::begin(uint32_t baud_pin){

    this->baud = baud_pin;
    this->SoftwareSerial::begin(baud);

}


DynamicJsonDocument GPSModule::createJson(){

  DynamicJsonDocument build = this->buildJson();

    this->customDelay(DEFAULT_DELAY_MS);

    return build;
}


void GPSModule::customDelay(uint32_t MS){

  unsigned long start = millis();

    do
    {
     while(this->SoftwareSerial::available())               //delay para agrupar mais dados
        TinyGPSPlus::encode(this->SoftwareSerial::read());
    } while (millis()-start < MS);

}



DynamicJsonDocument GPSModule::buildJson(){

const size_t capacity = JSON_OBJECT_SIZE(1) + JSON_OBJECT_SIZE(2) + 4*JSON_OBJECT_SIZE(3) + JSON_OBJECT_SIZE(4) + JSON_OBJECT_SIZE(6);
DynamicJsonDocument doc(capacity);


//Cria o PAI 
JsonObject infor_gps = doc.createNestedObject("infor_gps");

//Criar os Filhos

this->createJsonChild(infor_gps);

//For debug
//serializeJsonPretty(doc, Serial);

return doc;

}


void GPSModule::createJsonChild(JsonObject jsonObject){
         
        JsonObject infor_gps_location = jsonObject.createNestedObject("location");
        infor_gps_location["lat"] = TinyGPSPlus::location.lat();
        infor_gps_location["lng"] = TinyGPSPlus::location.lng();
        infor_gps_location["rawlat"] = TinyGPSPlus::location.rawLat().negative ? "-" : "+";
        infor_gps_location["rawlng"] = TinyGPSPlus::location.rawLng().negative ? "-" : "+";

        JsonObject infor_gps_date = jsonObject.createNestedObject("date");
        infor_gps_date["year"] = TinyGPSPlus::date.year();
        infor_gps_date["month"] = TinyGPSPlus::date.month();
        infor_gps_date["day"] = TinyGPSPlus::date.day();

        JsonObject infor_gps_time = jsonObject.createNestedObject("time");
        infor_gps_time["hour"] = TinyGPSPlus::time.hour()-3;
        infor_gps_time["minute"] = TinyGPSPlus::time.minute();
        infor_gps_time["second"] = TinyGPSPlus::time.second();

        JsonObject infor_gps_speed = jsonObject.createNestedObject("speed");
        infor_gps_speed["mph"] = TinyGPSPlus::speed.mph();
        infor_gps_speed["mps"] = TinyGPSPlus::speed.mps();
        infor_gps_speed["kmph"] = TinyGPSPlus::speed.kmph();

        JsonObject infor_gps_altitude = jsonObject.createNestedObject("altitude");
        infor_gps_altitude["meters"] = TinyGPSPlus::altitude.meters();
        infor_gps_altitude["miles"] = TinyGPSPlus::altitude.miles();
        infor_gps_altitude["kilometers"] = TinyGPSPlus::altitude.kilometers();

        JsonObject infor_gps_satellites = jsonObject.createNestedObject("satellites");
        infor_gps_satellites["satellites"] = TinyGPSPlus::satellites.value();
        infor_gps_satellites["hdop"] = TinyGPSPlus::hdop.value();

}






// TinyGPSPlus GPS_Module::init()
// {
//     return TinyGPSPlus();
// }

/* void GPS_Module::headerGps(){

Serial.println("==============================================================================================================");
Serial.println("==============================================================================================================");
Serial.println("=========================                                                      ===============================");
Serial.println("=========================              Management System VRT  1.0              ===============================");
Serial.println("=========================                    GPS Module  1.0                   ===============================");
Serial.println("=========================                                                      ===============================");
Serial.println("==============================================================================================================");
Serial.println("==============================================================================================================");

} */

