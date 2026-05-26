#include "ti_msp_dl_config.h"

int main(void)
{
    SYSCFG_DL_init();                      //Sysconfig初始化
    while(1)
		{
        DL_GPIO_clearPins(Demo_PORT,Demo_LED_PIN);//点亮LED
				delay_cycles(32000000);//32MHz的时候，32000000为1s  DL_Common_delayCycles(22333);			
        DL_GPIO_setPins(Demo_PORT,Demo_LED_PIN);
			  delay_cycles(32000000);//32MHz的时候，32000000为1s
   }
}