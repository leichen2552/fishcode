#include "MeasureAroundDeepth.h"


//��������ͨ��485תTTL���뵥Ƭ���Ĵ���2����Ҫ�����շ�ģʽ
void MeasureStartSignal(void)//AA A2 00 00 00 08
{
    //���ò��������100ms
    uint8_t SetMeasureDeepthPeriod100ms[] ={0xAA,0xA4,0x00,0x03,0xE8,(0xAA^0x04^0x00^0x03^0xE8)};
    //��ʱ��࣬Ĭ��������1s
    uint8_t MeasureDeepthOrder[] ={0xAA,0xA2,0x00,0x00,0x00,0x08};
    
    for(int i=0; i<sizeof(SetMeasureDeepthPeriod100ms)/sizeof(SetMeasureDeepthPeriod100ms[0]); i++)
    {
        comSendChar(COM4, SetMeasureDeepthPeriod100ms[i]);
    }
    
    bsp_DelayMS(200);
    
    for(int i=0; i<sizeof(MeasureDeepthOrder)/sizeof(MeasureDeepthOrder[0]); i++)
    {
        comSendChar(COM4, MeasureDeepthOrder[i]);
    }  
}

/*
�����Ƿ��صĲ������ݹ� 17 ���ֽڣ�ÿ���ֽڵĺ������£� 
�ֽ� 1���̶�Ϊ AB
�ֽ� 2���̶�Ϊ A0
�ֽ� 3���̶�Ϊ 0D

�ֽ� 4�������ǵĻ��ţ� 
�ֽ� 5��6��  ��һ��Ŀ����루���Ŀ����룩����һ��Ŀ����룽�ֽ� 5��256 + �ֽ� 6����λΪ 1mm��SF0010 �� SF0011������λΪ 10mm�������ͺţ�
�ֽ� 7��8��  ��һ��Ŀ��ǿ�ȣ��ز���ƽ�����ز���ƽ���ֽ� 7��256 + �ֽ� 8��
                                                ��ֵԽ���ʾ�ز��ź�Խǿ

�ֽ� 9��10�� ��ǿĿ����룬��ǿĿ����룽�ֽ� 9��256 + �ֽ� 10����λΪ 1mm��SF0010 �� SF0011������λΪ 10mm�������ͺţ�
�ֽ� 11��12����ǿĿ��ǿ�ȣ��ز���ƽ�����ز���ƽ���ֽ� 11��256 + �ֽ� 12��
                                                ��ֵԽ���ʾ�ز��ź�Խǿ

�ֽ� 13��14�����һ��Ŀ����루��ԶĿ����룩�����һ��Ŀ����룽�ֽ� 13��256 + �ֽ� 14����λΪ 1mm��SF0010 �� SF0011������λΪ 10mm�������ͺţ�
�ֽ� 15��16�����һ��Ŀ��ǿ�ȣ��ز���ƽ�����ز���ƽ���ֽ� 15��256 + �ֽ� 16��
                                                ��ֵԽ���ʾ�ز��ź�Խǿ

�ֽ� 17������ָ��ǰ 16 ���ֽڵ����У������
*/

static int GetUartData(void)   
{
    uint8_t readAroundTemp;
    int temp;
    
    comGetChar(COM4, &readAroundTemp);
    temp = (int)readAroundTemp;
    
    return temp;
}

int firstTargetDistance,firstTargetIntensity;//��һ������
int strongestTargetDistance,strongestTargetIntensity;//��ǿ����
int lastTargetDistance,lastTargetIntensity;//���һ�ξ���

//��ȡ������ԭʼ����
bool GetMeasureAroundDeepthOriginalData(void)
{
    int dataArray[17] = {0};
    int tempData = 0;

    
//    static int firstTargetDistance,firstTargetIntensity;//��һ������
//    static int strongestTargetDistance,strongestTargetIntensity;//��ǿ����
//    static int lastTargetDistance,lastTargetIntensity;//���һ�ξ���

    
    /*�ȶ�ǰ�������ݣ��浽��������*/
    for(int i=0; i<3; i++)
    {
        tempData = GetUartData();
        dataArray[i] = tempData;
    }
    
    /*�ж�ǰ���������ǲ���Э�����AB A0 0D*/
    if(dataArray[0] == 0xab && dataArray[1] == 0xa0 && dataArray[2] == 0x0d)
    {
        /*����ǣ��Ͱ�ʣ���14�����ݶ��������ӵ��ĸ�����Ҳ����dataArray[3]��ʼ*/
        for(int i=3; i<17;i++)
        {
            dataArray[i] = GetUartData();
        }
        
        firstTargetDistance = (dataArray[4] *256) + dataArray[5];
        firstTargetIntensity = (dataArray[6] *256) + dataArray[7];
        
        strongestTargetDistance = (dataArray[8] *256) + dataArray[9];
        strongestTargetIntensity = (dataArray[10] *256) + dataArray[11];
        
        lastTargetDistance = (dataArray[12] *256) + dataArray[13];
        lastTargetIntensity = (dataArray[14] *256) + dataArray[15];        
        
    
//        printf("first = %d,%d,strongest = %d,%d\r\n",firstTargetDistance,firstTargetIntensity,
//                                                     strongestTargetDistance,strongestTargetIntensity);
        //printf("firstTargetDistance = %d,strongestTargetDistance = %d,lastTargetDistance = %d\r\n",firstTargetDistance,strongestTargetDistance,lastTargetDistance);
        
        return true;
    }
    else
    {
        return false;
    }

}

int GetFrontDistance(void)
{
    //int tempMax = 0;
    int TargetIntensityMax = 0;
    
    if(GetMeasureAroundDeepthOriginalData())
    {
        TargetIntensityMax = firstTargetIntensity >= strongestTargetIntensity ? 
                                firstTargetIntensity : strongestTargetIntensity;
        //TargetIntensityMax = tempMax > lastTargetIntensity ? tempMax : lastTargetIntensity;
        
        if(TargetIntensityMax == firstTargetIntensity)
        {
            return firstTargetDistance;
        }
        else if(TargetIntensityMax == strongestTargetIntensity)
        {
            return strongestTargetDistance;
        }
//        else if(TargetIntensityMax == lastTargetDistance)
//        {
//            return lastTargetDistance;
//        }   
    }
    else
    {
        return false;
    }    

    return false;
}


