#ifndef DETECTWATER_H
#define	DETECTWATER_H

#include "bsp.h"
#include "stm32f4xx.h"

#define DETECTWATERSENSOR_PIN                  GPIO_Pin_2                 
#define DETECTWATERSENSOR_GPIO_PORT            GPIOE                      
#define DETECTWATERSENSOR_GPIO_CLK             RCC_AHB1Periph_GPIOE

#define DETECTWATER PEout(2)        //位带操作，仿51单片机	

void DetectWaterInit(void);
void IsWaterEnter(void);

#endif /* __LED_H */

