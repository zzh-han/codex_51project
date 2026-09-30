#include "Dri_Timer0.h"  


static  u16 s_Timer0_Count1 = 0;
static  u16 s_Timer0_Count2 = 0;

//led1 500ms
void Timer0_Fun1(void) 
{
    if (s_Timer0_Count1 == 500)
    {
        //到这说明已经过了500ms的时间
        s_Timer0_Count1 = 0; //重置计数器

        P10 = ~P10; //翻转P1.0的状态
    }

    s_Timer0_Count1++; //计数器加1
}

//led2 1000ms
void Timer0_Fun2(void)
{
    if (s_Timer0_Count2 == 1000)
    {
        //到这说明已经过了1000ms的时间
        s_Timer0_Count2 = 0; //重置计数器

        P13 = ~P13; //翻转P1.3的状态
    }

    s_Timer0_Count2++; //计数器加1
}


void main() 
{
    Dri_Timer0_Init(); //初始化定时器0
    Dri_Timer0_Register(Timer0_Fun1); //注册定时器0中断回调函数
    Dri_Timer0_Register(Timer0_Fun2); //注册定时器0中断回调函数

    while (1)
    {
        //主循环中可以执行其他任务
    }
}