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
 * @harfware   Template-DAC-ADC
 * @version     v1.0
 * @date        29-July-2024
 * @author      YunSword
 
*/


#include "ti_msp_dl_config.h"
#include "oled_spi.h"
#include "key.h"

#define COMP_0_INST_REF_VOLTAGE_mV (3300)//代表参考电压,其值为3300mV
#define COMP_0_INST_DAC8_OUTPUT_VOLTAGE_mV (800)//设置初始直流输出电压值
uint8_t choice  =0;
volatile bool gCheckADC;//用于判断ADC是否就绪的标志
volatile uint16_t gAdcResult=0;
uint16_t adcData[100]={0};//存储ADC通道0读取的数据
int j=0;
int k=0;
int i=0;
uint32_t data[20]={10,20,30,40,50,60,70,80,90,100,90,80,70,60,50,40,30,20,10,0};//DA需要输出的数据
int main(void){
	uint32_t dacValue;
    
    SYSCFG_DL_init();//初始化
    
    NVIC_EnableIRQ(TIMER_0_INST_INT_IRQN);//定时器中断使能
    DL_TimerG_startCounter(TIMER_0_INST);//定时器开始计数
    
    //通信初始化
	NVIC_ClearPendingIRQ(UART_0_INST_INT_IRQN );//清除中断标志??
    NVIC_EnableIRQ(UART_0_INST_INT_IRQN );
    
    //OLED_Init();
    //OLED_Clear();
    
    NVIC_EnableIRQ(ADC12_0_INST_INT_IRQN);//ADC中断使能
    
    gCheckADC = false;
    
    DL_COMP_enable(COMP_0_INST);//比较器与AD模块启动
    DL_ADC12_startConversion(ADC12_0_INST);//ADC开始转换
    
    dacValue = (COMP_0_INST_DAC8_OUTPUT_VOLTAGE_mV * 255) /COMP_0_INST_REF_VOLTAGE_mV;//计算输出的直流电压值对应的DACCode0
    
    DL_COMP_setDACCode0(COMP_0_INST, dacValue);//写入dacValue
    
    while (false == gCheckADC) {
        __WFE();
    }
    
    while (1){
        gAdcResult = DL_ADC12_getMemResult(ADC12_0_INST, DL_ADC12_MEM_IDX_0);//检测PA27引脚的输入电压，实现灯的亮与灭
        //OLED_ShowNum(2,4,gAdcResult,4,16);
        if(gAdcResult > 0xff){ //设置判定阈值，高于则亮灯，低于则灭灯，理论阈值为3.3*0xff/0xfff=3.3/16=2.06V
            DL_GPIO_clearPins(A_PORT, A_PIN_2_PIN);
        } 
        else {
            DL_GPIO_setPins(A_PORT, A_PIN_2_PIN);
        }                      
    }
}

void ADC12_0_INST_IRQHandler(void){//ADC的中断函数

    switch (DL_ADC12_getPendingInterrupt(ADC12_0_INST)) {
        case DL_ADC12_IIDX_MEM0_RESULT_LOADED://如果MEM0（对应通道0）中有数据写入，则存储其数据进入数组adcdata
            gCheckADC = true;	
			      adcData[j]=DL_ADC12_getMemResult(ADC12_0_INST, DL_ADC12_MEM_IDX_0);
			      j++;
			      j=j%100;
            break;
        default:
            break;
    }
}
void TIMER_0_INST_IRQHandler(void){//定时器的中断函数
    switch (DL_TimerG_getPendingInterrupt(TIMER_0_INST)) {
        case DL_TIMER_IIDX_ZERO://如果走完定时器的一个技术周期，则更改DACode0，实现DA输出电压的更改
				  DL_COMP_setDACCode0(COMP_0_INST, data[i]);
                    //OLED_ShowNum(2,6,data[i],2,16);
				  i++;
				  i=i%20;			
            break;
        default:
            break;
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


