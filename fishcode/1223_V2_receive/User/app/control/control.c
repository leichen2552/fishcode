#include "control.h"

//static int PectoralfinSwing[] = {900, 1000, 1100, 1200, 1300, 1400, 
//                                 1500, 1600, 1700, 1800, 1900, 2000, 2100}; 

/*
�����ʱ��1δ�õ�
*/


/*
�����ʱ��2δ�õ�
*/


/*
�����ʱ��3���������ϸ������ڰڶ�
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
�����ʱ��4���������³������ڰڶ�
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
�����ʱ��5����������ת�����ڰڶ�
*/
void StartPectoralFinRight(void)
{
//    pectoralfinSteer[0].SetDutyCycle(810);
//    bsp_DelayMS(500);//������ʩ�����ö���ص�ԭ��λ��
    
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
�����ʱ��6����������ת�����ڰڶ�
*/
void StartPectoralFinLeft(void)
{
//    pectoralfinSteer[3].SetDutyCycle(720);
//    bsp_DelayMS(500);//������ʩ�����ö���ص�ԭ��λ��
    
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
�����ʱ��7δ�õ�
*/


/*
�����ʱ��8δ�õ�
*/
