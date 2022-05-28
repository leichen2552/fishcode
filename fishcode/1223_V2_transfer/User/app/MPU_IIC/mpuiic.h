#ifndef __MPUIIC_H
#define __MPUIIC_H

#include "stm32f4xx.h"

#define MPU_IIC_SCL_PIN                  GPIO_Pin_9                 
#define MPU_IIC_SCL_GPIO_PORT            GPIOE                      
#define MPU_IIC_SCL_GPIO_CLK             RCC_AHB1Periph_GPIOE

#define MPU_IIC_SDA_PIN                  GPIO_Pin_8                 
#define MPU_IIC_SDA_GPIO_PORT            GPIOE                     
#define MPU_IIC_SDA_GPIO_CLK             RCC_AHB1Periph_GPIOE

//IO方向设置 SDA为PB11
#define SDA_IN()  {MPU_IIC_SDA_GPIO_PORT->MODER&=~(3<<(8*2));MPU_IIC_SDA_GPIO_PORT->MODER|=0<<8*2;}	//PE8输入模式
#define SDA_OUT() {MPU_IIC_SDA_GPIO_PORT->MODER&=~(3<<(8*2));MPU_IIC_SDA_GPIO_PORT->MODER|=1<<8*2;}   //PE8输出模式

//IO操作函数 SCL为PB0
#define IIC_SCL    PEout(9) 	//SCL
#define IIC_SDA    PEout(8)  	//SDA	 
#define READ_SDA   PEin(8)   	//输入SDA 

//IIC所有操作函数
void IIC_Init(void);                //初始化IIC的IO口				 
void IIC_Start(void);				//发送IIC开始信号
void IIC_Stop(void);	  			//发送IIC停止信号
void IIC_Send_Byte(u8 txd);			//IIC发送一个字节
u8 IIC_Read_Byte(unsigned char ack);//IIC读取一个字节
u8 IIC_Wait_Ack(void); 				//IIC等待ACK信号
void IIC_Ack(void);					//IIC发送ACK信号
void IIC_NAck(void);				//IIC不发送ACK信号 

////IIC所有操作函数
//void MPU_IIC_Init(void);                //初始化IIC的IO口				 
//void MPU_IIC_Start(void);				//发送IIC开始信号
//void MPU_IIC_Stop(void);	  			//发送IIC停止信号
//void MPU_IIC_Send_Byte(u8 txd);			//IIC发送一个字节
//u8 MPU_IIC_Read_Byte(unsigned char ack);//IIC读取一个字节
//u8 MPU_IIC_Wait_Ack(void); 				//IIC等待ACK信号
//void MPU_IIC_Ack(void);					//IIC发送ACK信号
//void MPU_IIC_NAck(void);				//IIC不发送ACK信号

//void MPU_IIC_Write_One_Byte(u8 daddr,u8 addr,u8 data);
//u8 MPU_IIC_Read_One_Byte(u8 daddr,u8 addr);	  
#endif
















