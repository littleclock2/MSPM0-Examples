//#include "ti_msp_dl_config.h"


//void delay_ms(unsigned int ms);

//#define BreathingPace 2   // µ•Œª: %
//#define BreathingChangingIntervals 25//µ•Œª: ms
//#define MAXDuty 90
//#define MINDuty 10
//const int SetPeriodCount = 1000;//÷‹∆⁄ ±≥§
//int nowPWMCount = 900;//’ºø’±»
//int duty;//ºÏ≤‚±Í◊º
//int modePWM = 1;

//int main(void)
//{
//    SYSCFG_DL_init();                      //Sysconfig≥ı ºªØ
//	
//		NVIC_EnableIRQ(PWM_0_INST_INT_IRQN);
//	
////		DL_TimerG_startCounter(PWM_0_INST);//pwm∆Ù”√
//    while(1)
//		{
////		duty = (SetPeriodCount - nowPWMCount)*100 / SetPeriodCount;
//////			
////		if (duty <= MINDuty) modePWM = 1,delay_ms(500);
////		else if (duty >=MAXDuty) modePWM = 0,delay_ms(500);
////			
////		if (modePWM){
////			nowPWMCount -= BreathingPace * SetPeriodCount /100;
////			duty +=BreathingPace;
////			delay_ms(BreathingChangingIntervals);
////		}
////		if (!modePWM){
////			nowPWMCount += BreathingPace * SetPeriodCount /100;
////			duty -=BreathingPace;
////			delay_ms(BreathingChangingIntervals);
////		}
////		DL_TimerG_setCaptureCompareValue(PWM_0_INST,nowPWMCount,DL_TIMER_CC_0_INDEX);
//			
//   }
//}

////º∆ ±∆˜œµÕ≥∂®“ÂÜ
////unsigned int utick = 0;

////void SysTick_Handler()
////{
////	SysTick->CTRL &= ~(1<<16);
////	utick++;
////}

////void delay_ms(unsigned int ms)
////{
////	unsigned int tick = utick;
////	while(utick < (tick + ms));
////}