/*******************************************************************************
 * @file     greedysnake.h
 * @brief    play greedy snake game with oled on STM32F103
 * @version  V1.0
 * @date     2021.2.5
 * @author   RainingRabbits contact@example.invalid
******************************************************************************/
#ifndef __GREEDYSNAKE_H
#define __GREEDYSNAKE_H

#include "mygui.h"
#include "stdlib.h"
#include "tim.h"
#include "key.h"

#define SNAKE_MAXLEN	200
#define SNAKE_MAP_XMAX	30
#define SNAKE_MAP_YMAX	20

typedef enum {
	DIR_UP = 0,
	DIR_LEFT,
	DIR_DOWN,
	DIR_RIGHT	
}DIR;

typedef struct {
	uint8_t body_X[SNAKE_MAXLEN];
	uint8_t body_Y[SNAKE_MAXLEN];
	uint8_t head,tail,length;
	DIR tmp_dir;
	DIR dir;
}SNAKE;

//extern uint16_t SNAKE_DELAYMS;

void	Snake_Dir			(void);

void 	Snake_Init			(SNAKE *obj);
void 	Snake_ClearTail		(SNAKE *obj);
void 	Snake_PaintHead		(SNAKE *obj);
void 	Snake_Move			(SNAKE *obj);
void 	Snake_CreateFood	(SNAKE *obj);
uint8_t Snake_CheckDeath	(SNAKE *obj);
uint8_t Snake_CheckFood		(SNAKE *obj);
uint8_t Snake_Level			(SNAKE *obj);

void	Snake_StartPage	(void);
void	Snake_GamePage	(void);
void	Snake_OverPage	(void);


void Snake_Start(void);

#endif
