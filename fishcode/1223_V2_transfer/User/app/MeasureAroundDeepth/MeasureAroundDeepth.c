#include "MeasureAroundDeepth.h"


//测深仪是通过485转TTL接入单片机的串口2，需要设置收发模式
void MeasureStartSignal(void)//AA A2 00 00 00 08
{
    int i = 0;
    uint8_t MeasureDeepthPerSecOrder[] ={0xAA,0xA2,0x00,0x00,0x00,0x08};//定时测距
    
    for(i=0; i<sizeof(MeasureDeepthPerSecOrder)/sizeof(MeasureDeepthPerSecOrder[0]); i++)
    {
        comSendChar(COM4, MeasureDeepthPerSecOrder[i]);
    }  
}

/*
测深仪返回的测量数据共 17 个字节，每个字节的含意如下： 
字节 1：固定为 AB
字节 2：固定为 A0
字节 3：固定为 0D

字节 4：测深仪的机号； 
字节 5～6：  第一个目标距离（最近目标距离），第一个目标距离＝字节 5×256 + 字节 6，单位为 1mm（SF0010 或 SF0011），单位为 10mm（其他型号）
字节 7～8：  第一个目标强度（回波电平），回波电平＝字节 7×256 + 字节 8，
                                                数值越大表示回波信号越强

字节 9～10： 最强目标距离，最强目标距离＝字节 9×256 + 字节 10，单位为 1mm（SF0010 或 SF0011），单位为 10mm（其他型号）
字节 11～12：最强目标强度（回波电平），回波电平＝字节 11×256 + 字节 12，
                                                数值越大表示回波信号越强

字节 13～14：最后一个目标距离（最远目标距离），最后一个目标距离＝字节 13×256 + 字节 14，单位为 1mm（SF0010 或 SF0011），单位为 10mm（其他型号）
字节 15～16：最后一个目标强度（回波电平），回波电平＝字节 15×256 + 字节 16，
                                                数值越大表示回波信号越强

字节 17：本条指令前 16 个字节的异或校验结果。
*/

static int GetUartData(void)   
{
    uint8_t readAroundTemp;
    int temp;
    
    comGetChar(COM4, &readAroundTemp);
    temp = (int)readAroundTemp;
    
    return temp;
}

int firstTargetDistance,firstTargetIntensity;//第一个距离
int strongestTargetDistance,strongestTargetIntensity;//最强距离
int lastTargetDistance,lastTargetIntensity;//最后一次距离


bool MeasureAroundDeepth(void)
{
    int dataArray[17] = {0};
    int tempData;
    
//    int firstTargetDistance,firstTargetIntensity;//第一个距离
//    int strongestTargetDistance,strongestTargetIntensity;//最强距离
//    int lastTargetDistance,lastTargetIntensity;//最后一次距离
    
    //tempData = GetUartData();
    //printf("%x ", tempData);
    
    /*先读前三个数据，存到数组里面*/
    for(int i=0; i<3; i++)
    {
        tempData = GetUartData();
        dataArray[i] = tempData;
    }
    
    /*判断前三个数据是不是协议里的AB A0 0D*/
    if(dataArray[0] == 0xab && dataArray[1] == 0xa0 && dataArray[2] == 0x0d)
    {
        /*如果是，就把剩余的14个数据读出来，从第四个数据也就是dataArray[3]开始*/
        for(int i=3; i<17;i++)
        {
            dataArray[i] = GetUartData();
        }
        
//        for(int j=0; j<17; j++)
//        {
//            printf("%x ", dataArray[j]);
//        }
        firstTargetDistance = (dataArray[4] << 8) + dataArray[5];
        firstTargetIntensity = (dataArray[6] << 8) + dataArray[7];
        
        strongestTargetDistance = (dataArray[8] << 8) + dataArray[9];
        strongestTargetIntensity = (dataArray[10] << 8) + dataArray[11];
        
        lastTargetDistance = (dataArray[12] << 8) + dataArray[13];
        lastTargetIntensity = (dataArray[14] << 8) + dataArray[15];
        
        printf("first = %d,%d,strongest = %d,%d,last = %d,%d\r\n",firstTargetDistance,firstTargetIntensity,
                                                                  strongestTargetDistance,strongestTargetIntensity,
                                                                  lastTargetDistance,lastTargetIntensity);
        //printf("firstTargetDistance = %x,strongestTargetDistance = %x,lastTargetDistance = %x\r\n",firstTargetDistance,strongestTargetDistance,lastTargetDistance);
        
        return true;
    }
    else
    {
        return false;
    }

}

