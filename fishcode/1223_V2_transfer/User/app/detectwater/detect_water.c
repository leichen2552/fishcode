#include "detect_water.h"

static void DetectWaterSensor_GPIO_Config(void)
{		
    /*定义一个GPIO_InitTypeDef类型的结构体*/
    GPIO_InitTypeDef GPIO_InitStructure;

    /*开启相关的GPIO外设时钟*/
    RCC_AHB1PeriphClockCmd ( DETECTWATERSENSOR_GPIO_CLK, ENABLE); 		

    /*设置引脚模式为输入模式*/
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;   
    
//    /*设置引脚的输出类型为推挽输出*/
//    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    
    /*设置引脚为上拉模式*/
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;

//    /*设置引脚速率为2MHz */  //引脚配置成输入后，输出速率即使配置了也是无效的   
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
        //如果检测漏水，应该开启上浮的动作
        #endif
    }
    else if(GPIO_ReadInputDataBit(DETECTWATERSENSOR_GPIO_PORT,DETECTWATERSENSOR_PIN) == RESET)
    {
        #if USE_UART_PRINT_TEST
            printf("No Water\r\n");
        #endif
    }
}

