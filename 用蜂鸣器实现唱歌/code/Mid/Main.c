#include "Dri_Timer0.h"

/**
 * @brief 主函数
 * 
 * 只需要初始化定时器，剩下的全部在中断里完成。
 * 主循环保持空转，不占用CPU时间。
 */
void main(void)
{
    Dri_Timer0_Init();   // 初始化定时器0（50us中断）+ 启动音乐播放

    while (1)
    {
        // 空循环：音乐播放和节拍全部由定时器中断驱动
    }
}