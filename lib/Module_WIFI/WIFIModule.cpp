#include "Arduino.h"
#include "WIFIModule.h"
#include <ArduinoJson.h>
#include <ESP8266WiFi.h>

WIFIModule::WIFIModule()
{
  _ssid = SSID_DEFAULT;
  _pass = PASS_DEFAULT;
}

uint8_t WIFIModule::connect()
{
  //Quando conectado contador volta a zero
  count = 0;

  WiFi.begin(_ssid, _pass);

  //Enquanto Wi-Fi não estiver conectado e o limite do tempo de conexão não exceder
  while (WiFi.status() != WL_CONNECTED && count <= 150)
  {
    delay(100);
    Serial.print(".");
    count += 1;
  }
  if ((WiFi.status() == WL_CONNECTED))
  {
    Serial.println("");
    Serial.print("Connect in: ");
    Serial.println(_ssid);
    Serial.print("Address IP: ");
    Serial.println(WiFi.localIP());
  }

  return WiFi.status();
}

void WIFIModule::checkConnection()
{

  if ((WiFi.status() == WL_CONNECTED))
  {
    return;
  }
  else
  {
    Serial.println("Reconnect...");
    this->connect();
  }
}


DynamicJsonDocument WIFIModule::createJson(){
 
  DynamicJsonDocument build = this->buildJson();

    return build;
}




DynamicJsonDocument WIFIModule::buildJson(){

StaticJsonDocument<192> doc;
        
//Cria o PAI 
    JsonObject infor_WIFI =  doc.createNestedObject("infor_WIFI");

//Criar os Filhos

this->createJsonChild(infor_WIFI);

//For debug
//serializeJsonPretty(doc, Serial);

return doc;

}

void WIFIModule::createJsonChild(JsonObject jsonObject){

  IPAddress ip = WiFi.localIP();
  IPAddress subMask = WiFi.subnetMask();
  IPAddress gateWay = WiFi.gatewayIP();
         
         
            jsonObject["ssid"] = WiFi.SSID();
            jsonObject["ip"] = ip.toString();
            jsonObject["mac"] = WiFi.macAddress();
            jsonObject["submask"] = subMask.toString();
            jsonObject["gateway"] = gateWay.toString();
            jsonObject["status"] = WiFi.status();
            
}




void WIFIModule::headerWIFI()
{

  Serial.println("==============================================================================================================");
  Serial.println("==============================================================================================================");
  Serial.println("=========================                                                      ===============================");
  Serial.println("=========================              Management System VRT  1.0              ===============================");
  Serial.println("=========================                    WIFI Module  1.0                   ===============================");
  Serial.println("=========================                                                      ===============================");
  Serial.println("==============================================================================================================");
  Serial.println("==============================================================================================================");
}