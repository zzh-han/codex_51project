#include "Int_Digital.h"
#include "Int_Keyboard.h"
#include "stdio.h"

void main() 
{
    Int_XianCun(123);
    while(1)
    {
        Int_Dig_Refresh();
    }
    /*u8 Key_count[4], str[9];

    while (1)
    {
        if(Int_Keyboard_IsSW1pressd())
            Key_count[0]++;
        if(Int_Keyboard_IsSW2pressd())
            Key_count[1]++;
        if(Int_Keyboard_IsSW3pressd())
            Key_count[2]++;
        if(Int_Keyboard_IsSW4pressd())
            Key_count[3]++;    

        sprintf(str, "%02d%02d%02d%02d", 
        (int)Key_count[0], (int)Key_count[1], 
        (int)Key_count[2], (int)Key_count[3]);
    
        Int_XianCun8(str);
        Int_Dig_Refresh();           
    }*/
}