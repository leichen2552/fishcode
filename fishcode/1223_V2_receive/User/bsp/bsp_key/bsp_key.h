#ifndef __KEY_H
#define	__KEY_H

#include "stm32f4xx.h"

#define KEY_COUNT       6   /*三个独立，三个组合*/

typedef enum
{
    KID_K1 = 0,
    KID_K2,
    KID_K3
}KEY_ID_E;

/*
	按键滤波时间50ms, 单位10ms。
	只有连续检测到50ms状态不变才认为有效，包括弹起和按下两种事件
	即使按键电路不做硬件滤波，该滤波机制也可以保证可靠地检测到按键事件
*/
#define KEY_FILTER_TIME     5
#define KEY_LONG_TIME       100 /* 单位10ms， 持续1秒，认为长按事件 */

typedef struct
{
    /*下面是一个函数指针*/
    uint8_t (*IsKeyDownFunc)(void);/*按键按下的判断函数，1表示按下*/
    
    uint8_t  Count;         /* 滤波计数器 */
    uint16_t LongCount;     /* 长按计数器 */
    uint16_t LongTime;      /* 按键按下的持续时间，0表示不检测长按 */
    uint8_t  State;         /* 按键当前状态（按下还是弹起） */
    uint8_t  RepeatSpeed;   /* 连续按键周期 */
    uint8_t  RepeatCount;   /* 连续按键计时器 */
}KEY_Typedef;

/*
	定义键值代码, 必须按如下次序定时每个键的按下、弹起和长按事件

	推荐使用enum, 不用#define，原因：
	(1) 便于新增键值,方便调整顺序，使代码看起来舒服点
	(2) 编译器可帮我们避免键值重复。
*/
typedef enum
{
    KEY_NONE = 0,
    
	KEY_1_DOWN,				/* 1键按下 1*/
	KEY_1_UP,				/* 1键弹起 2*/
	KEY_1_LONG,				/* 1键长按 3*/

	KEY_2_DOWN,				/* 2键按下 4*/
	KEY_2_UP,				/* 2键弹起 5*/
	KEY_2_LONG,				/* 2键长按 6*/ 

    KEY_3_DOWN,				/* 3键按下 7*/
	KEY_3_UP,				/* 3键弹起 8*/
	KEY_3_LONG,				/* 3键长按 9*/ 
    
    /*组合键*/
    KEY_4_DOWN,				/* 组合1、2键按下 10*/
	KEY_4_UP,				/* 组合1、2键弹起 11*/
	KEY_4_LONG,				/* 组合1、2键长按 12*/  

    KEY_5_DOWN,				/* 组合1、3键按下 13*/
	KEY_5_UP,				/* 组合1、3键弹起 14*/
	KEY_5_LONG,				/* 组合1、3键长按 15*/

    KEY_6_DOWN,				/* 组合2、3键按下 16*/
	KEY_6_UP,				/* 组合2、3键弹起 17*/
	KEY_6_LONG,				/* 组合2、3键长按 18*/ 
}KEY_ENUM;

/* 按键FIFO用到变量 */
#define KEY_FIFO_SIZE   10
typedef struct
{
    uint8_t Buf[KEY_FIFO_SIZE];     /* 键值缓冲区 */
    uint8_t Read;                   /* 缓冲区读指针1 */
    uint8_t Write;                  /* 缓冲区写指针 */
    uint8_t Read2;                  /* 缓冲区读指针2 */
}KEY_FIFO_Typedef;


void BspInitKEY(void);
void BspKeyScan(void);
uint8_t BspGetKey(void);
uint8_t BspGetKey2(void);
uint8_t BspGetKeyState(KEY_ID_E _ucKeyID);
void BspSetKeyParam(uint8_t _ucKeyID, uint16_t _LongTime, uint8_t _RepeatSpeed);
void BspClearKey(void);
void BspPutKey(uint8_t _KeyCode);


#endif /* __LED_H */

