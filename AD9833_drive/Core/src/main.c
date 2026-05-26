#include "ti_msp_dl_config.h"
#include "oled_spi.h"
#include "AD9833.h"
int main(void)
{
    SYSCFG_DL_init();
	
		AD9833_ALLInit(50000,74,0,50000,50,1);
//		AD9833_Sleep(0,1);
//		AD9833_Init();
//		AD9833_SetFreq(5000000,1,1);
//		delay_cycles(10000);
//		AD9833_AddPhaseReg(512,0,1);
//		AD9833_SetWaveform(1,1,0);
//		AD9833_SetWaveform(2,0,1);
		delay_cycles(10000);
	  int16_t data = 0;
    while(1)
		{
			
			delay_cycles(320000);
    }
}
