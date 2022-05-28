#ifndef MEASUREAROUNDDEEPTH_H
#define	MEASUREAROUNDDEEPTH_H

#include "bsp.h"
#include "stm32f4xx.h"


void MeasureStartSignal(void);
int GetFrontDistance(void);

extern int firstTargetDistance,firstTargetIntensity;//��һ������
extern int strongestTargetDistance,strongestTargetIntensity;//��ǿ����
extern int lastTargetDistance,lastTargetIntensity;//���һ�ξ���

#endif /* MEASUREAROUNDDEEPTH_H */


