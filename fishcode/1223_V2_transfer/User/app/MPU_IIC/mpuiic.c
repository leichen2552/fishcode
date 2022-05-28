#include "bsp.h"
#include "mpuiic.h"

/*
����ģ��IIC�����������������ܽţ������õ��ǣ�
SCL----PE9
SDA----PE8
*/

#define delay_us bsp_DelayUS

//��ʼ��IIC
void IIC_Init(void)
{			
	GPIO_InitTypeDef  GPIO_InitStructure_SCL;
	GPIO_InitTypeDef  GPIO_InitStructure_SDA;

	RCC_AHB1PeriphClockCmd(MPU_IIC_SCL_GPIO_CLK | MPU_IIC_SDA_GPIO_CLK, ENABLE);//ʹ��GPIOBʱ��

	//SCLΪPB10
	GPIO_InitStructure_SCL.GPIO_Pin = MPU_IIC_SCL_PIN;
	GPIO_InitStructure_SCL.GPIO_Mode = GPIO_Mode_OUT;//��ͨ���ģʽ
	GPIO_InitStructure_SCL.GPIO_OType = GPIO_OType_PP;//�������
	GPIO_InitStructure_SCL.GPIO_Speed = GPIO_Speed_50MHz;//100MHz
	GPIO_InitStructure_SCL.GPIO_PuPd = GPIO_PuPd_UP;//����
	GPIO_Init(MPU_IIC_SCL_GPIO_PORT, &GPIO_InitStructure_SCL);//��ʼ��
    
	//SDAΪPB11
	GPIO_InitStructure_SDA.GPIO_Pin = MPU_IIC_SDA_PIN;
	GPIO_InitStructure_SDA.GPIO_Mode = GPIO_Mode_OUT;//��ͨ���ģʽ
	GPIO_InitStructure_SDA.GPIO_OType = GPIO_OType_PP;//�������
	GPIO_InitStructure_SDA.GPIO_Speed = GPIO_Speed_50MHz;//100MHz
    GPIO_InitStructure_SCL.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(MPU_IIC_SDA_GPIO_PORT, &GPIO_InitStructure_SDA);//��ʼ��
	
	IIC_SCL=1;
	IIC_SDA=1;
}
//����IIC��ʼ�ź�
void IIC_Start(void)
{
	SDA_OUT();     //sda�����
	IIC_SDA=1;	  	  
	IIC_SCL=1;
	delay_us(4);
 	IIC_SDA=0;//START:when CLK is high,DATA change form high to low 
	delay_us(4);
	IIC_SCL=0;//ǯסI2C���ߣ�׼�����ͻ�������� 
}	  
//����IICֹͣ�ź�
void IIC_Stop(void)
{
	SDA_OUT();//sda�����
	IIC_SCL=0;
	IIC_SDA=0;//STOP:when CLK is high DATA change form low to high
 	delay_us(4);
	IIC_SCL=1; 
	IIC_SDA=1;//����I2C���߽����ź�
	delay_us(4);							   	
}
//�ȴ�Ӧ���źŵ���
//����ֵ��1������Ӧ��ʧ��
//        0������Ӧ��ɹ�
u8 IIC_Wait_Ack(void)
{
	u8 ucErrTime=0;
	SDA_IN();      //SDA����Ϊ����  
	IIC_SDA=1;delay_us(1);	   
	IIC_SCL=1;delay_us(1);	 
	while(READ_SDA)
	{
		ucErrTime++;
		if(ucErrTime>250)
		{
			IIC_Stop();
			return 1;
		}
	}
	IIC_SCL=0;//ʱ�����0 	   
	return 0;  
} 
//����ACKӦ��
void IIC_Ack(void)
{
	IIC_SCL=0;
	SDA_OUT();
	IIC_SDA=0;
	delay_us(2);
	IIC_SCL=1;
	delay_us(2);
	IIC_SCL=0;
}
//������ACKӦ��		    
void IIC_NAck(void)
{
	IIC_SCL=0;
	SDA_OUT();
	IIC_SDA=1;
	delay_us(2);
	IIC_SCL=1;
	delay_us(2);
	IIC_SCL=0;
}					 				     
//IIC����һ���ֽ�
//���شӻ�����Ӧ��
//1����Ӧ��
//0����Ӧ��			  
void IIC_Send_Byte(u8 txd)
{                        
    u8 t;   
	SDA_OUT(); 	    
    IIC_SCL=0;//����ʱ�ӿ�ʼ���ݴ���
    for(t=0;t<8;t++)
    {              
        IIC_SDA=(txd&0x80)>>7;
        txd<<=1; 	  
		delay_us(2);   //��TEA5767��������ʱ���Ǳ����
		IIC_SCL=1;
		delay_us(2); 
		IIC_SCL=0;	
		delay_us(2);
    }	 
} 	    
//��1���ֽڣ�ack=1ʱ������ACK��ack=0������nACK   
u8 IIC_Read_Byte(unsigned char ack)
{
	unsigned char i,receive=0;
	SDA_IN();//SDA����Ϊ����
    for(i=0;i<8;i++ )
	{
        IIC_SCL=0; 
        delay_us(2);
		IIC_SCL=1;
        receive<<=1;
        if(READ_SDA)receive++;   
		delay_us(1); 
    }					 
    if (!ack)
        IIC_NAck();//����nACK
    else
        IIC_Ack(); //����ACK   
    return receive;
}