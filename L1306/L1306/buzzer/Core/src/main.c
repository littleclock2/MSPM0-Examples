#include "ti_msp_dl_config.h"
//无源蜂鸣器实验
//实现功能：蜂鸣器播放音乐《天空之城》，伴随LED灯闪烁


//定义把每个音符和频率值对应起来
#define NOTE_D0 100
#define NOTE_D1 294
#define NOTE_D2 330
#define NOTE_D3 350
#define NOTE_D4 393
#define NOTE_D5 441
#define NOTE_D6 495
#define NOTE_D7 556

#define NOTE_DL1 147
#define NOTE_DL2 165
#define NOTE_DL3 175
#define NOTE_DL4 196
#define NOTE_DL5 221
#define NOTE_DL6 248
#define NOTE_DL7 278

#define NOTE_DH1 589
#define NOTE_DH2 661
#define NOTE_DH3 700
#define NOTE_DH4 786
#define NOTE_DH5 882
#define NOTE_DH6 990
#define NOTE_DH7 112

//用英文对应拍子
#define WHOLE 1
#define HALF 0.5
#define QUARTER 0.25
#define EIGHTH 0.25
#define SIXTEENTH 0.625

//整首曲子的音符部分，用了一个序列定义为tune，整数
int tune[] =
{
  NOTE_D0, NOTE_D0, NOTE_D0, NOTE_D6, NOTE_D7, NOTE_DH1, NOTE_D7, NOTE_DH1, NOTE_DH3, NOTE_D7, NOTE_D7, NOTE_D7, NOTE_D3, NOTE_D3,
  NOTE_D6, NOTE_D5, NOTE_D6, NOTE_DH1, NOTE_D5, NOTE_D5, NOTE_D5, NOTE_D3, NOTE_D4, NOTE_D3, NOTE_D4, NOTE_DH1,NOTE_D3, NOTE_D3,
  NOTE_D0, NOTE_DH1,NOTE_DH1, NOTE_DH1, NOTE_D7, NOTE_D4, NOTE_D4, NOTE_D7, NOTE_D7,NOTE_D7, NOTE_D0, NOTE_D6, NOTE_D7,
  NOTE_DH1, NOTE_D7, NOTE_DH1, NOTE_DH3, NOTE_D7, NOTE_D7, NOTE_D7, NOTE_D3, NOTE_D3, NOTE_D6, NOTE_D5, NOTE_D6, NOTE_DH1,
  NOTE_D5, NOTE_D5, NOTE_D5, NOTE_D2, NOTE_D3, NOTE_D4, NOTE_DH1, NOTE_D7, NOTE_D7, NOTE_DH1, NOTE_DH1, NOTE_DH2, NOTE_DH2, 
  NOTE_DH3, NOTE_DH1, NOTE_DH1, NOTE_DH1,NOTE_DH1, NOTE_D7, NOTE_D6, NOTE_D6, NOTE_D7, NOTE_D5, NOTE_D6, NOTE_D6, NOTE_D6, 
  NOTE_DH1, NOTE_DH2, NOTE_DH3, NOTE_DH2, NOTE_DH3, NOTE_DH5,NOTE_DH2, NOTE_DH2, NOTE_DH2, NOTE_D5, NOTE_D5, NOTE_DH1, NOTE_D7, 
  NOTE_DH1, NOTE_DH3, NOTE_DH3, NOTE_DH3, NOTE_DH3, NOTE_DH3,NOTE_D6, NOTE_D7, NOTE_DH1, NOTE_D7, NOTE_DH2, NOTE_DH2, NOTE_DH1, 
  NOTE_D5, NOTE_D5, NOTE_D5, NOTE_DH4, NOTE_DH3, NOTE_DH2, NOTE_DH1,NOTE_DH3, NOTE_DH3, NOTE_DH3, NOTE_DH3, NOTE_DH6, NOTE_DH6, 
  NOTE_DH5, NOTE_DH5, NOTE_DH3, NOTE_DH2, NOTE_DH1, NOTE_DH1, NOTE_D0, NOTE_DH1,NOTE_DH2, NOTE_DH1, NOTE_DH2, NOTE_DH2, NOTE_DH5, 
  NOTE_DH3, NOTE_DH3, NOTE_DH3, NOTE_DH3, NOTE_DH6, NOTE_DH6, NOTE_DH5, NOTE_DH5,NOTE_DH3, NOTE_DH2, NOTE_DH1, NOTE_DH1, NOTE_D0, 
  NOTE_DH1, NOTE_DH2, NOTE_DH1, NOTE_DH2, NOTE_DH2, NOTE_D7, NOTE_D6, NOTE_D6, NOTE_D6, NOTE_D6, NOTE_D7
};

//整首曲子的节拍部分，也定义个序列duration，浮点（数组的个数和前面音符的个数是一样的，一一对应）
float duration[] =

{
  1, 1, 1, 0.5, 0.5,     1 + 0.5, 0.5, 1, 1,     1, 1, 1, 0.5, 0.5,
  1 + 0.5, 0.5, 1, 1,     1, 1, 1, 1,          1 + 0.5, 0.5, 1, 1,
  1, 1, 0.5, 0.5, 0.5, 0.5,    1 + 0.5, 0.5, 1, 1,     1, 1, 1, 0.5, 0.5,
  1 + 0.5, 0.5, 1, 1,    1, 1, 1, 0.5, 0.5,     1 + 0.5, 0.5, 1, 1,
  1, 1, 1, 0.5,     1, 0.5, 0.25, 0.25, 0.25, 0.5,    0.5, 0.5, 0.5, 0.25, 0.5, 1,
  0.5, 0.5, 0.5, 0.5, 1, 1,    1, 1, 1, 0.5, 0.5,    1 + 0.5, 0.5, 1, 1,
  1, 1, 1, 0.5, 0.5,    1.5, 0.5, 1, 1,    1, 1, 1, 1,
  0.5, 0.5, 1, 1, 0.5, 0.5,    1.5, 0.25, 0.5, 1,    1, 1, 1, 1,
  1, 1, 1, 1,    1, 1, 1, 1,    0.5, 0.5, 1, 1, 0.5, 0.5,
  1, 0.5, 0.5, 1, 1,    1, 1, 1, 1,    1, 1, 1, 1,
  0.5, 0.5, 1, 1, 0.5, 0.5,    1, 0.5, 0.25, 0.5, 1,    1, 1, 1, 0.5, 0.5
};

int length;//定义一个变量，表示共有多少个音符
int led = 10;//定义LED引脚
void delay_ms(unsigned int ms);
int main(void){
    SYSCFG_DL_init();  
	DL_TimerG_startCounter(PWM_0_INST);//pwm计数启动
    NVIC_EnableIRQ(PWM_0_INST_INT_IRQN);//pwm中断使能
	
    length = sizeof(tune) / sizeof(tune[0]); //这里用了一个sizeof函数， 可以查出tone序列里有多少个音符
    while(1){
		for(int i = 0;i<3;i++){
				DL_Timer_setLoadValue(PWM_0_INST, tune[7]);
				DL_TimerG_setCaptureCompareValue(PWM_0_INST, tune[7] / 2 ,DL_TIMER_CC_0_INDEX);
				delay_ms(1000);
				DL_TimerG_setCaptureCompareValue(PWM_0_INST, 0 ,DL_TIMER_CC_0_INDEX);
				delay_ms(2000);
			}
        for (int x = 0; x < length; ++x) {//循环音符的次数
            DL_Timer_setLoadValue(PWM_0_INST, tune[x]);
			DL_TimerG_setCaptureCompareValue(PWM_0_INST,tune[x]/2,DL_TIMER_CC_0_INDEX);
            //每个音符持续的时间，即节拍duration，调整时间的越大，曲子速度越慢，越小曲子速度越快，节奏可自行调整
            //停止当前音符，进入下一音符
			delay_ms(500*duration[x]);
        }	
		
    }
}
//延时函数
void delay_ms(unsigned int ms)
{                         
	unsigned int a;
	ms  *=10;
	while(ms)
	{
		a=360;
		while(a--);
		ms--;
	}
	return;
}
