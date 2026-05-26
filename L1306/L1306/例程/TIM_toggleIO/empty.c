

#include "ti_msp_dl_config.h"


int main(void)
{
    SYSCFG_DL_init();                      //Sysconfig初始化
		NVIC_EnableIRQ(TIMG0_INT_IRQn);         //使能TIMG0中断
		DL_TimerG_startCounter(TIMG0);   //开启定时器
		while(1)
		{
			
		}
}




void TIMER_0_INST_IRQHandler()
{
	   switch (DL_TimerG_getPendingInterrupt(TIMG0))   //检查中断并清除中断标志位
		{
        case DL_TIMER_IIDX_ZERO:                            //如果是计数到0事件
            DL_GPIO_togglePins(GPIOA, DL_GPIO_PIN_14);       //翻转PA14
            break;
        default:
            break;
    }
}
