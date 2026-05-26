#include "ti_msp_dl_config.h"


void delay_ms(unsigned int ms);

#define BreathingPace 2   // unit: %
#define BreathingChangingIntervals 25//unit: ms
#define MAXDuty 90
#define MINDuty 10
const int SetPeriodCount = 1000;
int nowPWMCount = 900;
int duty;
int modePWM = 1;
int BuzzerCount = 0;

void Buzzer();
//该例程需要调整编译器的版本为ARMv6.21
//需通过杜邦线将PA3与板子上的蜂鸣器接口连接，详情请看图片
int main(void){
    SYSCFG_DL_init();                      //Sysconfig初始化
	
	NVIC_EnableIRQ(PWM_0_INST_INT_IRQN);
	
	DL_TimerG_startCounter(PWM_0_INST);
    while(1){
//		duty = (SetPeriodCount - nowPWMCount)*100 / SetPeriodCount;
//		if (duty <= MINDuty) modePWM = 1,delay_ms(500);
//		else if (duty >=MAXDuty) modePWM = 0,delay_ms(500);
//		if (modePWM) {
//			nowPWMCount -= BreathingPace * SetPeriodCount /100;
//			duty +=BreathingPace;
//			delay_ms(BreathingChangingIntervals);
//		}
//		if (!modePWM){
//			nowPWMCount += BreathingPace * SetPeriodCount /100;
//			duty -=BreathingPace;
//			delay_ms(BreathingChangingIntervals);
//		}
//		DL_TimerG_setCaptureCompareValue(PWM_0_INST,nowPWMCount,DL_TIMER_CC_0_INDEX);
//		//32000000
//		BuzzerCount++;
//		if(BuzzerCount%5==0){
//			DL_Timer_setLoadValue(PWM_0_INST, (2000 - (uint32_t) 1));//32000000/2000 = 16000Hz
//		}
//		else if (BuzzerCount%7==0){
//			DL_Timer_setLoadValue(PWM_0_INST, (5000 - (uint32_t) 1));//32000000/5000 = 6400Hz
//		}
//		else if (BuzzerCount%12==0){
//			DL_Timer_setLoadValue(PWM_0_INST, (1000 - (uint32_t) 1));
//		}
		Buzzer();
   }
}
void Buzzer(){
	duty = (SetPeriodCount - nowPWMCount)*100 / SetPeriodCount;
		if (duty <= MINDuty) modePWM = 1,delay_ms(500);
		else if (duty >=MAXDuty) modePWM = 0,delay_ms(500);
		if (modePWM) {
			nowPWMCount -= BreathingPace * SetPeriodCount /100;
			duty +=BreathingPace;
			delay_ms(BreathingChangingIntervals);
		}
		if (!modePWM){
			nowPWMCount += BreathingPace * SetPeriodCount /100;
			duty -=BreathingPace;
			delay_ms(BreathingChangingIntervals);
		}
		DL_TimerG_setCaptureCompareValue(PWM_0_INST,nowPWMCount,DL_TIMER_CC_0_INDEX);
		//32000000
		BuzzerCount++;
		if(BuzzerCount%5==0){
			DL_Timer_setLoadValue(PWM_0_INST, (2000 - (uint32_t) 1));//32000000/2000 = 16000Hz
		}
		else if (BuzzerCount%7==0){
			DL_Timer_setLoadValue(PWM_0_INST, (5000 - (uint32_t) 1));//32000000/5000 = 6400Hz
		}
		else if (BuzzerCount%12==0){
			DL_Timer_setLoadValue(PWM_0_INST, (1000 - (uint32_t) 1));
		}
}

unsigned int utick = 0;

void SysTick_Handler()
{
	SysTick->CTRL &= ~(1<<16);
	utick++;
}

void delay_ms(unsigned int ms)
{
	unsigned int tick = utick;
	while(utick < (tick + ms));
}