#include <Arduino.h>
#include <Wire.h>
#include "CAN_r.h"

byte x = 0;
CAN_r Com;
bool Timeout;
uint8_t Pack[150];
void setup()
{
  Serial.begin(9600);           // start serial for output
  
  Serial.println("aja");
  delay(900);
  pinMode(25,OUTPUT);
  
  Com.begin(3);
  Serial.println("aja");
  delay(900);
}

void loop()
{
  Com.send(10.5,11.2,0.12,0.001);
  delay(900);
  digitalWrite(25, !digitalRead(25));
  x++;
}


