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
#include "hw_test.h"

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
	u8 mode=CAN_Mode_Normal;//CAN_Mode_LoopBack;//CAN工作模式;CAN_Mode_Normal(0)：普通模式，CAN_Mode_LoopBack(1)：环回模式

	 	
   
	CAN_Mode_Init(CAN_SJW_2tq,CAN_BS2_5tq,CAN_BS1_3tq,20,mode);//CAN初始化环回模式,波特率180Kbps    

	
 	while(1)
	{


                for(i=0;i<8;i++)
                {
                  canbuf[i]=cnt+i;//填充发送缓冲区
                  printf("%s",canbuf[i]);	//显示数据
                }
                
                res=Can_Send_Msg(canbuf,8);//发送8个字节 
                if(res)printf("Failed");		//提示发送失败
                else printf("OK    ");	 		//提示发送成功								   
                
                
//                can_rcv=Can_Receive_Msg(canbuf);
//		if(can_rcv)//接收到有数据
//		{			
//			
// 			for(i=0;i<can_rcv;i++)
//			{									    
//				printf("%s",canbuf[i]);	//显示数据
// 			}
//		}
		t++; 
		delay_ms(10);
		if(t==20)
		{
			LED=!LED;//提示系统正在运行	
			t=0;
			cnt++;
		}		   
	}
}


int main(void)
{ 
     NVIC_Configuration();
     
     delay_init();
     
     LED_Init();
     
     
     
     
#if 0     
    spi1_test();
#else
  #if 1
      can_test();
  #else
      HW_TEST_INIT();
      HW_TEST();
  #endif
    
#endif

}
	   



