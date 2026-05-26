#include "sys.h"
#include "usart.h"		
#include "delay.h"	 
#include "oled.h"  
#include "key.h"
#include "beep.h"
#include "snake.h"
#include "exti.h" 



int main(void)
{
	Stm32_Clock_Init(9);	//系统时钟设置
//    SystemInit();
	uart_init(72,9600);	 	//串口初始化为9600
	delay_init(72);
	beep_init();	  		
	OLED_Init();			//初始化OLED  
	OLED_Clear();
	EXTI_Init();		//外部中断初始化
    
    Show_Interface();
    while(KeyValue==0)
    {
        delay_ms(50);
    }
    KeyValue=0;
    Start();
    Playing();
}

