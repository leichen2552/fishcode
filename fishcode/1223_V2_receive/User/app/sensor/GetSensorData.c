#include "GetSensorData.h"
#include "inv_mpu.h"
#include "mpu9250.h"
#include "niming.h"
#include "bsp.h"

float pitch,roll,yaw; 	//ŷ����
short aacx,aacy,aacz;	//���ٶȴ�����ԭʼ����
short gyrox,gyroy,gyroz;//������ԭʼ���� 
short temp;		        //�¶�
uint8_t report = 0;


/*��ȡMPU9250��Ԫ��*/
void GetSensorData(void)
{
    static uint32_t pf1pwm=0,pf2pwm=0;
    
    if(mpu_mpl_get_data(&pitch,&roll,&yaw) == 0)
    {
//        temp=MPU_Get_Temperature();	//�õ��¶�ֵ
//        printf("temp = %d.%d��C, ",temp/100,temp%100);
//        MPU_Get_Accelerometer(&aacx,&aacy,&aacz);	//�õ����ٶȴ�����ԭʼ����
//        MPU_Get_Gyroscope(&gyrox,&gyroy,&gyroz);	//�õ�������ԭʼ����
        
//        printf("pitch = %.2f,roll = %.2f, yaw = %.2f\r\n",pitch,roll,yaw);
        
//        printf("%.2f,%.2f,%.2f\r\n",pitch,roll,yaw);
        
        pf1pwm = (uint32_t)(1620 - (int32_t)((pitch-5.78)*7.4));
        pf2pwm = (uint32_t)(968 + (int32_t)((pitch-5.78)*7.4));
        
        pf1pwm = range(pf1pwm, 540, 2160);
        pf2pwm = range(pf2pwm, 540, 2160);
        //printf("%f,%d ",pitch,pwm);
        
//        printf("%.2f,%d\r\n",((pitch-5.78)*36),pf1pwm);
//        printf("%.2f,%d\r\n",((pitch-5.78)*22),pf2pwm);
        
        
        //pectoralfinSteer[0].SetDutyCycle(1350);
        pectoralfinSteer[3].SetDutyCycle(1350);
        pectoralfinSteer[1].SetDutyCycle(pf1pwm);
        pectoralfinSteer[2].SetDutyCycle(pf2pwm);
        
//        if(report) mpu9250_send_data(aacx,aacy,aacz,gyrox,gyroy,gyroz);//���ͼ��ٶ�+������ԭʼ����
//        if(report) usart1_report_imu((int)(roll*100),(int)(pitch*100),(int)(yaw*100),0,0);
    }
}



//static SENSOR_DATA_INFO sensor_data_info;			//��ȡ����������

//void GetSensorData()
//{
//    //��ȡ����������
//    mpu_mpl_get_data(   &sensor_data_info.attitude_sensor_angle.pitch,
//                        &sensor_data_info.attitude_sensor_angle.roll,
//                        &sensor_data_info.attitude_sensor_angle.yaw,
//                        acc_int,
//                        gyro_int);
//    //���ٶ�������������ת��ΪgΪ��λ�Ͷ�/sΪ��λ
//    Angle_Analysis( acc_int,
//                    gyro_int,
//                    &sensor_data_info.attitude_sensor_angle.acc,
//                    &sensor_data_info.attitude_sensor_angle.gyro);
//    //��ȡ��ȴ���������
//    //depthUpdate(&sensor_data_info.depth);
//    
//    printf(  "%.1f,%.1f,%.1f,",sensor_data_info.attitude_sensor_angle.pitch,
//             sensor_data_info.attitude_sensor_angle.roll,
//             sensor_data_info.attitude_sensor_angle.yaw,
//             acc_int,
//             gyro_int,);
//    
//}
