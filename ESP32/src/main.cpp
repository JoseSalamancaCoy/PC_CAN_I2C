#include <Arduino.h>
#include <Wire.h>
#include "CAN_r.h"

byte x = 0;
CAN_r Com;
bool Timeout;

void setup()
{
  Serial.begin(9600);           // start serial for output
  
  Serial.println("aja");
  delay(900);

  
  Com.begin(3);
  Serial.println("aja");
  delay(900);
  delay(900);
}

void loop()
{
  Com.send(x);
  delay(900);
  x++;
}


