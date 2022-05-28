#ifndef NIMING_H
#define NIMING_H

#include "stm32f4xx.h"

void usart1_niming_report(u8 fun,u8*data,u8 len);
void mpu9250_send_data(short aacx,short aacy,short aacz,short gyrox,short gyroy,short gyroz);
void usart1_report_imu(short roll,short pitch,short yaw,short csb,int prs);


#endif 
