#include <Arduino.h>
#include <Wire.h>
#include "WireSlave.h"
#include "CAN_r.h"


CAN_r Com;
uint8_t Pack[150];

void static ReceiveData(_Medicion);

static void LedBlink(void * parameter){
  pinMode(25,OUTPUT);
  for(;;)
  {
    digitalWrite(25, !digitalRead(25));
    vTaskDelay(250);    
  }

}
static void Comunication(void * parameter){
  Serial.println("Comunicacion");
  Com.begin(3);
  Com.onReceive(ReceiveData);
  Com.Init_Slave();
  vTaskDelay(250); 
  for(;;){
    Com.End_Slave();
    Com.Init_Master();  
    Com.send(10.5,11.2,0.12,0.001);
    Com.End_Master();
    Com.Init_Slave();
    Com.Update();
    vTaskDelay(100); 
  }
}


void setup()
{
  Serial.begin(115200);     
  Serial.println("Inicio ");
  xTaskCreate(LedBlink, "LED Blink", 10000, NULL, 4,  NULL);
  xTaskCreate(Comunication, "Comunicacion", 10000, NULL, 1,  NULL);
}

void loop()
{  
}

void ReceiveData(_Medicion Data){
  Serial.print("Mean =   "); Serial.println(Data.mean,4);
}





