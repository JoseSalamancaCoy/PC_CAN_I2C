#include <Arduino.h>
#include <Wire.h>
#include "Comunicacion/CAN_r.h"
#include "Comunicacion/Common.h"
#include <TimerOne.h>

float x = 0;
CAN_r Com;
bool Timeout;


void static ReceiveData(_Medicion, uint8_t);

void IRQ_interrup(){
    Timeout = true;

}

void setup()
{
  Serial.begin(115200);           // start serial for output
  Serial.println("Init atmega328");
  Com.begin();  
  Com.onReceive(ReceiveData);

  Timer1.initialize(1100000);
  Timer1.attachInterrupt(IRQ_interrup);
}

void loop()
{
  if(Timeout){
    Timeout = false;
    
    x+=0.001;
    Com.send(x,11.2,0.12,0.001,pm10_1);
    
  }
   //if(Timeout){Timeout = false; Serial.println("ok");} 

  delay(10);
}


void ReceiveData(_Medicion Data, uint8_t id){
  Serial.print("id =   "); Serial.print(id); Serial.print("     Mean =   "); Serial.println(Data.mean,4);
}