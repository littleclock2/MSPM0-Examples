#include "ti_msp_dl_config.h"

int main(void)
{
    SYSCFG_DL_init(); // Initialize the device
    while(1)
		{
        if(DL_GPIO_readPins(Switch_PORT, Switch_S1_PIN))
        {
            DL_GPIO_setPins(LED_PORT,LED_BLUE_PIN);
        }
        else
        {
            DL_GPIO_clearPins(LED_PORT,LED_BLUE_PIN);
        }
    }
}