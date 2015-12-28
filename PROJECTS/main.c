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
     SPI1_Init(); //SPI1初始化
     SPI1_SetSpeed(SPI_BaudRatePrescaler_256);//SPI速度两分频
     SPI1_NVIC();   //设置抢占优先级为1，响应优先级为1
     
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
	   



