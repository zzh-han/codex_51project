#include "Int_16led.h"
#include "Dri_Timer0.h"

#define     SER P34
#define  RCLOCK P35
#define  SCLOCK P36

//【关键1】定义一个静态全局指针，用来保存要显示的数组
static u8 *s_current_dat = 0; 

/**
 * @brief 将数据放入移位锁存器
 * 
 * @param dat_A 数据A
 * @param dat_B 数据B
 * @param dat_C 数据C
 * @param dat_D 数据D
 */
static void Int_16led_putdata(u8 dat_A, u8 dat_B, u8 dat_C, u8 dat_D)
{
    u8 i = 0;

    RCLOCK = 0;
    SCLOCK = 0;

    for(i = 0; i < 8; i++)
    {
        SER = dat_D >> 7; //将dat的高第一位输送给SER
        //SER接收需要一个SCLOCK的上升沿
        SCLOCK = 0;
        SCLOCK = 1;

        dat_D <<= 1;
    }//至此dat_D已经放到A移位锁存器，但是尚未锁存

    for(i = 0; i < 8; i++)
    {
        SER = dat_C >> 7; //将dat的高第一位输送给SER
        //SER接收需要一个SCLOCK的上升沿
        SCLOCK = 0;
        SCLOCK = 1;

        dat_C <<= 1;
    }//至此dat_C已经放到A移位锁存器，dat_D放到了B移位锁存器，但是尚未锁存

    for(i = 0; i < 8; i++)
    {
        SER = dat_B >> 7; //将dat的高第一位输送给SER
        //SER接收需要一个SCLOCK的上升沿
        SCLOCK = 0;
        SCLOCK = 1;

        dat_B <<= 1;
    }//至此dat_B已经放到A移位锁存器，但是尚未锁存

    for(i = 0; i < 8; i++)
    {
        SER = dat_A >> 7; //将dat的高第一位输送给SER
        //SER接收需要一个SCLOCK的上升沿
        SCLOCK = 0;
        SCLOCK = 1;

        dat_A <<= 1;
    }//至此4个数据都已放入4个移位锁存器，但是尚未锁存

    RCLOCK = 0;
    RCLOCK = 1; //锁存数据    
}

// 【关键2】设置数据源
void Int_16led_SetData(u8 *dat)
{
    s_current_dat = dat;
}


void Int_16led_Init(void)
{
    Dri_Timer0_Init();
    Dri_Timer0_Register(Int_16led_Display);
}



// 【关键4】改成无参函数！用静态变量 i 来控制扫描行
void Int_16led_Display(void)
{
    static u8 i = 0;
    
    // 如果数据还没设置，直接返回，防止空指针
    if (s_current_dat == 0) return;

    if (i < 8)
    {
        // 前8行：低8位有效
        Int_16led_putdata(s_current_dat[i], s_current_dat[i + 16], ~(1 << i), 0xFF);
    }
    else
    {  
        // 后8行：高8位有效
        Int_16led_putdata(s_current_dat[i], s_current_dat[i + 16], 0xFF, ~(1 << (i - 8)));
    }

    i++;
    if (i == 16) // 扫完16行后重置
    {
        i = 0;
    }
}
