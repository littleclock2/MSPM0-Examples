//////////////////////////////////////////////////////////////////////////////////	 
//              说明: 
//              ----------------------------------------------------------------
//              GND  电源地
//              VCC  3.3v电源
//              D0   PA0（SCL）
//              D1   PA1（SDA）
//              RES  PA7
//              DC   PA12
//              CS   PA13
//				BUSY PA18
//              ----------------------------------------------------------------
// 作    者   : Zhang han cong
//2024-06-15
//All rights reserved
//******************************************************************************/
#include "ti_msp_dl_config.h"
#include "bmp.h"
#include "oled.h"
#include "delay.h"

uint8_t  Image_BW[4736];
uint8_t  Image_R[4736];
//屏幕写入数据0时为黑色 写入数据1时为白色
//黑白电子纸屏幕支持局部刷新;但是局部刷屏的效果不够好，容易出现残影;不建议使用
int main()
{
	uint8_t t=' ';
	SYSCFG_DL_init();
	OLED_GUIInit();
	Paint_NewImage(Image_BW,OLED_W,OLED_H,0,WHITE); 
	Paint_NewImage(Image_R,OLED_W,OLED_H,0,WHITE);
	OLED_Clear(WHITE);	
	while(1)
	{
		OLED_SelectImage(Image_BW);
		OLED_Clear(WHITE);
		OLED_SelectImage(Image_R);
		OLED_Clear(WHITE);
		OLED_GUIInit();
		OLED_ShowPicture(10,0,272,128,gImage_mao,RED);//数据水平，字节垂直，字节内像素数据反序
		OLED_Display(Image_BW,Image_R);
		delay_ms(10000);
		OLED_SelectImage(Image_R);
		OLED_Clear(WHITE);
		OLED_SelectImage(Image_BW);
		OLED_Clear(WHITE);
		OLED_GUIInit();
		OLED_SelectImage(Image_BW);	
		OLED_ShowPicture(20,0,254,128,gImage_mao1,BLACK);//数据水平，字节垂直，字节内像素数据反序
		OLED_Display(Image_BW,Image_R);
//		delay_ms(1000);		
//		delay_ms(20000);
//		OLED_SelectImage(Image_R);
//		OLED_Clear(WHITE);
//		OLED_SelectImage(Image_BW);
//		OLED_Clear(WHITE);
//		OLED_GUIInit();
//	  	OLED_ShowChinese(61,0,0,16,BLACK);//中
//		OLED_ShowChinese(77,0,1,16,BLACK);//景
//		OLED_ShowChinese(93,0,2,16,BLACK);//园
//		OLED_ShowChinese(109,0,3,16,BLACK);//电
//		OLED_ShowChinese(125,0,4,16,BLACK);//子
//		OLED_ShowChinese(141,0,5,16,BLACK);//技
//		OLED_ShowChinese(157,0,6,16,BLACK);//术
//		OLED_ShowChinese(173,0,7,16,BLACK);//有
//		OLED_ShowChinese(189,0,8,16,BLACK);//限
//		OLED_ShowChinese(205,0,9,16,BLACK);//公
//		OLED_ShowChinese(221,0,10,16,BLACK);//司
//		OLED_SelectImage(Image_R);
//		OLED_ShowString(108,20,"2014/05/01",16,RED);
//		OLED_ShowString(80,40,"ASCII:",16,RED);  
//		OLED_ShowString(157,40,"CODE:",16,RED);
//		OLED_ShowChar(131,40,t,16,RED); 
//		OLED_ShowNum(198,40,t,3,16,RED);
//		t++;
//		if(t>'~')t=' ';	
//		OLED_ShowString(33,56,"Welcome to 2.90-inch E-paper",16,RED);		
//		OLED_ShowString(49,73,"with 296 x 128 resolution",16,RED);	
//		OLED_DrawLine(1,89,296,89,RED);
//		OLED_SelectImage(Image_BW);		
//		OLED_ShowString(30,90,"Zhongjingyuan Electronic",16,BLACK);
//		OLED_ShowString(52,106,"Technology Co.,Ltd.",16,BLACK);	
//		OLED_DrawRectangle(1,1,296,128,BLACK,0);
//		OLED_Display(Image_BW,Image_R);
		delay_ms(10000);
		OLED_SelectImage(Image_R);
		OLED_Clear(WHITE);
		OLED_SelectImage(Image_BW);
		OLED_Clear(WHITE);
		OLED_Display(Image_BW,Image_R);
		delay_ms(10000);
//		delay_ms(1000);		
//		delay_ms(1000);	
	}
}
