#include "ti_msp_dl_config.h"

#define CLK_HZ 32e+06 // 系统时钟

void delay_ms(int x);

int main(void)
{
  SYSCFG_DL_init();

  while (1)
  {
    // 第一种写法
    if (!DL_GPIO_readPins(KEY_PORT, KEY_KEY0_PIN)) // 出现低电平
    {
      delay_ms(10); // 按键消抖延迟，一般为10ms，一定要在外界改变时延迟，而不是读取输入后再延迟
      // 所谓的外界改变时，即用户刚刚按下的时刻
      // 这里无法得知这个时刻，因此在while(1)中不断判断低电平来近似这个时刻，但是本质上不是第一行所说的读取输入后再延迟
      if (!DL_GPIO_readPins(KEY_PORT, KEY_KEY0_PIN)) // 外界改变后经过10ms延迟，判断此时是否按下
      {
        DL_GPIO_togglePins(LED_PORT, LED_LED0_PIN); // 翻转LED
        delay_ms(300);                              // 300ms延迟，防止按下一次按键却被认为按下了多次按键，导致LED多次翻转
      }
    }

    // 第二种写法，去掉按键消抖的10ms延迟是没有问题的
    // 因为只要检测到了低电平，无论是抖动产生的低电平还是稳定时刻的低电平，都可认为按下了
    // 只需要300ms的延迟防止多次按下即可
    // if (!DL_GPIO_readPins(KEY_PORT, KEY_KEY0_PIN)) // 外界改变后经过10ms延迟，判断此时是否按下
    // {
    //   DL_GPIO_togglePins(LED_PORT, LED_LED0_PIN); // 翻转LED
    //   delay_ms(300);                              // 300ms延迟，防止按下一次按键却被认为按下了多次按键，导致LED多次翻转
    // }
  }
}

void delay_ms(int x)
{
  delay_cycles(CLK_HZ / 1000 * x);
}