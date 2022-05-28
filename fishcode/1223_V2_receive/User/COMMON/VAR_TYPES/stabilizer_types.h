#ifndef __STABILIZER_TYPES_H
#define __STABILIZER_TYPES_H

#include "stm32f4xx.h"
#include <stdbool.h>
#include "sensors_types.h"

//C语言不支持匿名结构体,需要使用编译指令指名
#if defined(__CC_ARM)
	#pragma anon_unions	
#endif

//系统采样速率定义
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

//PID计算速率
#define MAIN_LOOP_RATE 			RATE_500_HZ				//主循环速率
#define MAIN_LOOP_DT			(1.0/MAIN_LOOP_RATE)	

#define ATTITUDE_ESTIMAT_RATE	RATE_500_HZ				//姿态解算速率
#define ATTITUDE_ESTIMAT_DT		(1.0/ATTITUDE_ESTIMAT_RATE)

#define POSITION_ESTIMAT_RATE	ATTITUDE_ESTIMAT_RATE	//位置预估速率（和姿态解算速率一致）
#define POSITION_ESTIMAT_DT		(1.0/POSITION_ESTIMAT_RATE)

#define RATE_PID_RATE			MAIN_LOOP_RATE 			//角速度环PID速率（和主循环速率一致）
#define RATE_PID_DT				(1.0/RATE_PID_RATE)

#define ANGLE_PID_RATE			ATTITUDE_ESTIMAT_RATE 	//角度环PID速率（和姿态解算速率一致）
#define ANGLE_PID_DT			(1.0/ANGLE_PID_RATE)

#define VELOCITY_PID_RATE		POSITION_ESTIMAT_RATE 	//位置速度环PID速率（和位置预估速率一致）
#define VELOCITY_PID_DT			(1.0/VELOCITY_PID_RATE)

#define POSITION_PID_RATE		POSITION_ESTIMAT_RATE 	//位置环PID速率（和位置预估速率一致）
#define POSITION_PID_DT			(1.0/POSITION_PID_RATE)




//执行速率：tick % (1000 / rate_hz) == 0
//设置速率：500 知 (1000 / 500) = 2 知 tick % 2 == 500
//宏定义设置循环速率
#define RATE_DO_EXECUTE(RATE_HZ, TICK) ((TICK % (RATE_1000_HZ / RATE_HZ)) == 0)

typedef struct 
{
	u16 m1; //值范围：0-1000
	u16 m2;
	u16 m3;
	u16 m4;
}motorPWM_t;

//姿态数据结构
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

//点数据类型
typedef struct vec3_s point_t;
//速度数据类型
typedef struct vec3_s velocity_t;
//加速度数据类型
typedef struct vec3_s acc_t;

//Z轴距离传感器数据结构
typedef struct zDistance_s 
{
	float distance;
}zDistance_t;

//水压数据结构
typedef struct
{
	float pressure;
	float temperature;
	float asl;
}depth_t;

//传感器数据集合
typedef struct
{
	Axis3f acc;				//加速度（G）
	Axis3f gyro;			//陀螺仪（deg/s）
	Axis3f mag;				//磁力计（gauss）
	depth_t depth;			//深度传感器(cm)	
}sensorData_t;

//四轴姿态数据结构
typedef struct
{
	attitude_t 	attitude;	//姿态角度（deg）
	point_t 	position;	//估算的位置（cm）
	velocity_t 	velocity;	//估算的速度（cm/s）
	acc_t acc;				//估算的加速度（cm/ss）
}state_t;

//目标姿态数据结构
typedef struct
{
	attitude_t attitude;		//目标姿态角度（deg）
	attitude_t attitudeRate;	//目标角速度（deg/s）
	point_t position;         	//目标位置（cm）
	velocity_t velocity;      	//目标速度（cm/s）			
	float thrust;				//推进器基础油门			
}setpoint_t;

//控制数据结构
typedef struct
{
	float roll;
	float pitch;
	float yaw;
	float depth;
	float thrust;
}control_t;

#endif

