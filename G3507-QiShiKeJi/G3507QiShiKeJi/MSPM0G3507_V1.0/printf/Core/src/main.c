/*
 * UART_PRINTF示例
 * 主函数使用printf（115200波特率）每秒打印一次数据
 * 数据可在电脑串口软件上观察到
 * Author: zjs
 */
#include "ti_msp_dl_config.h"
#include "oled.h"
#include "key.h"
/* 使用printf需要包含以下头文件 */
#include "stdio.h"
#include "string.h"

//===================对printf进行重定向===================
 #pragma(__use_no_semihosting)
 struct FILE
 {
     int handle;
 };
 FILE __stdout;
 void _sys_exit(int x)
 {
     x = x;
 }
 int fputc(int ch, FILE *f)
 {
     /* 发送一个数据 */
     DL_UART_Main_transmitData(UART_0_INST, (uint8_t)ch);
     /* 等待数据传输完毕 */
     while (DL_UART_Main_isBusy(UART_0_INST))
         ;
     return ch;
 }
 int fputs(const char *_ptr, register FILE *_fp)
 {
     uint16_t i, len;
     len = strlen(_ptr);
     for (i = 0; i < len; i++)
     {
         /* 发送一个数据 */
         DL_UART_Main_transmitData(UART_0_INST, (uint8_t)_ptr[i]);
         /* 等待数据传输完毕 */
         while (DL_UART_Main_isBusy(UART_0_INST))
             ;
     }
     return len;
 }
//========================================================

uint8_t num = 0;
uint16_t temp = 0;
int main(void)
{
    SYSCFG_DL_init(); // Initialize the device
    NVIC_ClearPendingIRQ(UART_0_INST_INT_IRQN );//清除中断标志位
    NVIC_EnableIRQ(UART_0_INST_INT_IRQN );
    /* 初始化OLED屏幕 */
    OLED_Init();
    OLED_Clear();
    OLED_ShowString(8, 0, "Number:");

    while (1)
    {
    ///* printf串口发送 */
    //printf("Hello World! Number:%d\r\n", num);
    ///* OLED屏幕更新 */
    //OLED_ShowNum(8 * 8, 0, num, 3, 16);
    ///* 延时 */
    //delay_cycles(32000000);
    ///* num累加 */
    //num++;
     temp  = DL_UART_receiveData(UART_0_INST);
     DL_UART_transmitData(UART_0_INST,temp);
    }
}

void  UART_0_INST_IRQHandler(){
    
   switch (DL_UART_getPendingInterrupt(UART_0_INST )){ //检测是否串口中断
        case DL_UART_MAIN_IIDX_RX:
            num = DL_UART_receiveData(UART_0_INST);
            printf("yes\n");
            break;
        case DL_UART_MAIN_IIDX_TX:
            printf("SSS\n");
            break;
        default:
            break;
    }
}
