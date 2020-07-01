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
public:
    CAN_r();
    ~CAN_r();
    void send(uint8_t x);
    void update();
    void get();
};

