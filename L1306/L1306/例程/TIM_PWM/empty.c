

#include "ti_msp_dl_config.h"


int main(void)
{
    SYSCFG_DL_init();                      //Sysconfig初始化
		DL_TimerG_startCounter(TIMG0);   //开启定时器
		while(1)
		{
			
		}
}