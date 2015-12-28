#include "delay.h"
#include "sys.h"
////////////////////////////////////////////////////////////////////////////////// 	 

	 
static u8  fac_us=0;//us��ʱ������
static u16 fac_ms=0;//ms��ʱ������


//��ʼ���ӳٺ���
//SYSTICK��ʱ�ӹ̶�ΪHCLKʱ�ӵ�1/8
//SYSCLK:ϵͳʱ��
void delay_init()	 
{
	SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK_Div8);	//ѡ���ⲿʱ��  HCLK/8
	fac_us=SystemCoreClock/8000000;	//Ϊϵͳʱ�ӵ�1/8  
	 
	fac_ms=(u16)fac_us*1000;//����ÿ��ms��Ҫ��systickʱ����   
}								    

//��ʱnus
//nusΪҪ��ʱ��us��.		    								   
void delay_us(u32 nus)
{		
	u32 temp;
        
        if(nus != 0)
        {
            SysTick->LOAD=nus*fac_us; //ʱ�����	  		 
            SysTick->VAL=0x00;        //��ռ�����
            SysTick->CTRL|=SysTick_CTRL_ENABLE_Msk ;          //��ʼ����	 
            do
            {
                    temp=SysTick->CTRL;
            }
            while(temp&0x01&&!(temp&(1<<16)));//�ȴ�ʱ�䵽��   
            SysTick->CTRL&=~SysTick_CTRL_ENABLE_Msk;       //�رռ�����
            SysTick->VAL =0X00;       //��ռ�����
        }
}
//��ʱnms
//ע��nms�ķ�Χ
//SysTick->LOADΪ24λ�Ĵ���,����,�����ʱΪ:
//nms<=0xffffff*8*1000/SYSCLK
//SYSCLK��λΪHz,nms��λΪms
//��72M������,nms<=1864 
void delay_ms(u16 nms)
{	 		  	  
        u32 temp;
        u32 Count_H = 0,Count_L = 0;
        
        if(nms != 0)
        {                
            Count_H = nms/1864;
            Count_L = nms%1864;
                   
            Count_H ++;
            while(Count_H--)
            {
                if(Count_H > 0)nms = 1864;
                else nms = Count_L;
                
                SysTick->LOAD=(u32)nms*fac_ms;//ʱ�����(SysTick->LOADΪ24bit)
                SysTick->VAL =0x00;           //��ռ�����
                SysTick->CTRL|=SysTick_CTRL_ENABLE_Msk ;          //��ʼ����  
                do
                {
                  temp=SysTick->CTRL;
                }
                while(temp&0x01&&!(temp&(1<<16)));//�ȴ�ʱ�䵽��   
                SysTick->CTRL&=~SysTick_CTRL_ENABLE_Msk;       //�رռ�����
                SysTick->VAL =0X00;       //��ռ�����	  	    
            }
        }
} 































