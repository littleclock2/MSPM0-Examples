#include "ti_msp_dl_config.h"
#include "oled_spi.h"
#include "arm_const_structs.h"
#include "arm_math.h"
#include <stdio.h>
#include <string.h>
#include "tdc.h"
#include "driverlib.h"

#define TDC_TIMEOUT_MS 10 // TDC测量超时时间，单位毫秒，超时返回0xFFFFFFFF
#define BUF_SIZE 20

volatile u8 gTogglePolicy= 0;
uint8_t buf[BUF_SIZE]  ={0};
uint16_t buf_size = 0;
uint32_t temp = 0;

void PulseCreate(void);

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
    //TDC芯片初始化
	TDC_Config();
	
   uint32_t tdc_value = 0;
	float time = 0;
    while (1){
        DL_GPIO_togglePins(LED_PORT,LED_L1_PIN);
        delay_ms(100);
		DL_GPIO_togglePins(LED_PORT,LED_L2_PIN);
        delay_ms(100);
		OLED_ShowNum(2,4,tdc_value,9,16);
		OLED_ShowNum(2,6,(int)time,9,16);
        OLED_Refresh();
		DL_UART_transmitData(BlueTooth_INST,temp);
		//temp  = TDC_Test();
		TDC_Start_Measure();
		PulseCreate();
		tdc_value = TDC_Get_Measure_Value(TDC_TIMEOUT_MS);
		time = TDC_Value_to_Time_ns(tdc_value);
		// 等待中断
		  
		//DL_SYSCTL_setPowerPolicyRUN0SLEEP0();
		//DL_SYSCTL_setPowerPolicySTOP0();
		//DL_SYSCTL_setPowerPolicySTANDBY0();
		// while (0 == gTogglePolicy) {
		// 	__WFE();
		// }
    }
}
//脉冲产生函数
void PulseCreate(void){
	//寄存器翻转高电平
	PULSE_PORT->DOUTSET31_0 = PULSE_START_PIN;
	delay_cycles(4);
	//寄存器翻转低电平
	PULSE_PORT->DOUTCLR31_0 = PULSE_START_PIN;
	PULSE_PORT->DOUTCLR31_0 = PULSE_SP1_PIN;
	delay_cycles(4);//延时后产生下一个脉冲
//	__NOP();
//	__NOP();//__NOP();__NOP();__NOP();
	//寄存器翻转高电平
	PULSE_PORT->DOUTSET31_0 = PULSE_SP1_PIN;
	delay_cycles(4);
	//寄存器翻转低电平
	
	
	// 生成脉冲
    //DL_GPIO_setPins(PULSE_PORT, PULSE_START_PIN);  // 高电平
    //delay_cycles(16);                        // 假设48MHz时钟，约333ns
    //DL_GPIO_clearPins(PULSE_PORT, PULSE_START_PIN); /
//	DL_GPIO_setPins(PULSE_PORT, PULSE_SP1_PIN);  // 高电平
//    //delay_cycles(16);                        // 假设48MHz时钟，约333ns
//    DL_GPIO_clearPins(PULSE_PORT, PULSE_SP1_PIN); // 低电平
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


