#include "ti_msp_dl_config.h"
void Breath(int time,uint32_t input){
	uint32_t T = time;
	uint32_t i=0,m=0,n=0,t=0;
        for (i=0;i<T;i++)
        {
            DL_GPIO_clearPins(LED_PORT,input);  
            for (m=0;m<t;m++);
            DL_GPIO_setPins(LED_PORT,input);  
            for (n=0;n<T-t;n++);
            t++;

            if (t >= T)
            {
                for (i=0;i<T;i++)
                {
                    DL_GPIO_clearPins(LED_PORT,input);  
                    for (m=0;m<t;m++);
                   DL_GPIO_setPins(LED_PORT,input);
                    for (n=0;n<T-t;n++);
                    t--;
                }
            }
        }
    
}
int main(void)
{
    SYSCFG_DL_init();                      //Sysconfig初始化
    while(1){
        if(DL_GPIO_readPins(SWITCH_PORT,SWITCH_S1_PIN)==0)Breath(1000,LED_L0_PIN);
		if(DL_GPIO_readPins(SWITCH_PORT,SWITCH_S2_PIN)==0)Breath(1600 ,LED_L1_PIN);
		if(DL_GPIO_readPins(SWITCH_PORT,SWITCH_S3_PIN)==0)Breath(1800,LED_L2_PIN);
		DL_Common_delayCycles(32000000);
   }
}























