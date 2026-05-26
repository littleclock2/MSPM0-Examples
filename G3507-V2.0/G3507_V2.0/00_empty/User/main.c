/*
 * 武汉启是科技
 * 该工程根据SDK2_04_00_06,及sysconfig1.23.1构建
 * empty.syscfg文件仅有参考意义，非实际配置
 * 2025/6/1
 * 时钟配置80M
 */

#include "ti_msp_dl_config.h"
#include "bsp.h"

/*空工程，只保留时钟配置和串口调试，方便用户搭建自己的工程项目*/
int main(void)
{
	SYSCFG_DL_init();
	uart0_init(115200);

	while (1)
	{
	}
}
