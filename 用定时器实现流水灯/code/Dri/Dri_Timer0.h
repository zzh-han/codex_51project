#ifndef __DRI_TIMER0_H__
#define __DRI_TIMER0_H__

#include <stdio.h>
#include "uilt.h"
#include <STC89C5xRC.H>

typedef void (*callback)(void);

#define MAX_TIMER0_CALLBACK 4 // 定时器0中断回调函数数组最大长度

/**
 * @brief 定时器0初始化，16位定时器模式，溢出时间为1ms
 */
void Dri_Timer0_Init(void); //定时器0初始化

/**
 * @brief 注册定时器0中断回调函数
 * 
 * @param cb 回调函数指针
 * @return bit 注册是否成功, 1表示成功，0表示失败
 */
bit Dri_Timer0_Register(callback cb); //注册定时器0中断回调函数

/**
 * @brief 注销定时器0中断回调函数
 * 
 * @param cb 回调函数指针
 * @return bit 注销是否成功, 1表示成功，0表示失败
 */
bit Dri_Timer0_Unregister(callback cb); //注销定时器0中断回调函数


#endif