#include "buzzer.h"

// 定时器200us中断一次，所以：
// 500次 = 100ms
// 2000次 = 400ms
// 5000次 = 1000ms
/*
void buzzer_Int(void)
{
    static u16 count = 0;   // 计数器
    static u8  phase = 0;   // 当前处于哪个阶段

    count++;

    switch (phase)
    {
        // ============ 第一声“滴”：响100ms ============
        case 0:
            BUZZER = !BUZZER;           // 翻转产生方波，蜂鸣器响
            if (count >= 500)           // 100ms到
            {
                count = 0;
                phase = 1;
                BUZZER = 0;             // 强制拉低，确保静音
            }
            break;

        // ============ 短停100ms ============
        case 1:
            if (count >= 500)
            {
                count = 0;
                phase = 2;
            }
            break;

        // ============ 第二声“滴”：响100ms ============
        case 2:
            BUZZER = !BUZZER;
            if (count >= 500)
            {
                count = 0;
                phase = 3;
                BUZZER = 0;
            }
            break;

        // ============ 长停1000ms（“等一会”） ============
        case 3:
            if (count >= 5000)          // 1000ms = 1秒
            {
                count = 0;
                phase = 0;              // 回到开头，循环往复
            }
            break;
    }
}
*/


// ============ 音符定义 ============
// 半周期 = 5000 / 频率（以100us为单位）
#define N_G4  13   // 392 Hz
#define N_A4  11   // 440 Hz
#define N_B4  10   // 494 Hz
#define N_C5  10   // 523 Hz
#define N_D5   9   // 587 Hz
#define N_E5   8   // 659 Hz
#define N_F5   7   // 698 Hz
#define N_G5   6   // 784 Hz
#define N_REST 0

// 节拍：十六分音符 = 2000 × 100us = 200ms
#define BEAT   2000

// ============ 生日快乐歌 ============
// 音符：G G A G C B | G G A G D C | G G G' E C B A | F F E C D C
u8 code song_note[] = {
    N_G4, N_G4, N_A4, N_G4, N_C5, N_B4,          // Happy birthday to you
    N_G4, N_G4, N_A4, N_G4, N_D5, N_C5,          // Happy birthday to you
    N_G4, N_G4, N_G5, N_E5, N_C5, N_B4, N_A4,    // Happy birthday dear XX
    N_F5, N_F5, N_E5, N_C5, N_D5, N_C5,          // Happy birthday to you
    N_REST                                        // 结尾停顿
};

// 时长（单位：十六分音符 BEAT）
u16 code song_dur[] = {
    BEAT, BEAT, 2*BEAT, 2*BEAT, 2*BEAT, 4*BEAT,
    BEAT, BEAT, 2*BEAT, 2*BEAT, 2*BEAT, 4*BEAT,
    BEAT, BEAT, 2*BEAT, 2*BEAT, 2*BEAT, 2*BEAT, 4*BEAT,
    2*BEAT, 2*BEAT, 2*BEAT, 2*BEAT, 2*BEAT, 4*BEAT,
    4*BEAT
};

#define SONG_LEN (sizeof(song_note))

// ============ 播放器 ============
void buzzer_Int(void)
{
    static u8  half_count  = 0;   // 半周期计数
    static u16 dur_count   = 0;   // 音符时长计数
    static u8  song_idx    = 0;   // 当前播放到第几个音符

    // 1. 判断当前音符是否播放完毕
    dur_count++;
    if (dur_count >= song_dur[song_idx])
    {
        dur_count = 0;
        half_count = 0;
        BUZZER = 0;              // 静音，准备下一音符
        song_idx++;
        if (song_idx >= SONG_LEN)
        {
            song_idx = 0;        // 整首歌循环
        }
        return;
    }

    // 2. 休止符：保持静音
    if (song_note[song_idx] == N_REST) return;

    // 3. 产生方波：每 half_count 次中断翻转一次引脚
    half_count++;
    if (half_count >= song_note[song_idx])
    {
        half_count = 0;
        BUZZER = !BUZZER;
    }
}