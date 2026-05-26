#include "key.h"
#include "delay.h"
 
 	    
//按键初始化函数 

void KEY_Init(void)
{
	RCC->APB2ENR|=1<<3;     //使能PORTB时钟
	GPIOB->CRH&=0XFFF00000;	//PA0~PA7设置成输入
	GPIOB->CRH|=0X00088888;
	GPIOB->ODR|=0<<8;	   	//PB8下拉
    GPIOB->ODR|=0<<9;	   	//PB9下拉
    GPIOB->ODR|=0<<10;	   	//PB10下拉
    GPIOB->ODR|=0<<11;	   	//PB11下拉
    GPIOB->ODR|=0<<12;	   	//PB12下拉
} 
//按键处理函数
//返回按键值
//mode:0,不支持连续按;1,支持连续按;
//返回值：
//0，没有任何按键按下
//KEY0_PRES，KEY0按下
//KEY1_PRES，KEY1按下
//WKUP_PRES，WK_UP按下 
//注意此函数有响应优先级,KEY0>KEY1>WK_UP!!
u8 KEY_Scan(u8 mode)
{	 
	static u8 key_up=1;//按键按松开标志
	if(mode)key_up=1;  //支持连按
	if(key_up&&(KEY8==1||KEY9==1||KEY10==1||KEY11==1||KEY12==1))
	{
		delay_ms(1);//去抖动
		key_up=0;
		if(KEY8==1)return KEY8_PRES;
		else if(KEY9==1)return KEY9_PRES;
		else if(KEY10==1)return KEY10_PRES;
        else if(KEY11==1)return KEY11_PRES;
        else if(KEY12==1)return KEY12_PRES;
	}else if(KEY8==0&&KEY9==0&&KEY10==0&&KEY11==0&&KEY12==0)key_up=1; 	     
	return 0;// 无按键按下
}

