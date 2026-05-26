#include "ti_msp_dl_config.h"
#include <stdlib.h>
#include <math.h>
#include "oled_spi.h"
#define uint unsigned int
#define u16 uint16_t

//设置SDA输出模式
#define SDA_OUT()   {                                                \
                        DL_GPIO_initDigitalOutput(I2C_SDA_IOMUX);    \
                        DL_GPIO_setPins(I2C_PORT, I2C_SDA_PIN);      \
                        DL_GPIO_enableOutput(I2C_PORT, I2C_SDA_PIN); \
                    }
//设置SDA输入模式
#define SDA_IN()    { DL_GPIO_initDigitalInput(I2C_SDA_IOMUX); }
//获取SDA引脚的电平变化
#define READ_SDA   ( ( ( DL_GPIO_readPins(I2C_PORT,I2C_SDA_PIN) & I2C_SDA_PIN ) > 0 ) ? 1 : 0 )
//SDA与SCL输出
#define SDA(x)      ( (x) ? (DL_GPIO_setPins(I2C_PORT,I2C_SDA_PIN)) : (DL_GPIO_clearPins(I2C_PORT,I2C_SDA_PIN)) )
#define SCL(x)      ( (x) ? (DL_GPIO_setPins(I2C_PORT,I2C_SCL_PIN)) : (DL_GPIO_clearPins(I2C_PORT,I2C_SCL_PIN)) )

#define AD5933_SYS_Init					0x1000   //(1)<<12  
#define AD5933_Begin_Fre_Scan		0x2000   //(2)<<12
#define AD5933_Fre_UP						0x3000   //(3)<<12
#define AD5933_Fre_Rep					0x4000   //(4)<<12

#define AD5933_Get_Temp					0x9000   //(9)<<12
#define AD5933_Sleep						0xA000   //(10)<<12
#define AD5933_Standby					0xB000   //(11)<<12

#define AD5933_OUTPUT_2V				0x0000   //(0)<<9
#define AD5933_OUTPUT_1V				0x0600   //(3)<<9
#define AD5933_OUTPUT_400mV			0x0400   //(2)<<9
#define AD5933_OUTPUT_200mV			0x0200   //(1)<<9

#define AD5933_Gain_1						0x0100   //(1)<<8
#define AD5933_Gain_5						0x0000   //(0)<<8

#define AD5933_IN_MCLK					0x0000   //(0)<<3
#define AD5933_OUT_MCLK					0x0004   //(1)<<3

#define AD5933_Reset						0x0010   //(1)<<4

#define AD5933 1
#define AD5933_MCLK 16.776  //=536870912/MCLK;

extern long realArr[3],imageArr[3];

//定义函数
void GetACK(void);
void SendNACK(void);
void START(void);
void STOP(void);
void SendByte(u8 txd);	// 发送一个字节数据子函数 
u8 ReadByte(void);  //读一个字节数据
void Write_Byte(char nAddr,uint nValue);
void SetPointer(char nAddr);
int Rece_Byte(char nAddr);
void Delay_ms(unsigned long nValue);

u16 AD5933_Tempter(void);
float Scale_imp (u8 *SValue,u8 *IValue,u8 *NValue,u8 *CValue);
float Get_resistance(u16 num);
float AD5933_Sweep (float Fre_Begin,float Fre_UP,u16 UP_Num,u16 OUTPUT_Vatage,u16 Gain,u16 SWeep_Rep);
float DA5933_Get_Cap(void);
float DA5933_Get_L(void);
float DA5933_Get_Rs(void);

void GET_REG(void);

