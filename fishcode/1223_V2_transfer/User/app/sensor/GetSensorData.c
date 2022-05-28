#include "GetSensorData.h"
#include "inv_mpu.h"
#include "mpu9250.h"
#include "niming.h"
#include "bsp.h"

float pitch,roll,yaw; 	//欧拉角
short aacx,aacy,aacz;	//加速度传感器原始数据
short gyrox,gyroy,gyroz;//陀螺仪原始数据 
short temp;		        //温度
uint8_t report = 0;


/*读取MPU9250四元数*/
void GetSensorData(void)
{
    if(mpu_mpl_get_data(&pitch,&roll,&yaw) == 0)
    {
        temp=MPU_Get_Temperature();	//得到温度值
        printf("temp = %d.%d°C, ",temp/100,temp%100);
        MPU_Get_Accelerometer(&aacx,&aacy,&aacz);	//得到加速度传感器原始数据
        MPU_Get_Gyroscope(&gyrox,&gyroy,&gyroz);	//得到陀螺仪原始数据
        
        printf("pitch = %.2f,roll = %.2f, yaw = %.2f\r\n",pitch,roll,yaw);
        
        if(report) mpu9250_send_data(aacx,aacy,aacz,gyrox,gyroy,gyroz);//发送加速度+陀螺仪原始数据
        if(report) usart1_report_imu((int)(roll*100),(int)(pitch*100),(int)(yaw*100),0,0);
    }
}



//static SENSOR_DATA_INFO sensor_data_info;			//获取传感器数据

//void GetSensorData()
//{
//    //获取传感器数据
//    mpu_mpl_get_data(   &sensor_data_info.attitude_sensor_angle.pitch,
//                        &sensor_data_info.attitude_sensor_angle.roll,
//                        &sensor_data_info.attitude_sensor_angle.yaw,
//                        acc_int,
//                        gyro_int);
//    //加速度与陀螺仪数据转换为g为单位和度/s为单位
//    Angle_Analysis( acc_int,
//                    gyro_int,
//                    &sensor_data_info.attitude_sensor_angle.acc,
//                    &sensor_data_info.attitude_sensor_angle.gyro);
//    //获取深度传感器数据
//    //depthUpdate(&sensor_data_info.depth);
//    
//    printf(  "%.1f,%.1f,%.1f,",sensor_data_info.attitude_sensor_angle.pitch,
//             sensor_data_info.attitude_sensor_angle.roll,
//             sensor_data_info.attitude_sensor_angle.yaw,
//             acc_int,
//             gyro_int,);
//    
//}
