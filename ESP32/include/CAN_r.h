#include <Arduino.h>
#include <Wire.h>
#include "Pack_CAN_r.h"
void receiveEvent(int howMany);

class CAN_r : public Pack_CAN_r
{
private:
    void Init_Master();
    void End_Master();
    void Init_Slave();
    void End_Slave();
    void T_Master(uint8_t x);
    uint8_t Pack[150];
    uint8_t len;
public:
    CAN_r();
    ~CAN_r();
    void send(uint8_t val);
    void send(uint16_t val);
    void send(uint32_t val);
    void send(uint64_t val);
    void send(float val);
    void send(float mean, float max, float min, float desv);
    void update();
    void get();
};

