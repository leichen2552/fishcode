#include "bsp.h"
#include "GetSensorData.h"/*��ȡMPU9250��Ԫ��*/


int main(void)
{
    uint8_t com1Read;
    
    const uint16_t pectoralFinPWM = 45;
    static int16_t count_pectoralFinPWM = 0;
    
    const uint16_t forward = 45;
    static uint16_t count_forword = 0;
    
    const uint16_t backward = 45;
    static int16_t count_backward = 0;
    
//    static uint8_t turnAround = 0;//ת�����
    
    static int frontdis = 0;
    
    BspInit();
    
    bsp_StartAutoTimer(0, 200); /*�����ʱ��0ÿ��100ms��ȡ��ȴ�����������*/
    bsp_StartAutoTimer(1, 10); /*�����ʱ��0ÿ��100ms��ȡ��ȴ�����������*/
    MeasureStartSignal();       /*���Ͳ����ǵ���ʼ�����źţ�����ÿ��1s�з���һ������*/
    
//<<�ֲ�����ֵ800~2200>>            :800 900 1000 1100 1200 1300 1400 1500 1600 1700 1800 1900 2000 2100 2200
//<<50 HZ������޸ĵ�TIMSETCOMPARE>>:720 810 900  990  1080 1170 1260 1350 1440 1530 1620 1710 1800 1890 1980
   
    while(1)
    {
        if(comGetChar(COM1,&com1Read))
        {
            //DPRINT("%c\r\n",com1Read);
            switch(com1Read)
            {
                /*���������Ƕ���ǰת*/
                case 'a':   bsp_StopAllSoftTimerExcpet0();
                            pectoralfinSteer[0].SetDutyCycle(1350);
                            pectoralfinSteer[3].SetDutyCycle(1350);
                            count_pectoralFinPWM--;
                            
                            if(count_pectoralFinPWM < -8)
                            {
                                count_pectoralFinPWM = -8;
                            }
                            
                            /*pectoralfinSteer[1] �ϸ�45��1620*/
                            /*pectoralfinSteer[2] �ϸ�45��968*/
                            
                            pectoralfinSteer[1].SetDutyCycle(1305-pectoralFinPWM*count_pectoralFinPWM);
                            pectoralfinSteer[2].SetDutyCycle(1305-22+pectoralFinPWM*count_pectoralFinPWM);                       
                            //printf("%d,%d\r\n",1305-pectoralFinPWM*count_pectoralFinPWM,1305-22+pectoralFinPWM*count_pectoralFinPWM);
                    break;
                            
                /*���������Ƕ����ת*/
                case 'b':   bsp_StopAllSoftTimerExcpet0();
                            pectoralfinSteer[0].SetDutyCycle(1350);
                            pectoralfinSteer[3].SetDutyCycle(1350);
                            count_pectoralFinPWM++;
                            if(count_pectoralFinPWM >= 13)
                            {
                                count_pectoralFinPWM = 13;
                            }
                            /*pectoralfinSteer[1] �³�45��990*/
                            /*pectoralfinSteer[2] �³�45��1642*/
                            pectoralfinSteer[1].SetDutyCycle(1305-pectoralFinPWM*count_pectoralFinPWM);
                            pectoralfinSteer[2].SetDutyCycle(1305+22+pectoralFinPWM*count_pectoralFinPWM);
                            //printf("%d,%d\r\n",1305-pectoralFinPWM*count_pectoralFinPWM,1305+22+pectoralFinPWM*count_pectoralFinPWM);
                    break;
                            
                /*ֹͣ�����ʱ������ ��0�������ʱ��*/
                case 'c':   bsp_StopAllSoftTimerExcpet0();
                    break;
                            
                case 'd':   bsp_StopAllSoftTimerExcpet0();//bsp_StopTimer(1);
                    break;
                            
                /*ֹͣ�����ʱ������ ��0�������ʱ���������ϸ�*/            
                case 'e':   bsp_StopAllSoftTimerExcpet0();StartPectoralFinUp();
                            count_pectoralFinPWM = 0;
                    break;
                /*ֹͣ�����ʱ������ ��0�������ʱ���������³�*/ 
                case 'f':   bsp_StopAllSoftTimerExcpet0();StartPectoralFinDown();
                            count_pectoralFinPWM = 0;
                    break;
                
                /*��ǰ�ƽ�*/ 
                case 'g':   //bsp_StopAllSoftTimerExcpet0();
                            //pectoralfinSteer[0].SetDutyCycle(1350);//����810����������������
//                            pectoralfinSteer[3].SetDutyCycle(1350);
                            count_forword++; 
                            if(count_forword >5)
                            {
                                count_forword = 5;
                            }
                            
                            count_backward = 0;
                            SetMotorPWM(1350 + forward*count_forword);
                    break;
                /*������*/ 
                case 'h':   //bsp_StopAllSoftTimerExcpet0();
                            //pectoralfinSteer[0].SetDutyCycle(765);//ǰ��810����������������
//                            pectoralfinSteer[3].SetDutyCycle(765);
                            count_backward++;
                            if(count_backward >5)
                            {
                                count_backward = 5;
                            }
                            
                            count_forword =0;
                            SetMotorPWM(1350 - backward*count_backward);
                    break;
                            
                /*ֹͣ*/ 
                case 'i':   count_forword =0;
                            count_backward = 0;
                            StopMotor();
                    break;
                            
                /*����ת��*/ 
                case 'j':   
                            StartPectoralFinRight();
                            count_pectoralFinPWM = 0;
                            //AllEyeFullON();
                    break;
                            
                /*����ת��*/ 
                case 'k':   
                            StartPectoralFinLeft();
                            count_pectoralFinPWM = 0;
                            
                    break;
                default: break;
            }
        }        
        
//        if(bsp_CheckTimer(1))
//        {
////             GetSensorData();//��pitch�й�ϵ
//        }
//        
//        if(bsp_CheckTimer(0))
//        {
//            GetDeepthTemp();
//            frontdis = GetFrontDistance();
//            
//            if(frontdis)
//            {
//                //printf("frontdis = %d\r\n",frontdis);
//                if(frontdis <= 50)
//                {
//                    
//                }
//            }
//            
//            LED2_TOGGLE;           
//        }       

           
    }
}
