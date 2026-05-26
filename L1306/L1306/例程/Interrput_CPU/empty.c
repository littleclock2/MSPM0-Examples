

#include "ti_msp_dl_config.h"

int main(void)
{
	
   SYSCFG_DL_init();                      //Sysconfig初始化
	 NVIC_EnableIRQ( Demo_INT_IRQN );
		
    while (1) 
		{ 

			
		
   }
}

void GROUP1_IRQHandler()
{
	switch(DL_Interrupt_getPendingGroup(DL_INTERRUPT_GROUP_1))
	{
		case Demo_INT_IIDX:
			if(DL_GPIO_readPins(Demo_PORT,Demo_Key_PIN ))  //检查KEY是否被按下
			{
				DL_GPIO_setPins(Demo_PORT,Demo_LED_PIN );    //按下则点亮LED
			}
			else
			{
				DL_GPIO_clearPins(Demo_PORT,Demo_LED_PIN );  //否则熄灭LED
			}
		break;
			
	}
}