#include "deepth.h"

float Deepth;
float Temperature;
void GetDeepthTemp(void)
{
    /*T=32.11D=111.21\r\n 解算板传过来的字符串格式*/
    /*T=3.11D=11.21\r\n 解算板传过来的字符串格式*/
    /*T=32.11D=1.21\r\n 解算板传过来的字符串格式*/
    
    
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
        else if(readDeepthTemp == '.')//绝对覆盖到的是字符串里的第二个点
        {
            i_dot = i;
        }
        deepth[i++] = readDeepthTemp;
    }
    //printf("length = %d\r\n",strlen((const char*)deepth));
    
    if((deepth[i_T+1] == '=') && (deepth[i_T+3] == '.'))
    {
        Temperature = (deepth[i_T+2]-48) * 1 + (deepth[i_T+4]-48) * 0.1 + (deepth[i_T+5]-48) * 0.01;//减去48是因为这是字符转化成数字
    }
    else if((deepth[i_T+1] == '=') && (deepth[i_T+4] == '.'))
    {
        Temperature = (deepth[i_T+2] -48) * 10 +(deepth[i_T+3] - 48) * 1 + (deepth[i_T+5]-48) * 0.1 + (deepth[i_T+6]-48) * 0.01;
    }
    
    if(((i_dot - i_D) == 4) && (deepth[i_D+1] == '=') && (deepth[i_D+2] == '-'))//水平面上0-10米
    {
        Deepth = (-1) * ( (deepth[i_dot-1] -48) * 1 + (deepth[i_dot+1] -48) * 0.1 + (deepth[i_dot+2] -48) * 0.01);
    }
    else if(((i_dot - i_D) == 5) && (deepth[i_D+1] == '=') && (deepth[i_D+2] == '-'))//水平面上10-99米
    {
        Deepth = (-1) * ( (deepth[i_dot-2] -48) + (deepth[i_dot-1] -48) * 1 + (deepth[i_dot+1] -48) * 0.1 + (deepth[i_dot+2] -48) * 0.01);
    }
    else if(((i_dot - i_D) == 3) && (deepth[i_D+1] == '=') && ((deepth[i_D+2] >= '0') && (deepth[i_D+2] <= '9')))//水平面下1-9米
    {
        Deepth = (+1) * ( (deepth[i_dot-1] -48) * 1 + (deepth[i_dot+1] -48) * 0.1 + (deepth[i_dot+2] -48) * 0.01);
    }
    else if(((i_dot - i_D) == 4) && (deepth[i_D+1] == '=') && ((deepth[i_D+2] >= '0') && (deepth[i_D+2] <= '9')))//水平面下10-99米
    {
        Deepth = (+1) * ( (deepth[i_dot-2] -48) * 10 + (deepth[i_dot-1] -48) * 1 + (deepth[i_dot+1] -48) * 0.1 + (deepth[i_dot+2] -48) * 0.01);
    }
    else if(((i_dot - i_D) == 5) && (deepth[i_D+1] == '=') && ((deepth[i_D+2] >= '0') && (deepth[i_D+2] <= '9')))//水平面下100-299米
    {
        Deepth = (+1) * ( (deepth[i_dot-3] -48) * 100 + (deepth[i_dot-2] -48) * 10 + (deepth[i_dot-1] -48) * 1 + (deepth[i_dot+1] -48) * 0.1 + (deepth[i_dot+2] -48) * 0.01);
    }
    
    //printf("Temperature = %.2f,Deepth = %.2f\r\n",Temperature, Deepth);
    //printf("%.2f\r\n", Deepth);
#endif
}
