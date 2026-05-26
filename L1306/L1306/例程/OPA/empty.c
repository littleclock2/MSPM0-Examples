#include "ti_msp_dl_config.h"


int main(void)
{
    SYSCFG_DL_init();
                                         //等待写入完成

		while (1) 
		{
        __BKPT(0);
    }
}
