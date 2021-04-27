#ifndef GPSModule_h
#define GPSModule_h

#include <SoftwareSerial.h>
#include <Arduino.h>
#include <ArduinoJson.h>
#include <TinyGPS++.h>

#define DEFAULT_RX_PIN  10
#define DEFAULT_TX_PIN  9
#define DEFAULT_BAUD_RATE  9600
#define DEFAULT_DELAY_MS 80
#define DEFAULT_SERIAL_PORT 0
#define DEFAULT_SOFTWARECONFIG SWSERIAL_8N1

class GPSModule : public SoftwareSerial, public TinyGPSPlus
{
private:

    


public:


    //Variaveis
    uint8_t rx_pin;
    uint8_t tx_pin;
    uint32_t baud;
    SoftwareSerialConfig softwareConfig;
    


    //Contrutor
    GPSModule();
    GPSModule(uint8_t rx, uint8_t tx);
    


    //Metodos
    void begin();
    void begin(uint32_t baud);
    TinyGPSPlus init();

    void headerGps();
    DynamicJsonDocument buildJson();
    void customDelay(uint32_t MS);
    DynamicJsonDocument createJson();


};


#endif