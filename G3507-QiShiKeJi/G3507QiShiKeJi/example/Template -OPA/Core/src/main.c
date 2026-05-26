/*

      ___           ___           ___           ___           ___           ___           ___           ___     
     |\__\         /\__\         /\__\         /\  \         /\__\         /\  \         /\  \         /\  \    
     |:|  |       /:/  /        /::|  |       /::\  \       /:/ _/_       /::\  \       /::\  \       /::\  \   
     |:|  |      /:/  /        /:|:|  |      /:/\ \  \     /:/ /\__\     /:/\:\  \     /:/\:\  \     /:/\:\  \  
     |:|__|__   /:/  /  ___   /:/|:|  |__   _\:\~\ \  \   /:/ /:/ _/_   /:/  \:\  \   /::\~\:\  \   /:/  \:\__\ 
     /::::\__\ /:/__/  /\__\ /:/ |:| /\__\ /\ \:\ \ \__\ /:/_/:/ /\__\ /:/__/ \:\__\ /:/\:\ \:\__\ /:/__/ \:|__|
    /:/~~/~    \:\  \ /:/  / \/__|:|/:/  / \:\ \:\ \/__/ \:\/:/ /:/  / \:\  \ /:/  / \/_|::\/:/  / \:\  \ /:/  /
   /:/  /       \:\  /:/  /      |:/:/  /   \:\ \:\__\    \::/_/:/  /   \:\  /:/  /     |:|::/  /   \:\  /:/  / 
   \/__/         \:\/:/  /       |::/  /     \:\/:/  /     \:\/:/  /     \:\/:/  /      |:|\/__/     \:\/:/  /  
                  \::/  /        /:/  /       \::/  /       \::/  /       \::/  /       |:|  |        \::/__/   
                   \/__/         \/__/         \/__/         \/__/         \/__/         \|__|         ~~       

 * @brief       main
 * @language    C
 * @harfware   Template-OPA
 * @version     v1.0
 * @date        29-July-2024
 * @author      YunSword
 
*/


#include "ti_msp_dl_config.h"
#include "oled_spi.h"
#include "key.h"

uint8_t choice  =0;
int main(void){

    /* 系统初始化 */
    SYSCFG_DL_init();
    
    //通信初始化
	NVIC_ClearPendingIRQ(UART_0_INST_INT_IRQN );//清除中断标志??
    NVIC_EnableIRQ(UART_0_INST_INT_IRQN );
    
    OLED_Init();
    OLED_Clear();
    
    while (1){
        
    }
}

//通信接受中断函数
void  UART_0_INST_IRQHandler(){
   switch (DL_UART_getPendingInterrupt(UART_0_INST )){ //检测是否串口中??
        case DL_UART_MAIN_IIDX_RX:
            choice = DL_UART_receiveData(UART_0_INST);
            DL_UART_transmitData(UART_0_INST,1);
            break;
        default:
            break;
    }
}


