#include "bsp.h"


int main(void)
{
    uint8_t ucKeyCode;
    
    BspInit();

    
    while(1)
    {
        ucKeyCode = BspGetKey();
        
        if(ucKeyCode != KEY_NONE)
        {
            //printf("\r\nucKeyCode = %d\r\n",ucKeyCode);
            switch (ucKeyCode)
            {
                /*单独按键按下和长按*/
                case KEY_1_DOWN :
                        comSendChar(COM1, 'a');
                    break;               
                case KEY_2_DOWN :
                        comSendChar(COM1, 'b');
                    break;                
                case KEY_3_DOWN :
                        comSendChar(COM1, 'c');
                    break;
                case KEY_4_DOWN :
                        comSendChar(COM1, 'd');                    
                    break;
                case KEY_5_DOWN :
                        comSendChar(COM1, 'e'); 
                    break;
                case KEY_6_DOWN :
                        comSendChar(COM1, 'f');
                    break;
//                case KEY_7_DOWN :
//                        comSendChar(COM1, 'g');
//                    break;                               
//                case KEY_8_DOWN :
//                        comSendChar(COM1, 'h');
//                    break;
                case KEY_9_DOWN :
                        comSendChar(COM1, 'g');                    
                    break;
                case KEY_10_DOWN :
                        comSendChar(COM1, 'h'); 
                    break;
                case KEY_11_DOWN :
                        comSendChar(COM1, 'i');
                    break;    
                case KEY_12_DOWN :
                        comSendChar(COM1, 'j');
                    break;
                case KEY_13_DOWN :
                        comSendChar(COM1, 'k');
                    break;
                default:
                    break;
            }
        }                     
    }
}
