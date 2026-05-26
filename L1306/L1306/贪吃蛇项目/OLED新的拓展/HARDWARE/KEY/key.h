#ifndef __KEY_H
#define __KEY_H	 
#include "sys.h"
 

#define KEY8_PRES	1		//KEY8按下
#define KEY9_PRES	2		//KEY9按下
#define KEY10_PRES	3		//KEY10按下
#define KEY11_PRES	4		//KEY11按下
#define KEY12_PRES	5		//KEY12按下

#define KEY8  PBin(8)   	//PB8
#define KEY9  PBin(9)   	//PB9
#define KEY10  PBin(10)   	//PB10
#define KEY11  PBin(11)   	//PB11
#define KEY12  PBin(12)   	//PB12

	 
void KEY_Init(void);		//IO初始化
u8 KEY_Scan(u8 mode);		//按键扫描函数
#endif
