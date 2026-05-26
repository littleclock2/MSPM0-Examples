#include "ti_msp_dl_config.h"
#include<stdlib.h>
#include<math.h>

/*int main(void)
{
    SYSCFG_DL_init();    
	//Sysconfig初始化
    while(1)
		{
        DL_GPIO_clearPins(GPIO_GRP_0_PORT,GPIO_GRP_0_LED0_PIN);
			  for(uint32_t i=0 ; i<0X0000FFFF ; i++){}
					DL_GPIO_setPins(GPIO_GRP_0_PORT,GPIO_GRP_0_LED0_PIN);
			  for(uint32_t i=0 ; i<0X0000FFFF ; i++){}
					DL_GPIO_clearPins(GPIO_GRP_0_PORT,GPIO_GRP_0_LED1_PIN);
			  for(uint32_t i=0 ; i<0X0000FFFF ; i++){}
				  DL_GPIO_setPins(GPIO_GRP_0_PORT,GPIO_GRP_0_LED1_PIN);
			  for(uint32_t i=0 ; i<0X0000FFFF ; i++){}
					DL_GPIO_clearPins(GPIO_GRP_0_PORT,GPIO_GRP_0_LED2_PIN);
			  for(uint32_t i=0 ; i<0X0000FFFF ; i++){}
					DL_GPIO_setPins(GPIO_GRP_0_PORT,GPIO_GRP_0_LED2_PIN);
			  for(uint32_t i=0 ; i<0X0000FFFF ; i++){}
					DL_GPIO_clearPins(GPIO_GRP_0_PORT,GPIO_GRP_0_LED3_PIN);
			  for(uint32_t i=0 ; i<0X0000FFFF ; i++){}
				  DL_GPIO_setPins(GPIO_GRP_0_PORT,GPIO_GRP_0_LED3_PIN);
			  for(uint32_t i=0 ; i<0X0000FFFF ; i++){}
					DL_GPIO_clearPins(GPIO_GRP_0_PORT,GPIO_GRP_0_LED4_PIN);
			  for(uint32_t i=0 ; i<0X0000FFFF ; i++){}
					DL_GPIO_setPins(GPIO_GRP_0_PORT,GPIO_GRP_0_LED4_PIN);
			  for(uint32_t i=0 ; i<0X0000FFFF ; i++){}
					DL_GPIO_clearPins(GPIO_GRP_0_PORT,GPIO_GRP_0_LED5_PIN);
			  for(uint32_t i=0 ; i<0X0000FFFF ; i++){}
					DL_GPIO_setPins(GPIO_GRP_0_PORT,GPIO_GRP_0_LED5_PIN);
			  for(uint32_t i=0 ; i<0X0000FFFF ; i++){}
					DL_GPIO_clearPins(GPIO_GRP_0_PORT,GPIO_GRP_0_LED6_PIN);
			  for(uint32_t i=0 ; i<0X0000FFFF ; i++){}
					DL_GPIO_setPins(GPIO_GRP_0_PORT,GPIO_GRP_0_LED6_PIN);
			  for(uint32_t i=0 ; i<0X0000FFFF ; i++){}
					DL_GPIO_clearPins(GPIO_GRP_0_PORT,GPIO_GRP_0_LED7_PIN);
			  for(uint32_t i=0 ; i<0X0000FFFF ; i++){}
					DL_GPIO_setPins(GPIO_GRP_0_PORT,GPIO_GRP_0_LED7_PIN);
			  for(uint32_t i=0 ; i<0X0000FFFF ; i++){}
					
					DL_GPIO_clearPins(GPIO_GRP_0_PORT,GPIO_GRP_0_LED7_PIN);
			  for(uint32_t i=0 ; i<0X0000FFFF ; i++){}
					DL_GPIO_setPins(GPIO_GRP_0_PORT,GPIO_GRP_0_LED7_PIN);
			  for(uint32_t i=0 ; i<0X0000FFFF ; i++){}
					DL_GPIO_clearPins(GPIO_GRP_0_PORT,GPIO_GRP_0_LED6_PIN);
			  for(uint32_t i=0 ; i<0X0000FFFF ; i++){}
					DL_GPIO_setPins(GPIO_GRP_0_PORT,GPIO_GRP_0_LED6_PIN);
			  for(uint32_t i=0 ; i<0X0000FFFF ; i++){}
					DL_GPIO_clearPins(GPIO_GRP_0_PORT,GPIO_GRP_0_LED5_PIN);
			  for(uint32_t i=0 ; i<0X0000FFFF ; i++){}
					DL_GPIO_setPins(GPIO_GRP_0_PORT,GPIO_GRP_0_LED5_PIN);
			  for(uint32_t i=0 ; i<0X0000FFFF ; i++){}
					DL_GPIO_clearPins(GPIO_GRP_0_PORT,GPIO_GRP_0_LED4_PIN);
			  for(uint32_t i=0 ; i<0X0000FFFF ; i++){}
					DL_GPIO_setPins(GPIO_GRP_0_PORT,GPIO_GRP_0_LED4_PIN);
			  for(uint32_t i=0 ; i<0X0000FFFF ; i++){}
					DL_GPIO_clearPins(GPIO_GRP_0_PORT,GPIO_GRP_0_LED3_PIN);
			  for(uint32_t i=0 ; i<0X0000FFFF ; i++){}
					DL_GPIO_setPins(GPIO_GRP_0_PORT,GPIO_GRP_0_LED3_PIN);
			  for(uint32_t i=0 ; i<0X0000FFFF ; i++){}
					DL_GPIO_clearPins(GPIO_GRP_0_PORT,GPIO_GRP_0_LED2_PIN);
			  for(uint32_t i=0 ; i<0X0000FFFF ; i++){}
					DL_GPIO_setPins(GPIO_GRP_0_PORT,GPIO_GRP_0_LED2_PIN);
			  for(uint32_t i=0 ; i<0X0000FFFF ; i++){}
					DL_GPIO_clearPins(GPIO_GRP_0_PORT,GPIO_GRP_0_LED1_PIN);
			  for(uint32_t i=0 ; i<0X0000FFFF ; i++){}
					DL_GPIO_setPins(GPIO_GRP_0_PORT,GPIO_GRP_0_LED1_PIN);
			  for(uint32_t i=0 ; i<0X0000FFFF ; i++){}
					DL_GPIO_clearPins(GPIO_GRP_0_PORT,GPIO_GRP_0_LED0_PIN);
			  for(uint32_t i=0 ; i<0X0000FFFF ; i++){}
					DL_GPIO_setPins(GPIO_GRP_0_PORT,GPIO_GRP_0_LED0_PIN);
			  for(uint32_t i=0 ; i<0X0000FFFF ; i++){}
					DL_Common_delayCycles(32000000);
   }
}*/
//底板上的红色LED和核心板上的蓝色LED交替闪烁
int temp=0;
void SetPins(uint32_t input)
{	
	DL_GPIO_setPins(Switch_PORT,Switch_H1_PIN);
	DL_GPIO_setPins(Switch_PORT,Switch_H2_PIN);
	DL_GPIO_setPins(Switch_PORT,Switch_H3_PIN);
	DL_GPIO_setPins(Switch_PORT,Switch_H4_PIN);

	switch(input)
	{
		case Switch_H1_PIN:
			DL_GPIO_clearPins(Switch_PORT,Switch_H1_PIN);
				break;
		
		case Switch_H2_PIN:
			DL_GPIO_clearPins(Switch_PORT,Switch_H2_PIN);
		    break;
		
		case Switch_H3_PIN:
			DL_GPIO_clearPins(Switch_PORT,Switch_H3_PIN);
				break;
		
		case Switch_H4_PIN:
			DL_GPIO_clearPins(Switch_PORT,Switch_H4_PIN);
			  break;
		
	}
}
void CheckPins(uint32_t input)
	
{

	if(DL_GPIO_readPins(Switch_PORT,Switch_V1_PIN)==0)
		
		{
			switch(input)
			{
				case Switch_H1_PIN:
					temp=10000;
					break;
				case Switch_H2_PIN:
					temp=10001;
					break;
				case Switch_H3_PIN:
					temp=10010;
					break;
				case Switch_H4_PIN:
					temp=10011;			
					break;
		  }
		}
		else if(DL_GPIO_readPins(Switch_PORT,Switch_V2_PIN)==0)
		{
		 switch(input)
			{
				case Switch_H1_PIN:
					temp=10100;
					break;
				case Switch_H2_PIN:
					temp=10101;
					break;
				case Switch_H3_PIN:
					temp=10110;
					break;
				case Switch_H4_PIN:
				  temp=10111;
					break;
			}
		}
		else if(DL_GPIO_readPins(Switch_PORT,Switch_V3_PIN)==0)
			{
				switch(input)
			 {
				case Switch_H1_PIN:
					temp=11000;
					break;
				case Switch_H2_PIN:
					temp=11001;
					break;
				case Switch_H3_PIN:
					temp=11010;
					break;
				case Switch_H4_PIN:
					temp=11011;
					break;
			 }
			}				
		else if(DL_GPIO_readPins(Switch_PORT,Switch_V4_PIN)==0)
			{
				switch(input)
				{
					case Switch_H1_PIN:
					temp=11100;
					break;
				case Switch_H2_PIN:
					temp=11101;
					break;
				case Switch_H3_PIN:
					temp=11110;
					break;
				case Switch_H4_PIN:
					temp=11111;
					break;
				}
			}
			
}
void Breath(int time)
{
	uint32_t T=time;
	uint32_t i=0,m=0,n=0,t=0;
	
	for(i=0;i<T;i++)
	{
		DL_GPIO_setPins(LED_PORT,LED_L1_PIN);
		for(m=0;m<t;m++)
		DL_GPIO_setPins(LED_PORT,LED_L1_PIN);
		for(n=0;n<T-t;n++);
		t++;
		if(t>=T)
		{
			for(i=0;i<T;i++)
			{
				DL_GPIO_setPins(LED_PORT,LED_L1_PIN);
				for(m=0;m<t;m++);
				DL_GPIO_setPins(LED_PORT,LED_L1_PIN);
				for(n=0;n<T-t;n++);
				t--;
					
			}
		}
			
		
	}
}
	
int main(void)
{
	SYSCFG_DL_init();
	//int num=0;
	int result[4];
	
	
	while(1)
	{
		SetPins(Switch_H1_PIN);
		DL_Common_delayCycles(32000);
		CheckPins(Switch_H1_PIN);
		
		
		SetPins(Switch_H2_PIN);
		DL_Common_delayCycles(32000);
		CheckPins(Switch_H2_PIN);
		
		SetPins(Switch_H3_PIN);
		DL_Common_delayCycles(32000);
		CheckPins(Switch_H3_PIN);
		
		SetPins(Switch_H4_PIN);
		DL_Common_delayCycles(32000);
		CheckPins(Switch_H4_PIN);
		
		for(int i=0;i<4;i++)
	{
		result[i]=temp%10;
		temp/=10;
	}
	DL_GPIO_setPins(LED_PORT,LED_L1_PIN);
	DL_GPIO_setPins(LED_PORT,LED_L2_PIN);
	DL_GPIO_setPins(LED_PORT,LED_L3_PIN);
	DL_GPIO_setPins(LED_PORT,LED_L4_PIN);
	
	
	if(result[0])
	{
		DL_GPIO_clearPins(LED_PORT,LED_L4_PIN);
	}
	if(result[1])
	{
		DL_GPIO_clearPins(LED_PORT,LED_L3_PIN);
	}
	if(result[2])
	{
		DL_GPIO_clearPins(LED_PORT,LED_L2_PIN);
	}
	if(result[3])
	{
		DL_GPIO_clearPins(LED_PORT,LED_L1_PIN);
	}
		
	}
	
}
