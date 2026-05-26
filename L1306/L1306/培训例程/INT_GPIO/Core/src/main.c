#include "ti_msp_dl_config.h"

int main(void)
{
    /* 初始化 */
    SYSCFG_DL_init();
    
    /* 使能（开启）SWITCH对应的IO中断 */
    NVIC_EnableIRQ(SWITCH_INT_IRQN);
    
    while(1)
    {
        /* 执行空语句 */
        __NOP();
        /* 可以把__NOP替换为下面这个函数以节省功耗 */
        // __WFI();     // Wait For Interrupt
    }
}

void GROUP1_IRQHandler(void)
{
    switch(DL_Interrupt_getPendingGroup(DL_INTERRUPT_GROUP_1))
    {
        case SWITCH_INT_IIDX:         // GPIO中断
            /* 翻转LED灯对应的IO口电平 */
            DL_GPIO_togglePins(LED_PORT, LED_PIN_0_PIN);
        break;
        default: break; //不是GPIO中断，不做操作
    }
}