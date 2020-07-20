#include <Arduino.h>
#include <Wire.h>
#include "WireSlave.h"
#include "CAN_r.h"

CAN_r Com;
uint8_t Pack[150];


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
  Com.Init_Slave();
  vTaskDelay(250); 
  for(;;){
    //Serial.println("fin slave");
    //Com.End_Slave();
    //Serial.println("init Master");
    //Com.Init_Master();  
    //Serial.println("Envio  .. ");
    //Com.send(10.5,11.2,0.12,0.001);
    //Com.End_Master();
    //Com.Init_Slave(receiveEvent);
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



