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
	u8 mode=CAN_Mode_LoopBack;//CAN����ģʽ;CAN_Mode_Normal(0)����ͨģʽ��CAN_Mode_LoopBack(1)������ģʽ

	 	
   
	CAN_Mode_Init(CAN_SJW_1tq,CAN_BS2_8tq,CAN_BS1_9tq,4,CAN_Mode_LoopBack);//CAN��ʼ������ģʽ,������500Kbps    

	
 	while(1)
	{

		if(mode==CAN_Mode_LoopBack)//KEY0����,����һ������
		{
			for(i=0;i<8;i++)
			{
				canbuf[i]=cnt+i;//��䷢�ͻ�����
				if(i<4)printf("%s",canbuf[i]);	//��ʾ����
				else printf("%s",canbuf[i]);	//��ʾ����
 			}
			res=Can_Send_Msg(canbuf,8);//����8���ֽ� 
			if(res)printf("Failed");		//��ʾ����ʧ��
			else printf("OK    ");	 		//��ʾ���ͳɹ�								   
		}else if(mode==CAN_Mode_Normal)//WK_UP���£��ı�CAN�Ĺ���ģʽ
		{	   
//			mode=!mode;
  			CAN_Mode_Init(CAN_SJW_1tq,CAN_BS2_8tq,CAN_BS1_9tq,4,CAN_Mode_Normal);//CAN��ͨģʽ��ʼ��, ������500Kbps 

			if(mode==0)//��ͨģʽ����Ҫ2��������
			{
				printf("Nnormal Mode ");	    
			}else //�ػ�ģʽ,һ��������Ϳ��Բ�����.
			{
 				printf("LoopBack Mode");
			}

		}		 
		can_rcv=Can_Receive_Msg(canbuf);
		if(can_rcv)//���յ�������
		{			
			
 			for(i=0;i<can_rcv;i++)
			{									    
				if(i<4)printf("%s",canbuf[i]);	//��ʾ����
				else printf("%s",canbuf[i]);	//��ʾ����
 			}
		}
		t++; 
		delay_ms(10);
		if(t==20)
		{
			LED=!LED;//��ʾϵͳ��������	
			t=0;
			cnt++;
			printf("%d",cnt);	//��ʾ����
		}		   
	}
}


int main(void)
{ 
     NVIC_Configuration();
     
     delay_init();
     
        //�ⲿ���Ź���ʼ��
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
	   



