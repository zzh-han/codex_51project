#ifndef __DRI_UART_H__
#define __DRI_UART_H__

/**
 * @brief 初始化UART外设
 *
 * 当前实现选择串口模式1并允许接收，但尚未设置波特率。
 * 这是驱动向Main等上层模块公开的接口；上层无需直接操作串口寄存器。
 */
void Dri_UART_Init(void);

#endif
