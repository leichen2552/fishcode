#include "detect_water.h"

static void DetectWaterSensor_GPIO_Config(void)
{		
    /*����һ��GPIO_InitTypeDef���͵Ľṹ��*/
    GPIO_InitTypeDef GPIO_InitStructure;

    /*������ص�GPIO����ʱ��*/
    RCC_AHB1PeriphClockCmd ( DETECTWATERSENSOR_GPIO_CLK, ENABLE); 		

    /*��������ģʽΪ����ģʽ*/
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;   
    
//    /*�������ŵ��������Ϊ�������*/
//    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    
    /*��������Ϊ����ģʽ*/
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;

//    /*������������Ϊ2MHz */  //�������ó������������ʼ�ʹ������Ҳ����Ч��   
//    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
                                                           
    GPIO_InitStructure.GPIO_Pin = DETECTWATERSENSOR_PIN;	

    GPIO_Init(DETECTWATERSENSOR_GPIO_PORT, &GPIO_InitStructure);	
}

void DetectWaterInit(void)
{
	DetectWaterSensor_GPIO_Config();
}

void IsWaterEnter(void)
{
    if(GPIO_ReadInputDataBit(DETECTWATERSENSOR_GPIO_PORT,DETECTWATERSENSOR_PIN) == SET)
    {
        #if USE_UART_PRINT_TEST
            printf("Water Entering ... \r\n");
        //������©ˮ��Ӧ�ÿ����ϸ��Ķ���
        #endif
    }
    else if(GPIO_ReadInputDataBit(DETECTWATERSENSOR_GPIO_PORT,DETECTWATERSENSOR_PIN) == RESET)
    {
        #if USE_UART_PRINT_TEST
            printf("No Water\r\n");
        #endif
    }
}

