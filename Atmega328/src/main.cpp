#include <Arduino.h>
#include <Wire.h>
#include "CAN_r.h"
#include <TimerOne.h>

byte x = 0;
CAN_r Com;
bool Timeout;


void IRQ_interrup(){
    Timeout = true;
    Serial.println("ok");
}

void setup()
{
  Serial.begin(9600);           // start serial for output
  Com.Init_Slave();
  Timer1.initialize(1000);
  Timer1.attachInterrupt(IRQ_interrup);
}

void loop()
{
  if(Timeout){
    Timeout = false;
    Com.End_Slave();
    Com.Init_Master();
    Com.T_Master(x++);
    Com.End_Master();
    Com.Init_Slave();
  }
  delay(10);
}
