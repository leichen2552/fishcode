#ifndef GETSENSORDATA_H
#define GETSENSORDATA_H

#include "stabilizer_types.h"

//��̬�������ṹ��
typedef struct
{
	float roll;
	float pitch;
	float yaw;
	Axis3f acc;
	Axis3f gyro;
}ATTITUDE_SENSOR_DATA_INFO;

//�������ṹ��
typedef struct
{
	ATTITUDE_SENSOR_DATA_INFO attitude_sensor_angle;
	depth_t depth;
	float vecl;
}SENSOR_DATA_INFO;

void GetSensorData(void);


extern float pitch,roll,yaw; 	//ŷ����

#endif
