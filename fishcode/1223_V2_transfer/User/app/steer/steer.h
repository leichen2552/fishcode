#ifndef STEER_H
#define STEER_H

#include "bsp.h"

typedef struct _steer
{
    uint32_t m_ulFreq;
    uint32_t m_ulDutyCycle;

    void (*SteerInit)(void);
    void (*SetDutyCycle)(uint32_t _ulDutyCycle);
}SteerTypedef;



void BspInitSteer(void);

int* TailFinSwing(void);
int* PectoralFinDown(void);
int* PectoralFinUp(void);
int* PectoralFinQianHouSwing(void);


int* PectoralFinRight(void);
int* PectoralFinLeft(void);

int* TailFinLeft(void);
int* TailFinRight(void);

extern SteerTypedef tailfinSteer[2];
extern SteerTypedef pectoralfinSteer[4];


//extern int tailfinSteer_1_ArrayFlag;
//extern int tailfinSteer_1_LeftFlag;
//extern int tailfinSteer_1_RigthFlag;

//extern int pectoralfin_0_QianToHouFlag;
//extern int pectoralfin_3_QianToHouFlag;
//extern int pectoralfin_3_LeftFlag;
//extern int pectoralfin_0_RightFlag;

//extern int pectoralfin_0_UpSwingFlag;
//extern int pectoralfin_3_UpSwingFlag;

//extern int pectoralfin_0_DownSwingFlag;
//extern int pectoralfin_3_DownSwingFlag;
#endif
