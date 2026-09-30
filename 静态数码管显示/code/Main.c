#include "Int_Keyboard.h"

#define LED0 P10
#define LED1 P11
#define LED2 P12
#define LED3 P13

void main(void)
{   
    while (1)
    {
        if(Int_Keyboard_IsSW1pressd())
        {
            LED0 = !LED0;
        }
        if(Int_Keyboard_IsSW2pressd())
        {
            LED1 = !LED1;
        }
        if(Int_Keyboard_IsSW3pressd())
        {
            LED2 = !LED2;
        }
        if(Int_Keyboard_IsSW4pressd())
        {
            LED3 = !LED3;
        }
    }
}












