#include "ti_msp_dl_config.h"

int main(void)
{
    SYSCFG_DL_init();                       //初始化
    NVIC_EnableIRQ(TIMG0_INT_IRQn);         //使能定时器中断                              
		DL_GPIO_setPins(GPIOA, DL_GPIO_PIN_14);  //LED指示
	  DL_TimerG_startCounter(TIMG0);          //定时器计数开始
		while (1) 
		{
      
    }
}

void TIMG0_IRQHandler(void)
{
    switch (DL_TimerG_getPendingInterrupt(TIMG0))   //检查并清除定时器中断标志
			{
        case DL_TIMER_IIDX_ZERO:                     //如果是定时器计数到0中断
					  DL_WWDT_restart(WWDT0);                  //喂狗
            DL_GPIO_togglePins(GPIOA, DL_GPIO_PIN_14);  //翻转IO
            break;
        default:
            break;
    }
}
