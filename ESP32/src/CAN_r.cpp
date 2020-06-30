#include "CAN_r.h"

CAN_r::CAN_r(/* args */)
{

}

CAN_r::~CAN_r()
{

}

void CAN_r::Init_Master(){
  Wire.begin(); // join i2c bus (address optional for master)
}

void CAN_r::T_Master(uint8_t x)
{
  Wire.beginTransmission(10); // transmit to device #4
  Wire.write("x is ");        // sends five bytes
  Wire.write(x);              // sends one byte  
  Wire.endTransmission();    // stop transmitting
  x++;
}

void CAN_r::End_Master(){
  //delete Wire;
}

void CAN_r::Init_Slave(){
  Wire.begin(4);                // join i2c bus with address #4
  Wire.onReceive(receiveEvent); // register event
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
