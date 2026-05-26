#include "ti_msp_dl_config.h"
#include "FreeRTOS.h"
#include "task.h"

void FreeRTOS_Init(void);

int main(void)
{
    SYSCFG_DL_init(); // Sysconfig initialization
    FreeRTOS_Init();  // FreeRTOS initialization
    vTaskStartScheduler();  // Start FreeRTOS scheduler

    /* We should never get here as control is now taken by the scheduler */
    while(1)
		{

    }
}