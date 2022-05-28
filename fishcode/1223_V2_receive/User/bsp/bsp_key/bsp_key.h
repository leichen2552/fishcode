#ifndef __KEY_H
#define	__KEY_H

#include "stm32f4xx.h"

#define KEY_COUNT       6   /*�����������������*/

typedef enum
{
    KID_K1 = 0,
    KID_K2,
    KID_K3
}KEY_ID_E;

/*
	�����˲�ʱ��50ms, ��λ10ms��
	ֻ��������⵽50ms״̬�������Ϊ��Ч����������Ͱ��������¼�
	��ʹ������·����Ӳ���˲������˲�����Ҳ���Ա�֤�ɿ��ؼ�⵽�����¼�
*/
#define KEY_FILTER_TIME     5
#define KEY_LONG_TIME       100 /* ��λ10ms�� ����1�룬��Ϊ�����¼� */

typedef struct
{
    /*������һ������ָ��*/
    uint8_t (*IsKeyDownFunc)(void);/*�������µ��жϺ�����1��ʾ����*/
    
    uint8_t  Count;         /* �˲������� */
    uint16_t LongCount;     /* ���������� */
    uint16_t LongTime;      /* �������µĳ���ʱ�䣬0��ʾ����ⳤ�� */
    uint8_t  State;         /* ������ǰ״̬�����»��ǵ��� */
    uint8_t  RepeatSpeed;   /* ������������ */
    uint8_t  RepeatCount;   /* ����������ʱ�� */
}KEY_Typedef;

/*
	�����ֵ����, ���밴���´���ʱÿ�����İ��¡�����ͳ����¼�

	�Ƽ�ʹ��enum, ����#define��ԭ��
	(1) ����������ֵ,�������˳��ʹ���뿴���������
	(2) �������ɰ����Ǳ����ֵ�ظ���
*/
typedef enum
{
    KEY_NONE = 0,
    
	KEY_1_DOWN,				/* 1������ 1*/
	KEY_1_UP,				/* 1������ 2*/
	KEY_1_LONG,				/* 1������ 3*/

	KEY_2_DOWN,				/* 2������ 4*/
	KEY_2_UP,				/* 2������ 5*/
	KEY_2_LONG,				/* 2������ 6*/ 

    KEY_3_DOWN,				/* 3������ 7*/
	KEY_3_UP,				/* 3������ 8*/
	KEY_3_LONG,				/* 3������ 9*/ 
    
    /*��ϼ�*/
    KEY_4_DOWN,				/* ���1��2������ 10*/
	KEY_4_UP,				/* ���1��2������ 11*/
	KEY_4_LONG,				/* ���1��2������ 12*/  

    KEY_5_DOWN,				/* ���1��3������ 13*/
	KEY_5_UP,				/* ���1��3������ 14*/
	KEY_5_LONG,				/* ���1��3������ 15*/

    KEY_6_DOWN,				/* ���2��3������ 16*/
	KEY_6_UP,				/* ���2��3������ 17*/
	KEY_6_LONG,				/* ���2��3������ 18*/ 
}KEY_ENUM;

/* ����FIFO�õ����� */
#define KEY_FIFO_SIZE   10
typedef struct
{
    uint8_t Buf[KEY_FIFO_SIZE];     /* ��ֵ������ */
    uint8_t Read;                   /* ��������ָ��1 */
    uint8_t Write;                  /* ������дָ�� */
    uint8_t Read2;                  /* ��������ָ��2 */
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

