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
 * @harfware   Template-ADC-DMA
 * @version     v1.0
 * @date        29-July-2024
 * @author      YunSword
 
*/

#include "ti_msp_dl_config.h"
#include "oled_spi.h"
#include "key.h"
/* Number of samples */
#define NUM_SAMPLES 1024
bool DMA_done = false; // 电压DMA完成标志
bool Current_DMA_done = false; // 电流DMA完成标志
/* 检查adc是否完成转换 */
volatile bool gCheckADC;
//volatile uint16_t ADCResult0[60];/* adc转换结果 */
//volatile uint16_t ADCResult1[60];/* adc转换结果 */
volatile uint16_t ADC_sig[NUM_SAMPLES * 2];//ch0和ch1交替分配
volatile uint16_t complex_input0[NUM_SAMPLES];
volatile uint16_t complex_input1[NUM_SAMPLES];
int choice = 0;
int cnt;

void ADC_DMA_Resumption(ADC12_Regs * adc12,DMA_Regs *dma,uint8_t channelNum, uint16_t* Destination,uint16_t cnt);
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
    uint16_t adcResult0;         // adcChannel0转换结果（12bit，数字量）
    uint16_t adcResult1;         // adcChannel1转换结果（12bit，数字量）
    float adcResult_voltage0;    // adc0转换结果对应的电压值（单位:mV）
    float adcResult_voltage1;    // adc1转换结果对应的电压值（单位:mV） 

    /* 系统初始化 */
    SYSCFG_DL_init();
    
    //通信初始化
	NVIC_ClearPendingIRQ(UART_0_INST_INT_IRQN );//清除中断标志??
    NVIC_EnableIRQ(UART_0_INST_INT_IRQN );
    
    /* 开启 adc 中断 */
    NVIC_EnableIRQ(ADC12_0_INST_INT_IRQN);
    ADC_DMA_Resumption(ADC12_0_INST,DMA,DMA_CH0_CHAN_ID,(uint16_t*)&ADC_sig[0],NUM_SAMPLES);

    OLED_Init();
    OLED_Clear();
    OLED_ShowString(0, 0, "ADC0val:");
    OLED_ShowString(0, 2, "v0:");
    OLED_ShowString(0, 4, "ADC1val:");
    OLED_ShowString(0, 6, "v1:");
    OLED_ShowString(104, 2, "mV");
    OLED_ShowString(104, 6, "mV");
    

    /* 变量初始化 */
    gCheckADC = false;
    /* 启动adc转换 */
    
    // /* 确保内部参考电压在adc转换前已完成配置 */
    // while (DL_VREF_CTL1_READY_NOTRDY == DL_VREF_getStatus(VREF));

    /* 等待adc转换完成 */
//    while (false == gCheckADC){
//        /* 进入低功耗模式 wait for event */
//        __WFE();
//    }

    while (1){
        /* 根据公式计算对应的电压值，参考电压3.3V（sysconfig里设置） */
        int k = 0;
        for(uint16_t i = 0; i < NUM_SAMPLES * 2 - 1;i += 2){
            complex_input0[k++] = (ADC_sig[i + 1]) * 3300 / 4096;
            complex_input1[k++] =(ADC_sig[i]) * 3300 / 4096;
        }
        /* 在OLED上显示采样值 */
        OLED_ShowNum(72, 0, complex_input0[0], 4, 16);
        //OLED_ShowNum(72, 2, (uint16_t)adcResult_voltage0, 4, 16);
        OLED_ShowNum(72, 4, complex_input1[0], 4, 16);
        //OLED_ShowNum(72, 6, (uint16_t)adcResult_voltage1, 4, 16);

        int num  =getKeyValue();

       // OLED_ShowNum(0,6,num,2,16);
        
        UART_Send((uint8_t*)&complex_input0[0]);                //发送ADC数据
        UART_Send((uint8_t*)&complex_input1[0]);                //发送ADC数据
        /* 控制大概0.2s更新一次 */
        delay_cycles(32000000 * 0.2);

        /* 准备下一次采样 */
        gCheckADC = false;
        
        ADC_DMA_Resumption(ADC12_0_INST,DMA,DMA_CH0_CHAN_ID,(uint16_t*)&ADC_sig[0],NUM_SAMPLES);
        delay_cycles(320000);
    }
}

//通信接受中断函数
void  UART_0_INST_IRQHandlerD(){
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
        case DL_ADC12_IIDX_DMA_DONE://DMA完成中断
            DMA_done = true;
		    cnt++;
            break;
        default:
            break;
    }
}
void ADC_DMA_Resumption(ADC12_Regs * adc12,DMA_Regs *dma,uint8_t channelNum, uint16_t* Destination,uint16_t cnt){
        DL_ADC12_startConversion(adc12);
        DL_ADC12_enableDMA(adc12);
		DL_DMA_setSrcAddr(dma,channelNum,DL_ADC12_getFIFOAddress(adc12));
        DL_DMA_setDestAddr(dma,channelNum,(uint32_t)&Destination[0]);
        DL_DMA_setTransferSize(dma,channelNum,cnt);
        DL_DMA_enableChannel(dma,channelNum);
        DL_ADC12_startConversion(adc12);
}
