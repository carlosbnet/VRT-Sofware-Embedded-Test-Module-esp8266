

#ifndef WIFIModule_h
#define WIFIModule_h

//Libs necessarias para funcionar
#include <Arduino.h>
#include <ArduinoJson.h>
#include <ESP8266WiFi.h>
#include <IPAddress.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>

//Contantes

#define SSID_DEFAULT "javaUm"
#define PASS_DEFAULT "12345678"
#define HOST_DEFAULT "http://192.168.43.212:8080/"
#define PATH_DEFAULT "api/v1/module"

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

class WIFIModule : public IPAddress
{
private:
    const char *_ssid;
    const char *_pass;

public:
    uint16_t count;
    uint8_t httpResponseCode;
    String payload;
    HTTPClient http;
    String host;
    String path;

    //Construtor
    WIFIModule();
    WIFIModule(char *ssid, char *pass);

    //Metodos
    uint8_t connect();
    void begin();
    void begin(char *host, char *path);
    void checkConnection();
    DynamicJsonDocument buildJson();
    DynamicJsonDocument createJson();
    void sendData(DynamicJsonDocument doc);
    void headerWIFI();
};

#endif