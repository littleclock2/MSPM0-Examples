#include "ti_msp_dl_config.h"
#include "oled.h"

int main(void)
{
	SYSCFG_DL_init();                      //初始化
	OLED_Init();			//初始化OLED  
	OLED_Clear();
	OLED_ShowCHinese(0,0,3);//
	OLED_ShowCHinese(18,0,4);//
    OLED_ShowNum(0,2,100,3,18);
	OLED_ShowString(1,4,"2024.1.15");
    OLED_ShowString(2,6,"OLED TEST");
	//delay_ms(100000);this expression may be wrong! the sysclk doesn't recognize this function in right way!
	delay_cycles(120000000);
	OLED_Clear();
	
    while (1) 
			{
	OLED_ShowString(3,5,"HELLO OLED");
	delay_cycles(120000000);
	OLED_Clear();
	for(int i = 0;i<48;i++){
		OLED_DrawPoint(24,i);
	}
//	OLED_DrawBMP(27,0,74,64,rode);
//	delay_cycles(120000000);
//	OLED_Clear();
    }
}

