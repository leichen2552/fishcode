#include "eyeled.h"

#define RIGTH_EYE_PORT          GPIOA
#define RIGHT_EYE_PIN           GPIO_Pin_2
#define RIGHT_EYE_TIM           TIM5
#define RIGHT_EYE_CHANNEL       3  
#define RIGHT_EYE_FREQ          1000        /*推荐100~10000*/ 
#define RIGHT_EYE_INIT_DUTY     3000        /*1000就是10%的占空比*/ 
#define RIGHT_EYE_OFF           0
#define RIGHT_EYE_FULL_ON       10000

#define LEFT_EYE_PORT           GPIOA
#define LEFT_EYE_PIN            GPIO_Pin_3
#define LEFT_EYE_TIM            TIM5
#define LEFT_EYE_CHANNEL        4 
#define LEFT_EYE_FREQ           1000        /*推荐100~10000HZ*/ 
#define LEFT_EYE_INIT_DUTY      3000        /*1000就是10%的占空比*/
#define LEFT_EYE_OFF            0
#define LEFT_EYE_FULL_ON        10000


void EyeLedInit(void)
{
    BspSetTIMOutPWM(RIGTH_EYE_PORT, RIGHT_EYE_PIN, RIGHT_EYE_TIM, 
                                RIGHT_EYE_CHANNEL, RIGHT_EYE_FREQ,  RIGHT_EYE_INIT_DUTY);
    BspSetTIMOutPWM(LEFT_EYE_PORT,  LEFT_EYE_PIN,  LEFT_EYE_TIM,  
                                LEFT_EYE_CHANNEL,  LEFT_EYE_FREQ,   LEFT_EYE_INIT_DUTY);
}

/*
右眼
*/
void RightEyeOFF(void)
{
    BspSetTIMOutPWM(RIGTH_EYE_PORT, RIGHT_EYE_PIN, RIGHT_EYE_TIM, RIGHT_EYE_CHANNEL, RIGHT_EYE_FREQ,  RIGHT_EYE_OFF);
}
void RightEyeFullON(void)
{
    BspSetTIMOutPWM(RIGTH_EYE_PORT, RIGHT_EYE_PIN, RIGHT_EYE_TIM,  RIGHT_EYE_CHANNEL, RIGHT_EYE_FREQ,  RIGHT_EYE_FULL_ON);
}

void RightEyeSetDuty(uint32_t duty) //0-100
{   
    //BspSetTIMOutPWM(RIGTH_EYE_PORT, RIGHT_EYE_PIN, RIGHT_EYE_TIM,  RIGHT_EYE_CHANNEL, RIGHT_EYE_FREQ,  duty*100);
    TIM_SetCompare3(RIGHT_EYE_TIM, duty*9);
}

/*
左眼
*/
void LeftEyeOFF(void)
{
    BspSetTIMOutPWM(LEFT_EYE_PORT, LEFT_EYE_PIN, LEFT_EYE_TIM, LEFT_EYE_CHANNEL, LEFT_EYE_FREQ, LEFT_EYE_OFF);
}

void LeftEyeFullON(void)
{
    BspSetTIMOutPWM(LEFT_EYE_PORT, LEFT_EYE_PIN, LEFT_EYE_TIM, LEFT_EYE_CHANNEL, LEFT_EYE_FREQ, LEFT_EYE_FULL_ON);
}

void LeftEyeSetDuty(uint32_t duty) //0-100
{   
    //BspSetTIMOutPWM(LEFT_EYE_PORT, LEFT_EYE_PIN, LEFT_EYE_TIM, LEFT_EYE_CHANNEL, LEFT_EYE_FREQ, duty*100);
    TIM_SetCompare4(LEFT_EYE_TIM, duty*9);
}

/**/
void AllEyeFullON(void)
{
    LeftEyeFullON();
    RightEyeFullON();
}

void AllEyeFullOFF(void)
{
    LeftEyeOFF();
    RightEyeOFF();
}

void AllEyeSetDuty(uint32_t duty)
{
    LeftEyeSetDuty(duty);
    RightEyeSetDuty(duty);
}

void SeparateEyeSetDuty(uint32_t righteyeduty, uint32_t lefteyeduty)
{
    LeftEyeSetDuty(righteyeduty);
    RightEyeSetDuty(lefteyeduty);
}
