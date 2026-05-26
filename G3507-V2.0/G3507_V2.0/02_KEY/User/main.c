/*
 * 武汉启是科技
 * 该工程根据SDK2_04_00_06,及sysconfig1.23.1构建
 * empty.syscfg文件仅有参考意义，非实际配置
 * 2025/6/3
 * 时钟配置80M
 */

#include "ti_msp_dl_config.h"
#include "bsp.h"

int main(void)
{
	SYSCFG_DL_init();
	uart0_init(9600);
	LED_init();
	LED1(0);

	/* 板载按键初始化+外部触发中断 */
	KEY_init();

	while (1)
	{
	}
}
