#include "control.h"

//static int PectoralfinSwing[] = {900, 1000, 1100, 1200, 1300, 1400, 
//                                 1500, 1600, 1700, 1800, 1900, 2000, 2100}; 

/*
软件定时器1未用到
*/


/*
软件定时器2未用到
*/


/*
软件定时器3负责胸鳍上浮的周期摆动
*/
void StartPectoralFinUp(void)
{
    bsp_StartAutoTimer(PectoralFinUpSoftTimerID, 1000);
}

uint8_t CheckPectoralFinUpSoftTimerState(void)
{
    return bsp_CheckTimer(PectoralFinUpSoftTimerID);
}

void EndPectoralFinUp(void)
{  
    bsp_StopTimer(PectoralFinUpSoftTimerID);
}


/*
软件定时器4负责胸鳍下沉的周期摆动
*/
void StartPectoralFinDown(void)
{
    bsp_StartAutoTimer(PectoralFinDownSoftTimerID, 1000);
}

uint8_t CheckPectoralFinDownSoftTimerState(void)
{
    return bsp_CheckTimer(PectoralFinDownSoftTimerID);
}

void EndPectoralFinDown(void)
{ 
    bsp_StopTimer(PectoralFinDownSoftTimerID);
}


/*
软件定时器5负责胸鳍右转的周期摆动
*/
void StartPectoralFinRight(void)
{
//    pectoralfinSteer[0].SetDutyCycle(810);
//    bsp_DelayMS(500);//保护措施，先让舵机回到原来位置
    
    bsp_StartAutoTimer(PectoralFin_Right_SoftTimerID, 150);
}

uint8_t CheckPectoralFinRightSoftTimerState(void)
{
    return bsp_CheckTimer(PectoralFin_Right_SoftTimerID);
}

void EndPectoralFinRight(void)
{

    bsp_StopTimer(PectoralFin_Right_SoftTimerID);   
}

/*
软件定时器6负责胸鳍左转的周期摆动
*/
void StartPectoralFinLeft(void)
{
//    pectoralfinSteer[3].SetDutyCycle(720);
//    bsp_DelayMS(500);//保护措施，先让舵机回到原来位置
    
    bsp_StartAutoTimer(PectoralFin_Left_SoftTimerID, 150);
}

uint8_t CheckPectoralFinLeftSoftTimerState(void)
{
    return bsp_CheckTimer(PectoralFin_Left_SoftTimerID);
}

void EndPectoralFinLeft(void)
{
    bsp_StopTimer(PectoralFin_Left_SoftTimerID);
}

/*
软件定时器7未用到
*/


/*
软件定时器8未用到
*/
