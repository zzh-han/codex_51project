#include "buzzer.h"

/*
 * 《生日快乐》歌谱
 * 歌词：Happy birthday to you × 2
 *       Happy birthday dear XX
 *       Happy birthday to you
 *
 * 每个元素对应一个音符的频率计数值（见 buzzer.h 中的定义）
 */
u8 code song_note[] = {
    /* Happy birth-day to you */
    N_G4, N_G4, N_A4, N_G4, N_C5, N_B4,
    /* Happy birth-day to you */
    N_G4, N_G4, N_A4, N_G4, N_D5, N_C5,
    /* Happy birth-day dear XX */
    N_G4, N_G4, N_G5, N_E5, N_C5, N_B4, N_A4,
    /* Happy birth-day to you */
    N_F5, N_F5, N_E5, N_C5, N_D5, N_C5,
    /* 结尾停顿 */
    N_REST
};

/*
 * 每个音符的持续时长（单位：BEAT，1 BEAT = 200ms）
 * 与 song_note[] 数组一一对应，长度必须相同（都是26个）
 *
 * 例：2*BEAT = 400ms（四分之一音符），4*BEAT = 800ms（二分音符）
 */
u16 code song_dur[] = {
    BEAT, BEAT, 2*BEAT, 2*BEAT, 2*BEAT, 4*BEAT,
    BEAT, BEAT, 2*BEAT, 2*BEAT, 2*BEAT, 4*BEAT,
    BEAT, BEAT, 2*BEAT, 2*BEAT, 2*BEAT, 2*BEAT, 4*BEAT,
    2*BEAT, 2*BEAT, 2*BEAT, 2*BEAT, 2*BEAT, 4*BEAT,
    4*BEAT
};