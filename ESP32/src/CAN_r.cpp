#include "CAN_r.h"

CAN_r::CAN_r()
{
}

CAN_r::~CAN_r()
{

}

void CAN_r::send(uint8_t val)
{
  len = set_Pack(val, &Pack[0]);
  Wire.beginTransmission(_port_I2C); // transmit to device #4
  Wire.write(&Pack[0], len) ;         // sends one byte  
  Wire.endTransmission();    // stop transmitting
  Serial.println("");
}

void CAN_r::send(uint16_t val){
  len = set_Pack(val, &Pack[0]);
  Wire.beginTransmission(_port_I2C); // transmit to device #4
  Wire.write(&Pack[0], len) ;         // sends one byte  
  Wire.endTransmission();    // stop transmitting
  Serial.println("");
}

void CAN_r::send(uint32_t val){
  len = set_Pack(val, &Pack[0]);
  Wire.beginTransmission(_port_I2C); // transmit to device #4
  Wire.write(&Pack[0], len) ;         // sends one byte  
  Wire.endTransmission();    // stop transmitting
  Serial.println("");
}

void CAN_r::send(uint64_t val){
  len = set_Pack(val, &Pack[0]);
  Wire.beginTransmission(_port_I2C); // transmit to device #4
  Wire.write(&Pack[0], len) ;         // sends one byte  
  Wire.endTransmission();    // stop transmitting
  Serial.println("");
}

void CAN_r::send(float val){
  len = set_Pack(val, &Pack[0]);
  Wire.beginTransmission(_port_I2C); // transmit to device #4
  Wire.write(&Pack[0], len) ;         // sends one byte  
  Wire.endTransmission();    // stop transmitting
  Serial.println("");
}

void CAN_r::send(float mean, float max, float min, float desv){
  len = set_Pack(mean,max,min,desv, &Pack[0]);
  Wire.beginTransmission(_port_I2C); // transmit to device #4
  Wire.write(&Pack[0], len) ;         // sends one byte  
  Wire.endTransmission();    // stop transmitting
  Serial.println("");
}

void CAN_r::send(_Medicion val){
  len = set_Pack(val, &Pack[0]);
  Wire.beginTransmission(_port_I2C); // transmit to device #4
  Wire.write(&Pack[0], len) ;         // sends one byte  
  Wire.endTransmission();    // stop transmitting
}


void CAN_r::Init_Master(){

  Wire.begin();  //i2c master init
}

void CAN_r::End_Master(){
  
}

void CAN_r::Init_Slave(){
  bool success = WireSlave.begin(SDA_PIN, SCL_PIN, _port_I2C);
  if (!success) {
      Serial.println("I2C slave init failed");
      while(1) delay(100);
  }
  WireSlave.onReceive(receiveEvent);
}
void CAN_r::Update(){
    WireSlave.update();
}

void CAN_r::End_Slave(){
  WireSlave.update();
  WireSlave.loose();
}


uint8_t CAN_r::ReadAll(uint8_t *_pack_r,uint8_t len){
  while(WireSlave.available()) // loop through all but the last
  {
    *_pack_r = (uint8_t) WireSlave.read();    // receive byte as an integer
    len++;
    Serial.print(*_pack_r);
    Serial.print(" ");
    _pack_r++;
  }
  return len;
}

void CAN_r::GetData(uint8_t howMany){
  
    
  //Llenado de buffer
  static uint8_t len;
  static uint8_t Pack_r[255];
  static uint8_t relativ_init;
  uint8_t *_pack_r = &Pack_r[len];

  len = ReadAll(_pack_r, len);

  // uinit posicion relativa y supuesta de inicio de trama
  for(uint8_t uinit=relativ_init; uinit<len; uinit++){

      _pack_r = &Pack_r[uinit];
      //Serial.print("inicio =    "); Serial.println(*_pack_r);
      if(*_pack_r == 2){  //Identifica si el byte corresponde a 2 o inicio de trama
          _pack_r++; // Avanza a la siguiente posicion
          uint8_t _length = *_pack_r;
          if(_length > 7 && _length < 40){  // verifica si lengt esta entre la longitud maxima y minima de paquetes
              if(_length <= len-uinit){
                _pack_r+=_length-2; // Se mueve a la posicion esperada para el fin de la trama 
                if(*_pack_r == 3){ //Determina si corresponde a 3 o fin de trama, con esto se define si los datos corresponden o no a un Pack de datos.
                
                    _Medicion Data;
                    bool dataok = Get_Medicion( &Pack_r[uinit], &Data, _length); //Obtiene Dato
                    if(dataok){
                        Serial.print("Mean =   ");Serial.println(Data.mean,4);
                        //Reestablece
                        for(uint8_t i =0; i<uinit+_length;i++){ Pack_r[i] = 0; }  //Limpia buffer
                        relativ_init=0;
                        continue;
                    }
                    else{
                        // **Deberia continuar buscando en las siguientes posiciones hasta terminar, si entra aca quiere decir que se corrompieron los datos
                        //Reestablece
                        Serial.println("Data Corrupta");
                        for(uint8_t i =0; i<uinit+_length;i++){ Pack_r[i] = 0; }  //Limpia buffer
                        relativ_init=0;
                        continue;
                    }                    
                }
                else{
                    // **Deberia continuar buscando en las siguientes posiciones hasta terminar, si entra aca quiere decir que no corresponde a un Pack de datos
                    Serial.print("No fin");
                    continue;
                }
              }
              else{
                // Deberia salir y esperar a llenar mas el buffer pues quiere decir que aun no llegan todos los datos del paquete
                Serial.print("Buffer Incompleto");
                return;
              }
          }
          else{
            // **Deberia continuar buscando en las siguientes posiciones hasta terminar, si entra aca quiere decir que length se corrompio o que es un dato de paquete
            Serial.print("OutLenggth");
            continue;
          }
      }
      else{
        //Serial.print("NO Init");
          // **Deberia continuar buscando en las siguientes posiciones hasta terminar, si entra aca quiere decir que no ha encontrado el inicio de una trama
          continue;
      }

  }

  //Reinicia referencias y buffer
  for(uint8_t i =0; i<255;i++){ Pack_r[i] = 0; }  //Limpia buffer
    len=0;
    relativ_init=0;


  Serial.println("\n\n");
}

void receiveEvent(int howMany) //Evento de recepcion i2c
{
  Com.GetData(howMany);
} 


