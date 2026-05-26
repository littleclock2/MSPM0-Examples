/*******************************************************************************
 * @file     greedysnake.c
 * @brief    play greedy snake game with oled on STM32F103
 * @version  V1.0
 * @date     2021.2.5
 * @author   RainingRabbits contact@example.invalid
******************************************************************************/

#include "greedysnake.h"

uint16_t SNAKE_SPEED_LEVEL[11] = {0,300,250,200,170,150,130,110,100,90,80};
const uint8_t snake_bmp1[]={		/* (24 X 16 )*/
	0x00,0x0C,0x1E,0x96,0xF3,0xFF,0x7F,0x3E,0x1C,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x1E,0x3F,0x7B,0x70,0x70,0x78,
	0x3C,0x1E,0x0F,0x07,0x07,0x0F,0x1E,0x3C,0x38,0x70,0x60,0x60,0x70,0x30,0x10,0x00
};

uint8_t level;
uint8_t foodx,foody;

SNAKE snake1,snake2;

void Snake_Init(SNAKE *obj)
{
	srand(__HAL_TIM_GET_COUNTER(&htim4));
	obj->head = 0;
	obj->tail = 0;
	obj->length = 1;
	obj->body_X[obj->head] = 15;
	obj->body_Y[obj->head] = 10;
	obj->dir = DIR_RIGHT;
	obj->tmp_dir = DIR_RIGHT;
}

void Snake_Dir()
{
	if(KEY_UP)
		snake1.tmp_dir = DIR_UP;
	else if(KEY_DOWN)
		snake1.tmp_dir = DIR_DOWN;
	else if(KEY_LEFT)
		snake1.tmp_dir = DIR_LEFT;
	else if(KEY_RIGHT)
		snake1.tmp_dir = DIR_RIGHT;
	
	if(KEY_A)
		snake2.tmp_dir = DIR_UP;
	else if(KEY_D)
		snake2.tmp_dir = DIR_DOWN;
	else if(KEY_C)
		snake2.tmp_dir = DIR_LEFT;
	else if(KEY_B)
		snake2.tmp_dir = DIR_RIGHT;
}

void Snake_ClearTail(SNAKE *obj)
{
	uint8_t tmp = obj->tail;
	MYGUI_DrawRectangle(obj->body_X[tmp]*3-1,obj->body_Y[tmp]*3-1,obj->body_X[tmp]*3+1,obj->body_Y[tmp]*3+1,1,0);
}

void Snake_PaintHead(SNAKE *obj)
{
	uint8_t tmp = obj->head;
	MYGUI_DrawRectangle(obj->body_X[tmp]*3-1,obj->body_Y[tmp]*3-1,obj->body_X[tmp]*3+1,obj->body_Y[tmp]*3+1,1,1);
	
}

void Snake_Move(SNAKE *obj)
{
	uint8_t temp;
	
	temp = (obj->head+1) % SNAKE_MAXLEN;
	obj->body_X[temp] = obj->body_X[obj->head];
	obj->body_Y[temp] = obj->body_Y[obj->head];
	
	if((obj->tmp_dir+4-obj->dir)%4 != 2)
		obj->dir = obj->tmp_dir;
	switch(obj->dir)
	{
		case DIR_UP:
			obj->body_Y[temp]--;
			break;
		case DIR_LEFT:
			obj->body_X[temp]--;
			break;
		case DIR_DOWN:
			obj->body_Y[temp]++;
			break;
		case DIR_RIGHT:
			obj->body_X[temp]++;
			break;
		default:break;
	}
	obj->head = temp;
	Snake_PaintHead(obj);
	
	if(Snake_CheckFood(obj)==1)
	{
		obj->length++;
		Snake_CreateFood(obj);
	}
	else
	{
		Snake_ClearTail(obj);
		obj->tail++;
		obj->tail %= SNAKE_MAXLEN;
	}
	
	MYGUI_Refresh();
}

void Snake_CreateFood(SNAKE *obj)
{
	do
	{
		foodx = rand()%(SNAKE_MAP_XMAX-1)+1;
		foody = rand()%(SNAKE_MAP_YMAX-1)+1;
	}while(Snake_CheckFood(obj)==1);
	
	MYGUI_DrawPoint(foodx*3-1,foody*3-1,1);
	MYGUI_DrawPoint(foodx*3-1,foody*3,0);
	MYGUI_DrawPoint(foodx*3-1,foody*3+1,1);
	
	MYGUI_DrawPoint(foodx*3,foody*3-1,0);
	MYGUI_DrawPoint(foodx*3,foody*3,1);
	MYGUI_DrawPoint(foodx*3,foody*3+1,0);
	
	MYGUI_DrawPoint(foodx*3+1,foody*3-1,1);
	MYGUI_DrawPoint(foodx*3+1,foody*3,0);
	MYGUI_DrawPoint(foodx*3+1,foody*3+1,1);
	MYGUI_Refresh();
}

uint8_t Snake_CheckDeath(SNAKE *obj)
{
	if(	obj->body_X[obj->head] > SNAKE_MAP_XMAX	||\
		obj->body_X[obj->head] == 0				||\
		obj->body_Y[obj->head] > SNAKE_MAP_YMAX	||\
		obj->body_Y[obj->head] == 0 )
	{
		return 1;
	}
	for(uint16_t i = obj->tail; i != obj->head;)
    {
    	if(	obj->body_X[obj->head] == obj->body_X[i] && \
			obj->body_Y[obj->head] == obj->body_Y[i])
			return 1;
		i++;
		i %= SNAKE_MAXLEN;
		
    }
	return 0;
}

uint8_t Snake_CheckFood(SNAKE *obj)
{
	if(	(obj->body_X[obj->head] == foodx) && \
		(obj->body_Y[obj->head] == foody ))
		return 1;
	
	for(uint16_t i = obj->tail; i != obj->head;)
    {
    	if(	obj->body_X[i] == foodx && \
			obj->body_Y[i] == foody)
			return 1;
		i++;
		i %= SNAKE_MAXLEN;
    }
	return 0;
}

uint8_t Snake_Level(SNAKE *obj)
{
	uint8_t level;
	if(obj->length < 10)
		level = 1;
	else if(obj->length < 20)
		level = 2;
	else if(obj->length < 30)
		level = 3;
	else if(obj->length < 40)
		level = 4;
	else if(obj->length < 50)
		level = 5;
	else if(obj->length < 60)
		level = 6;
	else if(obj->length < 70)
		level = 7;
	else if(obj->length < 80)
		level = 8;
	else if(obj->length < 90)
		level = 9;
	else
		level = 10;
	return level;
}

void Snake_StartPage(void)
{
	MYGUI_Clear(0x00,0);
	MYGUI_Print(0,28,"PRESS KEY UP TO START",FONT_0806,1);
	MYGUI_Refresh();
	while(!KEY_UP);
	while(KEY_UP);
	Snake_Init(&snake1);
}

void Snake_GamePage(void)
{
	MYGUI_Clear(0x00,0);
	MYGUI_DrawRectangle(0,0,93,63,0,1);
	MYGUI_DrawRectangle(1,1,92,62,0,1);
	MYGUI_Print(95,5,"LEVEL",FONT_0806,1);
	MYGUI_Print(95,25,"SCORE",FONT_0806,1);
	MYGUI_Load(98,44,24,16,snake_bmp1,1);
	Snake_PaintHead(&snake1);
	Snake_CreateFood(&snake1);
	MYGUI_Refresh();
	//while(1);
	while(Snake_CheckDeath(&snake1) == 0)
	{
		HAL_Delay(SNAKE_SPEED_LEVEL[level]);
		Snake_Move(&snake1);
		
		level = Snake_Level(&snake1);
		MYGUI_DrawRectangle(95,15,107,23,1,0);
		MYGUI_PrintNum(95,15,level,FONT_0806,1);
		MYGUI_DrawRectangle(95,35,119,43,1,0);
		MYGUI_PrintNum(95,35,snake1.length,FONT_0806,1);
	}
}
void Snake_OverPage(void)
{
	MYGUI_DrawRectangle(8,12,84,50,1,1);
	MYGUI_Print(10,14,"GAME OVER",FONT_1608,0);
	MYGUI_PrintNum(35,30,snake1.length,FONT_1608,0);
	MYGUI_Refresh();
}

void Snake_Start(void)
{
	Snake_StartPage();
	Snake_GamePage();
	Snake_OverPage();
}
