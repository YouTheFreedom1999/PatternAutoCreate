#include <stdio.h>
#include "IIC.h"

#define IIC_CREATE_PATTREN

unsigned char data_p[8];	 //页

void write_all_sample()
{
	IIC i2c;
	unsigned char add = 0;
	for (int i = 0; i < 16; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			if (j % 2 != 0)
				data_p[j] = 85;
			else
				data_p[j] = 170;
		}

		printf("START_INDEX(%d)//第%d页写入10-01\n", 25 + i, 1 + i);
		i2c.write_p(add, 8, data_p);
		add += 8;
	}

}
