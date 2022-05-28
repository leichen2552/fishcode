#include "bsp_key.h" 

#define RCC_ALL_KEY                 ((RCC_AHB1Periph_GPIOC)|    \
                                     (RCC_AHB1Periph_GPIOA)|    \
                                     (RCC_AHB1Periph_GPIOD))

#define GPIO_PORT_K1                GPIOC
#define GPIO_PIN_K1                 GPIO_Pin_10

#define GPIO_PORT_K2                GPIOC
#define GPIO_PIN_K2                 GPIO_Pin_11

#define GPIO_PORT_K3                GPIOC
#define GPIO_PIN_K3                 GPIO_Pin_12

#define GPIO_PORT_K4                GPIOA
#define GPIO_PIN_K4                 GPIO_Pin_0

#define GPIO_PORT_K5                GPIOA
#define GPIO_PIN_K5                 GPIO_Pin_1

#define GPIO_PORT_K6                GPIOA
#define GPIO_PIN_K6                 GPIO_Pin_2

#define GPIO_PORT_K7                GPIOA
#define GPIO_PIN_K7                 GPIO_Pin_3

#define GPIO_PORT_K8                GPIOA
#define GPIO_PIN_K8                 GPIO_Pin_4

#define GPIO_PORT_K9                GPIOA
#define GPIO_PIN_K9                 GPIO_Pin_5

#define GPIO_PORT_K10                GPIOA
#define GPIO_PIN_K10                 GPIO_Pin_6

#define GPIO_PORT_K11                GPIOA
#define GPIO_PIN_K11                 GPIO_Pin_7

//PD14 PD15
#define GPIO_PORT_K12                GPIOD
#define GPIO_PIN_K12                 GPIO_Pin_14

#define GPIO_PORT_K13                GPIOD
#define GPIO_PIN_K13                 GPIO_Pin_15

static KEY_Typedef s_tBtn[KEY_COUNT];
static KEY_FIFO_Typedef s_tKey;

static uint8_t IsKeyDown1(void)  {if((GPIO_PORT_K1->IDR & GPIO_PIN_K1) == 0) {return 1;} else {return 0;}}
static uint8_t IsKeyDown2(void)  {if((GPIO_PORT_K2->IDR & GPIO_PIN_K2) == 0) {return 1;} else {return 0;}}
static uint8_t IsKeyDown3(void)  {if((GPIO_PORT_K3->IDR & GPIO_PIN_K3) == 0) {return 1;} else {return 0;}}
static uint8_t IsKeyDown4(void)  {if((GPIO_PORT_K4->IDR & GPIO_PIN_K4) == 0) {return 1;} else {return 0;}}
static uint8_t IsKeyDown5(void)  {if((GPIO_PORT_K5->IDR & GPIO_PIN_K5) == 0) {return 1;} else {return 0;}}
static uint8_t IsKeyDown6(void)  {if((GPIO_PORT_K6->IDR & GPIO_PIN_K6) == 0) {return 1;} else {return 0;}}
static uint8_t IsKeyDown7(void)  {if((GPIO_PORT_K7->IDR & GPIO_PIN_K7) == 0) {return 1;} else {return 0;}}
static uint8_t IsKeyDown8(void)  {if((GPIO_PORT_K8->IDR & GPIO_PIN_K8) == 0) {return 1;} else {return 0;}}
static uint8_t IsKeyDown9(void)  {if((GPIO_PORT_K9->IDR & GPIO_PIN_K9) == 0) {return 1;} else {return 0;}}
static uint8_t IsKeyDown10(void)  {if((GPIO_PORT_K10->IDR & GPIO_PIN_K10) == 0) {return 1;} else {return 0;}}
static uint8_t IsKeyDown11(void)  {if((GPIO_PORT_K11->IDR & GPIO_PIN_K11) == 0) {return 1;} else {return 0;}}
static uint8_t IsKeyDown12(void)  {if((GPIO_PORT_K12->IDR & GPIO_PIN_K12) == 0) {return 1;} else {return 0;}}
static uint8_t IsKeyDown13(void)  {if((GPIO_PORT_K13->IDR & GPIO_PIN_K13) == 0) {return 1;} else {return 0;}}

//static uint8_t IsKeyDown4(void)  {if(IsKeyDown1() && IsKeyDown2()) {return 1;} else {return 0;}}
//static uint8_t IsKeyDown5(void)  {if(IsKeyDown1() && IsKeyDown3()) {return 1;} else {return 0;}}
//static uint8_t IsKeyDown6(void)  {if(IsKeyDown2() && IsKeyDown3()) {return 1;} else {return 0;}}
//static uint8_t IsKeyDown7(void)  {if(IsKeyDown1() && IsKeyDown2() && IsKeyDown3()) {return 1;} else {return 0;}}

void BspPutKey(uint8_t _KeyCode)
{
    s_tKey.Buf[s_tKey.Write] = _KeyCode;
    
    if(++s_tKey.Write >= KEY_FIFO_SIZE)
    {
        s_tKey.Write = 0;
    }
}

/*�Ӱ���FIFO��������ȡһ����ֵ*/
uint8_t BspGetKey(void)
{
    uint8_t ret;
    
    if(s_tKey.Read == s_tKey.Write)
    {
        return KEY_NONE;
    }
    else
    {
        ret = s_tKey.Buf[s_tKey.Read];
        
        if(++s_tKey.Read >= KEY_FIFO_SIZE)
        {
            s_tKey.Read = 0;
        }
        
        return ret;
    }        
}

/*
*********************************************************************************************************
*	�� �� ��: bsp_GetKey2
*	����˵��: �Ӱ���FIFO��������ȡһ����ֵ�������Ķ�ָ�롣
*	��    ��:  ��
*	�� �� ֵ: ��������
*********************************************************************************************************
*/
uint8_t BspGetKey2(void)
{
    uint8_t ret;
    
    if(s_tKey.Read2 == s_tKey.Write)
    {
        return KEY_NONE;
    }
    else
    {
        ret = s_tKey.Buf[s_tKey.Read2];
        
        if(++s_tKey.Read2 >= KEY_FIFO_SIZE)
        {
            s_tKey.Read2 = 0;
        }
        
        return ret;
    }        
}

/*
*********************************************************************************************************
*	�� �� ��: bsp_GetKeyState
*	����˵��: ��ȡ������״̬
*	��    ��:  _ucKeyID : ����ID����0��ʼ
*	�� �� ֵ: 1 ��ʾ���£� 0 ��ʾδ����
*********************************************************************************************************
*/
uint8_t BspGetKeyState(KEY_ID_E _ucKeyID)
{
    return s_tBtn[_ucKeyID].State;
}

/*
*********************************************************************************************************
*	�� �� ��: bsp_SetKeyParam
*	����˵��: ���ð�������
*	��    �Σ�_ucKeyID : ����ID����0��ʼ
*			_LongTime : �����¼�ʱ��
*			 _RepeatSpeed : �����ٶ�
*	�� �� ֵ: ��
*********************************************************************************************************
*/
void BspSetKeyParam(uint8_t _ucKeyID, uint16_t _LongTime, uint8_t _RepeatSpeed)
{
    s_tBtn[_ucKeyID].LongTime = _LongTime;          /* ����ʱ�� 0 ��ʾ����ⳤ�����¼� */
    s_tBtn[_ucKeyID].RepeatSpeed = _RepeatSpeed;    /* �����������ٶȣ�0��ʾ��֧������ */
    s_tBtn[_ucKeyID].RepeatCount = 0;               /* ���������� */
}

/*
*********************************************************************************************************
*	�� �� ��: bsp_ClearKey
*	����˵��: ��հ���FIFO������
*	��    �Σ���
*	�� �� ֵ: ��������
*********************************************************************************************************
*/
void BspClearKey(void)
{
    s_tKey.Read = s_tKey.Write;
}


static void BspInitKeyHard(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	/*��������GPIO�ڵ�ʱ��*/
	RCC_AHB1PeriphClockCmd(RCC_ALL_KEY,ENABLE);
	 
    /* ��2�����������еİ���GPIOΪ��������ģʽ(ʵ����CPU��λ���������״̬) */
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN; 
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    
    GPIO_InitStructure.GPIO_Pin = GPIO_PIN_K1;
	GPIO_Init(GPIO_PORT_K1, &GPIO_InitStructure);    
  
	GPIO_InitStructure.GPIO_Pin = GPIO_PIN_K2; 
	GPIO_Init(GPIO_PORT_K2, &GPIO_InitStructure);  
    
    GPIO_InitStructure.GPIO_Pin = GPIO_PIN_K3; 
	GPIO_Init(GPIO_PORT_K3, &GPIO_InitStructure);
    
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN; 
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    
    GPIO_InitStructure.GPIO_Pin = GPIO_PIN_K4 | GPIO_PIN_K5 | GPIO_PIN_K6 | GPIO_PIN_K7|
                                    GPIO_PIN_K8 | GPIO_PIN_K9 | GPIO_PIN_K10 | GPIO_PIN_K11; 
	GPIO_Init(GPIOA, &GPIO_InitStructure);
    
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN; 
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    
    GPIO_InitStructure.GPIO_Pin = GPIO_PIN_K12 | GPIO_PIN_K13;
	GPIO_Init(GPIOD, &GPIO_InitStructure);

}

/*
*********************************************************************************************************
*	�� �� ��: bsp_InitKeyVar
*	����˵��: ��ʼ����������
*	��    ��:  ��
*	�� �� ֵ: ��
*********************************************************************************************************
*/
static void BspInitKeyVar(void)
{
    uint8_t i;
    
    s_tKey.Read = 0;
    s_tKey.Write = 0;
    s_tKey.Read2 = 0;
    
    for(i = 0; i < KEY_COUNT; i++)
    {
        s_tBtn[i].LongTime = KEY_LONG_TIME;         /* ����ʱ�� 0 ��ʾ����ⳤ�����¼� */
        s_tBtn[i].Count = KEY_FILTER_TIME / 2;      /* ����������Ϊ�˲�ʱ���һ�� */ 
        s_tBtn[i].State = 0;                        /* ����ȱʡ״̬��0Ϊδ���� */
        
        s_tBtn[i].RepeatSpeed = 0;                  /* �����������ٶȣ�0��ʾ��֧������ */   
        s_tBtn[i].RepeatCount = 0;                  /* ���������� */
    }

	/* �����Ҫ��������ĳ�������Ĳ����������ڴ˵������¸�ֵ */
	/* ���磬����ϣ������1���³���1����Զ��ط���ͬ��ֵ */    
//    s_tBtn[KID_K1].LongTime = 100;
//    s_tBtn[KID_K1].RepeatSpeed = 5;     /* ÿ��50ms�Զ����ͼ�ֵ */
//    
//    s_tBtn[KID_K2].LongTime = 100;
//    s_tBtn[KID_K2].RepeatSpeed = 5;     /* ÿ��50ms�Զ����ͼ�ֵ */
//    
//    s_tBtn[KID_K3].LongTime = 100;
//    s_tBtn[KID_K3].RepeatSpeed = 5;     /* ÿ��50ms�Զ����ͼ�ֵ */
    
    s_tBtn[0].IsKeyDownFunc = IsKeyDown1;
    s_tBtn[1].IsKeyDownFunc = IsKeyDown2;
    s_tBtn[2].IsKeyDownFunc = IsKeyDown3;
    s_tBtn[3].IsKeyDownFunc = IsKeyDown4;  
    s_tBtn[4].IsKeyDownFunc = IsKeyDown5;
    s_tBtn[5].IsKeyDownFunc = IsKeyDown6;
    s_tBtn[6].IsKeyDownFunc = IsKeyDown7;
    s_tBtn[7].IsKeyDownFunc = IsKeyDown8;
    s_tBtn[8].IsKeyDownFunc = IsKeyDown9;
    s_tBtn[9].IsKeyDownFunc = IsKeyDown10;  
    s_tBtn[10].IsKeyDownFunc = IsKeyDown11;
    s_tBtn[11].IsKeyDownFunc = IsKeyDown12;  
    s_tBtn[12].IsKeyDownFunc = IsKeyDown13;
}

static void BspDetectKey(uint8_t i)
{
    KEY_Typedef *pBtn;
    
    pBtn = &s_tBtn[i];
    if(pBtn->IsKeyDownFunc())
    {
        /*�������ִ�е��ǰ������µĴ���*/
        
        /* �������if�����Ҫ�����ڰ����˲�ǰ��Count����һ����ֵ��ǰ��˵������ʼ����ʱ���Ѿ�������Count = KEY_FILTER_TIME/2 */ 
        if(pBtn->Count < KEY_FILTER_TIME)
        {
            pBtn->Count = KEY_FILTER_TIME;
        }
        /* ����ʵ��KEY_FILTER_TIMEʱ�䳤�ȵ��ӳ� */
        else if(pBtn->Count < 2 * KEY_FILTER_TIME)
        {
            pBtn->Count ++;
        }
        /* ����ʵ��KEY_FILTER_TIMEʱ�䳤�ȵ��ӳ� */
        else
        {
            /* 
            ********************************************************************************** 
            ���State����������ʵ������ģ�������������ˣ�����ͽ�������Ϊ1�����û�а������ 
            ������ֵ�ͻ�һֱ��0���������õ�Ŀ�Ŀ�����Ч�ķ�ֹһ������ĳ��֣����簴��K1��ĳ�� 
            ʱ�̼�⵽�˰����а��£���ô���ͻ�����һ�����˲������������˲��Ĺ����У�������� 
            ���µ�״̬��ʧ�ˣ����ʱ��ͻ���뵽����ڶ���else������棬Ȼ�������������ּ���˲� 
            ���˲��������ж����State���������ǰ���û�м�⵽���£�����Ͳ����¼�������� 
            ********************************************************************************** 
            */
            if(pBtn->State == 0)
            {
                pBtn->State = 1;
                /* ���Ͱ�ť���µ���Ϣ */ 
                BspPutKey((uint8_t)(3 * i + 1));
            }
            
            if(pBtn->LongTime > 0)
            {
                if(pBtn->LongCount < pBtn->LongTime)
                {
                    /* ���Ͱ�ť���µ���Ϣ */ 
                    if(++pBtn->LongCount == pBtn->LongTime)
                    {
                        /* ��ֵ���밴��FIFO */ 
                        BspPutKey((uint8_t)(3 * i + 3));
                    }
                }
                else
                {
                    if(pBtn->RepeatSpeed > 0)
                    {
                        if(++pBtn->RepeatCount >= pBtn->RepeatSpeed)
                        {
                            pBtn->RepeatCount = 0;
                            
                            /* ��������ÿ��10ms����1������ */ 
                            BspPutKey((uint8_t)(3 * i + 1));
                        }
                    }
                }               
            }
        }       
    }
    else
    {
        /*�������ִ�е��ǰ������ֵĴ�����߰���û�а��µĴ��� */
        if(pBtn->Count > KEY_FILTER_TIME)
        {
            pBtn->Count = KEY_FILTER_TIME;
        }
        else if(pBtn->Count != 0)
        {
            pBtn->Count --;
        }
        else
        {
            if(pBtn->State == 1)
            {
                pBtn->State = 0;
                BspPutKey((uint8_t)(3 * i + 2));                
            }
        }  
            
        pBtn->LongCount = 0;
        pBtn->RepeatCount = 0;       
    }   
}

void BspKeyScan(void)
{
    uint8_t i;
    
    for(i = 0; i < KEY_COUNT; i++)
    {
        BspDetectKey(i);
    }
}

void BspInitKEY(void)
{
    BspInitKeyVar();
    BspInitKeyHard();
}



/*********************************************END OF FILE**********************/
