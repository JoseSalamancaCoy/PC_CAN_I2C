#include "Pack_CAN_r.h"

Pack_CAN_r::Pack_CAN_r()
{

}

Pack_CAN_r::~Pack_CAN_r()
{
}

void Pack_CAN_r::begin(uint8_t id)
{
    _id = id;
}

 uint8_t crc(uint8_t *data, uint8_t length) {
        uint8_t crc = 0;
        uint8_t extract;
        uint8_t sum;

        for (unsigned int i = 0; i < length; i++) {
            extract = *data;

            for (char j = 8; j; j--) {
                sum = (crc ^ extract) & 0x01;
                crc >>= 1;
                if (sum) {
                    crc ^= 0x8C;
                }
                extract >>= 1;
            }

            data++;
        }

        return crc;
    }

void Pack_CAN_r::set_Pack(uint8_t val){ 
    // Se llena la trama para transmitir
    _tag_uint8_t trama;
    trama._id = _id;
    trama._type = __uint8_t_;
    trama._lengt = 1;
    trama._data = val;
    trama._crc = 10;//crc(&trama._init, 4);

    // Se llena paquete de dato
    PackDato.tipo = __uint8_t_;
    PackDato._uint8 = trama;
}
/*void Pack_CAN_r::set_Pack(uint16_t){}
void Pack_CAN_r::set_Pack(uint32_t){}
void Pack_CAN_r::set_Pack(uint64_t){}
void Pack_CAN_r::set_Pack(float){}
void Pack_CAN_r::set_Pack(double){}
void Pack_CAN_r::set_Pack(float, float, float, float){}*/