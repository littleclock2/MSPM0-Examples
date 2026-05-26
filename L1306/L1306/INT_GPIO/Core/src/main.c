#include "ti_msp_dl_config.h"

int main(void){
	int timer = 32000000;
	int hz_16 = 16,hz_4 =4,hz_2 =2,hz_1 =1,base = 0;
    SYSCFG_DL_init();  
	
	NVIC_EnableIRQ(SWITCH_INT_IRQN);
		
    while(1){		
		DL_Common_delayCycles(timer/hz_16);
		base += (timer/hz_16);
		
		if(base%(timer/hz_1)==0)DL_GPIO_togglePins(LED_PORT,LED_L0_PIN);
		if(base%(hz_1*4))base = 0;
   }
	
}
void GROUP1_IRQHandler(void){
	int timer = 32000000;
	int hz_16 = 16,hz_4 =4,hz_2 =2,hz_1 =1,base = 0;
	
	switch(DL_Interrupt_getPendingGroup (DL_INTERRUPT_GROUP_1)){
		case SWITCH_INT_IIDX:
			DL_GPIO_togglePins(LED_PORT,LED_L_CORE_PIN);
			DL_Common_delayCycles(3200000);
			 while(DL_GPIO_readPins(SWITCH_PORT ,SWITCH_SW1_PIN)){
				DL_Common_delayCycles(timer/hz_16);
				base += (timer/hz_16);
			
				if(base%(timer/hz_16)==0)DL_GPIO_togglePins(LED_PORT,LED_L0_PIN);
				if(base%(hz_1*4))base = 0;
				 
				
			 
			 }
			break;
		default:
			break;
	}
}