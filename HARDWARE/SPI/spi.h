#ifndef __SPI_H
#define __SPI_H
#include "sys.h"

 
 				  	    													  
void SPI1_Init(void);			 //��ʼ��SPI��
void SPI1_SetSpeed(u8 SpeedSet); //����SPI�ٶ�   
u8 SPI1_ReadWriteByte(u8 TxData);//SPI���߶�дһ���ֽ�
void SPI1_NVIC(void);
u8 SPI1_ReadByte(u8 TxData);
		 
#endif

