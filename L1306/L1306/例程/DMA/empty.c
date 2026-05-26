

#include "ti_msp_dl_config.h"
uint8_t data;

int main(void)
{
	
   SYSCFG_DL_init();                      //Sysconfig初始化
	 DL_DMA_setSrcAddr(DMA, DMA_CH0_CHAN_ID,(uint32_t)&(UART1->RXDATA));  //配置源地址
   DL_DMA_setDestAddr(DMA, DMA_CH0_CHAN_ID,(uint32_t)&(UART1->TXDATA));       //配置目标地址
   DL_DMA_setTransferSize(DMA, DMA_CH0_CHAN_ID,1);                          //配置DMA传输次数
   DL_DMA_enableChannel(DMA, DMA_CH0_CHAN_ID);     //使能DMA 0通道
		
    while (1) 
		{ 
		
		
   }
}

