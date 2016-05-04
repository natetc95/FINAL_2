#define _SUPPRESS_PLIB_WARNING
#include <xc.h>
#include <sys/attribs.h>
#include "plib.h"
#include "config.h"
#include "interrupt.h"
#include "timer.h"
#include "i2c_imp.h"
#include "lcd.h"

#define SYS_CLK 10000000

int main(void){
    SYSTEMConfigPerformance(SYS_CLK);
    enableInterrupts();
    initI2CModule();
    int i;
    unsigned char data[6];
    int accel_x, accel_y, accel_z;
    initLCD();
    
    while(1){
        StartI2C2();
        IdleI2C2();
        MasterWriteI2C2(0xD0);
        IdleI2C2();
        MasterWriteI2C2(0x6B);
        IdleI2C2();
        MasterWriteI2C2(0x00);
        IdleI2C2();
        StopI2C2();
        IdleI2C2();
        
        delayMs(30);
        
        data[0] = readI2C(0x3B);
        data[1] = readI2C(0x3C);
        data[2] = readI2C(0x3D);
        data[3] = readI2C(0x3E);
        data[4] = readI2C(0x3F);
        data[5] = readI2C(0x40);
        StopI2C2();
        IdleI2C2();
        
        delayMs(30);
        accel_x = data[0] << 8 | data[1];
        accel_y = data[2] << 8 | data[3];
        accel_z = data[4] << 8 | data[5];
        
        char buf_1[7];
        char buf_2[7];
        char buf_3[7];
        
        sprintf(buf_1, "%3.0f ", 186*accel_x/32767);
        sprintf(buf_2, "%3.0f ", 186*accel_y/32767);
        sprintf(buf_3, "%3.0f", 186*accel_z/32767);
        
        clearLCD();
        
        printStringLCD(buf_1);
        printStringLCD(buf_2);
        printStringLCD(buf_3);
        
    }
    
    return 0;
}