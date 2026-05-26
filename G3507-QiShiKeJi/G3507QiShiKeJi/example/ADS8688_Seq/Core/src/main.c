#include "ti_msp_dl_config.h"
#include "oled_spi.h"
#include "ADS8688.h"
#define BUFFER_SIZE 1024
uint16_t data[BUFFER_SIZE] = {},cnt = 0,temp = 0;
int main(void){
    /* 系统初始化 */
    SYSCFG_DL_init();
	OLED_Init();
	OLED_ShowString(64,0,"SB");
	ADS8688_SequentialReadConfig(SEQ_CH0|SEQ_CH3);
	ADS8688_SetRange(0,RANGE_0_625_REF);
	ADS8688_SetRange(3,RANGE_2_5_REF);
	ADS8688_CommandRegAutoReset();//这个函数调用后，对ADS8688的下一条命令必须是读取命令，否则会出错
	while(1){
		data[cnt] = ADS8688_ContinueGetData();
		temp = data[cnt];
		OLED_ShowNum(48,2,temp,6,16);
		cnt = (cnt+1)%BUFFER_SIZE;
	}
		return 0;
}
