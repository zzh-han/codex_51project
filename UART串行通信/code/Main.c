#include "Dri/Dri_UART.h"

/**
 * @brief 应用程序入口
 *
 * Main层只安排应用流程，通过驱动接口初始化UART；
 * SCON等硬件寄存器的配置细节由Dri_UART模块负责。
 */
void main(void)
{
    Dri_UART_Init(); // 初始化UART外设；当前阶段先配置工作方式

    while (1)
    {
        // 当前还没有设置波特率，也没有向SBUF写入数据，因此串口暂时不会发送内容。
        // 下一步将在Dri_UART驱动中添加发送接口，再由Main调用它发送一个字节。
    }
}
