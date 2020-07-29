#include <stdio.h>
#include <String>
#include "IIC.h"
//默认识别地址000


#ifdef IIC_CREATE_PATTREN


/****************************************
	//IIC开始条件
	//SCL为高电平时
	//SDA由高电平切换到低电平
*****************************************/
void IIC::start()
{
	printf("//开始条件\n");

	SCL = '1';
	SDA = '1';
	printf("  INC\t(000 %c %c)\n", SCL, SDA);

	SDA = '0';
	printf("  INC\t(000 %c %c)\n", SCL, SDA);

	SCL = '0';
	SDA = '0';
	printf("  INC\t(000 %c %c)\n", SCL, SDA);
}


/*
	//图形停
	//仅适用于逻辑功能测试
*/
void IIC::HALT()
{
	printf("//图形停\n");
	printf("  HALT\t(000 0 X)\n");
}


/****************************************
	//终止条件
	//SCL为高电平时
	//SDA由低电平切换到高电平
******************************************/
void IIC::stop()
{
	printf("//终止条件\n");

	SCL = '1';
	SDA = '0';
	printf("  INC\t(000 %c %c)\n", SCL, SDA);

	SDA = '1';
	printf("  INC\t(000 %c %c)\n", SCL, SDA);

	SCL = '0';
	SDA = '1';
	printf("  INC\t(000 %c %c)\n", SCL, SDA);
}


/****************************************
	//设备识别
	//开始条件后进行设备与模式选择
	//rw:0为读模式; 1为写模式
	//t: 设备标识号 
	// 1 0 1 0 A2 A1 A0 R/W
******************************************/
void IIC::adv_id(bool rw, unsigned char t)
{
	t = t << 5;
	printf("//设备识别\n");

	printf("  INC\t(000 0 1)\n");
	printf("  INC\t(000 1 1)\n"); //1

	printf("  INC\t(000 0 0)\n");
	printf("  INC\t(000 1 0)\n"); //2

	printf("  INC\t(000 0 1)\n");
	printf("  INC\t(000 1 1)\n"); //3

	printf("  INC\t(000 0 0)\n");
	printf("  INC\t(000 1 0)\n"); //4

	//取A2
	if (t >> 7 == 1)
		SDA = '1';
	else
		SDA = '0';
	t = t << 1;
	printf("  INC\t(000 0 %c)\n", SDA);
	printf("  INC\t(000 1 %c)\n", SDA); //5

	//取A1
	if (t >> 7 == 1)
		SDA = '1';
	else
		SDA = '0';
	t = t << 1;
	printf("  INC\t(000 0 %c)\n", SDA);
	printf("  INC\t(000 1 %c)\n", SDA); //6

	//取A0
	if (t >> 7 == 1)
		SDA = '1';
	else
		SDA = '0';
	t = t << 1;
	printf("  INC\t(000 0 %c)\n", SDA);
	printf("  INC\t(000 1 %c)\n", SDA); //7

	//R/W
	if (rw)
	{
		printf("  INC\t(000 0 1)\n");
		printf("  INC\t(000 1 1)\n");
	}

	else
	{
		printf("  INC\t(000 0 0)\n");
		printf("  INC\t(000 1 0)\n");
	}
}


/****************************************
	//发送应答
******************************************/
void IIC::ACK_send()
{
	printf("//应答\n");
	printf("  INC\t(000 0 0)\n");
}


/****************************************
	//接受应答
******************************************/
void IIC::ACK_recive()
{
	printf("//应答\n");
	printf("  INC\t(000 0 L)\n");
}


/****************************************
	//向add中写入数据data
	//add data 均为八位二进制数
	//设备ID默认为0
******************************************/
void IIC::write_k(unsigned char add, unsigned char data)
{
	start();
	adv_id(0, 0);
	ACK_recive();

	printf("//写地址\n");

	for (int i = 0; i < 8; i++)
	{
		if (add >> 7 == 1)
			SDA = '1';
		else
			SDA = '0';
		add = add << 1;
		SCL = '0';
		printf("  INC\t(000 %c %c)\n", SCL, SDA);
		SCL = '1';
		printf("  INC\t(000 %c %c)\n", SCL, SDA);
	}

	ACK_recive();

	printf("//写数据\n");
	for (int i = 0; i < 8; i++)
	{
		if (data >> 7 == 1)
			SDA = '1';
		else
			SDA = '0';
		data = data << 1;
		SCL = '0';
		printf("  INC\t(000 %c %c)\n", SCL, SDA);
		SCL = '1';
		printf("  INC\t(000 %c %c)\n", SCL, SDA);
	}

	stop();
	HALT();
}


/****************************************
	//以add为起始地址写入数据
	//写入8个字节
******************************************/
void IIC::write_p(unsigned char add, unsigned char *data_p)
{
	start();
	adv_id(0, 0);
	ACK_recive();

	printf("//写地址\n");

	for (int i = 0; i < 8; i++)
	{
		if (add >> 7 == 1)
			SDA = '1';
		else
			SDA = '0';

		add = add << 1;

		SCL = '0';
		printf("  INC\t(000 %c %c)\n", SCL, SDA);

		SCL = '1';
		printf("  INC\t(000 %c %c)\n", SCL, SDA);
	}

	ACK_recive();

	printf("//写数据\n");

	for (int j = 0; j < 8; j++)
	{
		printf("//写入第%d个数据\n", j + 1);
		for (int i = 0; i < 8; i++)
		{
			if (data_p[j] >> 7 == 1)
				SDA = '1';
			else
				SDA = '0';

			data_p[j] = data_p[j] << 1;

			SCL = '0';
			printf("  INC\t(000 %c %c)\n", SCL, SDA);

			SCL = '1';
			printf("  INC\t(000 %c %c)\n", SCL, SDA);
		}

		ACK_recive();
	}

	stop();
	HALT();
}


/****************************************
	//以add为起始地址读出数据
	//读出一个字节
******************************************/
void IIC::read_k(unsigned char add, unsigned char data)
{
	start();
	adv_id(0, 0);
	ACK_recive();

	printf("//写地址\n");

	for (int i = 0; i < 8; i++)
	{
		if (add >> 7 == 1)
			SDA = '1';
		else
			SDA = '0';

		add = add << 1;

		SCL = '0';
		printf("  INC\t(000 %c %c)\n", SCL, SDA);

		SCL = '1';
		printf("  INC\t(000 %c %c)\n", SCL, SDA);
	}
	ACK_recive();

	start();
	adv_id(1, 0);
	ACK_recive();

	printf("//读数据\n");

	for (int i = 0; i < 8; i++)
	{
		SCL = '1';
		SDA = 'X';
		printf("  INC\t(000 %c %c)\n", SCL, SDA);

		if (data >> 7 == 1)
			SDA = 'H';
		else
			SDA = 'L';

		data = data << 1;

		SCL = '0';
		printf("  INC\t(000 %c %c)\n", SCL, SDA);
	}

	stop();
}

/****************************************
	//以add为起始地址读出数据
	//顺序读出num个字节
******************************************/
void IIC::read_p(unsigned char add, int num, unsigned char *data_all)
{
	start();
	adv_id(0, 0);
	ACK_recive();

	printf("//写地址\n");

	for (int i = 0; i < 8; i++)
	{
		if (add >> 7 == 1)
			SDA = '1';
		else
			SDA = '0';

		add = add << 1;

		SCL = '0';
		printf("  INC\t(000 %c %c)\n", SCL, SDA);

		SCL = '1';
		printf("  INC\t(000 %c %c)\n", SCL, SDA);
	}
	ACK_recive();

	start();
	adv_id(1, 0);
	ACK_recive();

	for (int j = 0; j < num; j++)
	{
		printf("//读第%d数据\n", j + 1);
		for (int i = 0; i < 8; i++)
		{
			SCL = '1';
			SDA = 'X';
			printf("  INC\t(000 %c %c)\n", SCL, SDA);

			if (data_all[j] >> 7 == 1)
				SDA = 'H';
			else
				SDA = 'L';

			data_all[j] = data_all[j] << 1;

			SCL = '0';
			printf("  INC\t(000 %c %c)\n", SCL, SDA);
		}

		ACK_send();
	}

	stop();
}
//真是白费了
#endif
