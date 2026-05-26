

#include "ti_msp_dl_config.h"
volatile uint16_t ADC_Result;
volatile bool gCheckADC;

void UART_Send(uint8_t *Data_Temp)
{
	uint8_t i;

	for(i=0;i<2;i++)
	{
		DL_UART_transmitData(UART0,*(Data_Temp+1));
		while(DL_UART_isTXFIFOFull(UART0))
		{
			
		}
		Data_Temp--;
	}
	
}

int main(void)
{
    SYSCFG_DL_init();                      //Sysconfig初始化
	NVIC_EnableIRQ(ADC0_INT_IRQn);         //使能ADC中断
	gCheckADC = false;                     //初始化ADC转换结束标志位
    while (1){
		DL_ADC12_startConversion(ADC12_0_INST);  //ADC转换开始
		while (false == gCheckADC)               //等待转换结束
		{}
		ADC_Result = DL_ADC12_getMemResult(ADC12_0_INST, DL_ADC12_MEM_IDX_0);  //读取ADC值                                      
		UART_Send((uint8_t*)&ADC_Result);                //发送ADC数据
//		Serial_SendNumber((uint8_t*)&ADC_Result,4);
		gCheckADC = false;					//清除ADC转换结束标志位
		delay_cycles(32000000);                           //延迟1秒
		DL_ADC12_enableConversions(ADC12_0_INST);		      //ADC单次转换模式下结束后会关闭ADC，需要再次打开ADC
    }
}



void ADC12_0_INST_IRQHandler(void)            //ADC中断函数
{
    switch (DL_ADC12_getPendingInterrupt(ADC12_0_INST)) //检查并清中断标志
		{    
        case DL_ADC12_IIDX_MEM0_RESULT_LOADED:        
            gCheckADC =true;                  //置位ADC转换结束标志
            break;
        default:
            break;
    }
}
