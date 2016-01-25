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
     SPI1_Init(); //SPI1��ʼ��
     SPI1_SetSpeed(SPI_BaudRatePrescaler_256);//SPI�ٶ�����Ƶ
     SPI1_NVIC();   //������ռ���ȼ�Ϊ1����Ӧ���ȼ�Ϊ1
     
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
	u8 mode=CAN_Mode_Normal;//CAN_Mode_LoopBack;//CAN����ģʽ;CAN_Mode_Normal(0)����ͨģʽ��CAN_Mode_LoopBack(1)������ģʽ

	 	
   
	CAN_Mode_Init(CAN_SJW_2tq,CAN_BS2_5tq,CAN_BS1_3tq,20,mode);//CAN��ʼ������ģʽ,������180Kbps    

	
 	while(1)
	{


                for(i=0;i<8;i++)
                {
                  canbuf[i]=cnt+i;//��䷢�ͻ�����
                  printf("%s",canbuf[i]);	//��ʾ����
                }
                
                res=Can_Send_Msg(canbuf,8);//����8���ֽ� 
                if(res)printf("Failed");		//��ʾ����ʧ��
                else printf("OK    ");	 		//��ʾ���ͳɹ�								   
                
                
//                can_rcv=Can_Receive_Msg(canbuf);
//		if(can_rcv)//���յ�������
//		{			
//			
// 			for(i=0;i<can_rcv;i++)
//			{									    
//				printf("%s",canbuf[i]);	//��ʾ����
// 			}
//		}
		t++; 
		delay_ms(10);
		if(t==20)
		{
			LED=!LED;//��ʾϵͳ��������	
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
	   



