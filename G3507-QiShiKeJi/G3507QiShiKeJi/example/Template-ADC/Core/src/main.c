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
#include "key.h"

/* 检查adc是否完成转换 */
volatile bool gCheckADC;
int choice = 0;
void UART_Send(uint8_t *Data_Temp){
	uint8_t i;

	for(i=0;i<2;i++){
		DL_UART_transmitData(UART0,*(Data_Temp+1));
		while(DL_UART_isTXFIFOFull(UART0)){
			
		}
		Data_Temp--;
	}
}

int main(void){
    /* adc转换结果 */
    uint16_t adcResult;         // adc转换结果（12bit，数字量）
    float adcResult_voltage;    // adc转换结果对应的电压值（单位:mV）

    /* 系统初始化 */
    SYSCFG_DL_init();
    
    //通信初始化
	NVIC_ClearPendingIRQ(UART_0_INST_INT_IRQN );//清除中断标志??
    NVIC_EnableIRQ(UART_0_INST_INT_IRQN );
    
    OLED_Init();
    OLED_Clear();
    OLED_ShowString(0, 0, "ADC val:");
    OLED_ShowString(0, 2, "voltage:");
    OLED_ShowString(104, 2, "mV");
    /* 开启 adc 中断 */
    NVIC_EnableIRQ(ADC12_0_INST_INT_IRQN);
    delay_cycles(32000000 * 0.1);
    /* 变量初始化 */
    gCheckADC = false;

    /* 确保内部参考电压在adc转换前已完成配置 */
    while (DL_VREF_CTL1_READY_NOTRDY == DL_VREF_getStatus(VREF))
        ;
    OLED_DrawPoint(100, 40, 1);
    OLED_DrawPoint(100, 41, 1);
    OLED_DrawPoint(100, 42, 1);
    OLED_DrawPoint(100, 43, 1);
    OLED_DrawPoint(100, 44, 1);
    OLED_DrawPoint(100, 45, 1);
    OLED_DrawPoint(100, 46, 1);
    OLED_DrawPoint(100, 47, 1);
    OLED_DrawPoint(100, 48, 1);
    OLED_DrawPoint(100, 49, 1);
    OLED_DrawPoint(100, 50, 1);
    OLED_DrawPoint(100, 51, 1);
    OLED_DrawPoint(100, 52, 1);
    OLED_DrawPoint(100, 53, 1);
    OLED_DrawPoint(100, 54, 1);
    OLED_DrawPoint(100, 55, 1);
    OLED_Refresh();
    while (1){
        /* 启动adc转换 */
        DL_ADC12_startConversion(ADC12_0_INST);
        /* 等待adc转换完成 */
        while (false == gCheckADC){
            /* 进入低功耗模式 wait for event */
			 int i = 114514*7888;
			//__WFE();
        }
        /* 将adc采样值读出 */
        adcResult = DL_ADC12_getMemResult(ADC12_0_INST, DL_ADC12_MEM_IDX_0);
        /* 根据公式计算对应的电压值，参考电压2.5V（sysconfig里设置） */
        adcResult_voltage = adcResult * 2500.0 / (4096.0 - 1) - 0.5 * 2500.0 / 4096.0;
        /* 在OLED上显示采样值 */
        OLED_ShowNum(72, 0, adcResult, 4, 16);
        OLED_ShowNum(72, 2, (uint16_t)adcResult_voltage, 4, 16);
        int num  =getKeyValue();
        OLED_ShowNum(0,6,num,2,16);
        UART_Send((uint8_t*)&adcResult);                //发送ADC数据
        
        /* 控制大概0.2s更新一次 */
        delay_cycles(3200000);

        /* 准备下一次采样 */
        gCheckADC = false;
        DL_ADC12_enableConversions(ADC12_0_INST);
        OLED_Refresh();
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

/* adc中断服务函数 */
void ADC12_0_INST_IRQHandler(void){
    switch (DL_ADC12_getPendingInterrupt(ADC12_0_INST)){
    /* adc转换完成后进入中断 */
    case DL_ADC12_IIDX_MEM0_RESULT_LOADED:
        gCheckADC = true;
        break;
    default:
        break;
    }
}

