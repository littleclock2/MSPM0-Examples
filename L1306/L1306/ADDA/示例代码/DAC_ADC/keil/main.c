//此项目可实现ADC通道0读取外接信号，DA产生指定信号、ADC内部通道12读取核心板产生的DA信号
//ADC通道0对应管脚PA27
//DA输出对应管脚PA16
#include "ti_msp_dl_config.h"
#define COMP_0_INST_REF_VOLTAGE_mV (3300)//代表参考电压,其值为3300mV
#define COMP_0_INST_DAC8_OUTPUT_VOLTAGE_mV (800)//设置初始直流输出电压值
volatile bool gCheckADC;//用于判断ADC是否就绪的标志
volatile uint16_t gAdcResult;
uint16_t adcData[100]={0};//存储ADC通道0读取的数据
int j=0;
int k=0;
int i=0;
uint32_t data[20]={50,65,79,90,98,100,98,90,79,65,50,35,21,10,2,0,2,10,21,35};//DA需要输出的数据
int main(void)
{
	uint32_t dacValue;
	
    SYSCFG_DL_init();//初始化
	
    NVIC_EnableIRQ(TIMER_0_INST_INT_IRQN);//定时器中断使能
    DL_TimerG_startCounter(TIMER_0_INST);//定时器开始计数
	
    NVIC_EnableIRQ(ADC12_0_INST_INT_IRQN);//ADC中断使能
	
    gCheckADC = false;
	
    DL_COMP_enable(COMP_0_INST);//比较器与AD模块启动
    DL_ADC12_startConversion(ADC12_0_INST);//ADC开始转换
	
    dacValue = (COMP_0_INST_DAC8_OUTPUT_VOLTAGE_mV * 255) /COMP_0_INST_REF_VOLTAGE_mV;//计算输出的直流电压值对应的DACCode0
	
	DL_COMP_setDACCode0(COMP_0_INST, dacValue);//写入dacValue
        while (false == gCheckADC) {
            __WFE();
        }
    while (1) {
       gAdcResult = DL_ADC12_getMemResult(ADC12_0_INST, DL_ADC12_MEM_IDX_0);//检测PA27引脚的输入电压，实现灯的亮与灭
        if (gAdcResult > 0xff) //设置判定阈值，高于则亮灯，低于则灭灯，理论阈值为3.3*0xff/0xfff=3.3/16=2.06V
				{
            DL_GPIO_clearPins(A_PORT, A_PIN_8_PIN);
        } else {
            DL_GPIO_setPins(A_PORT, A_PIN_8_PIN);
        }
                             
    }
}

void ADC12_0_INST_IRQHandler(void)//ADC的中断函数
{
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
void TIMER_0_INST_IRQHandler(void)//定时器的中断函数
{
    switch (DL_TimerG_getPendingInterrupt(TIMER_0_INST)) 
			{
        case DL_TIMER_IIDX_ZERO://如果走完定时器的一个技术周期，则更改DACode0，实现DA输出电压的更改
					DL_GPIO_togglePins(PA_PORT,PA_PIN_9_PIN);
				  DL_COMP_setDACCode0(COMP_0_INST, data[i]);
				  i++;
				  i=i%20;			
            break;
        default:
            break;
    }
}