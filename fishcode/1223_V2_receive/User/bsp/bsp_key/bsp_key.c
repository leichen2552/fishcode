#include "bsp_key.h" 

#define RCC_ALL_KEY                 (RCC_AHB1Periph_GPIOC)

#define GPIO_PORT_K1                GPIOC
#define GPIO_PIN_K1                 GPIO_Pin_10

#define GPIO_PORT_K2                GPIOC
#define GPIO_PIN_K2                 GPIO_Pin_11

#define GPIO_PORT_K3                GPIOC
#define GPIO_PIN_K3                 GPIO_Pin_12

static KEY_Typedef s_tBtn[KEY_COUNT];
static KEY_FIFO_Typedef s_tKey;

static uint8_t IsKeyDown1(void)  {if((GPIO_PORT_K1->IDR & GPIO_PIN_K1) == 0) {return 1;} else {return 0;}}
static uint8_t IsKeyDown2(void)  {if((GPIO_PORT_K2->IDR & GPIO_PIN_K2) == 0) {return 1;} else {return 0;}}
static uint8_t IsKeyDown3(void)  {if((GPIO_PORT_K3->IDR & GPIO_PIN_K3) == 0) {return 1;} else {return 0;}}
static uint8_t IsKeyDown4(void)  {if(IsKeyDown1() && IsKeyDown2()) {return 1;} else {return 0;}}
static uint8_t IsKeyDown5(void)  {if(IsKeyDown1() && IsKeyDown3()) {return 1;} else {return 0;}}
static uint8_t IsKeyDown6(void)  {if(IsKeyDown2() && IsKeyDown3()) {return 1;} else {return 0;}}
//static uint8_t IsKeyDown7(void)  {if(IsKeyDown1() && IsKeyDown2() && IsKeyDown3()) {return 1;} else {return 0;}}

void BspPutKey(uint8_t _KeyCode)
{
    s_tKey.Buf[s_tKey.Write] = _KeyCode;
    
    if(++s_tKey.Write >= KEY_FIFO_SIZE)
    {
        s_tKey.Write = 0;
    }
}

/*从按键FIFO缓冲区读取一个键值*/
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
*	函 数 名: bsp_GetKey2
*	功能说明: 从按键FIFO缓冲区读取一个键值。独立的读指针。
*	形    参:  无
*	返 回 值: 按键代码
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
*	函 数 名: bsp_GetKeyState
*	功能说明: 读取按键的状态
*	形    参:  _ucKeyID : 按键ID，从0开始
*	返 回 值: 1 表示按下， 0 表示未按下
*********************************************************************************************************
*/
uint8_t BspGetKeyState(KEY_ID_E _ucKeyID)
{
    return s_tBtn[_ucKeyID].State;
}

/*
*********************************************************************************************************
*	函 数 名: bsp_SetKeyParam
*	功能说明: 设置按键参数
*	形    参：_ucKeyID : 按键ID，从0开始
*			_LongTime : 长按事件时间
*			 _RepeatSpeed : 连发速度
*	返 回 值: 无
*********************************************************************************************************
*/
void BspSetKeyParam(uint8_t _ucKeyID, uint16_t _LongTime, uint8_t _RepeatSpeed)
{
    s_tBtn[_ucKeyID].LongTime = _LongTime;          /* 长按时间 0 表示不检测长按键事件 */
    s_tBtn[_ucKeyID].RepeatSpeed = _RepeatSpeed;    /* 按键连发的速度，0表示不支持连发 */
    s_tBtn[_ucKeyID].RepeatCount = 0;               /* 连发计数器 */
}

/*
*********************************************************************************************************
*	函 数 名: bsp_ClearKey
*	功能说明: 清空按键FIFO缓冲区
*	形    参：无
*	返 回 值: 按键代码
*********************************************************************************************************
*/
void BspClearKey(void)
{
    s_tKey.Read = s_tKey.Write;
}


static void BspInitKeyHard(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	/*开启按键GPIO口的时钟*/
	RCC_AHB1PeriphClockCmd(RCC_ALL_KEY,ENABLE);
	 
    /* 第2步：配置所有的按键GPIO为浮动输入模式(实际上CPU复位后就是输入状态) */
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
}

/*
*********************************************************************************************************
*	函 数 名: bsp_InitKeyVar
*	功能说明: 初始化按键变量
*	形    参:  无
*	返 回 值: 无
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
        s_tBtn[i].LongTime = KEY_LONG_TIME;         /* 长按时间 0 表示不检测长按键事件 */
        s_tBtn[i].Count = KEY_FILTER_TIME / 2;      /* 计数器设置为滤波时间的一半 */ 
        s_tBtn[i].State = 0;                        /* 按键缺省状态，0为未按下 */
        
        s_tBtn[i].RepeatSpeed = 0;                  /* 按键连发的速度，0表示不支持连发 */   
        s_tBtn[i].RepeatCount = 0;                  /* 连发计数器 */
    }

	/* 如果需要单独更改某个按键的参数，可以在此单独重新赋值 */
	/* 比如，我们希望按键1按下超过1秒后，自动重发相同键值 */    
//    s_tBtn[KID_K1].LongTime = 100;
//    s_tBtn[KID_K1].RepeatSpeed = 5;     /* 每隔50ms自动发送键值 */
//    
//    s_tBtn[KID_K2].LongTime = 100;
//    s_tBtn[KID_K2].RepeatSpeed = 5;     /* 每隔50ms自动发送键值 */
//    
//    s_tBtn[KID_K3].LongTime = 100;
//    s_tBtn[KID_K3].RepeatSpeed = 5;     /* 每隔50ms自动发送键值 */
    
    s_tBtn[0].IsKeyDownFunc = IsKeyDown1;
    s_tBtn[1].IsKeyDownFunc = IsKeyDown2;
    s_tBtn[2].IsKeyDownFunc = IsKeyDown3;
    s_tBtn[3].IsKeyDownFunc = IsKeyDown4;  
    s_tBtn[4].IsKeyDownFunc = IsKeyDown5;
    s_tBtn[5].IsKeyDownFunc = IsKeyDown6;
}

static void BspDetectKey(uint8_t i)
{
    KEY_Typedef *pBtn;
    
    pBtn = &s_tBtn[i];
    if(pBtn->IsKeyDownFunc())
    {
        /*这个里面执行的是按键按下的处理*/
        
        /* 下面这个if语句主要是用于按键滤波前给Count设置一个初值，前面说按键初始化的时候，已经设置了Count = KEY_FILTER_TIME/2 */ 
        if(pBtn->Count < KEY_FILTER_TIME)
        {
            pBtn->Count = KEY_FILTER_TIME;
        }
        /* 这里实现KEY_FILTER_TIME时间长度的延迟 */
        else if(pBtn->Count < 2 * KEY_FILTER_TIME)
        {
            pBtn->Count ++;
        }
        /* 这里实现KEY_FILTER_TIME时间长度的延迟 */
        else
        {
            /* 
            ********************************************************************************** 
            这个State变量是有其实际意义的，如果按键按下了，这里就将其设置为1，如果没有按下这个 
            变量的值就会一直是0，这样设置的目的可以有效的防止一种情况的出现：比如按键K1在某个 
            时刻检测到了按键有按下，那么它就会做进一步的滤波处理，但是在滤波的过程中，这个按键 
            按下的状态消失了，这个时候就会进入到上面第二步else语句里面，然后再做按键松手检测滤波 
            ，滤波结束后判断这个State变量，如果前面就没有检测到按下，这里就不会记录按键弹起。 
            ********************************************************************************** 
            */
            if(pBtn->State == 0)
            {
                pBtn->State = 1;
                /* 发送按钮按下的消息 */ 
                BspPutKey((uint8_t)(3 * i + 1));
            }
            
            if(pBtn->LongTime > 0)
            {
                if(pBtn->LongCount < pBtn->LongTime)
                {
                    /* 发送按钮按下的消息 */ 
                    if(++pBtn->LongCount == pBtn->LongTime)
                    {
                        /* 键值放入按键FIFO */ 
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
                            
                            /* 长按键后，每隔10ms发送1个按键 */ 
                            BspPutKey((uint8_t)(3 * i + 1));
                        }
                    }
                }               
            }
        }       
    }
    else
    {
        /*这个里面执行的是按键松手的处理或者按键没有按下的处理 */
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
