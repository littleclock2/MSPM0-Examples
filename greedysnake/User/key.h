/*******************************************************************************
 * @file     key.h
 * @brief    read and return the key state
 * @version  V1.0
 * @date     2021.2.4
 * @author   RainingRabbits contact@example.invalid
 ******************************************************************************/
#ifndef __KEY_H
#define __KEY_H
 
#include "stm32f1xx_hal.h"
#include "main.h"
#include "stdint.h"
#include "mygui.h"
 
extern volatile char Key_State[8];

#define KEY_UP		Key_State[0]
#define KEY_LEFT	Key_State[1]
#define KEY_DOWN	Key_State[2]
#define KEY_RIGHT	Key_State[3]

#define KEY_A		Key_State[4]
#define KEY_B		Key_State[5]
#define KEY_C		Key_State[6]
#define KEY_D		Key_State[7]


void Read_Pin_State(void);
void Key_Test(void);


 
#endif
