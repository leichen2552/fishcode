#include "bsp.h"
#include "GetSensorData.h"/*获取MPU9250四元数*/


int main(void)
{
    uint8_t com1Read;
    
    const uint16_t pectoralFinPWM = 45;
    static int16_t count_pectoralFinPWM = 0;
    
    const uint16_t forward = 45;
    static uint16_t count_forword = 0;
    
    const uint16_t backward = 45;
    static int16_t count_backward = 0;
    
//    static uint8_t turnAround = 0;//转弯变量
    
    static int frontdis = 0;
    
    BspInit();
    
    bsp_StartAutoTimer(0, 200); /*软件定时器0每隔100ms读取深度传感器的数据*/
    bsp_StartAutoTimer(1, 10); /*软件定时器0每隔100ms读取深度传感器的数据*/
    MeasureStartSignal();       /*发送测深仪的起始控制信号，让它每隔1s中返回一次数据*/
    
//<<手册脉宽值800~2200>>            :800 900 1000 1100 1200 1300 1400 1500 1600 1700 1800 1900 2000 2100 2200
//<<50 HZ情况下修改的TIMSETCOMPARE>>:720 810 900  990  1080 1170 1260 1350 1440 1530 1620 1710 1800 1890 1980
   
    while(1)
    {
        if(comGetChar(COM1,&com1Read))
        {
            //DPRINT("%c\r\n",com1Read);
            switch(com1Read)
            {
                /*调整胸鳍角度向前转*/
                case 'a':   bsp_StopAllSoftTimerExcpet0();
                            pectoralfinSteer[0].SetDutyCycle(1350);
                            pectoralfinSteer[3].SetDutyCycle(1350);
                            count_pectoralFinPWM--;
                            
                            if(count_pectoralFinPWM < -8)
                            {
                                count_pectoralFinPWM = -8;
                            }
                            
                            /*pectoralfinSteer[1] 上浮45度1620*/
                            /*pectoralfinSteer[2] 上浮45度968*/
                            
                            pectoralfinSteer[1].SetDutyCycle(1305-pectoralFinPWM*count_pectoralFinPWM);
                            pectoralfinSteer[2].SetDutyCycle(1305-22+pectoralFinPWM*count_pectoralFinPWM);                       
                            //printf("%d,%d\r\n",1305-pectoralFinPWM*count_pectoralFinPWM,1305-22+pectoralFinPWM*count_pectoralFinPWM);
                    break;
                            
                /*调整胸鳍角度向后转*/
                case 'b':   bsp_StopAllSoftTimerExcpet0();
                            pectoralfinSteer[0].SetDutyCycle(1350);
                            pectoralfinSteer[3].SetDutyCycle(1350);
                            count_pectoralFinPWM++;
                            if(count_pectoralFinPWM >= 13)
                            {
                                count_pectoralFinPWM = 13;
                            }
                            /*pectoralfinSteer[1] 下沉45度990*/
                            /*pectoralfinSteer[2] 下沉45度1642*/
                            pectoralfinSteer[1].SetDutyCycle(1305-pectoralFinPWM*count_pectoralFinPWM);
                            pectoralfinSteer[2].SetDutyCycle(1305+22+pectoralFinPWM*count_pectoralFinPWM);
                            //printf("%d,%d\r\n",1305-pectoralFinPWM*count_pectoralFinPWM,1305+22+pectoralFinPWM*count_pectoralFinPWM);
                    break;
                            
                /*停止软件定时器除了 第0个软件定时器*/
                case 'c':   bsp_StopAllSoftTimerExcpet0();
                    break;
                            
                case 'd':   bsp_StopAllSoftTimerExcpet0();//bsp_StopTimer(1);
                    break;
                            
                /*停止软件定时器除了 第0个软件定时器，开启上浮*/            
                case 'e':   bsp_StopAllSoftTimerExcpet0();StartPectoralFinUp();
                            count_pectoralFinPWM = 0;
                    break;
                /*停止软件定时器除了 第0个软件定时器，开启下沉*/ 
                case 'f':   bsp_StopAllSoftTimerExcpet0();StartPectoralFinDown();
                            count_pectoralFinPWM = 0;
                    break;
                
                /*向前推进*/ 
                case 'g':   //bsp_StopAllSoftTimerExcpet0();
                            //pectoralfinSteer[0].SetDutyCycle(1350);//后退810是胸鳍紧贴鱼身体
//                            pectoralfinSteer[3].SetDutyCycle(1350);
                            count_forword++; 
                            if(count_forword >5)
                            {
                                count_forword = 5;
                            }
                            
                            count_backward = 0;
                            SetMotorPWM(1350 + forward*count_forword);
                    break;
                /*向后减速*/ 
                case 'h':   //bsp_StopAllSoftTimerExcpet0();
                            //pectoralfinSteer[0].SetDutyCycle(765);//前进810是胸鳍紧贴鱼身体
//                            pectoralfinSteer[3].SetDutyCycle(765);
                            count_backward++;
                            if(count_backward >5)
                            {
                                count_backward = 5;
                            }
                            
                            count_forword =0;
                            SetMotorPWM(1350 - backward*count_backward);
                    break;
                            
                /*停止*/ 
                case 'i':   count_forword =0;
                            count_backward = 0;
                            StopMotor();
                    break;
                            
                /*向左转弯*/ 
                case 'j':   
                            StartPectoralFinRight();
                            count_pectoralFinPWM = 0;
                            //AllEyeFullON();
                    break;
                            
                /*向右转弯*/ 
                case 'k':   
                            StartPectoralFinLeft();
                            count_pectoralFinPWM = 0;
                            
                    break;
                default: break;
            }
        }        
        
//        if(bsp_CheckTimer(1))
//        {
////             GetSensorData();//跟pitch有关系
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
