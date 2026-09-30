#include "Dri_Timer0.h"

#define TOMS (FOSC/NT/1000) //定时器0溢出1ms所需的计数值

static  u16 s_Timer0_Count = 0;

/**
 * @brief 定时器0初始化，16位定时器模式，溢出时间为1ms
 *
 */
void Timer0_Init(void)
{
    EA = 1; //允许总中断
    ET0 = 1; //允许定时器0中断
    
    TMOD &= 0xF0; //设置定时器0为模式1，16位定时器模式
    TMOD |= 0x01;
    
    TL0 = (65536 - TOMS) % 256; //设置定时器初值
    TH0 = (65536 - TOMS) / 256;


    TR0 = 1; //启动定时器0
}

void Timer0_ISR(void) interrupt 1
{
    TL0 = (65536 - TOMS) % 256; //重新设置定时器初值
    TH0 = (65536 - TOMS) / 256;

    if(s_Timer0_Count == 500)
    {
        //到这说明已经过了500ms的时间
        s_Timer0_Count = 0; //重置计数器

        P10 = ~P10; //翻转P1.0的状态
    }

    s_Timer0_Count++; //计数器加1
}