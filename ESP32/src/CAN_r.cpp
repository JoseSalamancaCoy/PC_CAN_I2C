#include "CAN_r.h"

CAN_r::CAN_r()
{
}

CAN_r::~CAN_r()
{

}

void CAN_r::send(uint8_t val)
{
  len = set_Pack(val, &Pack[0]);
  Wire.beginTransmission(_port_I2C); // transmit to device #4
  Wire.write(&Pack[0], len) ;         // sends one byte  
  Wire.endTransmission();    // stop transmitting
  Serial.println("");
}

void CAN_r::send(uint16_t val){
  len = set_Pack(val, &Pack[0]);
  Wire.beginTransmission(_port_I2C); // transmit to device #4
  Wire.write(&Pack[0], len) ;         // sends one byte  
  Wire.endTransmission();    // stop transmitting
  Serial.println("");
}

void CAN_r::send(uint32_t val){
  len = set_Pack(val, &Pack[0]);
  Wire.beginTransmission(_port_I2C); // transmit to device #4
  Wire.write(&Pack[0], len) ;         // sends one byte  
  Wire.endTransmission();    // stop transmitting
  Serial.println("");
}

void CAN_r::send(uint64_t val){
  len = set_Pack(val, &Pack[0]);
  Wire.beginTransmission(_port_I2C); // transmit to device #4
  Wire.write(&Pack[0], len) ;         // sends one byte  
  Wire.endTransmission();    // stop transmitting
  Serial.println("");
}

void CAN_r::send(float val){
  len = set_Pack(val, &Pack[0]);
  Wire.beginTransmission(_port_I2C); // transmit to device #4
  Wire.write(&Pack[0], len) ;         // sends one byte  
  Wire.endTransmission();    // stop transmitting
  Serial.println("");
}

void CAN_r::send(float mean, float max, float min, float desv){
  len = set_Pack(mean,max,min,desv, &Pack[0]);
  Wire.beginTransmission(_port_I2C); // transmit to device #4
  Wire.write(&Pack[0], len) ;         // sends one byte  
  Wire.endTransmission();    // stop transmitting
  Serial.println("");
}

void CAN_r::send(_Medicion val){
  len = set_Pack(val, &Pack[0]);
  Wire.beginTransmission(_port_I2C); // transmit to device #4
  Wire.write(&Pack[0], len) ;         // sends one byte  
  Wire.endTransmission();    // stop transmitting
  Serial.println("");
}


void CAN_r::Init_Master(){
  Wire.begin();  //i2c master init
}

void CAN_r::End_Master(){
  Wire.flush();
}

void CAN_r::Init_Slave(void (*function)(int)){
  bool success = WireSlave.begin(SDA_PIN, SCL_PIN, _port_I2C);
  if (!success) {
      Serial.println("I2C slave init failed");
      while(1) delay(100);
  }
  WireSlave.onReceive(function);
}

void CAN_r::End_Slave(){
  WireSlave.update();
  WireSlave.flush();
}


