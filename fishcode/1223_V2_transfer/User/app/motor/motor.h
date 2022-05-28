#ifndef MOTOR_H
#define MOTOR_H

#include "bsp.h"

typedef struct _motor
{
    uint32_t m_ulFreq;
    uint32_t m_ulDutyCycle;

    void (*MotorInit)(void);
    void (*SetDutyCycle)(uint32_t _ulDutyCycle);
}MotorTypedef;



void BspInitMotor(void);

void MotorInit(void);
void SetMotorPWM(uint32_t _pwm);
void StopMotor(void);

#endif
