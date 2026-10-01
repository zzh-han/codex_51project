#include <STC89C5xRC.H>
#include "uilt.h"

/*
 * 电机驱动接口：使用开发板上的 TC1508S H 桥 A 通道。
 * 将单片机 P1.0 接到驱动输入 INA，将 P1.1 接到 INB；
 * 两线直流电机接在驱动输出 OUTA、OUTB 之间。
 * 电机电流由 H 桥驱动，不可直接接到单片机 IO 引脚。
 */
#define MOTOR_INA P10
#define MOTOR_INB P11

/*
 * 按键输入为低电平有效：
 * SW1 接 P3.0：前进；SW2 接 P3.1：后退；SW3 接 P3.2：刹车。
 * 8051 准双向 IO 作为输入前要先写 1，主函数中会完成初始化。
 */
#define KEY_FORWARD P30
#define KEY_REVERSE P31
#define KEY_BRAKE   P32

/* 电机运行状态。上电后先进入 MODE_STOP，避免复位时电机意外转动。 */
#define MODE_STOP    0
#define MODE_FORWARD 1
#define MODE_REVERSE 2
#define MODE_BRAKE   3

/* 按键数量，以及按键电平连续变化多少次后才确认状态改变。 */
#define KEY_COUNT    3
#define DEBOUNCE_MS  20

/*
 * 按键状态缓存：
 * s_keyStable 保存上一次确认的稳定电平；1 表示松开，0 表示按下。
 * s_keyCount 统计当前电平与稳定电平不同时的连续采样次数，用于消抖。
 * s_mode 保存当前电机模式；模式会保持，直到按下另一个功能键。
 */
static u8 s_keyStable[KEY_COUNT] = {1, 1, 1};
static u8 s_keyCount[KEY_COUNT] = {0, 0, 0};
static u8 s_mode = MODE_STOP;

/* 按键编号到实际 IO 的对应关系：0=SW1，1=SW2，2=SW3。 */
static u8 Key_Read(u8 key)
{
    if (key == 0) return KEY_FORWARD;
    if (key == 1) return KEY_REVERSE;
    return KEY_BRAKE;
}

/*
 * 扫描全部按键并返回一次按下事件：
 * 返回 1、2、3 分别代表 SW1、SW2、SW3；返回 0 表示没有新按下事件。
 * 按键电平必须连续与稳定状态不同 DEBOUNCE_MS 次，才确认状态变化。
 * 只有稳定状态从松开(1)变为按下(0)时才报告事件，因此长按不会重复触发。
 * 松开时也经过消抖，防止触点抖动让程序误判为多次按下。
 */
static u8 Key_GetPressEvent(void)
{
    u8 i;
    u8 raw;

    for (i = 0; i < KEY_COUNT; i++)
    {
        raw = Key_Read(i);
        if (raw == s_keyStable[i])
        {
            s_keyCount[i] = 0;
        }
        else
        {
            s_keyCount[i]++;
            if (s_keyCount[i] >= DEBOUNCE_MS)
            {
                s_keyStable[i] = raw;
                s_keyCount[i] = 0;
                if (raw == 0)
                {
                    return i + 1;
                }
            }
        }
    }
    return 0;
}

/*
 * 根据 TC1508S A 通道逻辑表设置 INA/INB：
 *   00：输出高阻，电机滑行停止（待机）；
 *   10：电机正转；
 *   01：电机反转；
 *   11：H 桥将电机两端拉到同一电平，形成电气刹车。
 * 实际正转方向取决于电机接线和安装方向；若方向相反，可对调电机两线，
 * 或交换前进、后退对应的输入状态。
 */
static void Motor_SetMode(u8 mode)
{
    if (mode == MODE_FORWARD)
    {
        MOTOR_INA = 1;
        MOTOR_INB = 0;
    }
    else if (mode == MODE_REVERSE)
    {
        MOTOR_INA = 0;
        MOTOR_INB = 1;
    }
    else if (mode == MODE_BRAKE)
    {
        MOTOR_INA = 1;
        MOTOR_INB = 1;
    }
    else
    {
        MOTOR_INA = 0;
        MOTOR_INB = 0;
    }
}

void main(void)
{
    u8 keyEvent;

    /*
     * 8051 准双向口通过写 1 释放引脚，使其可作为输入。
     * 按键按下时将对应引脚拉低，因此程序按低电平识别按键。
     * 电机上电先设置为 00（滑行停止），避免复位时意外启动。
     */
    KEY_FORWARD = 1;
    KEY_REVERSE = 1;
    KEY_BRAKE = 1;
    Motor_SetMode(MODE_STOP);

    while (1)
    {
        /* 轮询按键；只有完成消抖的稳定按下才会产生事件。 */
        keyEvent = Key_GetPressEvent();
        if (keyEvent == 1)
        {
            /* SW1：保存前进模式，并立即设置 H 桥输入。 */
            s_mode = MODE_FORWARD;
            Motor_SetMode(s_mode);
        }
        else if (keyEvent == 2)
        {
            /* SW2：保存后退模式，并立即设置 H 桥输入。 */
            s_mode = MODE_REVERSE;
            Motor_SetMode(s_mode);
        }
        else if (keyEvent == 3)
        {
            /* SW3：进入电气刹车；松开按键后仍保持刹车，直到选择其他模式。 */
            s_mode = MODE_BRAKE;
            Motor_SetMode(s_mode);
        }

        /* 短暂延时以降低空转轮询速度；延时期间维持当前 H 桥状态。 */
        Delay1ms(1);
    }
}
