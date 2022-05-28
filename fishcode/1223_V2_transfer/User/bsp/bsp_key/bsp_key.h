#ifndef __KEY_H
#define	__KEY_H

#include "stm32f4xx.h"

#define KEY_COUNT       13   /*三个独立，三个组合*/

typedef enum
{
    KID_K1 = 0,
    KID_K2,
    KID_K3,
    KID_K4,
    KID_K5,
    KID_K6,
    KID_K7,
    KID_K8,
    KID_K9,
    KID_K10,
    KID_K11,
    KID_K12,
    KID_K13
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
    
    KEY_4_DOWN,				/* 4键按下 10*/
	KEY_4_UP,				/* 4键弹起 11*/
	KEY_4_LONG,				/* 4键长按 12*/ 
    
    KEY_5_DOWN,				/* 5键按下 13*/
	KEY_5_UP,				/* 5键弹起 14*/
	KEY_5_LONG,				/* 5键长按 15*/ 
    
    KEY_6_DOWN,				/* 6键按下 16*/
	KEY_6_UP,				/* 6键弹起 17*/
	KEY_6_LONG,				/* 6键长按 18*/ 
    
    KEY_7_DOWN,				/* 7键按下 19*/
	KEY_7_UP,				/* 7键弹起 20*/
	KEY_7_LONG,				/* 7键长按 21*/ 
    
    KEY_8_DOWN,				/* 8键按下 22*/
	KEY_8_UP,				/* 8键弹起 23*/
	KEY_8_LONG,				/* 8键长按 24*/ 
    
    KEY_9_DOWN,				/* 9键按下 25*/
	KEY_9_UP,				/* 9键弹起 26*/
	KEY_9_LONG,				/* 9键长按 27*/ 
    
    KEY_10_DOWN,			/* 10键按下 28*/
	KEY_10_UP,				/* 10键弹起 29*/
	KEY_10_LONG,			/* 10键长按 30*/ 
    
    KEY_11_DOWN,			/* 11键按下 31*/
	KEY_11_UP,				/* 11键弹起 32*/
	KEY_11_LONG, 			/* 11键长按 33*/      
    
    KEY_12_DOWN,			/* 12键按下 34*/
	KEY_12_UP,				/* 12键弹起 35*/
	KEY_12_LONG, 			/* 12键长按 36*/ 
    
    KEY_13_DOWN,			/* 13键按下 37*/
	KEY_13_UP,				/* 13键弹起 38*/
	KEY_13_LONG 			/* 13键长按 39*/ 
//    /*组合键*/
//    KEY_4_DOWN,				/* 组合1、2键按下 10*/
//	KEY_4_UP,				/* 组合1、2键弹起 11*/
//	KEY_4_LONG,				/* 组合1、2键长按 12*/  

//    KEY_5_DOWN,				/* 组合1、3键按下 13*/
//	KEY_5_UP,				/* 组合1、3键弹起 14*/
//	KEY_5_LONG,				/* 组合1、3键长按 15*/

//    KEY_6_DOWN,				/* 组合2、3键按下 16*/
//	KEY_6_UP,				/* 组合2、3键弹起 17*/
//	KEY_6_LONG,				/* 组合2、3键长按 18*/ 
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

