#include "control.h"




/*
软件定时器1负责尾鳍的周期摆动
*/
void StartTailFinSwing(void)
{
    bsp_StartAutoTimer(TailFinSwingSoftTimerID, 500);
}

uint8_t CheckTailFinSwingSoftTimerState(void)
{
    return bsp_CheckTimer(TailFinSwingSoftTimerID);
}

void EndTailFinSwing(void)
{
    int* tailfinSteer_1_Array = NULL;
    
    tailfinSteer_1_Array = TailFinSwing();
    
    bsp_StopTimer(TailFinSwingSoftTimerID);
    bsp_DelayMS(1000);
    tailfinSteer[1].SetDutyCycle(1280);
    *tailfinSteer_1_Array = 0;
}

/*
软件定时器2负责胸鳍前后的周期摆动
*/
void StartPectoralFinQianHouSwing(void)
{
    bsp_StartAutoTimer(PectoralFinQianHouSoftTimerID, 1000);
}

uint8_t CheckPectoralFinQianHouSwingSoftTimerState(void)
{
    return bsp_CheckTimer(PectoralFinQianHouSoftTimerID);
}

void EndPectoralFinQianHouSwing(void)
{
    int* pectoralfinQianToHou = NULL;
    
    pectoralfinQianToHou = PectoralFinQianHouSwing();
    
    bsp_StopTimer(PectoralFinQianHouSoftTimerID);
    
    *pectoralfinQianToHou = 0;
}


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
    int* pectoralfinUpSwing = NULL;
    
    pectoralfinUpSwing = PectoralFinUp();
    
    bsp_StopTimer(PectoralFinUpSoftTimerID);
    
    *pectoralfinUpSwing = 0;
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
    int* pectoralfinDownSwing = NULL;
    
    pectoralfinDownSwing = PectoralFinDown();
    
    bsp_StopTimer(PectoralFinDownSoftTimerID);
    
    *pectoralfinDownSwing = 0;
}


/*
软件定时器5负责胸鳍右转的周期摆动
*/
void StartPectoralFinRight(void)
{
    bsp_StartAutoTimer(PectoralFinRightSoftTimerID, 1000);
}

uint8_t CheckPectoralFinRightSoftTimerState(void)
{
    return bsp_CheckTimer(PectoralFinRightSoftTimerID);
}

void EndPectoralFinRight(void)
{
    int* pectoralfinRight = NULL;
    
    pectoralfinRight = PectoralFinRight();
    
    bsp_StopTimer(PectoralFinRightSoftTimerID);
    
    *pectoralfinRight = 0;
}

/*
软件定时器6负责胸鳍左转的周期摆动
*/
void StartPectoralFinLeft(void)
{
    bsp_StartAutoTimer(PectoralFinLeftSoftTimerID, 1000);
}

uint8_t CheckPectoralFinLeftSoftTimerState(void)
{
    return bsp_CheckTimer(PectoralFinLeftSoftTimerID);
}

void EndPectoralFinLeft(void)
{
    int* pectoralfinLeft = PectoralFinLeft();
    
    bsp_StopTimer(PectoralFinLeftSoftTimerID);
    
    *pectoralfinLeft = 0;
}

/*
软件定时器7负责尾鳍左转的周期摆动
*/
void StartTailFinLeft(void)
{
    bsp_StartAutoTimer(TailFinLeftSoftTimerID, 1000);
}

uint8_t CheckTailFinLeftSoftTimerState(void)
{
    return bsp_CheckTimer(TailFinLeftSoftTimerID);
}

void EndTailFinLeft(void)
{
    int* tailfin_1_Left = NULL;
    
    tailfin_1_Left = TailFinLeft();
    
    bsp_StopTimer(TailFinLeftSoftTimerID);
    
    *tailfin_1_Left = 0;
    bsp_DelayMS(1000);
    tailfinSteer[1].SetDutyCycle(1280);
}


/*
软件定时器8负责尾鳍右转的周期摆动
*/
void StartTailFinRight(void)
{
    bsp_StartAutoTimer(TailFinRightSoftTimerID, 1000);
}

uint8_t CheckTailFinRightSoftTimerState(void)
{
    return bsp_CheckTimer(TailFinRightSoftTimerID);
}

void EndTailFinRight(void)
{
    int* tailfin_1_Right = NULL;
    
    tailfin_1_Right = TailFinRight();
    
    bsp_StopTimer(TailFinRightSoftTimerID);
    
    *tailfin_1_Right = 0;
    bsp_DelayMS(1000);
    tailfinSteer[1].SetDutyCycle(1280);
}
