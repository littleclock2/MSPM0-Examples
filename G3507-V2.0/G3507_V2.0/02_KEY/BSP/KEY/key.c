#include "KEY/key.h"

void KEY_init(void)
{

	DL_GPIO_initDigitalInputFeatures(KEY_B23_IOMUX,
									 DL_GPIO_INVERSION_DISABLE, DL_GPIO_RESISTOR_PULL_UP,
									 DL_GPIO_HYSTERESIS_DISABLE, DL_GPIO_WAKEUP_DISABLE);

	DL_GPIO_setUpperPinsPolarity(KEY_PORT, DL_GPIO_PIN_23_EDGE_FALL);
	DL_GPIO_clearInterruptStatus(KEY_PORT, KEY_B23_PIN);
	DL_GPIO_enableInterrupt(KEY_PORT, KEY_B23_PIN);
	NVIC_EnableIRQ(KEY_INT_IRQN); // 开启中断
}

void GROUP1_IRQHandler(void)
{
	/*收集可以产生触发中断的引脚*/
	uint32_t IRQn_key = DL_GPIO_getEnabledInterruptStatus(KEY_PORT, KEY_B23_PIN);
	/*根据不同引脚执行对应中断代码*/
	if ((IRQn_key & KEY_B23_PIN) == KEY_B23_PIN)
	{
		LED1_toggle;
	}
}
