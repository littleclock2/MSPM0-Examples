#include "ti_msp_dl_config.h"
#include "oled_spi.h"
#include "arm_const_structs.h"
#include "arm_math.h"
#include "TDC-GP22.h"
uint8_t choice  =0;
u32 Frequency = 30000;
 /*
    impe.Re;  //实部
    impe.Im;  //虚部
    impe.Impedance;  //模值
    impe.Phase;  //相位
    */
float temp;
int main(void){

    /* 系统初始化 */
    SYSCFG_DL_init();
    
    //通信初始化
	NVIC_ClearPendingIRQ(UART_0_INST_INT_IRQN );//清除中断标志??
    NVIC_EnableIRQ(UART_0_INST_INT_IRQN );
    
    // 配置CS引脚为输出，并初始化为高电平
    //DL_GPIO_setPins(GPIO_SPI_0_CS3_PORT, GPIO_SPI_0_CS3_PIN);
    
    OLED_Init();
    OLED_Clear();
    
	
	
    while (1){
        DL_GPIO_togglePins(LED_PORT,LED_PIN_1_PIN);
        delay_cycles(10000000);
        OLED_ShowString(2,3,"114514");
        OLED_Refresh();
		Tdc_test();
		
		delay_ms(500);
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




