#include <Arduino.h>
#include <Wire.h>

void receiveEvent(int howMany);

class CAN_r
{
private:

public:
    CAN_r(/* args */);
    ~CAN_r();
    void Init_Master();
    void End_Master();
    void Init_Slave();
    void End_Slave();
    void T_Master(uint8_t x);
};

