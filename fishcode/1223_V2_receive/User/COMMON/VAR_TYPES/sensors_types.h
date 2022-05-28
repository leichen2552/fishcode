#ifndef __SENSORS_TYPES_H
#define __SENSORS_TYPES_H

#include "stm32f4xx.h"

#if defined(__CC_ARM) 
	#pragma anon_unions
#endif

/***********传感器数据类型************/
//MPU:  X Y Z
//DEPTH:X Y Z
//浮点型与整形数据
//int16_t共用体类型定义:内存模型相同
typedef union
{
	struct
	{
		int16_t x;
		int16_t y;
		int16_t z;
	};
	int16_t axis[3];
}Axis3i16;

//int32_t共用体类型定义:内存模型相同
typedef union 
{
	struct 
	{
		int32_t x;
		int32_t y;
		int32_t z;
	};
	int32_t axis[3];
}Axis3i32;

//int64_t共用体类型定义:内存模型相同
typedef union 
{
	struct 
	{
		int64_t x;
		int64_t y;
		int64_t z;
	};
	int64_t axis[3];
} Axis3i64;

//float共用体类型定义:内存模型相同
typedef union 
{
	struct 
	{
		float x;
		float y;
		float z;
	};
	float axis[3];
} Axis3f;

#endif
