#include "CAN_r.h"

CAN_r::CAN_r()
{
}

CAN_r::~CAN_r()
{

}

void CAN_r::send(uint8_t val, uint8_t id){
  Update();
  End_Slave();
  Init_Master(); 
  set_id(id);
  len = set_Pack(val, &Pack[0]);
  Wire.beginTransmission(_port_I2C); // transmit to device #4
  Wire.write(&Pack[0], len) ;         // sends one byte  
  Wire.endTransmission();    // stop transmitting
  End_Master();
  Init_Slave();
}

void CAN_r::send(uint16_t val, uint8_t id){
  Update();
  End_Slave();
  Init_Master(); 
  set_id(id);
  len = set_Pack(val, &Pack[0]);
  Wire.beginTransmission(_port_I2C); // transmit to device #4
  Wire.write(&Pack[0], len) ;         // sends one byte  
  Wire.endTransmission();    // stop transmitting
  End_Master();
  Init_Slave();
}

void CAN_r::send(uint32_t val, uint8_t id){
  Update();
  End_Slave();
  Init_Master(); 
  set_id(id);
  len = set_Pack(val, &Pack[0]);
  Wire.beginTransmission(_port_I2C); // transmit to device #4
  Wire.write(&Pack[0], len) ;         // sends one byte  
  Wire.endTransmission();    // stop transmitting
  End_Master();
  Init_Slave();
}

void CAN_r::send(uint64_t val, uint8_t id){
  Update();
  End_Slave();
  Init_Master(); 
  set_id(id);
  len = set_Pack(val, &Pack[0]);
  Wire.beginTransmission(_port_I2C); // transmit to device #4
  Wire.write(&Pack[0], len) ;         // sends one byte  
  Wire.endTransmission();    // stop transmitting
  End_Master();
  Init_Slave();
}

void CAN_r::send(float val, uint8_t id){
  Update();
  End_Slave();
  Init_Master(); 
  set_id(id);
  len = set_Pack(val, &Pack[0]);
  Wire.beginTransmission(_port_I2C); // transmit to device #4
  Wire.write(&Pack[0], len) ;         // sends one byte  
  Wire.endTransmission();    // stop transmitting
  End_Master();
  Init_Slave();
}

void CAN_r::send(float mean, float max, float min, float desv, uint8_t id){
  Update();
  End_Slave();
  Init_Master(); 
  set_id(id);
  len = set_Pack(mean,max,min,desv, &Pack[0]);
  Wire.beginTransmission(_port_I2C); // transmit to device #4
  Wire.write(&Pack[0], len) ;         // sends one byte  
  Wire.endTransmission();    // stop transmitting
  End_Master();
  Init_Slave();
}

void CAN_r::send(_Medicion val, uint8_t id){
  Update();
  End_Slave();
  Init_Master(); 
  set_id(id);
  len = set_Pack(val, &Pack[0]);
  Wire.beginTransmission(_port_I2C); // transmit to device #4
  Wire.write(&Pack[0], len) ;         // sends one byte  
  Wire.endTransmission();    // stop transmitting
  End_Master();
  Init_Slave();
}


void CAN_r::End_Slave(){
  WireSlave.update();
  WireSlave.loose();
}

void CAN_r::Init_Master(){

  Wire.begin();  //i2c master init
}

void CAN_r::End_Master(){
  Wire.loose();
}
void CAN_r::Update(){
    WireSlave.update();
}



void CAN_r::Init_Slave(){
  bool success = WireSlave.begin(SDA_PIN, SCL_PIN, _port_I2C);
  if (!success) {
      Serial.println("I2C slave init failed");
      while(1) delay(100);
  }
  WireSlave.onReceive(receiveEvent);
}



uint8_t CAN_r::ReadAll(uint8_t *_pack_r,uint8_t len){
  while(WireSlave.available()) // loop through all but the last
  {
    *_pack_r = (uint8_t) WireSlave.read();    // receive byte as an integer
    len++;
    _pack_r++;
  }
  return len;
}
void CAN_r::unPack(uint8_t *init, uint8_t _length, uint8_t uinit){
    _Medicion Data;
    bool dataok = Get_Medicion(init, &Data, _length); //Obtiene Dato
    if(dataok){
        user_onReceive(Data); //Evento de newData
    }
}

void CAN_r::GetData(uint8_t howMany){
  //Llenado de buffer
  static uint8_t len;
  static uint8_t Pack_r[255];
  uint8_t *_pack_r = &Pack_r[len];

  len = ReadAll(_pack_r, len);

  // uinit posicion relativa y supuesta de inicio de trama
  for(uint8_t uinit=0; uinit<len; uinit++){
      _pack_r = &Pack_r[uinit];
      if(*_pack_r == 2){  //Identifica si el byte corresponde a 2 o inicio de trama
          _pack_r++; // Avanza a la siguiente posicion
          uint8_t _length = *_pack_r;
          if(_length > 7 && _length < 40){  // verifica si lengt esta entre la longitud maxima y minima de paquetes
              if(_length <= len-uinit){
                _pack_r+=_length-2; // Se mueve a la posicion esperada para el fin de la trama 
                if(*_pack_r == 3){  //Determina si corresponde a 3 o fin de trama.
                  unPack(&Pack_r[uinit],_length, uinit);                                     
                }
              }
              else{
                // Deberia salir y esperar a llenar mas el buffer pues quiere decir que aun no llegan todos los datos del paquete
                return;
              }
          }
      }

  }
  //Reinicia referencias y buffer
  for(uint8_t i =0; i<255;i++){ Pack_r[i] = 0; }  //Limpia buffer
  len=0;
}

void CAN_r::onReceive(void (*function)(_Medicion))
{
    user_onReceive = function;
}

void receiveEvent(int howMany) //Evento de recepcion i2c
{
  Com.GetData(howMany);
} 


