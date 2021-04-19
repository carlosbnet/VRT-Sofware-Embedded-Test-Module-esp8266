#ifndef SDModule_h
#define SDModule_h

//Libs necessarias para funcionar
#include <Arduino.h>
#include <ArduinoJson.h>
#include <SPI.h>
#include <SD.h>

//Arduino UNO Default Config
#define DEFAULT_PIN_CS 4
#define DEFAULT_PIN_MOSI 11
#define DEFAULT_PIN_MISO 12
#define DEFAULT_PIN_CLK 13

//Arduino Mega Default Config

#define DEFAULT_PIN_MOSI_MEGA 51
#define DEFAULT_PIN_MISO_MEGA 50
#define DEFAULT_PIN_CLK_MEGA 52


class SDModule : public String
{
private:


public:
    
    //Variaveis
    uint8_t pin_cs;


    //Contrutor
    SDModule(uint8_t cs_pin_number);

    //Metodos
    boolean begin();
    void dataSave(DynamicJsonDocument data);
    String createNameFile();
    void headerSD();

};

#endif