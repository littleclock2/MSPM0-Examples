/*
 * 武汉启是科技
 * 该工程根据SDK2_04_00_06,及sysconfig1.23.1构建
 * empty.syscfg文件仅有参考意义，非实际配置
 * 2025/6/3
 * 时钟配置80M
 */

#include "ti_msp_dl_config.h"
#include "bsp.h"
#include "OLED/oledfont_bmp.h"
int main(void)
{
	SYSCFG_DL_init();
	uart0_init(9600);
	LED_init();
	OLED_Init();
	OLED_Clear();
	OLED_DrawBMP(0, 1, 52, 8, qishi);
	OLED_DrawBMP(50, 1, 82, 8, qi);
	OLED_DrawBMP(88, 1, 120, 8, shi);
	while (1)
	{

	}
}
