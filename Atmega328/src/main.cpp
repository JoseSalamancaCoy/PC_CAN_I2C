#include <Arduino.h>
#include <Wire.h>
#include "CAN_r.h"
#include <TimerOne.h>

byte x = 0;
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
  Timer1.initialize(1000000);
  Timer1.attachInterrupt(IRQ_interrup);
}

void loop()
{
  if(Timeout){
    Timeout = false;
    Com.End_Slave();
    Com.Init_Master();
    Com.End_Master();
    Com.Init_Slave(receiveEvent);
  }
   //if(Timeout){Timeout = false; Serial.println("ok");} 

  delay(10);
}


void receiveEvent(int howMany) //Evento de recepcion i2c
{
  uint8_t len=0;
  static uint8_t Pack_r[255];
  uint8_t *_pack_r = &Pack_r[0];
  Serial.println("Evento    ");
  while(Wire.available()) // loop through all but the last
  {
    *_pack_r = (uint8_t) Wire.read();    // receive byte as an integer
    len++;
    Serial.print(*_pack_r);
    Serial.print(" ");
    _pack_r++;
  }
  Serial.println(" ");

  _pack_r = &Pack_r[0];
  if(*_pack_r == 2){  //Identifica si el byte corresponde a 2 o inicio de trama
      Serial.print("inicio de trama    ");
      _pack_r++; // Avanza a la siguiente posicion
      uint8_t _length = *_pack_r;
      if(_length > 7 && _length < 45){  // verifica si lengt esta entre la longitud maxima y minima de paquetes
          if(_length <= len){
            Serial.print("length <= len   ");
            _pack_r+=_length-2; // Se mueve a la posicion esperada para el fin de la trama 
            if(*_pack_r == 3){ //Determina si corresponde a 3 o fin de trama, con esto se define si los datos corresponden o no a un Pack de datos.
                Serial.print("Fin de trama OK    ");
                uint8_t _crc = Com.crc( &Pack_r[0], _length-2); //Calcula crc
                _pack_r--;  //Retrocede una posicion para obtener crc de trama
                if(*_pack_r == _crc){
                  Serial.print("crc OK    ");
                  _Medicion Dato = Com.Get_Medicion( &Pack_r[0], _length);
                  Serial.println(Dato.min,5);
                }
                else{
                    // **Deberia continuar buscando en las siguientes posiciones hasta terminar, si entra aca quiere decir que se corrompieron los datos
                }
            }
            else{
                // **Deberia continuar buscando en las siguientes posiciones hasta terminar, si entra aca quiere decir que no corresponde a un Pack de datos
            }
          }
          else{
            // Deberia salir y esperar a llenar mas el buffer pues quiere decir que aun no llegan todos los datos del paquete
          }
      }
      else{
        // **Deberia continuar buscando en las siguientes posiciones hasta terminar, si entra aca quiere decir que length se corrompio o que es un dato de paquete
      }
  }
  else{
    Serial.print("no encontro inicio");
      // **Deberia continuar buscando en las siguientes posiciones hasta terminar, si entra aca quiere decir que no ha encontrado el inicio de una trama
  }

  Serial.println("\n\n");

  //for(uint8_t i=0; i<150; i++) Pack_r[i] = 0; //Limpia buffer de escucha


} 
