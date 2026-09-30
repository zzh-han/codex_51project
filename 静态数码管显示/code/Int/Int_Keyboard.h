#ifndef _INT_KEYBOARD_H_
#define _INT_KEYBOARD_H_

#include "STC89C5xRC.H"
#include "uilt.h"
/**
 * @brief 检查SW1是否被按下
 * 
 * @param  
 * @return 0表示未按下，1表示按下
 */
bit Int_Keyboard_IsSW1pressd(void);
/**
 * @brief 检查SW2是否被按下
 * 
 * @param  
 * @return 0表示未按下，1表示按下
 */
bit Int_Keyboard_IsSW2pressd(void);
/**
 * @brief 检查SW3是否被按下
 * 
 * @param  
 * @return 0表示未按下，1表示按下
 */
bit Int_Keyboard_IsSW3pressd(void);
/**
 * @brief 检查SW4是否被按下
 * 
 * @param  
 * @return 0表示未按下，1表示按下
 */
bit Int_Keyboard_IsSW4pressd(void);


#endif