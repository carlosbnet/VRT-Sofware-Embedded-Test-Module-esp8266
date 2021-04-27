#include "Arduino.h"
#include "WIFIModule.h"
#include <ArduinoJson.h>
#include <ESP8266WiFi.h>
#include <WiFiClient.h>

WIFIModule::WIFIModule()
{
  _ssid = SSID_DEFAULT;
  _pass = PASS_DEFAULT;
}

WIFIModule::WIFIModule(char *ssid, char *pass)
{
  _ssid = ssid;
  _pass = pass;
}

void WIFIModule::begin()
{

  host = HOST_DEFAULT;
  path = PATH_DEFAULT;
}

void WIFIModule::begin(char *host, char *path)
{

  this->host = host;
  this->path = path;
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

DynamicJsonDocument WIFIModule::createJson()
{

  DynamicJsonDocument build = this->buildJson();

  return build;
}

DynamicJsonDocument WIFIModule::buildJson()
{

  StaticJsonDocument<192> doc;

  IPAddress ip = WiFi.localIP();
  IPAddress subMask = WiFi.subnetMask();
  IPAddress gateWay = WiFi.gatewayIP();

  doc["ssid"] = WiFi.SSID();
  doc["ip"] = ip.toString();
  doc["mac"] = WiFi.macAddress();
  doc["submask"] = subMask.toString();
  doc["gateway"] = gateWay.toString();
  doc["status"] = WiFi.status();

  //For debug
  //serializeJsonPretty(doc, Serial);

  return doc;
}

void WIFIModule::sendData(DynamicJsonDocument doc)
{
  
  String json;
  serializeJson(doc, json);

  http.begin(this->host + this->path);
  http.addHeader("Content-Type", "application/json");

  int httpResponseCode = http.POST(json);

  if (httpResponseCode > 0)
  {
    Serial.print("HTTP Response code: ");
    Serial.println(httpResponseCode);
  }
  else
  {
    Serial.print("Error code: ");
    Serial.println(httpResponseCode);
  }
  
  http.end(); //Close connection
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