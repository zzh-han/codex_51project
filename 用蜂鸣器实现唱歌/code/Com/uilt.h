#ifndef __UILT_H__
#define __UILT_H__



typedef unsigned char u8;
typedef unsigned int u16;

#define FOSC  12000000 //晶振频率
#define NT  12 //机器周期数

/**
 * @brief 延时n ms
 *
 * @param n 延时的秒数
 */
void Delay1ms(unsigned int n);


#endif