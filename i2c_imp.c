#define _SUPPRESS_PLIB_WARNING
#include "i2c_imp.h"
#include "plib.h"

void initI2CModule(){
    OpenI2C2(I2C_ON, 1024);
}

char readI2C(char address){
    char data;
    StartI2C2();
    IdleI2C2();
    MasterWriteI2C2(0xD0);
    IdleI2C2();
    MasterWriteI2C2(address);
    IdleI2C2();

    RestartI2C2();
    IdleI2C2();
    MasterWriteI2C2(0xD1);
    IdleI2C2();
    data = MasterReadI2C2();
    IdleI2C2();
    return data;
}

float sensor_Out(int q) {
    float out;
    short l = q >> 16;
    q = q & 0b0111111111111111;
    out = q/32767 * 18.6;
    if(l == 1) {
        out = out * -1;
    }
}