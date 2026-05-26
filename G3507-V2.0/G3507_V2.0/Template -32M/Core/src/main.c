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
 * @date        23-July-2025
 * @author      YunSword
 
*/


#include "ti_msp_dl_config.h"
#include "oled_spi.h"
#include "arm_const_structs.h"
#include "arm_math.h"
#include <stdio.h>
#include <string.h>

#define BUF_SIZE 20
volatile u8 gTogglePolicy= 0;
uint8_t buf[BUF_SIZE]  ={0};
uint16_t buf_size = 0;

int main(void){

    /* 系统初始化 */
    SYSCFG_DL_init();
    
    //通信初始化
	NVIC_ClearPendingIRQ(BlueTooth_INST_INT_IRQN );//清除中断标志??
    NVIC_EnableIRQ(BlueTooth_INST_INT_IRQN );
    
    // 配置CS引脚为输出，并初始化为高电平
    //DL_GPIO_setPins(GPIO_SPI_0_CS3_PORT, GPIO_SPI_0_CS3_PIN);
    
    OLED_Init();
    OLED_Clear();
    
    while (1){
        DL_GPIO_togglePins(LED_PORT,LED_L1_PIN);
        delay_ms(1000);
		DL_GPIO_togglePins(LED_PORT,LED_L2_PIN);
        delay_ms(1000);
        OLED_ShowString(2,3,"114514");
        OLED_Refresh();
		DL_UART_transmitData(BlueTooth_INST,114);
		//DL_SYSCTL_setPowerPolicyRUN0SLEEP0();
		//DL_SYSCTL_setPowerPolicySTOP0();
		//DL_SYSCTL_setPowerPolicySTANDBY0();
//		while (0 == gTogglePolicy) {
//			__WFE();
//		}

    }
}

//通信接受中断函数
void  BlueTooth_INST_IRQHandler(){
   switch (DL_UART_getPendingInterrupt(BlueTooth_INST )){ //检测是否串口中??
        case DL_UART_MAIN_IIDX_RX:
            buf[buf_size++] = DL_UART_receiveData(BlueTooth_INST);
			if  (buf_size >= 2){
				 if (buf[0] == 0x33 ){ //接收到帧头
					 //接收到帧尾
					 if (buf[buf_size-1] == 0x0A && buf[buf_size- 2] == 0x0D){ 					
						//此处为数据包处理逻辑
						buf_size = 0;
						memset(buf,0,BUF_SIZE);
						//DL_UART_transmitData(BlueTooth_INST,1); 
					 }  
				 }
				 else{
					 buf_size  =  0;
					 memset(buf,0,BUF_SIZE);
				 }
			}
						
			if(buf_size  >=  BUF_SIZE){
				 buf_size = 0;
				 memset(buf,0,BUF_SIZE);
			}
			
			if(gTogglePolicy){
				gTogglePolicy=0;
			}
			else if (gTogglePolicy==0){
				gTogglePolicy= 1;
			}
         break;
        default:
            break;
    }
}


