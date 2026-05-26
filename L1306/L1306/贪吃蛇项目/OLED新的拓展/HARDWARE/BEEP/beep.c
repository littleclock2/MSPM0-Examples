#include "beep.h"
 
void beep_init()
{
   RCC->APB2ENR|=1<<3;    //使能PORTB时钟
//	GPIO_Set(GPIOF,PIN8,GPIO_MODE_OUT,GPIO_OTYPE_PP,GPIO_SPEED_100M,GPIO_PUPD_PD); 
	GPIOB->CRL&=0XFFF0FFFF; 
	GPIOB->CRL|=0X00030000;//PB4 推挽输出   	 	
    BEEP = 0;
}

