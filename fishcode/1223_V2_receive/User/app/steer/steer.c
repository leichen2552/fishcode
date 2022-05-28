#include "steer.h"


SteerTypedef tailfinSteer[2];       /*��������β���������һ����β���0û���ϣ��õ���β�����1*/
SteerTypedef pectoralfinSteer[4];   /*�����ĸ������������ͷ����ǰ�棬�������� 0 1 2 3*/

/*����β�����Ķ�ʱ��*/
#define TAIL_FIN_TIM                    TIM3
#define PECTORAL_FIN_TIM                TIM4

/*����β���ĳ�ʼ��Ƶ�ʺ�ռ�ձ�*/
#define TAIL_FIN_STEER_FREQ             50
#define TAIL_FIN_STEER_INIT_DUTY        750

/*���������ĳ�ʼ��Ƶ�ʺ�ռ�ձ�*/
#define PECTORAL_FIN_STEER_FREQ         100
#define PECTORAL_FIN_STEER_INIT_DUTY    1500

/*���������˿ں�����*/
//#define PECTORAL_FIN0_PORT          GPIOD
//#define PECTORAL_FIN0_PIN           GPIO_Pin_12

#define PECTORAL_FIN0_PORT          GPIOB
#define PECTORAL_FIN0_PIN           GPIO_Pin_0

#define PECTORAL_FIN1_PORT          GPIOD
#define PECTORAL_FIN1_PIN           GPIO_Pin_13

#define PECTORAL_FIN2_PORT          GPIOD
#define PECTORAL_FIN2_PIN           GPIO_Pin_14

#define PECTORAL_FIN3_PORT          GPIOD
#define PECTORAL_FIN3_PIN           GPIO_Pin_15

/*����β���˿ں�����*/
#define TAIL_FIN0_PORT              GPIOB
#define TAIL_FIN0_PIN               GPIO_Pin_0

#define TAIL_FIN1_PORT              GPIOB
#define TAIL_Fin1_PIN               GPIO_Pin_1

/*
�����Ӧ�ı�ռ�ձȵ�ֵ��
<<�ֲ�����ֵ800~2200>>            :800 900 1000 1100 1200 1300 1400 1500 1600 1700 1800 1900 2000 2100 2200
<<100HZ������޸ĵ�TIMSETCOMPARE>>:720 810 900  990  1080 1170 1260 1350 1140 1530 1620 1710 1800 1890 1980
*/

/*
*********************************************************************************************************
*	�� �� ��: BspSetSteerPWM(����BspSetTIMOutPWM�޸����ģ�������Ա�)
*	����˵��: �������������PWM�źŵ�Ƶ�ʺ�ռ�ձ�.  ��Ƶ��Ϊ0������ռ��Ϊ0ʱ���رն�ʱ����GPIO���0��
*			  ��Ƶ��Ϊ0��ռ�ձ�Ϊ100%ʱ��GPIO���1.
*	��    ��: _ulFreq : PWM�ź�Ƶ�ʣ���λHz  (ʵ�ʲ��ԣ�������Ƶ��Ϊ 180M / 4 = 45M��. 0 ��ʾ��ֹ���
*			  _ulDutyCycle : PWM�ź�ռ�ձȣ���λ���ٷ�֮һ����5000����ʾ50.00%��ռ�ձ�
*	�� �� ֵ: ��
*********************************************************************************************************
*/
static void BspSetSteerPWM(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin_x,
                           TIM_TypeDef* TIMx,   uint8_t _ucChannel,
                           uint32_t _ulFreq,    uint16_t _ulDutyCycle)
{
    BspSetTIMOutPWM(GPIOx, GPIO_Pin_x, TIMx, _ucChannel, _ulFreq, (uint32_t)(_ulDutyCycle));
}

/*����0*/
void PectoralFin0Init(void)
{
    BspSetSteerPWM(PECTORAL_FIN0_PORT, PECTORAL_FIN0_PIN, TIM3,  3, pectoralfinSteer[0].m_ulFreq,  pectoralfinSteer[0].m_ulDutyCycle);    
    
    //BspSetSteerPWM(TAIL_FIN0_PORT, TAIL_FIN0_PIN, TAIL_FIN_TIM,  3, tailfinSteer[0].m_ulFreq,  tailfinSteer[0].m_ulDutyCycle); 

}

void PectoralFin0SetDutyCycle(uint32_t _ulDutyCycle)
{
    pectoralfinSteer[0].m_ulDutyCycle = _ulDutyCycle;
    
    TIM_SetCompare1(TIM3, pectoralfinSteer[0].m_ulDutyCycle);
}


/*����1*/
void PectoralFin1Init(void)
{
    BspSetSteerPWM(PECTORAL_FIN1_PORT, PECTORAL_FIN1_PIN, PECTORAL_FIN_TIM,  2, pectoralfinSteer[1].m_ulFreq,  pectoralfinSteer[1].m_ulDutyCycle);    
}

void PectoralFin1SetDutyCycle(uint32_t _ulDutyCycle)
{
    pectoralfinSteer[1].m_ulDutyCycle = _ulDutyCycle;

    TIM_SetCompare2(PECTORAL_FIN_TIM, pectoralfinSteer[1].m_ulDutyCycle);
}


/*����2*/
void PectoralFin2Init(void)
{
    BspSetSteerPWM(PECTORAL_FIN2_PORT, PECTORAL_FIN2_PIN, PECTORAL_FIN_TIM,  3, pectoralfinSteer[2].m_ulFreq,  pectoralfinSteer[2].m_ulDutyCycle);    
}

void PectoralFin2SetDutyCycle(uint32_t _ulDutyCycle)
{
    pectoralfinSteer[2].m_ulDutyCycle = _ulDutyCycle;

    TIM_SetCompare3(PECTORAL_FIN_TIM, pectoralfinSteer[2].m_ulDutyCycle);
}


/*����3*/
void PectoralFin3Init(void)
{
    BspSetSteerPWM(PECTORAL_FIN3_PORT, PECTORAL_FIN3_PIN, PECTORAL_FIN_TIM,  4, pectoralfinSteer[3].m_ulFreq,  pectoralfinSteer[3].m_ulDutyCycle);    
}

void PectoralFin3SetDutyCycle(uint32_t _ulDutyCycle)
{
    pectoralfinSteer[3].m_ulDutyCycle = _ulDutyCycle;

    TIM_SetCompare4(PECTORAL_FIN_TIM, pectoralfinSteer[3].m_ulDutyCycle);
}


/*β��0,û���õ�*/
void TailFinSteer0Init()
{
    BspSetSteerPWM(TAIL_FIN0_PORT, TAIL_FIN0_PIN, TAIL_FIN_TIM,  3, tailfinSteer[0].m_ulFreq,  tailfinSteer[0].m_ulDutyCycle);    
}

void TailFinSteer0SetDutyCycle(uint32_t _ulDutyCycle)
{
    tailfinSteer[0].m_ulDutyCycle = _ulDutyCycle;

    TIM_SetCompare3(TAIL_FIN_TIM, tailfinSteer[0].m_ulDutyCycle);
}

/*β��1�õ�*/
void TailFinSteer1Init()
{
    BspSetSteerPWM(TAIL_FIN1_PORT, TAIL_Fin1_PIN, TAIL_FIN_TIM,  4, tailfinSteer[1].m_ulFreq,  tailfinSteer[1].m_ulDutyCycle);
}

void TailFinSteer1SetDutyCycle(uint32_t _ulDutyCycle)
{
    tailfinSteer[1].m_ulDutyCycle = _ulDutyCycle;

    TIM_SetCompare4(TAIL_FIN_TIM, tailfinSteer[1].m_ulDutyCycle);
}


void SteerVarInit(void)
{
    /* ����������ʼ�� */ 
    pectoralfinSteer[0].m_ulFreq = PECTORAL_FIN_STEER_FREQ;
    pectoralfinSteer[0].m_ulDutyCycle = PECTORAL_FIN_STEER_INIT_DUTY;
    pectoralfinSteer[0].SteerInit = PectoralFin0Init;
    pectoralfinSteer[0].SetDutyCycle = PectoralFin0SetDutyCycle;    

    pectoralfinSteer[1].m_ulFreq = PECTORAL_FIN_STEER_FREQ;
    pectoralfinSteer[1].m_ulDutyCycle = PECTORAL_FIN_STEER_INIT_DUTY - 50;//΢��50��Ϊ����1�Ŷ������ֱ״̬
    pectoralfinSteer[1].SteerInit = PectoralFin1Init;
    pectoralfinSteer[1].SetDutyCycle = PectoralFin1SetDutyCycle;

    pectoralfinSteer[2].m_ulFreq = PECTORAL_FIN_STEER_FREQ;
    pectoralfinSteer[2].m_ulDutyCycle = PECTORAL_FIN_STEER_INIT_DUTY - 75;//΢��50��Ϊ����2�Ŷ������ֱ״̬
    pectoralfinSteer[2].SteerInit = PectoralFin2Init;
    pectoralfinSteer[2].SetDutyCycle = PectoralFin2SetDutyCycle;

    pectoralfinSteer[3].m_ulFreq = PECTORAL_FIN_STEER_FREQ;
    pectoralfinSteer[3].m_ulDutyCycle = PECTORAL_FIN_STEER_INIT_DUTY;
    pectoralfinSteer[3].SteerInit = PectoralFin3Init;
    pectoralfinSteer[3].SetDutyCycle = PectoralFin3SetDutyCycle;    
    
    /* β��������ʼ�� */
    tailfinSteer[0].m_ulFreq = TAIL_FIN_STEER_FREQ;
    tailfinSteer[0].m_ulDutyCycle = TAIL_FIN_STEER_INIT_DUTY;
    tailfinSteer[0].SteerInit = TailFinSteer0Init;
    tailfinSteer[0].SetDutyCycle = TailFinSteer0SetDutyCycle;
    
    tailfinSteer[1].m_ulFreq = TAIL_FIN_STEER_FREQ;
    tailfinSteer[1].m_ulDutyCycle = TAIL_FIN_STEER_INIT_DUTY;
    tailfinSteer[1].SteerInit = TailFinSteer1Init;
    tailfinSteer[1].SetDutyCycle = TailFinSteer1SetDutyCycle;
    

}

void BspInitSteer()
{
    SteerVarInit();
    
    for(int i =1; i < sizeof(pectoralfinSteer)/sizeof(pectoralfinSteer[0]); i++)
    {
        pectoralfinSteer[i].SteerInit();
    }
    
    for(int i =0; i < sizeof(tailfinSteer)/sizeof(tailfinSteer[0]); i++)
    {
        tailfinSteer[i].SteerInit();
    }
}



void PectoralFinQianHouSwing(void)
{   
    static int pectoralfinQianToHouFlag = 0;
    static int pectoralfinQianToHouSwing[] = {837,  864,  891,  918,  945,  972,  999, 1026, 1053, 1080, 1107,
                                              1134, 1161, 1188, 1215, 1242, 1269, 1296, 1323, 1350, 1377, 1404, 1431};
    

    /*����1��2���ɶȱ�����ֱ*/
    pectoralfinSteer[1].SetDutyCycle(1305);
    pectoralfinSteer[2].SetDutyCycle(1305); 

    /*����0��3���ɶ�ǰ��*/
    pectoralfinSteer[0].SetDutyCycle(pectoralfinQianToHouSwing[pectoralfinQianToHouFlag]);
    pectoralfinSteer[3].SetDutyCycle(pectoralfinQianToHouSwing[pectoralfinQianToHouFlag]);
    pectoralfinQianToHouFlag++;
    if(pectoralfinQianToHouSwing[pectoralfinQianToHouFlag] == pectoralfinQianToHouSwing[1])
    {
        bsp_StopTimer(PectoralFinQianHouSoftTimerID);
        bsp_StartAutoTimer(PectoralFinQianHouSoftTimerID,200);
    }
    if((sizeof(pectoralfinQianToHouSwing)/sizeof(pectoralfinQianToHouSwing[0])) == pectoralfinQianToHouFlag)
    {
        pectoralfinQianToHouFlag = 0;
        bsp_StopTimer(PectoralFinQianHouSoftTimerID);
        bsp_StartAutoTimer(PectoralFinQianHouSoftTimerID,1000);
    }
}


void PectoralFinLeft(void)
{
/*0�Ŷ��ǰ����1800��������810*/
/*3�Ŷ��ǰ����1845��������720 */ 
    static int pectoralfin_3_LeftFlag = 0;
    
    static int pectoralfin_3_LeftSwing[] = {720,  738,   756,  774, 792,   810,  828,  846,  864,  882,
                                            900,  918,   936,  954, 972,   990, 1008, 1026, 1044, 1062, 
                                            1080, 1098, 1116, 1134, 1152, 1170, 1188, 1206, 1224, 1242, 
                                            1260, 1278, 1296, 1314, 1332, 1350}; 
    
//    static int pectoralfin_0_LeftSwing[] = {1800, 1782, 1764, 1746, 1728, 1710, 1692, 1674, 1656, 1638, 
//                                            1620, 1602, 1584, 1566, 1548, 1530, 1521, 1512, 1503, 1494, 
//                                            1485, 1476, 1467, 1458, 1449, 1440, 1431, 1422, 1413, 1404, 
//                                            1395, 1386, 1377, 1368, 1359, 1350};
                                            
                                            
//    static int pectoralfin_0_LeftSwing[] = {1350, 1359, 1368, 1377, 1386, 1395, 1404, 1413, 1422, 1431, 
//                                            1440, 1449, 1458, 1467, 1476, 1485, 1494, 1503, 1512, 1521, 
//                                            1530, 1548, 1566, 1584, 1602, 1620, 1638, 1656, 1674, 1692, 
//                                            1710, 1728, 1746, 1764, 1782, 1800}; 

/*0�Ŷ��*/    
//1368 1386 1404 1422 1440 1458 1476 1494 1512 1530 1548 
//1566 1584 1602 1620 1638 1656 1674 1692 1710 1728 1746
//1764 1782 1800    

/* 3�Ŷ��*/
//1350 1332 1314 1296 1278 1260 1242 1224 1206 1188 1170 1152 1134 1116 1098 1080 1062 1044 1026 1008 990
//972 954 936 918 900 882 864 846 828 810 792 774 756 738 720 
    /*0�Ŷ��������*/ 
    

    pectoralfinSteer[2].SetDutyCycle(1305);
   
    pectoralfinSteer[3].SetDutyCycle(pectoralfin_3_LeftSwing[pectoralfin_3_LeftFlag]);                                                                                 
    pectoralfin_3_LeftFlag++;                                             
    if(pectoralfin_3_LeftSwing[pectoralfin_3_LeftFlag] == pectoralfin_3_LeftSwing[1])
    {
        bsp_StopTimer(PectoralFin_Left_SoftTimerID);
        bsp_StartAutoTimer(PectoralFin_Left_SoftTimerID,150);
    } 
    else if((sizeof(pectoralfin_3_LeftSwing)/sizeof(pectoralfin_3_LeftSwing[0])) == pectoralfin_3_LeftFlag)
    {
        pectoralfin_3_LeftFlag = 0;
        bsp_StopTimer(PectoralFin_Left_SoftTimerID);
        bsp_StartAutoTimer(PectoralFin_Left_SoftTimerID,1000);
    }
    
    
    
    
}

void PectoralFinRight(void)
{
    static int pectoralfin_0_LeftFlag = 0;
    static int pectoralfin_0_LeftSwing[] = {810,828,846,864,882,900, 918,936,954,972,990, 
                                        1008, 1026, 1044, 1062, 1080, 1098, 1116, 1134, 1152, 1170, 
                                        1188, 1206, 1224, 1242, 1260, 1278, 1296, 1314, 1332, 1350}; 
        
    pectoralfinSteer[1].SetDutyCycle(1305);
                                        
    //printf("pectoralfin_0_LeftFlag = %d\r\n",pectoralfin_0_LeftFlag); 
    pectoralfinSteer[0].SetDutyCycle(pectoralfin_0_LeftSwing[pectoralfin_0_LeftFlag]);
    pectoralfin_0_LeftFlag++;
    if(pectoralfin_0_LeftSwing[pectoralfin_0_LeftFlag] == pectoralfin_0_LeftSwing[1])
    {
        bsp_StopTimer(PectoralFin_Right_SoftTimerID);
        bsp_StartAutoTimer(PectoralFin_Right_SoftTimerID,150);
    }
    if((sizeof(pectoralfin_0_LeftSwing)/sizeof(pectoralfin_0_LeftSwing[0])) == pectoralfin_0_LeftFlag)
    {
        pectoralfin_0_LeftFlag = 0;
        bsp_StopTimer(PectoralFin_Right_SoftTimerID);
        bsp_StartAutoTimer(PectoralFin_Right_SoftTimerID,1000);
    }
}


/*
�����Ӧ�ı�ռ�ձȵ�ֵ��
800 900 1000 1100 1200 1300 1400 1500 1600 1700 1800 1900 2000 2100 2200
720 810 900  990  1080 1170 1260 1350 1140 1530 1620 1710 1800 1890 1980
*/

void PectoralFinUp(void)
{
    static int pectoralfinUpSwingFlag = 0;
    static int pectoralfinUpSwing[] = {1080,1620,1620,1080}; 
    
    if(pectoralfinUpSwingFlag <=1)
    {
        pectoralfinSteer[1].SetDutyCycle(1935);
        pectoralfinSteer[2].SetDutyCycle(630); 
    }
    
    if(pectoralfinUpSwingFlag >1)
    {
        pectoralfinSteer[1].SetDutyCycle(720);
        pectoralfinSteer[2].SetDutyCycle(1935);
    }
    
    pectoralfinSteer[0].SetDutyCycle(pectoralfinUpSwing[pectoralfinUpSwingFlag]);
    pectoralfinSteer[3].SetDutyCycle(pectoralfinUpSwing[pectoralfinUpSwingFlag]);
    pectoralfinUpSwingFlag++;
    if((sizeof(pectoralfinUpSwing)/sizeof(pectoralfinUpSwing[0])) == pectoralfinUpSwingFlag)
    {
        pectoralfinUpSwingFlag=0;
    }
}


void PectoralFinDown(void)
{
    static int pectoralfinDownSwingFlag = 0;
    static int pectoralfinDownSwing[] = {1620,1080,1080,1620}; 
    
    if(pectoralfinDownSwingFlag <=1)
    {
        pectoralfinSteer[1].SetDutyCycle(1935);
        pectoralfinSteer[2].SetDutyCycle(630); 
    }
    
    if(pectoralfinDownSwingFlag >1)
    {
        pectoralfinSteer[1].SetDutyCycle(720);
        pectoralfinSteer[2].SetDutyCycle(1935);
    }
    
    pectoralfinSteer[0].SetDutyCycle(pectoralfinDownSwing[pectoralfinDownSwingFlag]);
    pectoralfinSteer[3].SetDutyCycle(pectoralfinDownSwing[pectoralfinDownSwingFlag]);
    pectoralfinDownSwingFlag++;
    if((sizeof(pectoralfinDownSwing)/sizeof(pectoralfinDownSwing[0])) == pectoralfinDownSwingFlag)
    {
        pectoralfinDownSwingFlag=0;
    }
}

