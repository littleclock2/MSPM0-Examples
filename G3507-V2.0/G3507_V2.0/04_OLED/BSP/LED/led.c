#include "LED/led.h"

void LED_init(void)
{
	// 初始化输出引脚为禁用引脚输出反相、使能上拉、禁用高驱动强度、禁用高阻态
	DL_GPIO_initDigitalOutputFeatures(LED1_IOMUX, IOMUX_PINCM_INV_DISABLE, DL_GPIO_RESISTOR_PULL_UP,
									  DL_GPIO_DRIVE_STRENGTH_LOW, DL_GPIO_HIZ_DISABLE);
	DL_GPIO_initDigitalOutputFeatures(LED2_IOMUX, IOMUX_PINCM_INV_DISABLE, DL_GPIO_RESISTOR_PULL_UP,
									  DL_GPIO_DRIVE_STRENGTH_LOW, DL_GPIO_HIZ_DISABLE);

	DL_GPIO_setPins(LED1_PORT, LED1_PIN);	   // 初始状态为拉高
	DL_GPIO_enableOutput(LED1_PORT, LED1_PIN); // 使能输出

	DL_GPIO_setPins(LED2_PORT, LED2_PIN);	   // 初始状态为拉高
	DL_GPIO_enableOutput(LED2_PORT, LED2_PIN); // 使能输出
}
