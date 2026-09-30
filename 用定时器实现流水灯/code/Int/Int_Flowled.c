#include "Int_Flowled.h"


static u16 s_timer0_count = 500;




/**
 * @brief 实现流水灯 
 *  
 **/
void Int_Flowled(void)
{
    static u8 temp;

    s_timer0_count --;    

    if (s_timer0_count == 0)
    {
        temp = ~LED; //从 1111 1110 到 0000 0001
        temp <<= 1;  //从 0000 0001 到 0000 0010
        LED = ~temp;  //从 0000 0010 到 1111 1101

        //如果P1等于 1111 1111也就是 0x7f 时把 P1 重新置为 0xfe
        if (LED == 0xff)
        {
            LED = 0xfe;
        }  

        //把计数器重新置为0
        s_timer0_count = 500;
    }
}