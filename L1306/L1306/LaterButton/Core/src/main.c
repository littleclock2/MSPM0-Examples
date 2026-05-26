#include "ti_msp_dl_config.h"

int main(void)
{
    SYSCFG_DL_init();                      //Sysconfig初始化
	
    while(1){
		DL_GPIO_setPins(LED_PORT,LED_L0_PIN);	
		DL_GPIO_setPins(LED_PORT,LED_L1_PIN);
		DL_GPIO_setPins(LED_PORT,LED_L2_PIN);
        if(DL_GPIO_readPins(USERBUTTON_PORT,USERBUTTON_U1_PIN)==0){
			DL_Common_delayCycles(32000);
			if(DL_GPIO_readPins(USERBUTTON_PORT,USERBUTTON_U1_PIN)==0)DL_GPIO_clearPins(LED_PORT,LED_L0_PIN);
		}
   }
}



