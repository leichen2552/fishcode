#ifndef EYELED_H
#define EYELED_H

#include "bsp.h"
#include "stm32f4xx.h"

void EyeLedInit(void);

/*ÓÒÑÛapi*/
void RightEyeOFF(void);
void RightEyeFullON(void);
void RightEyeSetDuty(uint32_t duty); //0-100

/*×óÑÛapi*/
void LeftEyeOFF(void);
void LeftEyeFullON(void);
void LeftEyeSetDuty(uint32_t duty); //0-100


void AllEyeFullON(void);
void AllEyeFullOFF(void);
void AllEyeSetDuty(uint32_t duty);
void SeparateEyeSetDuty(uint32_t righteyeduty, uint32_t lefteyeduty);




#endif
