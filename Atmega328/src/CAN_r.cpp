#include "CAN_r.h"

CAN_r::CAN_r(/* args */)
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
  Wire.begin(); // join i2c bus (address optional for master)
}


void CAN_r::End_Master(){
  Wire.end();
}

void CAN_r::Init_Slave(){
  Wire.begin(_port_I2C);                // join i2c bus with address #4
  Wire.onReceive(receiveEvent); // register event
}

void CAN_r::End_Slave(){
  Wire.end();
}

void receiveEvent(int howMany)
{
  uint8_t len=0;
  while(Wire.available()) // loop through all but the last
  {
    uint8_t x = Wire.read();    // receive byte as an integer
    Serial.print(x);
    Serial.print(" ");
    len++;
  }
  Serial.print("      * ");
  Serial.println(len);

           // print the integer
} 
