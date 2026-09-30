#include "Int_Digital.h"

static unsigned char code  seg_table[] = 
{
     0x3F, 0x06, 0x5B, 0x4F, 0x66, 
     0x6D, 0x7D, 0x07, 0x7F, 0x6F
};

static u8  XianCun_buff[] = 
{
    0, 0, 0, 0, 0, 0, 0, 0
}; 


/**
 * @brief 显示数码管
 * 
 * @param dig 数码管编号
 * @param dat 要显示的数字
 */
static void s_DongTaishuma(u8 dig, u8 dat)
{
    P0 = 0x0;           //消隐
    //Delay1ms(1);      //黑暗的时间延长
    P1 = 0;             //置0
    P1 = dig - 1;         //选择哪一个数码管

    P0 = dat;  //显示哪一个数
}

/**
 * @brief 将要显示的数保存到显存里
 * 
 * @param n 要显示的数
 */
void Int_XianCun(u16 n)
{
    u8 i;
    for(i = 0; i < 8; i++)
    {
        XianCun_buff[i] = 0;
    }
    
    i = 7;
    if(n == 0)
    {
        XianCun_buff[7] = seg_table[0];  //如果n为0就显示0
    }
    
    while (n > 0)
    {
        XianCun_buff[i] = seg_table[n % 10];  //把n的个位数存到显存里
        n = n / 10;
        i--;
    }
} 

/**
 * @brief 将要显示的字符串保存到显存里
 * 
 * @param str 要显示的字符串
 */
void Int_XianCun8(char* str)
{
    u8 i;
    for(i = 0; i < 8; i++)
    {
        XianCun_buff[i] = 0;
    }
    
    for(i = 0; i < 8; i++)
    {
        if(str[i] < '0' || str[i] > '9')
        {
            XianCun_buff[i] = 0;
        }
        else
        {
            XianCun_buff[i] = seg_table[str[i] - '0'];
        }
    }
}

/**
 * @brief 刷新数码管显示
 * 
 */
void Int_Dig_Refresh(void)
{
    u8 i = 0;
    for (i = 0; i < 8; i++)
    {
        s_DongTaishuma(i + 1, XianCun_buff[i]);  //显示哪一个数码管的哪一个数
        Delay1ms(1);     
    }
}