#ifndef Common_H
#define Common_H

#include <stdio.h>

enum id_Variable{
    __t=10,         __t_log=40,
    __h=11,         __h_log=41,
    __p=12,         __p_log=42,
    __pm10_1=13,    __pm10_1_log=43,
    __pm10_2=14,    __pm10_2_log=44,
    __pm25_1=15,    __pm25_1_log=45,
    __pm25_2=16,    __pm25_2_log=46,
    __pm1_1=17,     __pm1_1_log=47,
    __pm1_2=18,     __pm1_2_log=48,
    __ruido=19,     __ruido_log=49,
    __ir=20,        __ir_log=50,
    __il=21,        __il_log=51,
    __a=22,         __a_log=52,
    __lluvia=23,    __lluvia_log=53,

    __V_Bat=64,     __V_Bat_log=94,
    __V_Cargador=65,__V_Cargador_log=95,
    __V_110=66,     __V_110_log=96,
    __V_Panel=67,   __V_Panel_log=97,

                    __Aire_log=40,
                    __Clima_log=40,
                    __Power_log=40,
                    __Main_log=40
};

struct _Medicion{ //Estructura para almacenar mediciones
        float mean;
        float max;
        float min;
        float desv;
    };

#endif