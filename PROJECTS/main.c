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
#include "can.h"
#include "led.h"
#include "ewdt.h"

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

void can_test(void)
 {	 
	u8 i=0,t=0;
	u8 cnt=0;
	u8 canbuf[8];
	u8 res;
        u8 can_rcv;
	u8 mode=CAN_Mode_LoopBack;//CAN工作模式;CAN_Mode_Normal(0)：普通模式，CAN_Mode_LoopBack(1)：环回模式

	 	
   
	CAN_Mode_Init(CAN_SJW_1tq,CAN_BS2_8tq,CAN_BS1_9tq,4,CAN_Mode_LoopBack);//CAN初始化环回模式,波特率500Kbps    

	
 	while(1)
	{

		if(mode==CAN_Mode_LoopBack)//KEY0按下,发送一次数据
		{
			for(i=0;i<8;i++)
			{
				canbuf[i]=cnt+i;//填充发送缓冲区
				if(i<4)printf("%s",canbuf[i]);	//显示数据
				else printf("%s",canbuf[i]);	//显示数据
 			}
			res=Can_Send_Msg(canbuf,8);//发送8个字节 
			if(res)printf("Failed");		//提示发送失败
			else printf("OK    ");	 		//提示发送成功								   
		}else if(mode==CAN_Mode_Normal)//WK_UP按下，改变CAN的工作模式
		{	   
//			mode=!mode;
  			CAN_Mode_Init(CAN_SJW_1tq,CAN_BS2_8tq,CAN_BS1_9tq,4,CAN_Mode_Normal);//CAN普通模式初始化, 波特率500Kbps 

			if(mode==0)//普通模式，需要2个开发板
			{
				printf("Nnormal Mode ");	    
			}else //回环模式,一个开发板就可以测试了.
			{
 				printf("LoopBack Mode");
			}

		}		 
		can_rcv=Can_Receive_Msg(canbuf);
		if(can_rcv)//接收到有数据
		{			
			
 			for(i=0;i<can_rcv;i++)
			{									    
				if(i<4)printf("%s",canbuf[i]);	//显示数据
				else printf("%s",canbuf[i]);	//显示数据
 			}
		}
		t++; 
		delay_ms(10);
		if(t==20)
		{
			LED=!LED;//提示系统正在运行	
			t=0;
			cnt++;
			printf("%d",cnt);	//显示数据
		}		   
	}
}


int main(void)
{ 
     NVIC_Configuration();
     
     delay_init();
     
        //外部看门狗初始化
//        EWDT_Drv_pin_config();
//        power_on_bsp_check();
     
     
     
     
#if 1     
    spi1_test();
#else
  #if 1
      can_test();
  #else
      
  #endif
    
#endif

}
	   



