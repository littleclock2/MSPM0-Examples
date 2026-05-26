/*******************************************************************************
 * @file     key.c
 * @brief    read and return the key state
 * @version  V1.0
 * @date     2021.1.24
 * @author   RainingRabbits contact@example.invalid
 ******************************************************************************/
#include "key.h"

volatile char Key_State[8];

void Read_Pin_State(void)
{
	Key_State[0] = !HAL_GPIO_ReadPin(K1_GPIO_Port,K1_Pin);
	Key_State[1] = !HAL_GPIO_ReadPin(K2_GPIO_Port,K2_Pin);
	Key_State[2] = !HAL_GPIO_ReadPin(K3_GPIO_Port,K3_Pin);
	Key_State[3] = !HAL_GPIO_ReadPin(K4_GPIO_Port,K4_Pin);
	Key_State[4] = !HAL_GPIO_ReadPin(K5_GPIO_Port,K5_Pin);
	Key_State[5] = !HAL_GPIO_ReadPin(K6_GPIO_Port,K6_Pin);
	Key_State[6] = !HAL_GPIO_ReadPin(K7_GPIO_Port,K7_Pin);
	Key_State[7] = !HAL_GPIO_ReadPin(K8_GPIO_Port,K8_Pin);
}


void Key_Test(void)
{
	uint8_t key_x[8] ={24,16,24,32,92,104,92,104};
	uint8_t key_y[8] ={24,32,40,32,26,26,38,38};
	uint8_t key_test = 0x00;
	MYGUI_Clear(0x00,0);
	MYGUI_Print(0,0,"KEY TEST",FONT_1206,1);
	while(1)
	{
		for(int i=0;i<8;i++)
		{
			MYGUI_DrawCircle(key_x[i],key_y[i],5,Key_State[i],Key_State[i]);
			if(Key_State[i])
				key_test |= (0x01<<i);
		}
		MYGUI_Refresh();
		
		if(key_test == 0xFF)
		{
			MYGUI_Print(0,51,"KEY TEST SUCCESS!",FONT_1206,1);
			MYGUI_Refresh();
			break;
		}
	}
	HAL_Delay(1500);
}
