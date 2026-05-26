#include "ti_msp_dl_config.h"
void Breath(uint32_t input,uint32_t m,uint32_t n){
	uint32_t T = 1000,i = 0;
	DL_GPIO_clearPins(LED_PORT,input); 
for(i=0;i<T;i++){	
    for (m=0;m<T;m++);
    DL_GPIO_setPins(LED_PORT,input);  
	for (n=0;n<T;n++);	
}
}
int main(void){
	int timer = 32000000;
	int hz_16 = 16,hz_4 =4,hz_2 =2,hz_1 =1,base = 0;
    SYSCFG_DL_init();  
	
	NVIC_EnableIRQ(SWITCH_INT_IRQN);
		
    while(1){	
			Breath(LED_L0_PIN,75,25);
   }
	
}
void GROUP1_IRQHandler(void){
	int timer = 32000000;
	int hz_16 = 16,hz_4 =4,hz_2 =2,hz_1 =1,base = 0;
	
	switch(DL_Interrupt_getPendingGroup (DL_INTERRUPT_GROUP_1)){
		case SWITCH_INT_IIDX:
			DL_GPIO_togglePins(LED_PORT,LED_L_CORE_PIN);
			Breath(LED_L0_PIN,0,100);
			break;
		default:
			break;
	}
}