#include "exti.h"
#include "key.h"
#include "oled.h"
#include "delay.h"
#include "usart.h"
#include "snake.h"

//////////////////////////////////////////////////////////////////////////////////	 
//本程序只供学习使用，未经作者许可，不得用于其它任何用途
//ALIENTEK Mini STM32开发板
//外部中断 驱动代码			   
//正点原子@ALIENTEK
//技术论坛:www.openedv.com
//修改日期:2014/3/06  
//版本：V1.0
//版权所有，盗版必究。
//Copyright(C) 广州市星翼电子科技有限公司 2009-2019
//All rights reserved									 
////////////////////////////////////////////////////////////////////////////////// 	  

void EXTI9_5_IRQHandler(void)
{					 
    if(KEY8==1)		//按键0
	{
        KeyValue=1;
        EXTI->PR=1<<8;
	}else if(KEY9==1){
        KeyValue=2;
        EXTI->PR=1<<9;
    }
 	     //清除LINE5上的中断标志位  
}
//外部中断15~10服务程序
void EXTI15_10_IRQHandler(void)
{					 
    if(KEY10==1)		//按键1
	{
        KeyValue=3;
        EXTI->PR=1<<10;
	}else if(KEY11==1)		//按键1
	{
        KeyValue=4;
        EXTI->PR=1<<11;
	}else if(KEY12==1)		//按键1
	{
        Show_Endface();
        KeyValue=5;
        EXTI->PR=1<<12;
	}
 	 //清除LINE15上的中断标志位  
}
//外部中断初始化程序
//初始化PA0,PC5,PA15为中断输入.
void EXTI_Init(void)
{
	KEY_Init();
	Ex_NVIC_Config(GPIO_B,8,RTIR); 		//上升沿触发
	Ex_NVIC_Config(GPIO_B,9,RTIR);		//上升沿触发
	Ex_NVIC_Config(GPIO_B,10,RTIR);		//上升沿触发
    Ex_NVIC_Config(GPIO_B,11,RTIR);		//上升沿触发
    Ex_NVIC_Config(GPIO_B,12,RTIR);		//上升沿触发

	MY_NVIC_Init(2,0,EXTI9_5_IRQn,2);    	//抢占2，子优先级2，组2
    MY_NVIC_Init(2,1,EXTI15_10_IRQn,2);    	//抢占2，子优先级2，组2 
}

