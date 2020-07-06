#include <Arduino.h>


#define byte_init_data 0x02
#define byte_end_data 0x03
class Pack_CAN_r
{
private:
       /* union _tag_uint8_t {
        struct {
            const uint8_t _init = 0x02;
            uint8_t _id;
            uint8_t _type;
            uint8_t _lengt;
            uint8_t _data;
            uint8_t _crc;
            uint8_t _end;
        };
        uint8_t _total[7];
    };
    union _tag_uint16_t {
        struct {
            const uint8_t _init = 0x02;
            uint8_t _id;
            uint8_t _type;
            uint8_t _lengt;
            uint16_t _data;
            uint8_t _crc;
            uint8_t _end;
        };
        uint8_t _total[8];
    };
    union _tag_uint32_t {
        struct {
            const uint8_t _init = 0x02;
            uint8_t _id;
            uint8_t _type;
            uint8_t _lengt;
            uint32_t _data;
            uint8_t _crc;
            uint8_t _end;
        }
        uint8_t _total[10];
    };
    union _tag_uint64_t {
        struct {
            const uint8_t _init = 0x02;
            uint8_t _id;
            uint8_t _type;
            uint8_t _lengt;
            uint64_t _data;
            uint8_t _crc;
            uint8_t _end;
        }        
        uint8_t _total[15];
    };
    union _tag_float {
        const uint8_t _init = 0x02;
        uint8_t _id;
        uint8_t _type;
        uint8_t _lengt;
        float _data;
        uint8_t _crc;
        uint8_t _end;
        uint8_t _total[10];
    } data_uint16_t;
    union _tag_double {
        const uint8_t _init = 0x02;
        uint8_t _id;
        uint8_t _type;
        uint8_t _lengt;
        uint64_t _data;
        uint8_t _crc;
        uint8_t _end;
        uint8_t _total[14];
    } data_double;
    union _tag_char {
        const uint8_t _init = 0x02;
        uint8_t _id;
        uint8_t _type;
        uint8_t _lengt;
        void* _data;
        uint8_t _crc;
        uint8_t _end;
        uint8_t *_total;
    } data_double;*/
    enum type_dato{__uint8_t_,__uint16_t_,__uint32_t_,__uint64_t_,__float_,__double_,__char_,__Medicion_};
    struct _Medicion{
        float mean;
        float max;
        float min;
        float desv;
    };
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
    uint8_t _id;
public:
    Pack_CAN_r();
    ~Pack_CAN_r();
    void begin(uint8_t id);
    uint8_t set_Pack(uint8_t val, uint8_t *pack);
    uint8_t set_Pack(uint16_t val, uint8_t *pack);
    uint8_t set_Pack(uint32_t val, uint8_t *pack);
    uint8_t set_Pack(uint64_t val, uint8_t *pack);
    uint8_t set_Pack(float val, uint8_t *pack);
    uint8_t set_Pack(double val, uint8_t *pack);
    uint8_t set_Pack(float mean, float max, float min, float desv, uint8_t *pack);
    uint8_t crc(uint8_t *val,uint8_t length);
};
