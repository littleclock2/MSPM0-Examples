#include "ti_msp_dl_config.h"

int main(void){
    SYSCFG_DL_init();                      //Sysconfig初始化
	
    while(1){
		int temp = 0,choice,a = 0,b = 0,c =0;
		DL_GPIO_setPins(LED_PORT, LED_L2_PIN);
		DL_GPIO_setPins(LED_PORT, LED_L1_PIN);
		DL_GPIO_setPins(LED_PORT, LED_L0_PIN);
		DL_GPIO_setPins(LED_PORT, LED_L3_PIN);
		DL_GPIO_setPins(LED_PORT, LED_L4_PIN);
		DL_GPIO_setPins(LED_PORT, LED_L5_PIN);
		DL_GPIO_setPins(LED_PORT, LED_L6_PIN);
		DL_GPIO_setPins(LED_PORT, LED_L7_PIN);
        if(DL_GPIO_readPins(KEY_PORT,KEY_SW1_PIN)==0)a= 1;
		if(DL_GPIO_readPins(KEY_PORT,KEY_SW2_PIN)==0)b= 1;
		if(DL_GPIO_readPins(KEY_PORT,KEY_SW3_PIN)==0)c= 1;
		
		choice = 4*a + 2*b +c*1;
		switch(choice){
			case 0:
				DL_GPIO_clearPins(LED_PORT, LED_L0_PIN);
				break;
			case 1:
				DL_GPIO_clearPins(LED_PORT, LED_L1_PIN);
				break;
			case 2:
				DL_GPIO_clearPins(LED_PORT, LED_L2_PIN);
				break;
			case 3:
				DL_GPIO_clearPins(LED_PORT, LED_L3_PIN);
				break;
			case 4:
				DL_GPIO_clearPins(LED_PORT, LED_L4_PIN);
				break;
			case 5:
				DL_GPIO_clearPins(LED_PORT, LED_L5_PIN);
				break;
			case 6:
				DL_GPIO_clearPins(LED_PORT, LED_L6_PIN);
				break;
			case 7:
				DL_GPIO_clearPins(LED_PORT, LED_L7_PIN);
				break;
		}
	}
}
//底板上的红色LED和核心板上的蓝色LED交替闪烁