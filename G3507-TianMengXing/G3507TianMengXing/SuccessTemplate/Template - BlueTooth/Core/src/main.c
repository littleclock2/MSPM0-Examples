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
 * @harfware   Template
 * @version     v1.0
 * @date        29-July-2024
 * @author      YunSword
 
*/


#include "ti_msp_dl_config.h"
#include "oled_spi.h"
#include "arm_const_structs.h"
#include "arm_math.h"
#include "board.h"
#include "hc05.h"
//#include "key.h"

uint8_t choice  =0;
int main(void){

    /* 系统初始化 */
    SYSCFG_DL_init();
    
    //通信初始化
	NVIC_ClearPendingIRQ(UART_0_INST_INT_IRQN );//清除中断标志??
    NVIC_EnableIRQ(UART_0_INST_INT_IRQN );
	
	NVIC_EnableIRQ(TIMER_0_INST_INT_IRQN);
    DL_TimerG_startCounter(TIMER_0_INST);
	
    Bluetooth_Init();//蓝牙初始化
    delay_ms(100);
    lc_printf("HC05 Bluetooth Init!!\r\n");
    
    // 配置CS引脚为输出，并初始化为高电平
    //DL_GPIO_setPins(GPIO_SPI_0_CS3_PORT, GPIO_SPI_0_CS3_PIN);
    
    OLED_Init();
    OLED_Clear();
    DL_GPIO_setPins(LED_PORT,LED_PIN_1_PIN);
	DL_GPIO_setPins(HC05_PORT,HC05_BRTS_PIN);
	
	
	volatile bool gTogglePolicy;
	
    while (1){
        
		//DL_SYSCTL_setPowerPolicySTOP0();
//		while (false == gTogglePolicy) {
//			__WFE();
//		}
//		gTogglePolicy = false;
		
//        OLED_ShowString(2,3,"114514");
//        OLED_Refresh();
        //发送数据到蓝牙
        BLE_send_String((uint8_t *)"TMX MSPM0G3507!!\n");
		//OLED_ShowString(4,3,"ewdkfewhfv");
        //如果接收到蓝牙数据则通过串口显示
        Receive_Bluetooth_Data();
        delay_ms(3000);
		DL_GPIO_togglePins(HC05_PORT,HC05_BRTS_PIN);
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

void  TIMER_0_INST_IRQHandler(){
   switch (DL_TimerG_getPendingInterrupt(TIMER_0_INST)){ //检测是否串口中??
        case DL_TIMERG_IIDX_ZERO:
			__NOP();
            break;
        default:
            break;
    }
}



