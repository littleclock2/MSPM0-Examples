#include "ti_msp_dl_config.h"
#include "oled_spi.h"
#include "arm_const_structs.h"
#include "arm_math.h"
#include "ESP.h"
uint8_t choice  =0;
uint8_t count = 0;
u8 mode = 0;
int main(void){     
    /* 系统初始化 */
    SYSCFG_DL_init();
    
    //通信初始化
	  NVIC_ClearPendingIRQ(UART_0_INST_INT_IRQN );//清除中断标志
    NVIC_EnableIRQ(UART_0_INST_INT_IRQN );
	
    NVIC_ClearPendingIRQ(UART_1_INST_INT_IRQN );//清除中断标志
    NVIC_EnableIRQ(UART_1_INST_INT_IRQN );
    
    OLED_Init();
    OLED_Clear();

    printf("start\r\n");
    WIFI_MODE_STA_AP_Init(mode); //初始化WIFI模块，1为透传模式，0为非透传模式
    while(1){     
        DL_GPIO_togglePins(LED_PORT,LED_PIN_1_PIN);
        OLED_ShowString(2,3,"114514");
        OLED_Refresh();
		    delay_ms(500);
        if(mode == 0){ //非透传模式
            WIFI_Send_Auto("114514\r\n"); //发送数据
        }
        else if(mode == 1){ //透传模式
            WIFI_Send_Through("1919810\r\n"); //透传模式下发送数据
            count ++;
            if(count>10){//自动退出透传模式
                count = 0;
                WIFI_Send_OutThrough(); //退出透传模式
            }
        }
		    
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


