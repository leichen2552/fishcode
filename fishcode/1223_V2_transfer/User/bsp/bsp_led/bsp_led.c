#include "bsp_led.h"   

 /**
  * @brief  ��ʼ������LED��IO
  * @param  ��
  * @retval ��
  */
static void LED_GPIO_Config(void)
{		
    /*����һ��GPIO_InitTypeDef���͵Ľṹ��*/
    GPIO_InitTypeDef GPIO_InitStructure;

    /*����LED��ص�GPIO����ʱ��*/
    RCC_AHB1PeriphClockCmd ( LED1_GPIO_CLK|
                             LED2_GPIO_CLK|
                             LED3_GPIO_CLK|
                             LED4_GPIO_CLK, ENABLE); 
    
    /*��������ģʽΪ���ģʽ*/
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;     
    /*�������ŵ��������Ϊ�������*/
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;   
    /*��������Ϊ����ģʽ*/
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
    /*������������Ϊ2MHz */   
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
    /*���ÿ⺯����ʹ���������õ�GPIO_InitStructure��ʼ��GPIO*/
    
    /*ѡ��Ҫ���Ƶ�GPIO����*/															   
    GPIO_InitStructure.GPIO_Pin = LED1_PIN;	
    GPIO_Init(LED1_GPIO_PORT, &GPIO_InitStructure);	
    
    /*ѡ��Ҫ���Ƶ�GPIO����*/															   
    GPIO_InitStructure.GPIO_Pin = LED2_PIN;	
    GPIO_Init(LED2_GPIO_PORT, &GPIO_InitStructure);	
    
    /*ѡ��Ҫ���Ƶ�GPIO����*/															   
    GPIO_InitStructure.GPIO_Pin = LED3_PIN;	
    GPIO_Init(LED3_GPIO_PORT, &GPIO_InitStructure);	

    /*ѡ��Ҫ���Ƶ�GPIO����*/															   
    GPIO_InitStructure.GPIO_Pin = LED4_PIN;	
    GPIO_Init(LED4_GPIO_PORT, &GPIO_InitStructure);        
    
    LED1(OFF);
    LED2(OFF);
    LED3(OFF);
    LED4(OFF);
}

void BspInitLED(void)
{
	LED_GPIO_Config();
}

void SystemWorkNormalLED(void)
{
    LED4_TOGGLE;
}

void SystemEnterHardFaultHandler(void)
{
    LED1_ON;
    LED2_ON;
    LED3_ON;
    LED4_ON;    
}

/*********************************************END OF FILE**********************/
