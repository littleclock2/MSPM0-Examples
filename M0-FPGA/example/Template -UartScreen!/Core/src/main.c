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
 * @harfware   Template-UartScreen
 * @version     v1.0
 * @date        29-July-2024
 * @author      YunSword
 
*/


#include "ti_msp_dl_config.h"
#include "uart_screen.h"
#include "oled_spi.h"
#include "key.h"
#include <stdio.h>
uint8_t second = 7;
uint8_t choice  =0;
uint8_t year = 1;
int main(void){

    /* 系统初始化 */
    SYSCFG_DL_init();
    
    //通信初始化
	NVIC_ClearPendingIRQ(UART_0_INST_INT_IRQN );//清除中断标志??
    NVIC_EnableIRQ(UART_0_INST_INT_IRQN );

    DL_TimerG_startCounter(TIMER_0_INST);//启动计时??
	NVIC_EnableIRQ(TIMER_0_INST_INT_IRQN);//中断函数启动
    OLED_Init();
    OLED_Clear();
    
    while (1){
        OLED_ShowNum(0,0,second,1,16);
    }
}

//通信接受中断函数
void  UART_0_INST_IRQHandler(){
   switch (DL_UART_getPendingInterrupt(UART_0_INST )){ //检测是否串口中??
        case DL_UART_MAIN_IIDX_RX:
            choice = DL_UART_receiveData(UART_0_INST);

            HMISendb(0xff);
            if(choice==0x01) year=2;
			else if(choice==0x02) year=3;
			else if(choice==0x00) year=1;
            break;
        default:
            break;
    }
}
//中断函数
void TIMER_0_INST_IRQHandler (void){
	switch( DL_TimerG_getPendingInterrupt (TIMER_0_INST)){
		case DL_TIMERG_IIDX_ZERO:ss
			{//向外界实时发送信??
				
				uint8_t month = 3;
				uint8_t day = 4;
				uint8_t hour = 5;
				uint8_t minute = 6;
				
				//DL_UART_transmitData(UART_0_INST,year);
				//固定向外界发送信??
				//printf("%d,%d,%d,%d,%d,%d\n",year_1*100 + year_2,month,day,hour,minute,second);
				unsigned char  buf[64];
				sprintf((char *)buf,"n0.val=%d",year);  //显示年
				HMISends((char *)buf);
				HMISendb(0xff);

				sprintf((char *)buf,"n1.val=%d",month);  //显示月
				HMISends((char *)buf);
				HMISendb(0xff);

				sprintf((char *)buf,"n2.val=%d",day);  //显示日
				HMISends((char *)buf);
				HMISendb(0xff);

				sprintf((char *)buf,"n3.val=%d",hour);  //显示时
				HMISends((char *)buf);
				HMISendb(0xff);

				sprintf((char *)buf,"n4.val=%d",minute);  //显示分
				HMISends((char *)buf);
				HMISendb(0xff);

				sprintf((char *)buf,"n5.val=%d",second);  //显示秒
				HMISends((char *)buf);
				HMISendb(0xff);
                second++;
			}
			break;
		default:
			break;
	}
}

