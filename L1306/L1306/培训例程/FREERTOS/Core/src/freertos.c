/**
 * @file freertos.c
 * @author 
 * @brief 
 * @version 0.1
 * @date 2024-01-14
 * 
 * @copyright Copyright (c) 2024
 * 
 */


#include "FreeRTOS.h"
#include "task.h"
#include "timers.h"

#include "ti_msp_dl_config.h"

/* Task Handles */
TaskHandle_t defaultTaskHandle;
TaskHandle_t LEDTaskHandle;

/* Timer Handles */

/* Semaphores */

/* Task Definition */
void StartDefaultTask(void * argument);
void LEDBlinkTask(void * argument);

void FreeRTOS_Init(void)
{
    xTaskCreate(StartDefaultTask, "defaultTask", 64, NULL, tskIDLE_PRIORITY, &defaultTaskHandle);
    xTaskCreate(LEDBlinkTask, "LEDBlinkTask", 64, NULL, 1, &LEDTaskHandle);
}


void StartDefaultTask(void * argument)
{
    for(;;)
    {
        vTaskDelay(1000);
    }
}

void LEDBlinkTask(void * argument)
{
    for(;;)
    {
        DL_GPIO_clearPins(Demo_PORT,Demo_LED_PIN);
        vTaskDelay(500);
        DL_GPIO_setPins(Demo_PORT,Demo_LED_PIN);
        vTaskDelay(500);
    }
}


#if (configCHECK_FOR_STACK_OVERFLOW)
    /*
     *  ======== vApplicationStackOverflowHook ========
     *  When stack overflow checking is enabled the application must provide a
     *  stack overflow hook function. This default hook function is declared as
     *  weak, and will be used by default, unless the application specifically
     *  provides its own hook function.
     */
    #if defined(__IAR_SYSTEMS_ICC__)
__weak void vApplicationStackOverflowHook(TaskHandle_t pxTask, char *pcTaskName)
    #elif (defined(__TI_COMPILER_VERSION__))
        #pragma WEAK(vApplicationStackOverflowHook)
void vApplicationStackOverflowHook(TaskHandle_t pxTask, char *pcTaskName)
    #elif (defined(__GNUC__) || defined(__ti_version__))
void __attribute__((weak)) vApplicationStackOverflowHook(TaskHandle_t pxTask, char *pcTaskName)
    #endif
{
    /* default to spin upon stack overflow */
    while (1) {}
}
#endif