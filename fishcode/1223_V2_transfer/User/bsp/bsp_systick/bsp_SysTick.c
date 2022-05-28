#include "bsp_SysTick.h"

static __IO u32 TimingDelay;

void SysTickInit(void)
{
    SetSysTickPeriod(1);
}

void SetSysTickPeriod(uint32_t ms)
{
    /* 
     * SystemFrequency / 1000    1ms中断一次
	 * SystemFrequency / 100000	 10us中断一次
	 * SystemFrequency / 1000000 1us中断一次
	 */

    SysTick->LOAD  = ms * SystemCoreClock / 1000000 - 1;
    NVIC_SetPriority (SysTick_IRQn, (1<<__NVIC_PRIO_BITS) - 1);
    SysTick->VAL   = 0;                           
    SysTick->CTRL  = SysTick_CTRL_CLKSOURCE_Msk |
                     SysTick_CTRL_TICKINT_Msk   |
                     SysTick_CTRL_ENABLE_Msk; 
}

void Delay_us(__IO u32 nTime)
{ 
	TimingDelay = nTime;	

	while(TimingDelay != 0);
}

void TimingDelay_Decrement(void)
{
	if (TimingDelay != 0x00)
	{ 
		TimingDelay--;
	}
}

void SysTick_Handler(void)
{  
    TimingDelay_Decrement();
}
/*********************************************END OF FILE**********************/
