#include "Dri_Timer0.h"
#include "buzzer.h"

/**
 * @brief 定时器0初始化
 * 
 * 16位定时器模式，50us溢出一次。
 * 50us @ 12MHz、12T 的初值计算：
 *   计数 = 65536 - (50us / 1us) = 65536 - 50 = 65486 = 0xFFCE
 */
void Dri_Timer0_Init(void)
{
    EA  = 1;              // 打开总中断
    ET0 = 1;              // 打开定时器0中断

    TMOD &= 0xF0;         // 保留高4位（定时器1的配置）
    TMOD |= 0x01;         // 设置定时器0为模式1（16位定时器）

    TL0 = 0xCE;           // 低8位初值
    TH0 = 0xFF;           // 高8位初值

    TR0 = 1;              // 启动定时器0
}

/**
 * @brief 定时器0中断服务函数，每50us进入一次
 * 
 * 把音乐播放逻辑直接内联进来，省掉函数调用和回调数组遍历的开销，
 * 保证整个 ISR 能在 50us 内执行完毕。
 */
void Timer0_ISR(void) interrupt 1
{
    /* 静态变量：跨中断调用保存状态 */
    static u8  half_count = 0;   // 半周期计数：累计到 song_note 的值时翻转一次蜂鸣器
    static u16 dur_count  = 0;   // 时长计数：累计到 song_dur 的值时切到下一个音符
    static u8  song_idx   = 0;   // 当前播放到第几个音符（数组下标）

    /* 重装定时器初值，保证下次仍是 50us 溢出 */
    TL0 = 0xCE;
    TH0 = 0xFF;

    /* ---------- 1. 判断当前音符是否播放完毕 ---------- */
    dur_count++;
    if (dur_count >= song_dur[song_idx])
    {
        dur_count  = 0;
        half_count = 0;
        BUZZER     = 0;           // 强制拉低，避免残留方波导致杂音
        song_idx++;

        if (song_idx >= SONG_LEN) // 一首歌播完
        {
            song_idx = 0;         // 从头循环
        }
        return;                   // 本次中断到此结束
    }

    /* ---------- 2. 休止符：只静音不发声 ---------- */
    if (song_note[song_idx] == N_REST) return;

    /* ---------- 3. 产生方波 ---------- */
    half_count++;
    if (half_count >= song_note[song_idx])
    {
        half_count = 0;
        BUZZER = !BUZZER;         // 翻转引脚，产生方波驱动无源蜂鸣器
    }
}