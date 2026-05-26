#include "ti_msp_dl_config.h"

#define CLK_HZ 32e+06 // 系统时钟

void delay_ms(int x);

uint8_t key_num = 0;

// 论使用哪种中断方式，都将前四个拨码开关拨至下方
// 这样所有行被硬件上拉，如果行作为输入则不需要额外软件上拉，如果行作为输出那么上拉也不会有影响

// 矩阵键盘中断，本例程使用行输出列输入，采用中断标志位确定所在列，二分法确定所在行
int main(void)
{
  SYSCFG_DL_init();

  NVIC_EnableIRQ(MAT_KEY_INT_IRQN); // IO中断使能

  DL_GPIO_clearPins(MAT_KEY_PORT, MAT_KEY_ROW0_PIN | MAT_KEY_ROW1_PIN | MAT_KEY_ROW2_PIN | MAT_KEY_ROW3_PIN); // 0000

  while (1)
  {
    if (key_num != 0)
    {
      if ((key_num - 1) & 1)
      {
        DL_GPIO_clearPins(LED_PORT, LED_LED3_PIN);
      }
      else
      {
        DL_GPIO_setPins(LED_PORT, LED_LED3_PIN);
      }
      if ((key_num - 1) & 2)
      {
        DL_GPIO_clearPins(LED_PORT, LED_LED2_PIN);
      }
      else
      {
        DL_GPIO_setPins(LED_PORT, LED_LED2_PIN);
      }
      if ((key_num - 1) & 4)
      {
        DL_GPIO_clearPins(LED_PORT, LED_LED1_PIN);
      }
      else
      {
        DL_GPIO_setPins(LED_PORT, LED_LED1_PIN);
      }
      if ((key_num - 1) & 8)
      {
        DL_GPIO_clearPins(LED_PORT, LED_LED0_PIN);
      }
      else
      {
        DL_GPIO_setPins(LED_PORT, LED_LED0_PIN);
      }

      key_num = 0;
    }
  }
}

void GROUP1_IRQHandler(void)
{
  uint32_t col_pin = 0;

  int8_t col = -1;
  int8_t row = -1;
  switch (DL_GPIO_getPendingInterrupt(MAT_KEY_PORT)) // 获取col
  {
  case MAT_KEY_COL0_IIDX:
    col = 0;
    col_pin = MAT_KEY_COL0_PIN;
    break;
  case MAT_KEY_COL1_IIDX:
    col = 1;
    col_pin = MAT_KEY_COL1_PIN;
    break;
  case MAT_KEY_COL2_IIDX:
    col = 2;
    col_pin = MAT_KEY_COL2_PIN;
    break;
  case MAT_KEY_COL3_IIDX:
    col = 3;
    col_pin = MAT_KEY_COL3_PIN;
    break;
  default:
    break;
  }
  if (col != -1)
  {
    delay_ms(10);                                   // 按键消抖
    if (!(DL_GPIO_readPins(MAT_KEY_PORT, col_pin))) // 按下对应列
    {
      DL_GPIO_setPins(MAT_KEY_PORT, MAT_KEY_ROW2_PIN | MAT_KEY_ROW3_PIN); // 0000->0011
      delay_ms(10);
      if (!(DL_GPIO_readPins(MAT_KEY_PORT, col_pin))) // row为0或1
      {
        DL_GPIO_setPins(MAT_KEY_PORT, MAT_KEY_ROW1_PIN); // 0011->0111
        delay_ms(10);
        if (!(DL_GPIO_readPins(MAT_KEY_PORT, col_pin))) // row为0
        {
          row = 0;
        }
        else // row为1
        {
          row = 1;
        }
      }
      else // row为2或3
      {
        DL_GPIO_clearPins(MAT_KEY_PORT, MAT_KEY_ROW2_PIN); // 0011->1101
        DL_GPIO_setPins(MAT_KEY_PORT, MAT_KEY_ROW0_PIN | MAT_KEY_ROW1_PIN);
        delay_ms(10);
        if (!(DL_GPIO_readPins(MAT_KEY_PORT, col_pin))) // row为2
        {
          row = 2;
        }
        else // row为3
        {
          row = 3;
        }
      }

      DL_GPIO_clearPins(MAT_KEY_PORT, MAT_KEY_ROW0_PIN | MAT_KEY_ROW1_PIN | MAT_KEY_ROW2_PIN | MAT_KEY_ROW3_PIN); // 0000
      delay_ms(10);                                                                                               // 防止重置行输出后再次进入中断
      key_num = row * 4 + col + 1;
      DL_GPIO_clearInterruptStatus(MAT_KEY_PORT, MAT_KEY_COL0_PIN | MAT_KEY_COL1_PIN | MAT_KEY_COL2_PIN | MAT_KEY_COL3_PIN); // 清除按键抖动或者二分扫描时产生的中断请求
    }
  }
}

void delay_ms(int x)
{
  delay_cycles(CLK_HZ / 1000 * x);
}