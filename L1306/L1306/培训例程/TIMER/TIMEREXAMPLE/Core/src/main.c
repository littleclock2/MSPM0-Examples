#include "ti_msp_dl_config.h"







int main(void)
{
    SYSCFG_DL_init();                      //Sysconfig
		DL_TimerG_startCounter(TIMER_0_INST);
		NVIC_EnableIRQ(TIMER_0_INST_INT_IRQN);
		DL_TimerG_startCounter(PWM_0_INST);
		DL_TimerG_setCaptureCompareValue(PWM_0_INST, 250,DL_TIMERG_CAPTURE_COMPARE_0_INDEX);
		DL_TimerG_setCaptureCompareValue(PWM_0_INST, 750,DL_TIMERG_CAPTURE_COMPARE_1_INDEX);
    while(1)
		{
			
		}
}
void TIMER_0_INST_IRQHandler (void){
	
		DL_GPIO_togglePins(Demo_PORT, Demo_LED_PIN);
	
}