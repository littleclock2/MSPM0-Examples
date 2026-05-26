#include "delay.h"
#include "ti_msp_dl_config.h"
#define CLK_HZ 32e+06 // ????
////////////////////////////////////////////////////////////////////////////////// 	 

//延时nus
//nus为要延时的us数.		    								   
void delay_us(int nus)
{		
	delay_cycles(CLK_HZ / 1000000 * nus);
}

void delay_ms(int nms)
{	 		  	  
	delay_cycles(CLK_HZ / 1000 * nms);
} 

































