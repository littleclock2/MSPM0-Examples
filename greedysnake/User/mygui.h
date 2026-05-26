/*******************************************************************************
 * @file     mygui.h
 * @brief    load fonts or draw shapes to screen 
 * @version  V1.2
 * @date     2021.2.8
 * @author   RainingRabbits contact@example.invalid
 ******************************************************************************/
 
/*******************Hareware Define**********************************
1.	The Ram to display screen is show as below. For example, the ram is 
		unsigend char MYGUI_RAM[ MYGUI_XBYTE_MAX*MYGUI_YBYTE_MAX ]={a,b,c,d...};
	The screen is	
					 x0 x1 x2 x3 x4 .. xmax
				   
				y0   a0 b0 c0 d0 e0 .. h0
				y1   a1 .. .. .. .. .. ..
				y2   a2 .. .. .. .. .. ..
				y3   a3 .. .. .. .. .. ..
				y4   a4 .. .. .. .. .. ..
				y5   a5 .. .. .. .. .. ..
				y6   a6 .. .. .. .. .. ..
				y7   a7 .. .. .. .. .. ..
				y8   i0 g0 k0 l0 m0 .. p0
				y9   .. .. .. .. .. .. ..
				..   .. .. .. .. .. .. ..
			  ymax   .. .. .. .. .. .. ..
	This is important for you to create fonts or bmp.
2.	For different screens, you only need to re-write the function MYGUI_DrawPoint.
3.	MYGUI_Clear will fill screen with parameter data, parameter dir appoint to
	the rotation degree.
	  dir -> rotation degree
		0 -> 0бу
		1 -> 90бу
		2 -> 180бу
		3 -> 270бу
******************************************************************/
#ifndef __MYGUI_H
#define __MYGUI_H

#include "oled.h"
#include "stdint.h"

#define MYGUI_X_MAX			OLED_X_MAX
#define MYGUI_Y_MAX			OLED_Y_MAX

#define MYGUI_XBYTE_MAX		OLED_X_MAX
#define MYGUI_YBYTE_MAX		OLED_Y_MAX/8

void MYGUI_Init			(void);
void MYGUI_Clear		(uint8_t data,uint8_t dir);
void MYGUI_Refresh		(void);
void MYGUI_DrawPoint	(int16_t x,int16_t y,uint8_t color);
void MYGUI_DrawLine		(int16_t x1,int16_t y1,int16_t x2,int16_t y2,uint8_t color);
void MYGUI_DrawRectangle(int16_t x1,int16_t y1,int16_t x2,int16_t y2,uint8_t fill,uint8_t color);
void MYGUI_DrawCircle 	(int16_t x,int16_t y,uint16_t r,uint8_t fill,uint8_t color);
void MYGUI_Load			(int16_t x,int16_t y,uint16_t xlen,uint16_t ylen,const uint8_t *data,uint8_t color);

#include "mygui_fonts.h"
void MYGUI_Print		(int16_t x,int16_t y,char *data,FONT_SIZE size,uint8_t color);
void MYGUI_PrintNum		(int16_t x,int16_t y,long num,FONT_SIZE size,uint8_t color);

#endif
