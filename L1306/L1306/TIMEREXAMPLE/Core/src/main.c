#include "ti_msp_dl_config.h"
int count = 0,i = 0;
int main(void)
{
    SYSCFG_DL_init();                      //Sysconfig
	DL_TimerG_startCounter(TIMER_0_INST);//启动计时器
	
	NVIC_EnableIRQ(TIMER_0_INST_INT_IRQN);//中断函数启动
	NVIC_EnableIRQ(PWM_0_INST_INT_IRQN );//PWM_0_INST中断
	DL_TimerG_startCounter(PWM_0_INST);//pwm启动
	//设置两个频道的占空比
	DL_TimerG_setCaptureCompareValue(PWM_0_INST, 100,DL_TIMERG_CAPTURE_COMPARE_0_INDEX);
	DL_TimerG_setCaptureCompareValue(PWM_0_INST, 750,DL_TIMERG_CAPTURE_COMPARE_1_INDEX);
    while(1)
		{
			
		}
}
void TIMER_0_INST_IRQHandler (void){//中断后执行的函数
	switch(DL_TimerG_getPendingInterrupt (TIMER_0_INST)){
		case DL_TIMERG_IIDX_ZERO:
			count++;
			if(i==0&&count%4==0){
				DL_GPIO_togglePins(Demo_PORT, Demo_LED_PIN);
				i = 1;
			}
			else if(i==1&&count%4==0){
				DL_GPIO_togglePins(Demo_PORT, Demo_LED_PIN);
				i = 0;
			}	
			break;
		default:
			break;
	}
}
void PWM_0_INST_IRQHandler (void){//中断后执行的函数
	
		DL_GPIO_togglePins(Demo_PORT, Demo_LED_PIN);
	
}