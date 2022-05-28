#ifndef __STABILIZER_TYPES_H
#define __STABILIZER_TYPES_H

#include "stm32f4xx.h"
#include <stdbool.h>
#include "sensors_types.h"

//C���Բ�֧�������ṹ��,��Ҫʹ�ñ���ָ��ָ��
#if defined(__CC_ARM)
	#pragma anon_unions	
#endif

//ϵͳ�������ʶ���
#define RATE_2_HZ		2
#define RATE_5_HZ		5
#define RATE_10_HZ		10
#define RATE_20_HZ		20
#define RATE_25_HZ		25
#define RATE_50_HZ		50
#define RATE_100_HZ		100
#define RATE_200_HZ 	200
#define RATE_250_HZ 	250
#define RATE_500_HZ 	500
#define RATE_1000_HZ 	1000

//PID��������
#define MAIN_LOOP_RATE 			RATE_500_HZ				//��ѭ������
#define MAIN_LOOP_DT			(1.0/MAIN_LOOP_RATE)	

#define ATTITUDE_ESTIMAT_RATE	RATE_500_HZ				//��̬��������
#define ATTITUDE_ESTIMAT_DT		(1.0/ATTITUDE_ESTIMAT_RATE)

#define POSITION_ESTIMAT_RATE	ATTITUDE_ESTIMAT_RATE	//λ��Ԥ�����ʣ�����̬��������һ�£�
#define POSITION_ESTIMAT_DT		(1.0/POSITION_ESTIMAT_RATE)

#define RATE_PID_RATE			MAIN_LOOP_RATE 			//���ٶȻ�PID���ʣ�����ѭ������һ�£�
#define RATE_PID_DT				(1.0/RATE_PID_RATE)

#define ANGLE_PID_RATE			ATTITUDE_ESTIMAT_RATE 	//�ǶȻ�PID���ʣ�����̬��������һ�£�
#define ANGLE_PID_DT			(1.0/ANGLE_PID_RATE)

#define VELOCITY_PID_RATE		POSITION_ESTIMAT_RATE 	//λ���ٶȻ�PID���ʣ���λ��Ԥ������һ�£�
#define VELOCITY_PID_DT			(1.0/VELOCITY_PID_RATE)

#define POSITION_PID_RATE		POSITION_ESTIMAT_RATE 	//λ�û�PID���ʣ���λ��Ԥ������һ�£�
#define POSITION_PID_DT			(1.0/POSITION_PID_RATE)




//ִ�����ʣ�tick % (1000 / rate_hz) == 0
//�������ʣ�500 ֪ (1000 / 500) = 2 ֪ tick % 2 == 500
//�궨������ѭ������
#define RATE_DO_EXECUTE(RATE_HZ, TICK) ((TICK % (RATE_1000_HZ / RATE_HZ)) == 0)

typedef struct 
{
	u16 m1; //ֵ��Χ��0-1000
	u16 m2;
	u16 m3;
	u16 m4;
}motorPWM_t;

//��̬���ݽṹ
typedef struct  
{
	float roll;
	float pitch;
	float yaw;
}attitude_t;

struct  vec3_s 
{
	float x;
	float y;
	float z;
};

//����������
typedef struct vec3_s point_t;
//�ٶ���������
typedef struct vec3_s velocity_t;
//���ٶ���������
typedef struct vec3_s acc_t;

//Z����봫�������ݽṹ
typedef struct zDistance_s 
{
	float distance;
}zDistance_t;

//ˮѹ���ݽṹ
typedef struct
{
	float pressure;
	float temperature;
	float asl;
}depth_t;

//���������ݼ���
typedef struct
{
	Axis3f acc;				//���ٶȣ�G��
	Axis3f gyro;			//�����ǣ�deg/s��
	Axis3f mag;				//�����ƣ�gauss��
	depth_t depth;			//��ȴ�����(cm)	
}sensorData_t;

//������̬���ݽṹ
typedef struct
{
	attitude_t 	attitude;	//��̬�Ƕȣ�deg��
	point_t 	position;	//�����λ�ã�cm��
	velocity_t 	velocity;	//������ٶȣ�cm/s��
	acc_t acc;				//����ļ��ٶȣ�cm/ss��
}state_t;

//Ŀ����̬���ݽṹ
typedef struct
{
	attitude_t attitude;		//Ŀ����̬�Ƕȣ�deg��
	attitude_t attitudeRate;	//Ŀ����ٶȣ�deg/s��
	point_t position;         	//Ŀ��λ�ã�cm��
	velocity_t velocity;      	//Ŀ���ٶȣ�cm/s��			
	float thrust;				//�ƽ�����������			
}setpoint_t;

//�������ݽṹ
typedef struct
{
	float roll;
	float pitch;
	float yaw;
	float depth;
	float thrust;
}control_t;

#endif

