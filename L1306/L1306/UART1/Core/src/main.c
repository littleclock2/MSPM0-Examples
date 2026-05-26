#include "ti_msp_dl_config.h"
uint8_t data;

int main(void){
    SYSCFG_DL_init();                      //Sysconfig初始化
    NVIC_ClearPendingIRQ(UART1_INT_IRQn);//清除中断标志位
    NVIC_EnableIRQ(UART1_INT_IRQn);

    while(1){
    }
}

void  UART1_IRQHandler(){
   switch (DL_UART_getPendingInterrupt(UART1)) //检测是否串口中断
		 {
        case DL_UART_MAIN_IIDX_RX:
            data = DL_UART_receiveData(UART1);  //发送接收到的数据
            DL_UART_transmitData(UART1, data);
            break;
        default:
            break;
    }
}