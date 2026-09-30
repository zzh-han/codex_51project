#include "Int_Keyboard.h"

#define SW1 P30
#define SW2 P31
#define SW3 P32
#define SW4 P33

#define KEYIN P2


u8 Int_Keyboard_IsSW16pressd(void)
{
    static u8 s_key_value = 0;//按键值
    static u8 row = 0;  //哪一行
    static u8 law = 0;  //哪一列
    static u8 p1_value = 0; //该变量用于存储P1口的值

    /*************扫描16键键盘，得到按键的行值*****************/
    KEYIN = 0x0f; //设置P1口的低四位为输入，高四位为输出
    p1_value = KEYIN; //读取P1口的值
    if(p1_value == 0x0f)
    {
        return 0;
    }
    Delay1ms(20); //消除按键抖动
    p1_value = KEYIN; //再读取P1口的值
    if(p1_value == 0x0f)
    {
        return 0;
    }
    
    switch (p1_value)
    {
    case  0x0e:
        row = 1;
        break;
    case  0x0d:
        row = 2;
        break;
    case  0x0b:
        row = 3;
        break;
    case  0x07:
        row = 4;
        break;
    
    default:
        break;
    }
    /*************扫描16键键盘，得到按键的列值*****************/
    KEYIN = 0xf0; //设置P1口的低四位为输入，高四位为输出
    p1_value = KEYIN; //读取P1口的值存到p1_value中

    switch (p1_value)
    {
    case 0xe0:
        law = 1;
        break;
    case 0xd0:
        law = 2;
        break;
    case 0xb0: 
        law = 3;
        break;
    case 0x70: 
        law = 4;
        break;
    
    default:
        break;
    }

    /***************根据行列值计算按键值****************/
    if (row != 0 && law != 0)
    {
        s_key_value = (row - 1) * 4 + law;
    }
    else
    {
        s_key_value = 0;
    }

    while(KEYIN != 0xf0) //等待按键释放
    {
        if(KEYIN == 0xf0)
        {
            Delay1ms(20); //消除按键抖动
            if(KEYIN == 0xf0)
                break;
        }
    }

    return s_key_value;
}




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