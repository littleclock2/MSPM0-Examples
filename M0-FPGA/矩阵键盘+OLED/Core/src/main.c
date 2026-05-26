/*
 * KEYBOARD_OLED示例
 * 主函数在OLED打印Hello World
 * 按下矩阵键盘，OLED显示对应数字
 * Author: zjs
 */
#include "ti_msp_dl_config.h"
#include "key.h"
#include "oled.h"

int key_value = 0;

int main(void)
{
    SYSCFG_DL_init(); // Initialize the device
    
    OLED_Init();
    OLED_Clear();
    
    OLED_ShowString(0, 0, "Hello World!");
    
    while(1)
    {
        key_value = getKeyValue();
        if(key_value != 0)
        {
            OLED_ShowNum(2, 3, (unsigned int)key_value, 2, 16);
        }
    }
}