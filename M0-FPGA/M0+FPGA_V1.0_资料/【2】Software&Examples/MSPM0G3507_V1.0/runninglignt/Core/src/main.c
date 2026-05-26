#include "ti_msp_dl_config.h"

#define CLK_HZ 32e+06 // 系统时钟

// 将LED_PIN存储到数组，方便使用for循环
int LED_tab[8] = {LED_LED0_PIN, LED_LED1_PIN, LED_LED2_PIN, LED_LED3_PIN, LED_LED4_PIN, LED_LED5_PIN, LED_LED6_PIN, LED_LED7_PIN};
//size_t LED_port[8] = {LED_LED0_PORT, LED_LED1_PORT, LED_LED2_PORT, LED_LED3_PORT, LED_LED4_PORT, LED_LED5_PORT, LED_LED6_PORT, LED_LED7_PORT};

void delay_ms(int x);

// 所有LED的初始值均在syscfg里设置为set，也就是高电平，熄灭
int main(void)
{
  SYSCFG_DL_init();
	while (1)
  {
		DL_GPIO_clearPins(LED_LED0_PORT, LED_LED0_PIN);
			delay_ms(100);
		DL_GPIO_clearPins(LED_LED1_PORT, LED_LED1_PIN);
		delay_ms(100);
		DL_GPIO_clearPins(LED_LED2_PORT, LED_LED2_PIN);
		delay_ms(100);
		DL_GPIO_clearPins(LED_LED3_PORT, LED_LED3_PIN);
		delay_ms(100);
		DL_GPIO_clearPins(LED_LED4_PORT, LED_LED4_PIN);
		delay_ms(100);
		DL_GPIO_clearPins(LED_LED5_PORT, LED_LED5_PIN);
		delay_ms(100);
		DL_GPIO_clearPins(LED_LED6_PORT, LED_LED6_PIN);
		delay_ms(100);
		DL_GPIO_clearPins(LED_LED7_PORT, LED_LED7_PIN);
		delay_ms(100);
		DL_GPIO_setPins(LED_LED0_PORT, LED_LED0_PIN);
		delay_ms(100);
		DL_GPIO_setPins(LED_LED1_PORT, LED_LED1_PIN);
		delay_ms(100);
		DL_GPIO_setPins(LED_LED2_PORT, LED_LED2_PIN);
		delay_ms(100);
		DL_GPIO_setPins(LED_LED3_PORT, LED_LED3_PIN);
		delay_ms(100);
		DL_GPIO_setPins(LED_LED4_PORT, LED_LED4_PIN);
		delay_ms(100);
		DL_GPIO_setPins(LED_LED5_PORT, LED_LED5_PIN);
		delay_ms(100);
		DL_GPIO_setPins(LED_LED6_PORT, LED_LED6_PIN);
		delay_ms(100);
		DL_GPIO_setPins(LED_LED7_PORT, LED_LED7_PIN);
		delay_ms(100);
  }
}
	
////	DL_GPIO_setPins(LED_LED0_PORT, LED_LED0_PIN);
////	DL_GPIO_setPins(LED_LED1_PORT, LED_LED1_PIN);
////	DL_GPIO_setPins(LED_LED2_PORT, LED_LED2_PIN);
////	DL_GPIO_setPins(LED_LED3_PORT, LED_LED3_PIN);
////	DL_GPIO_setPins(LED_LED4_PORT, LED_LED4_PIN);
////	DL_GPIO_setPins(LED_LED5_PORT, LED_LED5_PIN);
////	DL_GPIO_setPins(LED_LED6_PORT, LED_LED6_PIN);
////	DL_GPIO_setPins(LED_LED7_PORT, LED_LED7_PIN);

//////  DL_GPIO_clearPins(LED_PORT, LED_tab[0]); // 初始时LED0亮
//  delay_ms(50);
//	  while (1)
////  {

////		DL_GPIO_setPins(LED_LED0_PORT, LED_LED0_PIN);
////		DL_GPIO_setPins(LED_LED1_PORT, LED_LED1_PIN);
////		DL_GPIO_setPins(LED_LED2_PORT, LED_LED2_PIN);
////		DL_GPIO_setPins(LED_LED3_PORT, LED_LED3_PIN);
////		DL_GPIO_setPins(LED_LED4_PORT, LED_LED4_PIN);
////		DL_GPIO_setPins(LED_LED5_PORT, LED_LED5_PIN);
////		DL_GPIO_setPins(LED_LED6_PORT, LED_LED6_PIN);
////		DL_GPIO_setPins(LED_LED7_PORT, LED_LED7_PIN);
////		delay_ms(5000);
////		DL_GPIO_clearPins(LED_LED0_PORT, LED_LED0_PIN);
////		DL_GPIO_clearPins(LED_LED1_PORT, LED_LED1_PIN);
////		DL_GPIO_clearPins(LED_LED2_PORT, LED_LED2_PIN);
////		DL_GPIO_clearPins(LED_LED3_PORT, LED_LED3_PIN);
////		DL_GPIO_clearPins(LED_LED4_PORT, LED_LED4_PIN);
////		DL_GPIO_clearPins(LED_LED5_PORT, LED_LED5_PIN);
////		DL_GPIO_clearPins(LED_LED6_PORT, LED_LED6_PIN);
////		DL_GPIO_clearPins(LED_LED7_PORT, LED_LED7_PIN);
////		
////  }

////  while (1)
////  {
////    for (int i = 0; i < 7; i++)
////    {
////      DL_GPIO_setPins(LED_port[i], LED_tab[i]);       // 熄灭后
////      DL_GPIO_clearPins(LED_port[i], LED_tab[i + 1]); // 立马点亮下一个
////      delay_ms(50);                                // 延迟
////    }
////    for (int i = 7; i > 0; i--)
////    {
////      DL_GPIO_setPins(LED_port[i], LED_tab[i]);
////      DL_GPIO_clearPins(LED_port[i], LED_tab[i - 1]);
////      delay_ms(50);
////    }
////  }
////}

void delay_ms(int x)
{
  delay_cycles(CLK_HZ / 1000 * x);
}

