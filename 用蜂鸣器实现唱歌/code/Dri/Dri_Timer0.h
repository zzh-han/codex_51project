#ifndef __DRI_TIMER0_H__
#define __DRI_TIMER0_H__

#include "uilt.h"
#include <STC89C5xRC.H>

/**
 * @brief 定时器0初始化
 * 
 * 配置为16位定时器模式，50us溢出一次并开启中断。
 */
void Dri_Timer0_Init(void);

#endif