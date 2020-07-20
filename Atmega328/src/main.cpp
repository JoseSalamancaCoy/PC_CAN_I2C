#include <Arduino.h>
#include <Wire.h>
#include "CAN_r.h"
#include <TimerOne.h>

float x = 0;
CAN_r Com;
bool Timeout;


void static receiveEvent(int howMany);

void IRQ_interrup(){
    Timeout = true;

}

void setup()
{
  Serial.begin(115200);           // start serial for output
  Serial.println("Init atmega328");
  Com.begin(5);
  Com.Init_Slave(receiveEvent);
  Timer1.initialize(2000000);
  Timer1.attachInterrupt(IRQ_interrup);
}

void loop()
{
  if(Timeout){
    Timeout = false;
    Com.End_Slave();
    Com.Init_Master();
    x+=0.001;
    Com.send(x,11.2,0.12,0.001);
    Serial.println(x,4);
    Com.End_Master();
    Com.Init_Slave(receiveEvent);
  }
   //if(Timeout){Timeout = false; Serial.println("ok");} 

  delay(10);
}


void receiveEvent(int howMany) //Evento de recepcion i2c
{
  static uint8_t len;
  static uint8_t Pack_r[255];
  static uint8_t relativ_init;
  uint8_t *_pack_r = &Pack_r[len];
  while(Wire.available()) // loop through all but the last
  {
    *_pack_r = (uint8_t) Wire.read();    // receive byte as an integer
    len++;
    Serial.print(*_pack_r);
    Serial.print(" ");
    _pack_r++;
  }
  // uinit posicion relativa y supuesta de inicio de trama
  for(uint8_t uinit=relativ_init; uinit<len; uinit++){

      _pack_r = &Pack_r[uinit];
      if(*_pack_r == 2){  //Identifica si el byte corresponde a 2 o inicio de trama
          _pack_r++; // Avanza a la siguiente posicion
          uint8_t _length = *_pack_r;
          if(_length > 7 && _length < 45){  // verifica si lengt esta entre la longitud maxima y minima de paquetes
              if(_length <= len-uinit){
                _pack_r+=_length-2; // Se mueve a la posicion esperada para el fin de la trama 
                if(*_pack_r == 3){ //Determina si corresponde a 3 o fin de trama, con esto se define si los datos corresponden o no a un Pack de datos.
                
                    _Medicion Data;
                    bool dataok = Com.Get_Medicion( &Pack_r[uinit], &Data, _length); //Obtiene Dato
                    if(dataok){
                        Serial.println(Data.mean,4);
                        //Reestablece
                        for(uint8_t i =0; i<uinit+_length;i++){ Pack_r[i] = 0; }  //Limpia buffer
                        len=len-(uinit+_length);
                        relativ_init=0;
                        return;
                    }
                    else{
                        // **Deberia continuar buscando en las siguientes posiciones hasta terminar, si entra aca quiere decir que se corrompieron los datos
                        continue;
                    }                    
                }
                else{
                    // **Deberia continuar buscando en las siguientes posiciones hasta terminar, si entra aca quiere decir que no corresponde a un Pack de datos
                    continue;
                }
              }
              else{
                // Deberia salir y esperar a llenar mas el buffer pues quiere decir que aun no llegan todos los datos del paquete
                return;
              }
          }
          else{
            // **Deberia continuar buscando en las siguientes posiciones hasta terminar, si entra aca quiere decir que length se corrompio o que es un dato de paquete
            continue;
          }
      }
      else{
        Serial.print("no encontro inicio");
          // **Deberia continuar buscando en las siguientes posiciones hasta terminar, si entra aca quiere decir que no ha encontrado el inicio de una trama
          continue;
      }

  }

  //Reinicia referencias y buffer
  for(uint8_t i =0; i<len;i++){ Pack_r[i] = 0; }  //Limpia buffer
  len=0;
  relativ_init=0;


  Serial.println("\n\n");
} 
