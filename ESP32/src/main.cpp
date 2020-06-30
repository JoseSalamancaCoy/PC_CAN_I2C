#include <Arduino.h>
#include <Wire.h>
#include "CAN_r.h"

byte x = 0;
CAN_r Com;
bool Timeout;

void setup()
{
  Serial.begin(9600);           // start serial for output
  Com.Init_Slave();
  delay(900);
}

void loop()
{
  
  Com.End_Slave();
  Com.Init_Master();
  Com.T_Master(x++);
  Com.End_Master();
  Com.Init_Slave();  
  delay(900);
}

