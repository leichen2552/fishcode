#include "deepth.h"

float Deepth;
float Temperature;
void GetDeepthTemp(void)
{
    /*T=32.11D=111.21\r\n ����崫�������ַ�����ʽ*/
    /*T=3.11D=11.21\r\n ����崫�������ַ�����ʽ*/
    /*T=32.11D=1.21\r\n ����崫�������ַ�����ʽ*/
    
    
    uint8_t deepth[20];
    uint8_t i=0;
    uint8_t i_T = 0, i_D = 0, i_dot = 0;
    uint8_t readDeepthTemp;

#if 1    
    while(comGetChar(COM2, &readDeepthTemp))
    {
        
        if(readDeepthTemp == '\r')
        {
            deepth[i++] = '\0';
            break;
        }
        else if(readDeepthTemp == 'T')
        {
            i_T = i;
        }        
        else if(readDeepthTemp == 'D')
        {
            i_D = i;
        }
        else if(readDeepthTemp == '.')//���Ը��ǵ������ַ�����ĵڶ�����
        {
            i_dot = i;
        }
        deepth[i++] = readDeepthTemp;
    }
    //printf("length = %d\r\n",strlen((const char*)deepth));
    
    if((deepth[i_T+1] == '=') && (deepth[i_T+3] == '.'))
    {
        Temperature = (deepth[i_T+2]-48) * 1 + (deepth[i_T+4]-48) * 0.1 + (deepth[i_T+5]-48) * 0.01;//��ȥ48����Ϊ�����ַ�ת��������
    }
    else if((deepth[i_T+1] == '=') && (deepth[i_T+4] == '.'))
    {
        Temperature = (deepth[i_T+2] -48) * 10 +(deepth[i_T+3] - 48) * 1 + (deepth[i_T+5]-48) * 0.1 + (deepth[i_T+6]-48) * 0.01;
    }
    
    if(((i_dot - i_D) == 4) && (deepth[i_D+1] == '=') && (deepth[i_D+2] == '-'))//ˮƽ����0-10��
    {
        Deepth = (-1) * ( (deepth[i_dot-1] -48) * 1 + (deepth[i_dot+1] -48) * 0.1 + (deepth[i_dot+2] -48) * 0.01);
    }
    else if(((i_dot - i_D) == 5) && (deepth[i_D+1] == '=') && (deepth[i_D+2] == '-'))//ˮƽ����10-99��
    {
        Deepth = (-1) * ( (deepth[i_dot-2] -48) + (deepth[i_dot-1] -48) * 1 + (deepth[i_dot+1] -48) * 0.1 + (deepth[i_dot+2] -48) * 0.01);
    }
    else if(((i_dot - i_D) == 3) && (deepth[i_D+1] == '=') && ((deepth[i_D+2] >= '0') && (deepth[i_D+2] <= '9')))//ˮƽ����1-9��
    {
        Deepth = (+1) * ( (deepth[i_dot-1] -48) * 1 + (deepth[i_dot+1] -48) * 0.1 + (deepth[i_dot+2] -48) * 0.01);
    }
    else if(((i_dot - i_D) == 4) && (deepth[i_D+1] == '=') && ((deepth[i_D+2] >= '0') && (deepth[i_D+2] <= '9')))//ˮƽ����10-99��
    {
        Deepth = (+1) * ( (deepth[i_dot-2] -48) * 10 + (deepth[i_dot-1] -48) * 1 + (deepth[i_dot+1] -48) * 0.1 + (deepth[i_dot+2] -48) * 0.01);
    }
    else if(((i_dot - i_D) == 5) && (deepth[i_D+1] == '=') && ((deepth[i_D+2] >= '0') && (deepth[i_D+2] <= '9')))//ˮƽ����100-299��
    {
        Deepth = (+1) * ( (deepth[i_dot-3] -48) * 100 + (deepth[i_dot-2] -48) * 10 + (deepth[i_dot-1] -48) * 1 + (deepth[i_dot+1] -48) * 0.1 + (deepth[i_dot+2] -48) * 0.01);
    }
    
    //printf("Temperature = %.2f,Deepth = %.2f\r\n",Temperature, Deepth);
    //printf("%.2f\r\n", Deepth);
#endif
}
