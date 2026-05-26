#include "ti_msp_dl_config.h"

int main(void)
{
    SYSCFG_DL_init();                      //Sysconfig初始化
	int timer = 32000000;
	int hz_16 = 16,hz_4 =4,hz_2 =2,hz_1 =1,base = 0;
	
	int temp = 10,n ;
    while(1){
		int i = 0,a[4]={0},
		//闪烁四个不同频率
//			DL_Common_delayCycles(timer/hz_16);
//			base += (timer/hz_16);
//			
//			if(base%(timer/hz_16)==0)
//				DL_GPIO_togglePins(LED_PORT,LED_L0_PIN);			 
//			if(base%(timer/hz_4)==0)
//				DL_GPIO_togglePins(LED_PORT,LED_L1_PIN);
//			if(base%(timer/hz_2)==0)
//				DL_GPIO_togglePins(LED_PORT,LED_L2_PIN);
//			if(base%(timer/hz_1)==0)
//				DL_GPIO_togglePins(LED_PORT,LED_L3_PIN);
//			if(base%(hz_1*4))base = 0;
		
		//改变时钟频率
//			DL_GPIO_setPins(LED_PORT,LED_L3_PIN);
//			DL_Common_delayCycles(32000);
//			DL_GPIO_clearPins(LED_PORT,LED_L3_PIN);
//			DL_Common_delayCycles(32000);
//	if(DL_GPIO_readPins(KEY_PORT,KEY_S1_PIN)==0)DL_SYSCTL_switchMCLKfromSYSOSCtoLFCLK(0);
//	if(DL_GPIO_readPins(KEY_PORT,KEY_S1_PIN)!=0)DL_SYSCTL_switchMCLKfromLFCLKtoSYSOSC();

		//	倒计时系统
		n = temp;
		while (n>0){
			a[i] = n % 2;
			i = i + 1;
			n = n / 2;
		}
		
		DL_GPIO_setPins(LED_PORT, LED_L3_PIN);
		DL_GPIO_setPins(LED_PORT, LED_L2_PIN);
		DL_GPIO_setPins(LED_PORT, LED_L1_PIN);
		DL_GPIO_setPins(LED_PORT, LED_L0_PIN);
		
		if(a[0])DL_GPIO_clearPins(LED_PORT, LED_L3_PIN);
		if(a[1])DL_GPIO_clearPins(LED_PORT, LED_L2_PIN);
		if(a[2])DL_GPIO_clearPins(LED_PORT, LED_L1_PIN);
		if(a[3])DL_GPIO_clearPins(LED_PORT, LED_L0_PIN);
		
		DL_Common_delayCycles(32000000);
		
		temp--;
   }
}



//底板上的红色LED和核心板上的蓝色LED交替闪烁