/*******************************************************************************
 * @file     mygui_fonts.c
 * @brief    fonts data for screen to display
 * @version  V1.0
 * @date     2021.1.24
 * @author   RainingRabbits contact@example.invalid
 ******************************************************************************/

#ifndef __MYGUI_FONTS_H
#define __MYGUI_FONTS_H

//Only support ' '(0x20) to '~'(0x7e)
//Size include 0806 1206 1608 2412

#include "stdint.h"

typedef enum{
	FONT_0806,
	FONT_1206,
	FONT_1608,
	FONT_2412
}FONT_SIZE;

extern const uint8_t ASCII_0806[][6];
extern const uint8_t ASCII_1206[][12];
extern const uint8_t ASCII_1608[][16];
extern const uint8_t ASCII_2412[][36];


#endif
