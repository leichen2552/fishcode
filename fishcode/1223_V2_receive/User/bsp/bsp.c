#include "bsp.h"

void BspInit(void)
{
	SystemCoreClockUpdate();	/* ����PLL���ø���ϵͳʱ��Ƶ�ʱ��� SystemCoreClock = 180 000 000Hz */
    
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);	/* ���ȼ���������Ϊ4 */

	BspInitLED();       /*��ʼ��LED��*/
    BspInitKEY();       /*��ʼ������*/    
    bsp_InitTimer();    /*��ʼ�������ʱ��*/
    BspInitUart();      /*��ʼ������*/
    
    //printf("\r\nThis is �� Contol board test\r\n");
    DPRINT("This is �� Contol board test\r\n");
    
    BspInitSteer();     /*��ʼ�����*/
    DetectWaterInit();  /*��ʼ��©ˮ���*/
    
    MPU_Init();         /*��ʼ��MPU9250*/
    while(mpu_dmp_init()){DPRINT("MPU9250 Error\r\n");LED2_ON;} /*��ʼ��MPU_MPL��*/
    
    EyeLedInit();
    bsp_DelayMS(2000);
    AllEyeFullOFF();

/*
�����Ӧ�ı�ռ�ձȵ�ֵ��
800 900 1000 1100 1200 1300 1400 1500 1600 1700 1800 1900 2000 2100 2200
720 810 900  990  1080 1170 1260 1350 1140 1530 1620 1710 1800 1890 1980
*/

/*0�Ŷ��ǰ����1800��������810*/
/*3�Ŷ��ǰ����1845��������720 */    
    //������
//    pectoralfinSteer[0].SetDutyCycle(810);//810����������������
//    pectoralfinSteer[3].SetDutyCycle(720);
    
//    pectoralfinSteer[0].SetDutyCycle(1800);//810����������������
//    pectoralfinSteer[3].SetDutyCycle(1845);
    
    MotorInit();
}

/*
*********************************************************************************************************
*	�� �� ��: bsp_RunPer10ms
*	����˵��: �ú���ÿ��10ms��Systick�жϵ���1�Ρ���� bsp_timer.c�Ķ�ʱ�жϷ������һЩ����ʱ��Ҫ���ϸ��
*			������Է��ڴ˺��������磺����ɨ�衢���������п��Ƶȡ�
*	��    �Σ���
*	�� �� ֵ: ��
*********************************************************************************************************
*/
void bsp_RunPer10ms(void)
{
	BspKeyScan();
}

/*
*********************************************************************************************************
*	�� �� ��: bsp_RunPer1ms
*	����˵��: �ú���ÿ��1ms��Systick�жϵ���1�Ρ���� bsp_timer.c�Ķ�ʱ�жϷ������һЩ��Ҫ�����Դ��������
*			 ���Է��ڴ˺��������磺��������ɨ�衣
*	��    ��: ��
*	�� �� ֵ: ��
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
*	�� �� ��: bsp_Idle
*	����˵��: ����ʱִ�еĺ�����һ����������for��whileѭ������������Ҫ���� CPU_IDLE() �������ñ�������
*			 ������ȱʡΪ�ղ������û��������ι��������CPU��������ģʽ�Ĺ��ܡ�
*	��    �Σ���
*	�� �� ֵ: ��
*********************************************************************************************************
*/
void bsp_Idle(void)
{
	/* --- ι�� */

	/* --- ��CPU�������ߣ���Systick��ʱ�жϻ��ѻ��������жϻ��� */

	/* ���� emWin ͼ�ο⣬���Բ���ͼ�ο���Ҫ����ѯ���� */
	//GUI_Exec();

	/* ���� uIP Э�飬���Բ���uip��ѯ���� */
}  
