#include <Arduino.h>


#define byte_init_data 0x02
#define byte_end_data 0x03

struct _Medicion{ //Estructura para almacenar mediciones
        float mean;
        float max;
        float min;
        float desv;
    };

class Pack_CAN_r
{
    public:
        Pack_CAN_r();
        ~Pack_CAN_r();
        
        uint8_t set_Pack(uint8_t val, uint8_t *pack);
        uint8_t set_Pack(uint16_t val, uint8_t *pack);
        uint8_t set_Pack(uint32_t val, uint8_t *pack);
        uint8_t set_Pack(uint64_t val, uint8_t *pack);
        uint8_t set_Pack(float val, uint8_t *pack);
        uint8_t set_Pack(double val, uint8_t *pack);
        uint8_t set_Pack(float mean, float max, float min, float desv, uint8_t *pack);
        uint8_t set_Pack(_Medicion val, uint8_t *pack);

        void set_id(uint8_t id);
        bool Get_Medicion(uint8_t *trama, _Medicion *data, uint8_t *id,uint8_t length);

        uint8_t crc(uint8_t *val,uint8_t length);


    private:
    
        uint8_t _id;

        enum type_dato{__uint8_t_,__uint16_t_,__uint32_t_,__uint64_t_,__float_,__double_,__char_,__Medicion_};

        struct _tag_uint8_t{
            uint8_t _init = byte_init_data;
            uint8_t _lengt;
            uint8_t _id;
            uint8_t _type;
            uint8_t _data;
            uint8_t _crc;
            uint8_t _end = byte_end_data;
        };
        struct _tag_uint16_t{
            uint8_t _init = byte_init_data;
            uint8_t _lengt;
            uint8_t _id;
            uint8_t _type;
            uint16_t _data;
            uint8_t _crc;
            uint8_t _end = byte_end_data;
        };        
        struct _tag_uint32_t{
            uint8_t _init = byte_init_data;
            uint8_t _lengt;
            uint8_t _id;
            uint8_t _type;
            uint32_t _data;
            uint8_t _crc;
            uint8_t _end = byte_end_data;
        };
        struct _tag_uint64_t{
            uint8_t _init = byte_init_data;
            uint8_t _lengt;
            uint8_t _id;
            uint8_t _type;
            uint64_t _data;
            uint8_t _crc;
            uint8_t _end = byte_end_data;
        };     
        struct _tag_float {
            uint8_t _init = byte_init_data;
            uint8_t _lengt;
            uint8_t _id;
            uint8_t _type;
            float _data;
            uint8_t _crc;
            uint8_t _end = byte_end_data;
        };
        struct _tag_double {
            uint8_t _init = byte_init_data;
            uint8_t _lengt;
            uint8_t _id;
            uint8_t _type;
            uint64_t _data;
            uint8_t _crc;
            uint8_t _end = byte_end_data;
        };
        struct _tag_char {
            uint8_t _init = byte_init_data;
            uint8_t _lengt;
            uint8_t _id;
            uint8_t _type;
            char  *_data;
            uint8_t _crc;
            uint8_t _end = byte_end_data;
        };
        struct _tag_Data {
            uint8_t _init = byte_init_data;
            uint8_t _lengt;
            uint8_t _id;
            uint8_t _type;
            _Medicion _data;
            uint8_t _crc;
            uint8_t _end = byte_end_data;
        };
};
