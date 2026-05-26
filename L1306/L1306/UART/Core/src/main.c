#include "ti_msp_dl_config.h"
#include "stdio.h"
int data;
int Count=0;
uint8_t output_1  =0 ,output_2 = 0,output_3 = 100;
int fputc(int ch, FILE *stream){
    //当串口0忙的时候等待，不忙的时候再发送传进来的字符
    
    DL_UART_transmitData(UART_0_INST,ch);
	while(DL_UART_isBusy(UART_0_INST)==true){}
    return ch;
}


int main(void){
    SYSCFG_DL_init();                      //Sysconfig初始化
    NVIC_ClearPendingIRQ(UART_0_INST_INT_IRQN );//清除中断标志位
    NVIC_EnableIRQ(UART_0_INST_INT_IRQN );
	DL_GPIO_clearPins(LED_PORT,LED_L0_PIN);
	
  
	while(1){
		if( DL_GPIO_readPins(KEY_PORT, KEY_K1_PIN )){
			DL_GPIO_setPins(LED_PORT,LED_L0_PIN);
        }
        else{
            DL_GPIO_clearPins(LED_PORT,LED_L0_PIN);
			//按下按钮就发送一个字母A，然后等待松手。
			DL_UART_transmitDataBlocking(UART_0_INST,'A');
            //printf("Hello\n");
            while(DL_GPIO_readPins(KEY_PORT, KEY_K1_PIN )==0);
		}
		//循环计数系统
		output_1++;
		if(output_1 >= 120) output_1 = 0;
		//printf("%d,%d,%d\n",output_1,output_2,output_3);
		DL_Common_delayCycles(3200000);
    }
}


void  UART_0_INST_IRQHandler(){
   switch (DL_UART_getPendingInterrupt(UART_0_INST )){ //检测是否串口中断
       //case DL_UART_IIDX_RX_TIMEOUT_ERROR:
         //   DL_UART_transmitDataBlocking(UART_0_INST,'A');
        //    break;
        case DL_UART_MAIN_IIDX_RX:
            Count = DL_UART_receiveData(UART_0_INST );
            //printf("Count:%d",Count);
            DL_UART_transmitDataBlocking(UART_0_INST,'A');
            //NVIC_ClearPendingIRQ(UART_0_INST_INT_IRQN );//清除中断标志位
            break;
        
        default:
            break;
    }
}