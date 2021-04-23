


#ifndef WIFIModule_h
#define WIFIModule_h

//Libs necessarias para funcionar
#include <Arduino.h>
#include <ArduinoJson.h>
#include <ESP8266WiFi.h>
#include <IPAddress.h>


//Contantes

#define SSID_DEFAULT "javaUm"
#define PASS_DEFAULT "12345678"


// 3 metodos

// 1 - Connecte
// 2 - Reconecte
// 3 - Infor

//Retorno de Informações
// 1 - IP
// 2 - MAC
// 3 - SubMask
// 4 - GatWayIp
// 5 - Status
// 6 - SSID




class WIFIModule: public IPAddress
{
private:


public:
    
    
    
    const char* _ssid;
    const char* _pass;
    uint16_t count;


    //Contrutor
    WIFIModule();

    //Metodos
    uint8_t connect();
    void checkConnection();
    DynamicJsonDocument buildJson();
    void createJsonChild(JsonObject jsonObject);
    DynamicJsonDocument createJson();
       
    void headerWIFI();

};

#endif