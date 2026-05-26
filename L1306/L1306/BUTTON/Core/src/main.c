#include "ti_msp_dl_config.h"
int temp = 0;
void SetPins(uint32_t input){
		DL_GPIO_setPins(Switch_PORT, Switch_H1_PIN);
		DL_GPIO_setPins(Switch_PORT, Switch_H2_PIN);
		DL_GPIO_setPins(Switch_PORT, Switch_H3_PIN);
		DL_GPIO_setPins(Switch_PORT, Switch_H4_PIN);
		switch(input){
			case Switch_H1_PIN:
					DL_GPIO_clearPins(Switch_PORT, Switch_H1_PIN);
					break;
			case Switch_H2_PIN:
					DL_GPIO_clearPins(Switch_PORT, Switch_H2_PIN);
					break;
			case Switch_H3_PIN:
					DL_GPIO_clearPins(Switch_PORT, Switch_H3_PIN);
					break;
			case Switch_H4_PIN:
					DL_GPIO_clearPins(Switch_PORT, Switch_H4_PIN);
					break;
		}
}
void CheckPins(uint32_t input){
	if(DL_GPIO_readPins(Switch_PORT, Switch_V1_PIN)==0){
		switch(input){
			case Switch_H1_PIN:
					temp = 10000;
					break;
			case Switch_H2_PIN:
					temp = 10001;
					break;
			case Switch_H3_PIN:
					temp = 10010;
					break;
			case Switch_H4_PIN:
					temp = 10011;
					break;
		}
	}
	else if(DL_GPIO_readPins(Switch_PORT, Switch_V2_PIN)==0){
		switch(input){
			case Switch_H1_PIN:
					temp = 10100;
					break;
			case Switch_H2_PIN:
					temp = 10101;
					break;
			case Switch_H3_PIN:
					temp = 10110;
					break;
			case Switch_H4_PIN:
					temp = 10111 ;
					break;
		}
	}
	else if(DL_GPIO_readPins(Switch_PORT, Switch_V3_PIN)==0){
		switch(input){
			case Switch_H1_PIN:
					temp = 11000;
					break;
			case Switch_H2_PIN:
					temp = 11001;
					break;
			case Switch_H3_PIN:
					temp = 11010;
					break;
			case Switch_H4_PIN:
					temp = 11011;
					break;
		}
	}
	else if(DL_GPIO_readPins(Switch_PORT, Switch_V4_PIN)==0){
		switch(input){
			case Switch_H1_PIN:
					temp = 11100;
					break;
			case Switch_H2_PIN:
					temp = 11101;
					break;
			case Switch_H3_PIN:
					temp = 11110;
					break;
			case Switch_H4_PIN:
					temp = 11111;
					break;
		}
	}
}
void Breath(int time){
		uint32_t T = time;
		uint32_t i = 0,m = 0,n = 0 ,t = 0;
	
		for(i = 0;i<T;i++){
				DL_GPIO_setPins(LED_PORT,LED_L1_PIN);
				for(m = 0;m<t;m++);
				DL_GPIO_setPins(LED_PORT,LED_L1_PIN);
				for(n = 0;n<T-t;n++);
				t++;
		
				if(t>=T){
						for(i = 0;i<T;i++){
								DL_GPIO_setPins(LED_PORT,LED_L1_PIN);
								for(m = 0;m<t;m++);
								DL_GPIO_setPins(LED_PORT,LED_L1_PIN);
								for(n = 0;n<T-t;n++);
								t--;
						}
				}
		}
}
int main(void)
{	
	int a = 0,b = 0,c = 0,d =0;
    SYSCFG_DL_init(); // Initialize the device
	
		
    while(1){
		SetPins(Switch_H1_PIN);
		DL_Common_delayCycles(32000);
		CheckPins(Switch_H1_PIN);
		
		SetPins(Switch_H2_PIN);
		DL_Common_delayCycles(32000);
		CheckPins(Switch_H2_PIN);
		
		SetPins(Switch_H3_PIN);
		DL_Common_delayCycles(32000);
		CheckPins(Switch_H3_PIN);
		
		SetPins(Switch_H4_PIN);
		DL_Common_delayCycles(32000);
		CheckPins(Switch_H4_PIN);
		d = temp%10;
		c = (temp/10)%2;
		b = (temp/100)%10;
		a = (temp/1000)%10;
		DL_GPIO_setPins(LED_PORT, LED_L7_PIN);
		DL_GPIO_setPins(LED_PORT, LED_L6_PIN);
		DL_GPIO_setPins(LED_PORT, LED_L5_PIN);
		DL_GPIO_setPins(LED_PORT, LED_L4_PIN);
		DL_GPIO_setPins(LED_PORT, LED_L3_PIN);
		DL_GPIO_setPins(LED_PORT, LED_L2_PIN);
		DL_GPIO_setPins(LED_PORT, LED_L1_PIN);
		DL_GPIO_setPins(LED_PORT, LED_L0_PIN);
		if(d)DL_GPIO_clearPins(LED_PORT, LED_L3_PIN);
		if(c)DL_GPIO_clearPins(LED_PORT, LED_L2_PIN);
		if(b)DL_GPIO_clearPins(LED_PORT, LED_L1_PIN);
		if(a)DL_GPIO_clearPins(LED_PORT, LED_L0_PIN);
    }
}