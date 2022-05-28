#include "bsp.h"

void BspInit(void)
{
	SystemCoreClockUpdate();	/* 根据PLL配置更新系统时钟频率变量 SystemCoreClock = 180 000 000Hz */
    
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);	/* 优先级分组设置为4 */

	BspInitLED();       /*初始化LED灯*/
    BspInitKEY();       /*初始化按键*/    
    bsp_InitTimer();    /*初始化软件定时器*/
    BspInitUart();      /*初始化串口*/
    
    //printf("\r\nThis is 蠃 Contol board test\r\n");
    DPRINT("This is 蠃 Contol board test\r\n");
    
    BspInitSteer();     /*初始化舵机*/
    DetectWaterInit();  /*初始化漏水检测*/
    
    MPU_Init();         /*初始化MPU9250*/
    while(mpu_dmp_init()){DPRINT("MPU9250 Error\r\n");LED2_ON;} /*初始化MPU_MPL库*/
    
    EyeLedInit();
    bsp_DelayMS(2000);
    AllEyeFullOFF();

/*
脉宽对应改变占空比的值：
800 900 1000 1100 1200 1300 1400 1500 1600 1700 1800 1900 2000 2100 2200
720 810 900  990  1080 1170 1260 1350 1140 1530 1620 1710 1800 1890 1980
*/

/*0号舵机前贴身1800，后贴身810*/
/*3号舵机前贴身1845，后贴身720 */    
    //将鱼体
//    pectoralfinSteer[0].SetDutyCycle(810);//810是胸鳍紧贴鱼身体
//    pectoralfinSteer[3].SetDutyCycle(720);
    
//    pectoralfinSteer[0].SetDutyCycle(1800);//810是胸鳍紧贴鱼身体
//    pectoralfinSteer[3].SetDutyCycle(1845);
    
    MotorInit();
}

/*
*********************************************************************************************************
*	函 数 名: bsp_RunPer10ms
*	功能说明: 该函数每隔10ms被Systick中断调用1次。详见 bsp_timer.c的定时中断服务程序。一些处理时间要求不严格的
*			任务可以放在此函数。比如：按键扫描、蜂鸣器鸣叫控制等。
*	形    参：无
*	返 回 值: 无
*********************************************************************************************************
*/
void bsp_RunPer10ms(void)
{
	BspKeyScan();
}

/*
*********************************************************************************************************
*	函 数 名: bsp_RunPer1ms
*	功能说明: 该函数每隔1ms被Systick中断调用1次。详见 bsp_timer.c的定时中断服务程序。一些需要周期性处理的事务
*			 可以放在此函数。比如：触摸坐标扫描。
*	形    参: 无
*	返 回 值: 无
*********************************************************************************************************
*/

uint16_t g_ledflag = 0;
//uint16_t g_Deepflag = 0;
void bsp_RunPer1ms(void)
{
    if(++g_ledflag == 500)
    {
        SystemWorkNormalLED();
        g_ledflag = 0;
    }    

    if(CheckPectoralFinUpSoftTimerState())
    {            
        PectoralFinUp();
    }
    
    if(CheckPectoralFinDownSoftTimerState())
    {            
        PectoralFinDown();
    }
    
    if(CheckPectoralFinRightSoftTimerState())
    {
        PectoralFinRight();
    }
    
    if(CheckPectoralFinLeftSoftTimerState())
    {
        PectoralFinLeft();
    }
}

/*
*********************************************************************************************************
*	函 数 名: bsp_Idle
*	功能说明: 空闲时执行的函数。一般主程序在for和while循环程序体中需要插入 CPU_IDLE() 宏来调用本函数。
*			 本函数缺省为空操作。用户可以添加喂狗、设置CPU进入休眠模式的功能。
*	形    参：无
*	返 回 值: 无
*********************************************************************************************************
*/
void bsp_Idle(void)
{
	/* --- 喂狗 */

	/* --- 让CPU进入休眠，由Systick定时中断唤醒或者其他中断唤醒 */

	/* 例如 emWin 图形库，可以插入图形库需要的轮询函数 */
	//GUI_Exec();

	/* 例如 uIP 协议，可以插入uip轮询函数 */
}  
