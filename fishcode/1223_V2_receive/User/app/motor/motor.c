#include "motor.h"

//初始化推进器的占空比和停止推进器的占空比都是一个值
#define MOTOR_INIT_PWM_DUTYCYCLE    1350
#define MOTOR_STOP_PWM_DUTYCYCLE    1350

void MotorInit(void)
{
    tailfinSteer[1].SetDutyCycle(MOTOR_INIT_PWM_DUTYCYCLE);
}

void SetMotorPWM(uint32_t _pwm)
{
    tailfinSteer[1].SetDutyCycle(_pwm);
}

void StopMotor(void)
{
    tailfinSteer[1].SetDutyCycle(MOTOR_STOP_PWM_DUTYCYCLE);
}


