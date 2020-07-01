#include "CAN_r.h"

CAN_r::CAN_r()
{
  Wire.begin(); // join i2c bus (address optional for master)
}

CAN_r::~CAN_r()
{

}

void CAN_r::send(uint8_t x)
{
  //T_Master(x);
  set_Pack(x);
  Wire.beginTransmission(4); // transmit to device #4
  Wire.write(&PackDato._uint8._init, 7 ) ;         // sends one byte  
  Wire.endTransmission();    // stop transmitting
}


void CAN_r::Init_Master(){
  
}

void CAN_r::T_Master(uint8_t x)
{
  Wire.beginTransmission(4); // transmit to device #4
  Wire.write("x is ");        // sends five bytes
  Wire.write(x);             // sends one byte  
  Wire.endTransmission();    // stop transmitting
}

void CAN_r::End_Master(){
  //delete Wire;
}

void CAN_r::Init_Slave(){
  Wire.begin();                // join i2c bus with address #4
}

void CAN_r::End_Slave(){
  //Wire.end();
}

void receiveEvent(int howMany)
{
  while(1 < Wire.available()) // loop through all but the last
  {
    char c = Wire.read();    // receive byte as a character
    Serial.print(c);         // print the character
  }
  int x = Wire.read();    // receive byte as an integer
  Serial.println(x);         // print the integer
} 
