#include "Dri_Timer0.h"

#define TOMS (FOSC/NT/1000) //定时器0溢出1ms所需的计数值

static callback s_timer0_callback[MAX_TIMER0_CALLBACK] = {NULL, NULL, NULL, NULL}; // 定时器0中断回调函数数组



/**
 * @brief 定时器0初始化，16位定时器模式，溢出时间为1ms
 *
 */
void Dri_Timer0_Init(void)
{
    EA = 1; //允许总中断
    ET0 = 1; //允许定时器0中断
    
    TMOD &= 0xF0; //设置定时器0为模式1，16位定时器模式
    TMOD |= 0x01;
    
    TL0 = (65536 - TOMS) % 256; //设置定时器初值
    TH0 = (65536 - TOMS) / 256;

    TR0 = 1; //启动定时器0
}

/**
 * @brief 注册定时器0中断回调函数
 * 
 * @param callback 回调函数指针
 * @return bit 注册是否成功, 1表示成功，0表示失败
 */
bit Dri_Timer0_Register(callback cb)
{
    static u8 i;

    for (i = 0; i < MAX_TIMER0_CALLBACK; i++)
    {
        // 查找是否已经注册过该回调函数
        if (s_timer0_callback[i] == cb)
        {
            return 0; //回调函数已经注册过，注册失败
        }
    }
    if (cb == NULL)
    {
        return 0; //回调函数指针为空，注册失败
    }
    for (i = 0; i < MAX_TIMER0_CALLBACK; i++)
    {
        // 查找空闲的回调函数槽位
        if (s_timer0_callback[i] == NULL)
        {
            s_timer0_callback[i] = cb;
            return 1; //注册成功
        }
    }

    return 0; //到这说明回调函数数组已满，注册失败
    
}

/**
 * @brief 注销定时器0中断回调函数
 * 
 * @param callback 回调函数指针
 * @return bit 注销是否成功, 1表示成功，0表示失败
 */
bit Dri_Timer0_Unregister(callback cb)
{
    static u8 i;

    for (i = 0; i < MAX_TIMER0_CALLBACK; i++)
    {
        // 查找是否已经注册过该回调函数
        if (s_timer0_callback[i] == cb)
        {
            s_timer0_callback[i] = NULL; //注销回调函数
            return 1; //注销成功
        }
    }

    return 0; //到这说明回调函数数组中没有该回调函数，注销失败
}


void Timer0_ISR(void) interrupt 1
{
    static u8 i;

    TL0 = (65536 - TOMS) % 256; //设置定时器初值
    TH0 = (65536 - TOMS) / 256;

    //调用所有注册的回调函数
    for (i = 0; i < MAX_TIMER0_CALLBACK; i++)
    {
        if (s_timer0_callback[i] != NULL)
        {
            s_timer0_callback[i](); //调用回调函数
        }
    }
}