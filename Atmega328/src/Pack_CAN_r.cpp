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

uint8_t Pack_CAN_r::crc(uint8_t *data, uint8_t length) {
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

uint8_t Pack_CAN_r::set_Pack(uint8_t val, uint8_t *pack){ 
    // Se llena la trama para transmitir
    _tag_uint8_t trama;
    uint8_t *_pack;
    trama._lengt = 6 + 1; // 4 + length(Val)
    trama._id = _id;
    trama._type = __uint8_t_;
    trama._data = val;
    trama._crc = crc(&trama._init, 5);

    _pack= &trama._init;
    for(int i =0; i<trama._lengt;i++) *pack++ =*_pack++; //Copia datos en puntero externo
    return trama._lengt; // Retorna la longitud del vector
}
uint8_t Pack_CAN_r::set_Pack(uint16_t val, uint8_t *pack){
    _tag_uint16_t trama;
    uint8_t *_pack;
    trama._lengt = 6 + 2; // 4 + length(Val)
    trama._id = _id;
    trama._type = __uint16_t_;
    trama._data = val;
    trama._crc = crc(&trama._init, 4);

    _pack= &trama._init;
    for(int i =0; i<trama._lengt;i++) *pack++ =*_pack++; //Copia datos en puntero externo
    return trama._lengt; // Retorna la longitud del vector
}
uint8_t Pack_CAN_r::set_Pack(uint32_t val, uint8_t *pack){
    _tag_uint32_t trama;
    uint8_t *_pack;
    trama._lengt = 6 + 4; // 4 + length(Val)
    trama._id = _id;
    trama._type = __uint32_t_;
    
    trama._data = val;
    trama._crc = crc(&trama._init, 4);

    _pack= &trama._init;
    for(int i =0; i<trama._lengt;i++) *pack++ =*_pack++; //Copia datos en puntero externo
    return trama._lengt; // Retorna la longitud del vector
}
uint8_t Pack_CAN_r::set_Pack(uint64_t val, uint8_t *pack){
    _tag_uint64_t trama;
    uint8_t *_pack;
    trama._lengt = 6 + 8; // 4 + length(Val)
    trama._id = _id;
    trama._type = __uint64_t_;
    trama._data = val;
    trama._crc = crc(&trama._init, 4);
    
    _pack= &trama._init;
    for(int i =0; i<trama._lengt;i++) *pack++ =*_pack++; //Copia datos en puntero externo
    return trama._lengt; // Retorna la longitud del vector
}
uint8_t Pack_CAN_r::set_Pack(float val, uint8_t *pack){
    _tag_float trama;
    uint8_t *_pack;
    trama._lengt = 6 + 4; // 4 + length(Val)
    trama._id = _id;
    trama._type = __float_;
    trama._data = val;
    trama._crc = crc(&trama._init, 4);
    
    _pack= &trama._init;
    for(int i =0; i<trama._lengt;i++) *pack++ =*_pack++; //Copia datos en puntero externo
    return trama._lengt; // Retorna la longitud del vector
}
uint8_t Pack_CAN_r::set_Pack(double val, uint8_t *pack){
    _tag_double trama;
    uint8_t *_pack;
    trama._lengt = 6 + 8; // 4 + length(Val)
    trama._id = _id;
    trama._type = __double_;
    trama._data = val;
    trama._crc = crc(&trama._init, 4);

    _pack= &trama._init;
    for(int i =0; i<trama._lengt;i++) *pack++ =*_pack++; //Copia datos en puntero externo
    return trama._lengt; // Retorna la longitud del vector
}
uint8_t Pack_CAN_r::set_Pack(float mean, float max, float min, float desv, uint8_t *pack){
    _tag_Data trama;
    _Medicion val;
    uint8_t *_pack;

    val.mean = mean; val.max = max; val.min =min; val.desv = desv;
    trama._lengt = 6 + 16; // 4 + length(Val)
    trama._id = _id;
    trama._type = __Medicion_;
    trama._data = val;
    trama._crc = crc(&trama._init, 4);

    _pack= &trama._init;
    for(int i =0; i<trama._lengt;i++) *pack++ =*_pack++; //Copia datos en puntero externo
    return trama._lengt; // Retorna la longitud del vector
}


uint8_t Pack_CAN_r::set_Pack(_Medicion val, uint8_t *pack){
    _tag_Data trama;
    uint8_t *_pack;

    trama._lengt = 6 + 16; // 4 + length(Val)
    trama._id = _id;
    trama._type = __Medicion_;
    trama._data = val;
    trama._crc = crc(&trama._init, 20);

    _pack= &trama._init;
    for(int i =0; i<trama._lengt;i++) *pack++ =*_pack++; //Copia datos en puntero externo
    return trama._lengt; // Retorna la longitud del vector
}