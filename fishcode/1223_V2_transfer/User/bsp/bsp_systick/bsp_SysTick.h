#ifndef __SYSTICK_H
#define __SYSTICK_H

#include "bsp.h"

void SysTickInit(void);
void Delay_us(__IO u32 nTime);
#define Delay_ms(x) Delay_us(1000*x)	 //µ¥Î»ms

void SetSysTickPeriod(uint32_t ms);

#endif /* __SYSTICK_H */
