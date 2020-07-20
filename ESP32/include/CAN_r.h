#include <Arduino.h>
#include <Wire.h>
#include "WireSlave.h"
#include "Pack_CAN_r.h"

#define _port_I2C 4

#define SDA_PIN 21
#define SCL_PIN 22
void static receiveEvent(int howMany);


class CAN_r : public Pack_CAN_r
{
private:
    uint8_t Pack[255];
    uint8_t len;
    uint8_t ReadAll(uint8_t *_pack_r,uint8_t len);
    void unPack(uint8_t *init, uint8_t _length, uint8_t uinit);

    void (*user_onReceive)(_Medicion);
    

public:
    CAN_r();
    ~CAN_r();
    void send(uint8_t val);
    void send(uint16_t val);
    void send(uint32_t val);
    void send(uint64_t val);
    void send(float val);
    void send(float mean, float max, float min, float desv);
    void send(_Medicion val);

    void Update();

    void Init_Master();
    void End_Master();
    void static Init_Slave();
    void End_Slave();
    void GetData(uint8_t howMany);


    void onReceive(void (*)(_Medicion));
    

};

extern CAN_r Com;

