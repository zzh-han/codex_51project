#include "Int_Keyboard.h"

#define SW1 P30
#define SW2 P31
#define SW3 P32
#define SW4 P33

bit Int_Keyboard_IsSW1pressd(void)
{
    //如果SW1没有被按下，返回0
    if (SW1 == 1)
    {
        return 0;
    }
    //如果SW1被按下，延时20ms后再次检测SW1是否被按下
    Delay1ms(20); 
    if (SW1 == 1)
    {
        return 0;
    }
    //如果SW1被按下，等待SW1释放后返回1
    while (1)
    {
        if (SW1 == 1)
        {
            //消除按键抖动
            Delay1ms(20);
            if (SW1 == 1)
            {
                break;
            }
        }
    }
    return 1;
}

bit Int_Keyboard_IsSW2pressd(void)
{
    //如果SW2没有被按下，返回0
    if (SW2 == 1)
    {
        return 0;
    }
    //如果SW2被按下，延时20ms后再次检测SW2是否被按下
    Delay1ms(20); 
    if (SW2 == 1)
    {
        return 0;
    }
    //如果SW2被按下，等待SW2释放后返回1
    while (1)
    {
        if (SW2  == 1)
        {
            //消除按键抖动
            Delay1ms(20);
            if (SW2 == 1)
            {
                break;
            }
        }
    }
    return 1;
}

bit Int_Keyboard_IsSW3pressd(void)
{
    //如果SW3没有被按下，返回0
    if (SW3 == 1)
    {
        return 0;
    }
    //如果SW3被按下，延时20ms后再次检测SW3是否被按下
    Delay1ms(20); 
    if (SW3 == 1)
    {
        return 0;
    }
    //如果SW3被按下，等待SW3释放后返回1
    while (1)
    {
        if (SW3  == 1)
        {
            //消除按键抖动
            Delay1ms(20);
            if (SW3 == 1)
            {
                break;
            }
        }
    }
    return 1;
}

bit Int_Keyboard_IsSW4pressd(void)
{
    //如果SW4没有被按下，返回0
    if (SW4 == 1)
    {
        return 0;
    }
    //如果SW4被按下，延时20ms后再次检测SW4是否被按下
    Delay1ms(20); 
    if (SW4 == 1)
    {
        return 0;
    }
    //如果SW4被按下，等待SW4释放后返回1
    while (1)
    {
        if (SW4  == 1)
        {
            //消除按键抖动
            Delay1ms(20);
            if (SW4 == 1)
            {
                break;
            }
        }
    }
    return 1;
}