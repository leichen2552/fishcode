#include "bsp_tim_pwm.h"

/*
	可以输出到GPIO的TIM通道:

	TIM1_CH1, PA8,	PE9,
	TIM1_CH2, PA9,	PE11
	TIM1_CH3, PA10,	PE13
	TIM1_CH4, PA11,	PE14

	TIM2_CH1, PA15 (仅限429，439) 407没有此脚
	TIM2_CH2, PA1,	PB3
	TIM2_CH3, PA2,	PB10
	TIM2_CH4, PA3,	PB11

	TIM3_CH1, PA6,  PB4, PC6
	TIM3_CH2, PA7,	PB5, PC7
	TIM3_CH3, PB0,	PC8
	TIM3_CH4, PB1,	PC9

	TIM4_CH1, PB6,  PD12
	TIM4_CH2, PB7,	PD13
	TIM4_CH3, PB8,	PD14
	TIM4_CH4, PB9,	PD15

	TIM5_CH1, PA0,  PH10
	TIM5_CH2, PA1,	PH11
	TIM5_CH3, PA2,	PH12
	TIM5_CH4, PA3,	PI10

	TIM8_CH1, PC6,  PI5
	TIM8_CH2, PC7,	PI6
	TIM8_CH3, PC8,	PI7
	TIM8_CH4, PC9,	PI2

	TIM9_CH1, PA2,  PE5
	TIM9_CH2, PA3,	PE6

	TIM10_CH1, PB8,  PF6

	TIM11_CH1, PB9,  PF7

	TIM12_CH1, PB14,  PH6
	TIM12_CH2, PB15,  PH9

	TIM13_CH1, PA6,  PF8
	TIM14_CH1, PA7,  PF9

	APB1 定时器有 TIM2, TIM3 ,TIM4, TIM5, TIM6, TIM7, TIM12, TIM13, TIM14 
	APB2 定时器有 TIM1, TIM8 ,TIM9, TIM10, TIM11
	

	APB1 定时器的输入时钟 TIMxCLK = SystemCoreClock / 2; 84M
	APB2 定时器的输入时钟 TIMxCLK = SystemCoreClock; 168M
*/

static uint32_t bspGetRCCofTIM(TIM_TypeDef* TIMx)
{
    uint32_t rcc = 0;
    
    /*
		APB1 定时器有 TIM2, TIM3 ,TIM4, TIM5, TIM6, TIM7, TIM12, TIM13, TIM14
		APB2 定时器有 TIM1, TIM8 ,TIM9, TIM10, TIM11
	*/
    
    /*APB2时钟上的定时外设*/
    if(TIMx == TIM1)
    {
        rcc = RCC_APB2Periph_TIM1;
    }
    else if(TIMx == TIM8)
    {
        rcc = RCC_APB2Periph_TIM8;
    }
    else if(TIMx == TIM9)
    {
        rcc = RCC_APB2Periph_TIM9;
    }
    else if(TIMx == TIM10)
    {
        rcc = RCC_APB2Periph_TIM10;
    }
    else if(TIMx == TIM11)
    {
        rcc = RCC_APB2Periph_TIM11;
    }
    /*APB1时钟上的定时外设*/
    else if(TIMx == TIM2)
    {
        rcc = RCC_APB1Periph_TIM2;
    }
    else if(TIMx == TIM3)
    {
        rcc = RCC_APB1Periph_TIM3;
    }
    else if(TIMx == TIM4)
    {
        rcc = RCC_APB1Periph_TIM4;
    }
    else if(TIMx == TIM5)
    {
        rcc = RCC_APB1Periph_TIM5;
    }
    else if(TIMx == TIM6)
    {
        rcc = RCC_APB1Periph_TIM6;
    }
    else if(TIMx == TIM7)
    {
        rcc = RCC_APB1Periph_TIM7;
    }
    else if(TIMx == TIM12)
    {
        rcc = RCC_APB1Periph_TIM12;
    }
    else if(TIMx == TIM13)
    {
        rcc = RCC_APB1Periph_TIM13;
    }
    else if(TIMx == TIM14)
    {
        rcc = RCC_APB1Periph_TIM14;
    } 
    
    return rcc;
}

void bspSetTIMForInt(TIM_TypeDef* TIMx, uint32_t _ulFreq, uint8_t _PreemptPriority, uint8_t _SubPriority)
{
    TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
    uint16_t usPeriod;
    uint16_t usPrescaler;
    uint32_t ulTIMxCLK;
    
    if((TIMx == TIM1)||(TIMx == TIM8))
    {
        RCC_APB2PeriphClockCmd(bspGetRCCofTIM(TIMx), ENABLE);
    }
    else
    {
        RCC_APB1PeriphClockCmd(bspGetRCCofTIM(TIMx), ENABLE);
    }
    
    if(0 == _ulFreq)
    {
        TIM_Cmd(TIMx, DISABLE);
        return ;
    }
    
    if((TIMx == TIM1)||(TIMx == TIM8)||(TIMx == TIM9)||(TIMx == TIM10)||(TIMx == TIM11))
    {
        ulTIMxCLK = SystemCoreClock;
    }
    else
    {
        ulTIMxCLK = SystemCoreClock / 2;
    }
    
    if(_ulFreq < 100)
    {
        usPrescaler = 10000 - 1;                        /* 分频比 = 1000 */
        usPeriod = (ulTIMxCLK / 10000) / _ulFreq - 1; /* 自动重装的值 */
    }
    else if(_ulFreq < 3000)
    {
        usPrescaler = 100 - 1;                      /* 分频比 = 100 */
        usPeriod = (ulTIMxCLK / 100 ) / _ulFreq - 1; /* 自动重装的值 */
    }
    else/* 大于4K的频率，无需分频 */
    {
        usPrescaler = 0;                /* 分频比 = 1 */
        usPeriod = ulTIMxCLK / _ulFreq - 1; /* 自动重装的值 */
    }
    
    TIM_TimeBaseStructure.TIM_Period = usPeriod;
    TIM_TimeBaseStructure.TIM_Prescaler = usPrescaler;
    TIM_TimeBaseStructure.TIM_ClockDivision = 0;
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_TimeBaseStructure.TIM_RepetitionCounter = 0x0000;   /* TIM1 和 TIM8 必须设置 */
    
    TIM_TimeBaseInit(TIMx, &TIM_TimeBaseStructure);
    
    TIM_ARRPreloadConfig(TIMx, ENABLE);
    
    TIM_ITConfig(TIMx, TIM_IT_Update, ENABLE);
    
    TIM_Cmd(TIMx, ENABLE);
    
    {
        NVIC_InitTypeDef NVIC_InitStructure;
        uint8_t irq = 0;
        
        if ((TIMx == TIM1) || (TIMx == TIM10))
			irq = TIM1_UP_TIM10_IRQn;
		else if (TIMx == TIM2)
			irq = TIM2_IRQn;
		else if (TIMx == TIM3)
			irq = TIM3_IRQn;
		else if (TIMx == TIM4)
			irq = TIM4_IRQn;
		else if (TIMx == TIM5)
			irq = TIM5_IRQn;
		else if (TIMx == TIM6)
			irq = TIM6_DAC_IRQn;
		else if (TIMx == TIM7)
			irq = TIM7_IRQn;
		else if (TIMx == TIM7)
			irq = TIM7_IRQn;
		else if (TIMx == TIM7)
			irq = TIM7_IRQn;
		else if ((TIMx == TIM8) || (TIMx == TIM13))
			irq = TIM8_UP_TIM13_IRQn;
		else if (TIMx == TIM9)
			irq = TIM1_BRK_TIM9_IRQn;
		else if (TIMx == TIM11)
			irq = TIM1_TRG_COM_TIM11_IRQn;
		else if (TIMx == TIM12)
			irq = TIM8_BRK_TIM12_IRQn;
		else if (TIMx == TIM14)
			irq = TIM8_TRG_COM_TIM14_IRQn;
        
        NVIC_InitStructure.NVIC_IRQChannel = irq;
        NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = _PreemptPriority;
        NVIC_InitStructure.NVIC_IRQChannelSubPriority = _SubPriority;
        NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
        
        NVIC_Init(&NVIC_InitStructure);
    }
}


uint32_t BspGetRCCofGPIO(GPIO_TypeDef* GPIOx)
{
    uint32_t rcc = 0;
    
    if(GPIOx == GPIOA)
    {
        rcc = RCC_AHB1Periph_GPIOA;
    }
    else if(GPIOx == GPIOB)
    {
        rcc = RCC_AHB1Periph_GPIOB;
    }
    else if(GPIOx == GPIOC)
    {
        rcc = RCC_AHB1Periph_GPIOC;
    }
    else if(GPIOx == GPIOD)
    {
        rcc = RCC_AHB1Periph_GPIOD;
    }
    else if(GPIOx == GPIOE)
    {
        rcc = RCC_AHB1Periph_GPIOE;
    }
    else if(GPIOx == GPIOF)
    {
        rcc = RCC_AHB1Periph_GPIOF;
    }
    else if(GPIOx == GPIOG)
    {
        rcc = RCC_AHB1Periph_GPIOG;
    }
    else if(GPIOx == GPIOH)
    {
        rcc = RCC_AHB1Periph_GPIOH;
    }
    else if(GPIOx == GPIOI)
    {
        rcc = RCC_AHB1Periph_GPIOI;
    }   

    return rcc;    
}

uint16_t BspGetPinSource(uint16_t gpio_pin)
{
    uint16_t ret = 0;
    
    if(gpio_pin == GPIO_Pin_0)
    {
        ret = GPIO_PinSource0;
    }
    else if(gpio_pin == GPIO_Pin_1)
    {
        ret = GPIO_PinSource1;
    }
    else if(gpio_pin == GPIO_Pin_2)
    {
        ret = GPIO_PinSource2;
    }
    else if(gpio_pin == GPIO_Pin_3)
    {
        ret = GPIO_PinSource3;
    }
    else if(gpio_pin == GPIO_Pin_3)
    {
        ret = GPIO_PinSource3;
    }
    else if(gpio_pin == GPIO_Pin_4)
    {
        ret = GPIO_PinSource4;
    }
    else if(gpio_pin == GPIO_Pin_5)
    {
        ret = GPIO_PinSource5;
    }
    else if(gpio_pin == GPIO_Pin_6)
    {
        ret = GPIO_PinSource6;
    }
    else if(gpio_pin == GPIO_Pin_7)
    {
        ret = GPIO_PinSource7;
    }
    else if(gpio_pin == GPIO_Pin_8)
    {
        ret = GPIO_PinSource8;
    }
    else if(gpio_pin == GPIO_Pin_9)
    {
        ret = GPIO_PinSource9;
    }
    else if(gpio_pin == GPIO_Pin_10)
    {
        ret = GPIO_PinSource10;
    }
    else if(gpio_pin == GPIO_Pin_11)
    {
        ret = GPIO_PinSource11;
    }
    else if(gpio_pin == GPIO_Pin_12)
    {
        ret = GPIO_PinSource12;
    }
    else if(gpio_pin == GPIO_Pin_13)
    {
        ret = GPIO_PinSource13;
    }
    else if(gpio_pin == GPIO_Pin_14)
    {
        ret = GPIO_PinSource14;
    }
    else if(gpio_pin == GPIO_Pin_15)
    {
        ret = GPIO_PinSource15;
    }
    
    return ret;
}

uint8_t BspGetAFofTIM(TIM_TypeDef* TIMx)
{
    uint8_t ret = 0;
    
    /*
		APB1 定时器有 TIM2, TIM3 ,TIM4, TIM5, TIM6, TIM7, TIM12, TIM13, TIM14
		APB2 定时器有 TIM1, TIM8 ,TIM9, TIM10, TIM11
	*/
    
    if(TIMx == TIM1)
    {
        ret = GPIO_AF_TIM1;
    }
    else if(TIMx == TIM8)
    {
        ret = GPIO_AF_TIM8;
    }
    else if(TIMx == TIM9)
    {
        ret = GPIO_AF_TIM9;
    }
    else if(TIMx == TIM10)
    {
        ret = GPIO_AF_TIM10;
    }
    else if(TIMx == TIM11)
    {
        ret = GPIO_AF_TIM11;
    }
    /* 下面是 APB1时钟 */
    else if(TIMx == TIM2)
    {
        ret = GPIO_AF_TIM2;
    }
    else if(TIMx == TIM3)
    {
        ret = GPIO_AF_TIM3;
    }
    else if(TIMx == TIM4)
    {
        ret = GPIO_AF_TIM4;
    }
    else if(TIMx == TIM5)
    {
        ret = GPIO_AF_TIM5;
    }
    /* 没有 TIM6 TIM7 */
    else if(TIMx == TIM8)
    {
        ret = GPIO_AF_TIM8;
    }
    else if(TIMx == TIM9)
    {
        ret = GPIO_AF_TIM9;
    }
    else if(TIMx == TIM12)
    {
        ret = GPIO_AF_TIM12;
    }
    else if(TIMx == TIM13)
    {
        ret = GPIO_AF_TIM13;
    }
    else if(TIMx == TIM14)
    {
        ret = GPIO_AF_TIM14;
    }
    
    return ret;
}

/*
****************************************************************************************************************
* 函 数 名：
* 功能说明：配置GPIO和TIM时钟， GPIO连接到TIM输出通道
* 形    参：
*
*
*
* 返 回 值：
*****************************************************************************************************************
*/
void BspConfigTIMGpio(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin_x, TIM_TypeDef* TIMx, uint8_t _ucChannel)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    
    RCC_AHB1PeriphClockCmd(BspGetRCCofGPIO(GPIOx), ENABLE);
	
    /*
		APB1 定时器有 TIM2, TIM3 ,TIM4, TIM5, TIM6, TIM7, TIM12, TIM13, TIM14
		APB2 定时器有 TIM1, TIM8 ,TIM9, TIM10, TIM11
	*/    
    if((TIMx == TIM1)||(TIMx == TIM8)||(TIMx == TIM9)||(TIMx == TIM10)||(TIMx == TIM11))
    {
        RCC_APB2PeriphClockCmd(bspGetRCCofTIM(TIMx), ENABLE);
    }
    else
    {
        RCC_APB1PeriphClockCmd(bspGetRCCofTIM(TIMx), ENABLE);
    }
    
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_x;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
    GPIO_Init(GPIOx, &GPIO_InitStructure);
    
    GPIO_PinAFConfig(GPIOx, BspGetPinSource(GPIO_Pin_x), BspGetAFofTIM(TIMx));
}

/*
*********************************************************************************************************
*	函 数 名: bsp_ConfigGpioOut
*	功能说明: 配置GPIO为推挽输出。主要用于PWM输出，占空比为0和100的情况。
*	形    参: GPIOx
*			  GPIO_PinX
*	返 回 值: 无
*********************************************************************************************************
*/
void BspConfigGpioOut(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin_x)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    
    RCC_AHB1PeriphClockCmd(BspGetRCCofGPIO(GPIOx), ENABLE);
    
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_x;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
    GPIO_Init(GPIOx, &GPIO_InitStructure);
}

/*
*********************************************************************************************************
*	函 数 名: bsp_SetTIMOutPWM
*	功能说明: 设置引脚输出的PWM信号的频率和占空比.  当频率为0，并且占空为0时，关闭定时器，GPIO输出0；
*			  当频率为0，占空比为100%时，GPIO输出1.
*	形    参: _ulFreq : PWM信号频率，单位Hz  (实际测试，最大输出频率为 180M / 4 = 42M）. 0 表示禁止输出
*			  _ulDutyCycle : PWM信号占空比，单位：万分之一。如5000，表示50.00%的占空比
*	返 回 值: 无
*********************************************************************************************************
*/
void BspSetTIMOutPWM(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin_x,
                     TIM_TypeDef* TIMx,   uint8_t _ucChannel,
                     uint32_t _ulFreq,    uint32_t _ulDutyCycle)
{
    TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
    TIM_OCInitTypeDef TIM_OCInitStructure;
    uint16_t usPeriod;
    uint16_t usPrescaler;
    uint32_t uiTIMxCLK;
    
    if(0 == _ulDutyCycle)/*如果占空比为0*/
    {
        TIM_Cmd(TIMx, DISABLE);
        BspConfigGpioOut(GPIOx, GPIO_Pin_x);
        GPIO_WriteBit(GPIOx, GPIO_Pin_x, Bit_RESET);/* PWM = 0 */
        
        return;
    }
    else if(10000 == _ulDutyCycle)/*如果占空比为1*/
    {
        TIM_Cmd(TIMx, DISABLE);
        
        BspConfigGpioOut(GPIOx, GPIO_Pin_x);
        GPIO_WriteBit(GPIOx, GPIO_Pin_x, Bit_SET);/* PWM = 1 */
        return;
    }
    
    BspConfigTIMGpio(GPIOx, GPIO_Pin_x, TIMx, _ucChannel);
    
    /*-----------------------------------------------------------------------
		system_stm32f4xx.c 文件中 void SetSysClock(void) 函数对时钟的配置如下：

		HCLK = SYSCLK / 1     (AHB1Periph)
		PCLK2 = HCLK / 2      (APB2Periph)
		PCLK1 = HCLK / 4      (APB1Periph)

		因为APB1 prescaler != 1, 所以 APB1上的TIMxCLK = PCLK1 x 2 = SystemCoreClock / 2;
		因为APB2 prescaler != 1, 所以 APB2上的TIMxCLK = PCLK2 x 2 = SystemCoreClock;

		APB1 定时器有 TIM2, TIM3 ,TIM4, TIM5, TIM6, TIM6, TIM12, TIM13,TIM14
		APB2 定时器有 TIM1, TIM8 ,TIM9, TIM10, TIM11

	----------------------------------------------------------------------- */
    
    if((TIMx == TIM1)||(TIMx == TIM8)||(TIMx == TIM9)||(TIMx == TIM10)||(TIMx == TIM11))
    {
        /* APB2 定时器 */
        uiTIMxCLK = SystemCoreClock;
    }
    else
    {
        /* APB1 定时器 */
        uiTIMxCLK = SystemCoreClock / 2;
    }
   
    if(_ulFreq < 100)
    { 
        //usPrescaler = 10000 - 1;
        //usPeriod = (uiTIMxCLK / 10000) / _ulFreq - 1; // usPeriod = (90 000 000 / 10000) /50  - 1 = 179
        usPrescaler = 100 - 1;                    //TIM3 假如是50Hz:
        usPeriod = (uiTIMxCLK / 100) / _ulFreq - 1; // usPeriod = (90 000 000 / 100) /50  - 1 = 17999
    }
    else if(_ulFreq < 3000)
    { 
        usPrescaler = 100 - 1;
        usPeriod = (uiTIMxCLK / 100) / _ulFreq - 1; //TIM3 假如是100Hz: usPeriod = (90 000 000 / 100) /100  - 1 = 8999
    }
    else
    {
        usPrescaler = 0;
        usPeriod = uiTIMxCLK / _ulFreq - 1;
    }
    
    TIM_TimeBaseStructure.TIM_Period = usPeriod;                
    TIM_TimeBaseStructure.TIM_Prescaler = usPrescaler;          
    TIM_TimeBaseStructure.TIM_ClockDivision = 0;
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up; 
    TIM_TimeBaseStructure.TIM_RepetitionCounter = 0x0000;   /* TIM1 和 TIM8 必须设置 */	
    
    TIM_TimeBaseInit(TIMx, &TIM_TimeBaseStructure);
    
    TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
    TIM_OCInitStructure.TIM_Pulse = (_ulDutyCycle * usPeriod) / 10000;  
    TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
    
    TIM_OCInitStructure.TIM_OutputNState = TIM_OutputNState_Disable;    /* only for TIM1 and TIM8. */	
    TIM_OCInitStructure.TIM_OCNPolarity = TIM_OCNPolarity_High;         /* only for TIM1 and TIM8. */	
    TIM_OCInitStructure.TIM_OCIdleState = TIM_OCIdleState_Reset;        /* only for TIM1 and TIM8. */	
    TIM_OCInitStructure.TIM_OCNIdleState = TIM_OCNIdleState_Reset;      /* only for TIM1 and TIM8. */	
    
    if(1 == _ucChannel)
    {
        TIM_OC1Init(TIMx, &TIM_OCInitStructure);
        TIM_OC1PreloadConfig(TIMx, TIM_OCPreload_Enable);
    }
    else if(2 == _ucChannel)
    {
        TIM_OC2Init(TIMx, &TIM_OCInitStructure);
        TIM_OC2PreloadConfig(TIMx, TIM_OCPreload_Enable);
    }
    else if(3 == _ucChannel)
    {
        TIM_OC3Init(TIMx, &TIM_OCInitStructure);
        TIM_OC3PreloadConfig(TIMx, TIM_OCPreload_Enable);
    }
    else if(4 == _ucChannel)
    {
        TIM_OC4Init(TIMx, &TIM_OCInitStructure);
        TIM_OC4PreloadConfig(TIMx, TIM_OCPreload_Enable);
    }
    
    TIM_ARRPreloadConfig(TIMx, ENABLE);
    
    TIM_Cmd(TIMx, ENABLE);
    
    if((TIMx == TIM1)||(TIMx == TIM8))
    {
        TIM_CtrlPWMOutputs(TIMx, ENABLE);
    }
    
}




/*
*********************************************************************************************************
*	函 数 名: bsp_SetTIMOutPWM_N
*	功能说明: 设置TIM的反相引脚（比如TIM8_CH3N) 输出的PWM信号的频率和占空比.  当频率为0，并且占空为0时，关闭定时器，GPIO输出0；
*			  当频率为0，占空比为100%时，GPIO输出1.
*	形    参: _ulFreq : PWM信号频率，单位Hz  (实际测试，最大输出频率为 168M / 4 = 42M）. 0 表示禁止输出
*			  _ulDutyCycle : PWM信号占空比，单位：万分之一。如5000，表示50.00%的占空比
*	返 回 值: 无
*********************************************************************************************************
*/
void BspSetTIMOutPWM_N(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin, 
                       TIM_TypeDef* TIMx,   uint8_t _ucChannel,
                       uint32_t _ulFreq,    uint32_t _ulDutyCycle)
{
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;
	uint16_t usPeriod;
	uint16_t usPrescaler;
	uint32_t uiTIMxCLK;

	if (_ulDutyCycle == 0)
	{		
		TIM_Cmd(TIMx, DISABLE);		/* 关闭PWM输出 */
		BspConfigGpioOut(GPIOx, GPIO_Pin);	/* 配置GPIO为推挽输出 */		
		GPIO_WriteBit(GPIOx, GPIO_Pin, Bit_RESET);	/* PWM = 0 */		
		return;
	}
	else if (_ulDutyCycle == 10000)
	{
		TIM_Cmd(TIMx, DISABLE);		/* 关闭PWM输出 */

		BspConfigGpioOut(GPIOx, GPIO_Pin);	/* 配置GPIO为推挽输出 */		
		GPIO_WriteBit(GPIOx, GPIO_Pin, Bit_SET);	/* PWM = 1 */	
		return;
	}
	

	BspConfigTIMGpio(GPIOx, GPIO_Pin, TIMx, _ucChannel);	/* 使能GPIO和TIM时钟，并连接TIM通道到GPIO */
	
    /*-----------------------------------------------------------------------
		system_stm32f4xx.c 文件中 void SetSysClock(void) 函数对时钟的配置如下：

		HCLK = SYSCLK / 1     (AHB1Periph)
		PCLK2 = HCLK / 2      (APB2Periph)
		PCLK1 = HCLK / 4      (APB1Periph)

		因为APB1 prescaler != 1, 所以 APB1上的TIMxCLK = PCLK1 x 2 = SystemCoreClock / 2;
		因为APB2 prescaler != 1, 所以 APB2上的TIMxCLK = PCLK2 x 2 = SystemCoreClock;

		APB1 定时器有 TIM2, TIM3 ,TIM4, TIM5, TIM6, TIM6, TIM12, TIM13,TIM14
		APB2 定时器有 TIM1, TIM8 ,TIM9, TIM10, TIM11

	----------------------------------------------------------------------- */
	if ((TIMx == TIM1) || (TIMx == TIM8) || (TIMx == TIM9) || (TIMx == TIM10) || (TIMx == TIM11))
	{
		/* APB2 定时器 */
		uiTIMxCLK = SystemCoreClock;
	}
	else	/* APB1 定时器 */
	{
		uiTIMxCLK = SystemCoreClock / 2;
	}

	if (_ulFreq < 100)
	{
		usPrescaler = 10000 - 1;					/* 分频比 = 10000 */
		usPeriod =  (uiTIMxCLK / 10000) / _ulFreq  - 1;		/* 自动重装的值 */
	}
	else if (_ulFreq < 3000)
	{
		usPrescaler = 100 - 1;					/* 分频比 = 100 */
		usPeriod =  (uiTIMxCLK / 100) / _ulFreq  - 1;		/* 自动重装的值 */
	}
	else	/* 大于4K的频率，无需分频 */
	{
		usPrescaler = 0;					/* 分频比 = 1 */
		usPeriod = uiTIMxCLK / _ulFreq - 1;	/* 自动重装的值 */
	}

	/* Time base configuration */
	TIM_TimeBaseStructure.TIM_Period = usPeriod;
	TIM_TimeBaseStructure.TIM_Prescaler = usPrescaler;
	TIM_TimeBaseStructure.TIM_ClockDivision = 0;
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseStructure.TIM_RepetitionCounter = 0x0000;		/* TIM1 和 TIM8 必须设置 */	

	TIM_TimeBaseInit(TIMx, &TIM_TimeBaseStructure);

	/* PWM1 Mode configuration: Channel1 */
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Disable;		/* 此处和正相引脚不同 */
	TIM_OCInitStructure.TIM_Pulse = (_ulDutyCycle * usPeriod) / 10000;
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
	
	TIM_OCInitStructure.TIM_OutputNState = TIM_OutputNState_Enable;		/* only for TIM1 and TIM8. 此处和正相引脚不同 */	
	TIM_OCInitStructure.TIM_OCNPolarity = TIM_OCNPolarity_High;			/* only for TIM1 and TIM8. */		 
	TIM_OCInitStructure.TIM_OCIdleState = TIM_OCIdleState_Reset;		/* only for TIM1 and TIM8. */
	TIM_OCInitStructure.TIM_OCNIdleState = TIM_OCNIdleState_Reset;		/* only for TIM1 and TIM8. */
	
	if (_ucChannel == 1)
	{
		TIM_OC1Init(TIMx, &TIM_OCInitStructure);
		TIM_OC1PreloadConfig(TIMx, TIM_OCPreload_Enable);
	}
	else if (_ucChannel == 2)
	{
		TIM_OC2Init(TIMx, &TIM_OCInitStructure);
		TIM_OC2PreloadConfig(TIMx, TIM_OCPreload_Enable);
	}
	else if (_ucChannel == 3)
	{
		TIM_OC3Init(TIMx, &TIM_OCInitStructure);
		TIM_OC3PreloadConfig(TIMx, TIM_OCPreload_Enable);
	}
	else if (_ucChannel == 4)
	{
		TIM_OC4Init(TIMx, &TIM_OCInitStructure);
		TIM_OC4PreloadConfig(TIMx, TIM_OCPreload_Enable);
	}

	TIM_ARRPreloadConfig(TIMx, ENABLE);

	/* TIMx enable counter */
	TIM_Cmd(TIMx, ENABLE);

	/* 下面这句话对于TIM1和TIM8是必须的，对于TIM2-TIM6则不必要 */
	if ((TIMx == TIM1) || (TIMx == TIM8))
	{
		TIM_CtrlPWMOutputs(TIMx, ENABLE);
	}
}

