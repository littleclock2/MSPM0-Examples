/*
 * 武汉启是科技
 * 该工程根据SDK2_04_00_06,及sysconfig1.23.1构建
 * empty.syscfg文件仅有参考意义，非实际配置
 * 2025/6/11
 * 时钟配置80M
 */
#include "ti_msp_dl_config.h"
#include "bsp.h"
float ypr[3]; // 上传yaw pitch roll的值
int main(void)
{
	/* 初始化系统，主频时钟为80M */
	SYSCFG_DL_init();

	/* 初始化板载调试串口，目前仅提供波特率9600；其中包含常用延时定义，以及printf重定向 */
	uart0_init(9600);

	/* 板载2个LED初始化，.h文件中有相关驱动方法 */
	LED_init();

	SPI0_init();
	delay_ms(100); // 等待部署
	IMU_init();
	tim_g6_init();

	while (1)
	{
		IMU_getYawPitchRoll(ypr);
		printf("%.2f-%.2f-%.2f\r\n", ypr[0], ypr[1], ypr[2]);
		delay_ms(10);
	}
}
