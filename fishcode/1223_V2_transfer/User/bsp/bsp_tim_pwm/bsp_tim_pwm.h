#ifndef BSP_TIM_PWM_H
#define BSP_TIM_PWM_H

#include "stm32f4xx.h"

void bspSetTIMForInt(TIM_TypeDef* TIMx, uint32_t _ulFreq, uint8_t _PreemptPriority, uint8_t _SubPriority);

void BspSetTIMOutPWM(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin_x,
                     TIM_TypeDef*  TIMx,  uint8_t  _ucChannel,
                     uint32_t   _ulFreq,  uint32_t _ulDutyCycle);

void BspSetTIMOutPWM_N(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin, 
                       TIM_TypeDef* TIMx,   uint8_t _ucChannel,
                       uint32_t _ulFreq,    uint32_t _ulDutyCycle);

#endif

