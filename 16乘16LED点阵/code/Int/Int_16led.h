#ifndef _INT_16LED_H_
#define _INT_16LED_H_

#include <STC89C5xRC.H>
#include <uilt.h>


/**
 * @brief 初始化16个LED点阵
 * 
 */ 
void Int_16led_Init(void);

// 设置要显示的汉字数组（必须传入code数组的指针）
void Int_16led_SetData(u8 *dat);

// 显示当前设置的汉字数据
void Int_16led_Display();

#endif 