#ifndef __MPUIIC_H
#define __MPUIIC_H

#include "stm32f4xx.h"

#define MPU_IIC_SCL_PIN                  GPIO_Pin_9                 
#define MPU_IIC_SCL_GPIO_PORT            GPIOE                      
#define MPU_IIC_SCL_GPIO_CLK             RCC_AHB1Periph_GPIOE

#define MPU_IIC_SDA_PIN                  GPIO_Pin_8                 
#define MPU_IIC_SDA_GPIO_PORT            GPIOE                     
#define MPU_IIC_SDA_GPIO_CLK             RCC_AHB1Periph_GPIOE

//IO�������� SDAΪPB11
#define SDA_IN()  {MPU_IIC_SDA_GPIO_PORT->MODER&=~(3<<(8*2));MPU_IIC_SDA_GPIO_PORT->MODER|=0<<8*2;}	//PE8����ģʽ
#define SDA_OUT() {MPU_IIC_SDA_GPIO_PORT->MODER&=~(3<<(8*2));MPU_IIC_SDA_GPIO_PORT->MODER|=1<<8*2;}   //PE8���ģʽ

//IO�������� SCLΪPB0
#define IIC_SCL    PEout(9) 	//SCL
#define IIC_SDA    PEout(8)  	//SDA	 
#define READ_SDA   PEin(8)   	//����SDA 

//IIC���в�������
void IIC_Init(void);                //��ʼ��IIC��IO��				 
void IIC_Start(void);				//����IIC��ʼ�ź�
void IIC_Stop(void);	  			//����IICֹͣ�ź�
void IIC_Send_Byte(u8 txd);			//IIC����һ���ֽ�
u8 IIC_Read_Byte(unsigned char ack);//IIC��ȡһ���ֽ�
u8 IIC_Wait_Ack(void); 				//IIC�ȴ�ACK�ź�
void IIC_Ack(void);					//IIC����ACK�ź�
void IIC_NAck(void);				//IIC������ACK�ź� 

////IIC���в�������
//void MPU_IIC_Init(void);                //��ʼ��IIC��IO��				 
//void MPU_IIC_Start(void);				//����IIC��ʼ�ź�
//void MPU_IIC_Stop(void);	  			//����IICֹͣ�ź�
//void MPU_IIC_Send_Byte(u8 txd);			//IIC����һ���ֽ�
//u8 MPU_IIC_Read_Byte(unsigned char ack);//IIC��ȡһ���ֽ�
//u8 MPU_IIC_Wait_Ack(void); 				//IIC�ȴ�ACK�ź�
//void MPU_IIC_Ack(void);					//IIC����ACK�ź�
//void MPU_IIC_NAck(void);				//IIC������ACK�ź�

//void MPU_IIC_Write_One_Byte(u8 daddr,u8 addr,u8 data);
//u8 MPU_IIC_Read_One_Byte(u8 daddr,u8 addr);	  
#endif
















