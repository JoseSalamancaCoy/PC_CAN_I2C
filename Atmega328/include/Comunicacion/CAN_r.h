#include <Arduino.h>
#include <Wire.h>
#include "Pack_CAN_r.h"


#define _port_I2C 4
void receiveEvent(int howMany);


class CAN_r: public Pack_CAN_r
{
private: 
    uint8_t Pack[BUFFER_LENGTH];
    uint8_t len;

    void Init_Master();
    void End_Master();
    void End_Slave();  
    void Init_Slave();

    uint8_t ReadAll(uint8_t *_pack_r,uint8_t len);
    void unPack(uint8_t *init, uint8_t _length, uint8_t uinit);

    void (*user_onReceive)(_Medicion, uint8_t);


public:
    CAN_r(/* args */);
    ~CAN_r();
    void begin();
    void end();
    void send(uint8_t val, uint8_t id);
    void send(uint16_t val, uint8_t id);
    void send(uint32_t val, uint8_t id);
    void send(uint64_t val, uint8_t id);
    void send(float val, uint8_t id);
    void send(float mean, float max, float min, float desv, uint8_t id);
    void send(_Medicion val, uint8_t id);

    void GetData(uint8_t howMany);

    void onReceive(void (*)(_Medicion, uint8_t));
};

extern CAN_r Com;
