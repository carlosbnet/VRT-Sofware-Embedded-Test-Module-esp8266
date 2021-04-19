

#include "Arduino.h"
#include "MPUModule.h"
#include <ArduinoJson.h>
#include <Wire.h>


uint8_t AcX, AcY,  AcZ, Tmp,  GyX,  GyY,  GyZ;


MPUModule::MPUModule(void)
{
    _port = DEFAULT_ADDRESS_MPU;
}

MPUModule::MPUModule(byte port)
{
    _port = port;
}


void MPUModule::begin(){

    this->TwoWire::begin();
    this->TwoWire::beginTransmission(_port);
    this->TwoWire::write(0x6B);
    this->TwoWire::write(0);
    this->TwoWire::endTransmission(true);

}


DynamicJsonDocument MPUModule::createJson(){


  this->dataMPU();
 
  DynamicJsonDocument build = this->buildJson();

    delay(DEFAULT_DELAY_MS);

    return build;
}


void MPUModule::dataMPU(){

       this->TwoWire::beginTransmission(_port);
       this->TwoWire::write(0x3B);  // starting with register 0x3B (ACCEL_XOUT_H)
       this->TwoWire::endTransmission(false);

        //Solicita os dados do sensor
        Wire.requestFrom(0x68,14,true);
       // this->TwoWire::requestFrom(0x68,14,true);  


        //Armazena o valor dos sensores nas variaveis correspondentes
        AcX=this->TwoWire::read()<<8|this->TwoWire::read();  //0x3B (ACCEL_XOUT_H) & 0x3C (ACCEL_XOUT_L)     
        AcY=this->TwoWire::read()<<8|this->TwoWire::read();  //0x3D (ACCEL_YOUT_H) & 0x3E (ACCEL_YOUT_L)
        AcZ=this->TwoWire::read()<<8|this->TwoWire::read();  //0x3F (ACCEL_ZOUT_H) & 0x40 (ACCEL_ZOUT_L)
        Tmp=this->TwoWire::read()<<8|this->TwoWire::read();  //0x41 (TEMP_OUT_H) & 0x42 (TEMP_OUT_L)
        GyX=this->TwoWire::read()<<8|this->TwoWire::read();  //0x43 (GYRO_XOUT_H) & 0x44 (GYRO_XOUT_L)
        GyY=this->TwoWire::read()<<8|this->TwoWire::read();  //0x45 (GYRO_YOUT_H) & 0x46 (GYRO_YOUT_L)
        GyZ=this->TwoWire::read()<<8|this->TwoWire::read();  //0x47 (GYRO_ZOUT_H) & 0x48 (GYRO_ZOUT_L)

        

}




DynamicJsonDocument MPUModule::buildJson(){

const size_t capacity = JSON_OBJECT_SIZE(1) + JSON_OBJECT_SIZE(2) + 4*JSON_OBJECT_SIZE(3) + JSON_OBJECT_SIZE(4) + JSON_OBJECT_SIZE(6);
DynamicJsonDocument doc(capacity);

        
//Cria o PAI 
    JsonObject infor_MPU6050 =  doc.createNestedObject("infor_MPU6050");

//Criar os Filhos

this->createJsonChild(infor_MPU6050);

//For debug
//serializeJsonPretty(doc, Serial);

return doc;

}


void MPUModule::createJsonChild(JsonObject jsonObject){

         
      JsonObject infor_MPU6050_ac =  jsonObject.createNestedObject("accelerometer");
            infor_MPU6050_ac["x"] = AcX;
            infor_MPU6050_ac["y"] = AcY;
            infor_MPU6050_ac["z"] = AcZ;

        JsonObject infor_MPU6050_gy =  jsonObject.createNestedObject("gyroscope");
            infor_MPU6050_gy["x"] = GyX;
            infor_MPU6050_gy["y"] = GyY;
            infor_MPU6050_gy["z"] = GyZ;

        jsonObject["temperature"] = Tmp/340.00+36.53;

}





void MPUModule::header(){


Serial.println("==============================================================================================================");
Serial.println("==============================================================================================================");
Serial.println("=========================                                                      ===============================");
Serial.println("=========================              Management System VRT  1.0              ===============================");
Serial.println("=========================                    MPU Module  1.0                   ===============================");
Serial.println("=========================                                                      ===============================");
Serial.println("==============================================================================================================");
Serial.println("==============================================================================================================");

}

