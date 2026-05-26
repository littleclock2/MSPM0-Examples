#include "ti_msp_dl_config.h"
void WaterFlood(){
		DL_GPIO_clearPins(LED_PORT,LED_L0_PIN);
		for(uint32_t i=0 ; i<0X0000FFFF ; i++){}//软件延时
    DL_GPIO_setPins(LED_PORT,LED_L0_PIN);
		for(uint32_t i=0 ; i<0X0000FFFF ; i++){}
				
		DL_GPIO_clearPins(LED_PORT,LED_L1_PIN);
		for(uint32_t i=0 ; i<0X0000FFFF ; i++){}//软件延时
    DL_GPIO_setPins(LED_PORT,LED_L1_PIN);
		for(uint32_t i=0 ; i<0X0000FFFF ; i++){}
					
		DL_GPIO_clearPins(LED_PORT,LED_L2_PIN);
		for(uint32_t i=0 ; i<0X0000FFFF ; i++){}//软件延时
    DL_GPIO_setPins(LED_PORT,LED_L2_PIN);
		for(uint32_t i=0 ; i<0X0000FFFF ; i++){}
					
		DL_GPIO_clearPins(LED_PORT,LED_L3_PIN);
		for(uint32_t i=0 ; i<0X0000FFFF ; i++){}//软件延时
		DL_GPIO_setPins(LED_PORT,LED_L3_PIN);
		for(uint32_t i=0 ; i<0X0000FFFF ; i++){}
					
		DL_GPIO_clearPins(LED_PORT,LED_L4_PIN);
		for(uint32_t i=0 ; i<0X0000FFFF ; i++){}//软件延时
		DL_GPIO_setPins(LED_PORT,LED_L4_PIN);
		for(uint32_t i=0 ; i<0X0000FFFF ; i++){}
					
		DL_GPIO_clearPins(LED_PORT,LED_L5_PIN);
		for(uint32_t i=0 ; i<0X0000FFFF ; i++){}//软件延时
    DL_GPIO_setPins(LED_PORT,LED_L5_PIN);
		for(uint32_t i=0 ; i<0X0000FFFF ; i++){}
					
		DL_GPIO_clearPins(LED_PORT,LED_L6_PIN);
		for(uint32_t i=0 ; i<0X0000FFFF ; i++){}//软件延时
    DL_GPIO_setPins(LED_PORT,LED_L6_PIN);
		for(uint32_t i=0 ; i<0X0000FFFF ; i++){}
					
		DL_GPIO_clearPins(LED_PORT,LED_L7_PIN);
		for(uint32_t i=0 ; i<0X0000FFFF ; i++){}//软件延时
    DL_GPIO_setPins(LED_PORT,LED_L7_PIN);
		for(uint32_t i=0 ; i<0X0000FFFF ; i++){}
}
void MinusWaterFlood(){
		DL_GPIO_clearPins(LED_PORT,LED_L6_PIN);
		for(uint32_t i=0 ; i<0X0000FFFF ; i++){}//软件延时
    DL_GPIO_setPins(LED_PORT,LED_L6_PIN);
		for(uint32_t i=0 ; i<0X0000FFFF ; i++){}
				
		DL_GPIO_clearPins(LED_PORT,LED_L5_PIN);
		for(uint32_t i=0 ; i<0X0000FFFF ; i++){}//软件延时
    DL_GPIO_setPins(LED_PORT,LED_L5_PIN);
		for(uint32_t i=0 ; i<0X0000FFFF ; i++){}
					
		DL_GPIO_clearPins(LED_PORT,LED_L4_PIN);
		for(uint32_t i=0 ; i<0X0000FFFF ; i++){}//软件延时
    DL_GPIO_setPins(LED_PORT,LED_L4_PIN);
		for(uint32_t i=0 ; i<0X0000FFFF ; i++){}
					
		DL_GPIO_clearPins(LED_PORT,LED_L3_PIN);
		for(uint32_t i=0 ; i<0X0000FFFF ; i++){}//软件延时
		DL_GPIO_setPins(LED_PORT,LED_L3_PIN);
		for(uint32_t i=0 ; i<0X0000FFFF ; i++){}
					
		DL_GPIO_clearPins(LED_PORT,LED_L2_PIN);
		for(uint32_t i=0 ; i<0X0000FFFF ; i++){}//软件延时
		DL_GPIO_setPins(LED_PORT,LED_L2_PIN);
		for(uint32_t i=0 ; i<0X0000FFFF ; i++){}
					
		DL_GPIO_clearPins(LED_PORT,LED_L1_PIN);
		for(uint32_t i=0 ; i<0X0000FFFF ; i++){}//软件延时
    DL_GPIO_setPins(LED_PORT,LED_L1_PIN);
		for(uint32_t i=0 ; i<0X0000FFFF ; i++){}
					
		DL_GPIO_clearPins(LED_PORT,LED_L0_PIN);
		for(uint32_t i=0 ; i<0X0000FFFF ; i++){}//软件延时
    DL_GPIO_setPins(LED_PORT,LED_L0_PIN);
		for(uint32_t i=0 ; i<0X0000FFFF ; i++){}

}

void Breath_LED2(){
		uint32_t T = 1600;
		uint32_t i = 0,m = 0,n = 0 ,t = 0;
	
		for(i = 0;i<T;i++){
				DL_GPIO_setPins(LED_PORT,LED_L1_PIN);
				for(m = 0;m<t;m++);
				DL_GPIO_clearPins(LED_PORT,LED_L1_PIN);
				for(n = 0;n<T-t;n++);
				t++;
		
				if(t>=T){
						for(i = 0;i<T;i++){
								DL_GPIO_setPins(LED_PORT,LED_L1_PIN);
								for(m = 0;m<t;m++);
								DL_GPIO_clearPins(LED_PORT,LED_L1_PIN);
								for(n = 0;n<T-t;n++);
								t--;
						}
				}
		}
}
void Breath_LED3(){
		uint32_t T = 1600;
		uint32_t i = 0,m = 0,n = 0 ,t = 0;
	//周期不断变化，调整占空比
		for(i = 0;i<T;i++){
				DL_GPIO_setPins(LED_PORT,LED_L2_PIN);
				for(m = 0;m<t;m++);
				DL_GPIO_clearPins(LED_PORT,LED_L2_PIN);
				for(n = 0;n<T-t;n++);
				t++;
		
				if(t>=T){
						for(i = 0;i<T;i++){
								DL_GPIO_setPins(LED_PORT,LED_L2_PIN);
								for(m = 0;m<t;m++);
								DL_GPIO_clearPins(LED_PORT,LED_L2_PIN);
								for(n = 0;n<T-t;n++);
								t--;
						}
				}
		}
}
int main(void)
{
    SYSCFG_DL_init();                      //Sysconfig初始化
		while(1){//不断循环
				Breath_LED3();
				DL_Common_delayCycles(32000000);
				Breath_LED2();
				DL_Common_delayCycles(32000000);
				WaterFlood();
				DL_Common_delayCycles(32000000);
				MinusWaterFlood();
				DL_Common_delayCycles(32000000);
   }
}
