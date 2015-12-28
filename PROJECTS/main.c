/****************************************Copyright (c)****************************************************
** File Name:           main.c
** Created By:          lisonchen
** Created date:        2015-12-22
** Version:             v0.1
** Descriptions:        stm32f103xb
** Last Update:                    
*********************************************************************************************************/

#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "spi.h"

extern u8 Slave_Temp;

void spi1_test(void)
{
     SPI1_Init(); //SPI1��ʼ��
     SPI1_SetSpeed(SPI_BaudRatePrescaler_256);//SPI�ٶ�����Ƶ
     SPI1_NVIC();   //������ռ���ȼ�Ϊ1����Ӧ���ȼ�Ϊ1
     
     while(1)
     { 
       printf("Slave_Temp=%x\r\n",Slave_Temp);
       delay_ms(100); 
     }

}

int main(void)
{ 
     NVIC_Configuration();
     
     delay_init();
     
    spi1_test();

}
	   



