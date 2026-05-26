#ifndef __AD9959_H__
#define __AD9959_H__
#include "ti_msp_dl_config.h"
#include "oled_spi.h"
/***********************引脚定义*******************/
#define AD9959_P0 			AD9959_P0_PIN			
#define AD9959_P1 			AD9959_P1_PIN
#define AD9959_P2			AD9959_P2_PIN
#define AD9959_P3			AD9959_P3_PIN
#define AD9959_UPDATE		AD9959_UPDATE_PIN
#define AD9959_CS			AD9959_CS_AD9959_PIN
#define AD9959_SCLK			AD9959_SCLK_PIN
#define AD9959_SDIO0		    AD9959_SDIO0_PIN
#define AD9959_SDIO1		    AD9959_SDIO1_PIN
#define AD9959_SDIO2		    AD9959_SDIO2_PIN
#define AD9959_SDIO3		    AD9959_SDIO3_PIN
#define AD9959_PWR			AD9959_PWR_PIN
#define AD9959_RESET		    AD9959_REST_PIN 


///***********************管脚定义*******************/
//#define AD9959_GPIO_P0 					(GPIOA)
//#define AD9959_GPIO_P1	  				(GPIOA)
//#define AD9959_GPIO_P2 					(GPIOB)
//#define AD9959_GPIO_P3 					(GPIOB)
//#define AD9959_GPIO_UPDATE				(GPIOA)
//#define AD9959_GPIO_CS					(GPIOA)
//#define AD9959_GPIO_SCLK				(GPIOA)
//#define AD9959_GPIO_SDIO0				(GPIOA)
//#define AD9959_GPIO_SDIO1				(GPIOA)
//#define AD9959_GPIO_SDIO2				(GPIOB)
//#define AD9959_GPIO_SDIO3				(GPIOB)
//#define AD9959_GPIO_PWR					(GPIOA)
//#define AD9959_GPIO_RESET				(GPIOB)

#define	PS0_Set_High()	DL_GPIO_setPins(GPIOA,AD9959_P0)			 //PB0	->	P0
#define PS0_Set_Low()		DL_GPIO_clearPins(GPIOA,AD9959_P0)

#define	PS1_Set_High()	DL_GPIO_setPins(GPIOA,AD9959_P1)		 	 //PC6	->	P1
#define PS1_Set_Low()		DL_GPIO_clearPins(GPIOA,AD9959_P1)

#define	PS2_Set_High()	DL_GPIO_setPins(GPIOB,AD9959_P2)			 //PB13 ->	P2
#define PS2_Set_Low()		DL_GPIO_clearPins(GPIOB,AD9959_P2)

#define	PS3_Set_High()	DL_GPIO_setPins(GPIOB,AD9959_P3)			 //PA0	->	P3
#define PS3_Set_Low()		DL_GPIO_clearPins(GPIOB,AD9959_P3)

#define IO_UPDATE_0()	DL_GPIO_clearPins(GPIOA,AD9959_UPDATE)			 //PE3	->	IO_UP
#define IO_UPDATE_1()	DL_GPIO_setPins(GPIOA,AD9959_UPDATE)

#define CS_Enable()		DL_GPIO_clearPins(GPIOA,AD9959_CS)		   //PE2  -> CS
#define CS_Disable()	DL_GPIO_setPins(GPIOA,AD9959_CS)

#define SCLK_0()	DL_GPIO_clearPins(GPIOA,AD9959_SCLK)					 //PB10 -> SCLK
#define SCLK_1() 	DL_GPIO_setPins(GPIOA,AD9959_SCLK)

#define SDIO0_0()	DL_GPIO_clearPins(GPIOA,AD9959_SDIO0)				   //PB11 ->	SDIO0
#define SDIO0_1()	DL_GPIO_setPins(GPIOA,AD9959_SDIO0)			

#define SDIO1_0()	DL_GPIO_clearPins(GPIOA,AD9959_SDIO1)				   //PD12 ->	SDIO1
#define SDIO1_1()	DL_GPIO_setPins(GPIOA,AD9959_SDIO1)			

#define SDIO2_0()	DL_GPIO_clearPins(GPIOB,GPIO_Pin_8)				   //PA8  ->	SDIO2
#define SDIO2_1()	DL_GPIO_setPins(GPIOB,GPIO_Pin_8)			

#define SDIO3_0()	DL_GPIO_clearPins(GPIOB,AD9959_SDIO3)				   //PE0  ->	SDIO3
#define SDIO3_1()	DL_GPIO_setPins(GPIOB,AD9959_SDIO3)			

#define PWR_0()	DL_GPIO_clearPins(GPIOA,AD9959_PWR)			 			 //PD2	->	pwr
#define PWR_1()	DL_GPIO_setPins(GPIOA,AD9959_PWR)

#define RESET_0()	DL_GPIO_clearPins(GPIOB,AD9959_RESET)			 		 //PC12	->	RESET
#define RESET_1()	DL_GPIO_setPins(GPIOB,AD9959_RESET)

#define TestFreq1M   1000000
#define TestFreq50M  50000000
#define TestFreq100M 100000000


typedef  struct 
{
	u8 ChState;				//通道状态  1为开，0为关
	u8 SweepMode;			//扫频模式	0为连续，1为单次
	u32 S0;						//start_freq
	u32 E0;						//end_frq
	uint16_t SweepTime;		//扫频时间
	uint16_t SweepDelay;		//扫频间隔
	double SweepVPP;	//峰峰值
	double SweepPhase;//相位
}Chrip_Config;

extern Chrip_Config Ch1_ChripConfig;
extern Chrip_Config Ch2_ChripConfig;
extern Chrip_Config Ch3_ChripConfig;
extern Chrip_Config Ch4_ChripConfig;




/***********************函数声明************************/


void AD9959_Init(void);
void AD9959_Reset(void);
void IO9959_Init(void);
void SPI_Write_Byte(u8 btye);
void AD9959_Write_Reg(u8 addr,u8 num,u8 *command);
void AD9959_Updata_First(void);
void AD9959_Updata_Final(void);
void AD9959_Update(void);
void AD9959_SingleTone_Init(void);
void AD9959_SingleTone_Freq(u8 Channel,u32 Freq);
void AD9959_SingleTone_Amp(u8 Channel,uint16_t Amplitude);
void AD9959_SingleTone_Phase(u8 Channel,uint16_t Phase);
void ReadFromeAD9959(u8 addr,u8 num,u8 *RegisterData);
void AD9959_Set_Freq(u32 Freq);


void AD9959_Chrip_StartFreq(u32 StartFreq);
void AD9959_Chrip_EndFreq(u32 EndFreq);
void AD9959_Chrip_Delta_Up_Freq(u32 Delta_Up_Freq);
void AD9959_Chrip_Delta_Down_Freq(u32 Delta_Down_Freq);
void AD9959_Chrip_Delta_Ramp(u8 Up_Ramp,u8 Down_Ramp);




void AD9959_Phase(uint16_t Phase);
void AD9959_Freq(u32 Freq);		//设置频率

#endif

