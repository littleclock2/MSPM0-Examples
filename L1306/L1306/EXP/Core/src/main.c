#include "ti_msp_dl_config.h"

int main(void)
{
    SYSCFG_DL_init();                      //Sysconfig初始化
	
    while(1)
		{
        DL_GPIO_clearPins(LED_PORT,LED_L0_PIN);
			  for(uint32_t i=0 ; i<0X0000FFFF ; i++){}//软件延时
        DL_GPIO_setPins(LED_PORT,LED_L0_PIN);
				DL_GPIO_clearPins(LED_PORT,LED_L1_PIN);
			  for(uint32_t i=0 ; i<0X0000FFFF ; i++){}
				DL_GPIO_setPins(LED_PORT,LED_L1_PIN);
				DL_GPIO_clearPins(LED_PORT,LED_L2_PIN);
			  for(uint32_t i=0 ; i<0X0000FFFF ; i++){}
        DL_GPIO_setPins(LED_PORT,LED_L2_PIN);
				DL_Common_delayCycles(32000000);
   }
}



//底板上的红色LED和核心板上的蓝色LED交替闪烁