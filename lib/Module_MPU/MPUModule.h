#ifndef MPUModule_h
#define MPUModule_h


#include <Arduino.h>
#include <ArduinoJson.h>
#include <Wire.h>

#define DEFAULT_ADDRESS_MPU  0x68
#define DEFAULT_DELAY_MS 1000

class MPUModule : public TwoWire
{
private:

    uint8_t _port;

public:




    //Contrutor
    MPUModule();
    MPUModule(byte port);


    //Metodos
    void begin();
    
    void dataMPU();
    void header();
    DynamicJsonDocument buildJson();
    void createJsonChild(JsonObject jsonObject);
    DynamicJsonDocument createJson();

};


#endif