/*
 * 武汉启是科技
 * 该工程根据SDK2_04_00_06,及sysconfig1.23.1构建
 * empty.syscfg文件仅有参考意义，非实际配置
 * 使用编译器V6.23
 * 2025/6/1
 * 时钟配置80M
 */

#include "ti_msp_dl_config.h"
#include "bsp.h"

int main(void)
{
	SYSCFG_DL_init();
	uart0_init(9600);

	
	/* 定时器A1生成1路pwm控制sk6812 ，频率800k*/
	tima1_pwm_rgb_init();

	/*初始化随机数生成器*/
	TRNG_init();

	while (1)
	{

		//		set_RGB((uint8_t)get_TRNG(), (uint8_t)get_TRNG(), (uint8_t)get_TRNG());
		//		delay_ms(50);
		int i = 0;
		for (i = 0; i < 256; i++)
		{
			set_RGB(i, 0, 0);
			delay_ms(15);
		}
		for (i = 0; i < 256; i++)
		{
			set_RGB(0, i, 0);
			delay_ms(15);
		}
		for (i = 0; i < 256; i++)
		{
			set_RGB(0, 0, i);
			delay_ms(15);
		}
		for (i = 0; i < 256; i++)
		{
			set_RGB(i, i, 0);
			delay_ms(15);
		}
		for (i = 0; i < 256; i++)
		{
			set_RGB(0, i, i);
			delay_ms(15);
		}
		for (i = 0; i < 256; i++)
		{
			set_RGB(i, 0, i);
			delay_ms(15);
		}
	}
}
