#include "ti_msp_dl_config.h"
volatile uint16_t ADC_Result[10];
volatile bool gCheckADC;

int main(void)
{
    SYSCFG_DL_init();                      //Sysconfig初始化
		NVIC_EnableIRQ(ADC0_INT_IRQn);         //使能ADC中断
		gCheckADC = false;                     //初始化ADC转换结束标志
		DL_DMA_setSrcAddr(DMA, DMA_CH0_CHAN_ID,(uint32_t) &ADC0->ULLMEM.MEMRES[0]);  //配置源地址，非FIFO模式，DMA直接从结果寄存器中搬运数据
    DL_DMA_setDestAddr(DMA, DMA_CH0_CHAN_ID, (uint32_t) &ADC_Result[0]);       //配置目标地址
    DL_DMA_setTransferSize(DMA, DMA_CH0_CHAN_ID, 10);                          //配置DMA传输次数，教程所用的SYSCONIFG版本无法生成初始化代码，这里手动设置
    DL_DMA_enableChannel(DMA, DMA_CH0_CHAN_ID);                               //使能DMA
		DL_ADC12_startConversion(ADC12_0_INST);                                   //开启ADC转换
	  while (false == gCheckADC)                                     //等待转换完成
		{

    }
		__BKPT(0);
    while (1) 
		{
	
    }
}

void ADC12_0_INST_IRQHandler(void)           //ADC中断函数
{
    switch (DL_ADC12_getPendingInterrupt(ADC12_0_INST))   //查询并清除ADC中断
		{
        case DL_ADC12_IIDX_DMA_DONE:                      //检查是否是DMA完成中断
            gCheckADC = true;                //置位ADC转换结束标志
            break;
        default:
            break;
    }
}
