#ifndef GETSENSORDATA_H
#define GETSENSORDATA_H

#include "stabilizer_types.h"

//姿态传感器结构体
typedef struct
{
	float roll;
	float pitch;
	float yaw;
	Axis3f acc;
	Axis3f gyro;
}ATTITUDE_SENSOR_DATA_INFO;

//传感器结构体
typedef struct
{
	ATTITUDE_SENSOR_DATA_INFO attitude_sensor_angle;
	depth_t depth;
	float vecl;
}SENSOR_DATA_INFO;

void GetSensorData(void);


extern float pitch,roll,yaw; 	//欧拉角

#endif
