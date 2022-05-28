#ifndef MEASUREAROUNDDEEPTH_H
#define	MEASUREAROUNDDEEPTH_H

#include "bsp.h"
#include "stm32f4xx.h"


void MeasureStartSignal(void);
int GetFrontDistance(void);

extern int firstTargetDistance,firstTargetIntensity;//第一个距离
extern int strongestTargetDistance,strongestTargetIntensity;//最强距离
extern int lastTargetDistance,lastTargetIntensity;//最后一次距离

#endif /* MEASUREAROUNDDEEPTH_H */


