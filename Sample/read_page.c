#include <stdio.h>
#include "IIC.h"

#define IIC_CREATE_PATTREN

unsigned char data_all[128]; //全储存器

void read_page_sample()
{
    IIC i2c;
    for (int i = 0; i < 128; i++)
    {
        if (i % 2 == 0)
            data_all[i] = 170;
        else
            data_all[i] = 85;
    }

    i2c.read_p(0, 128, data_all);
    HALT();
    
}
