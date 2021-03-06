#include <Arduino.h>
#include "Comunicacion/CAN_r.h"
#include "Comunicacion/Common.h"

CAN_r Com;
uint8_t Pack[150];
float x=0.000;

void static ReceiveData(_Medicion, uint8_t);

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
  Com.begin();
  Com.onReceive(ReceiveData);
  
  vTaskDelay(250); 
  for(;;){ 
    Com.send(x,11.2,0.12,0.001,10);
    x+=0.001;
    Com.Update();
    vTaskDelay(1000); 
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

void ReceiveData(_Medicion Data, uint8_t id){
  Serial.print("id =   "); Serial.print(id); Serial.print("         Mean =   "); Serial.println(Data.mean,4);
}





