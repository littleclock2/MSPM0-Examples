#pragma once
#include "ti_msp_dl_config.h"
/*电平变化宏*/
#define WAIT __NOP();__NOP();__NOP()//;__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();//可以设置延迟时间
#define CS1_P DL_GPIO_setPins(AD9833_PORT,AD9833_CS1_PIN)
#define CS1_N DL_GPIO_clearPins(AD9833_PORT,AD9833_CS1_PIN)
#define CS2_P DL_GPIO_setPins(AD9833_PORT,AD9833_CS2_PIN)
#define CS2_N DL_GPIO_clearPins(AD9833_PORT,AD9833_CS2_PIN)
#define SCLK_P DL_GPIO_setPins(AD9833_PORT,AD9833_SCLK_PIN)
#define SCLK_N DL_GPIO_clearPins(AD9833_PORT,AD9833_SCLK_PIN)
#define PICO_P DL_GPIO_setPins(AD9833_PORT,AD9833_PICO_PIN)
#define PICO_N DL_GPIO_clearPins(AD9833_PORT,AD9833_PICO_PIN)


/*command*/
#define COMMAND_B28 0b0010000000000000
#define COMMAND_HLB 0b0001000000000000
#define COMMAND_FSEL 0b0000100000000000
#define COMMAND_PSEL 0b0000010000000000
#define COMMAND_RESET 0b0000000100000000
#define COMMAND_SLEEP1 0b0000000010000000
#define COMMAND_SLEEP2 0b0000000001000000
#define COMMAND_OPBITEN 0b0000000000100000
#define COMMAND_DIV2 0b0000000000001000
#define COMMAND_MODE 0b0000000000000010

/*寄存器地址*/
#define AD9833_SEL_CTR 0x0000
#define AD9833_SEL_FREQ0 0x4000
#define AD9833_SEL_FREQ1 0x8000
#define AD9833_SEL_PHASE0 0xC000
#define AD9833_SEL_PHASE1 0xE000

/*函数声明*/
void AD9833_SetRefClk(double freq); //设置参考时钟频率
void AD9833_Init(void);//初始化AD9833
void AD9833_Reset(bool channel1_en, bool channel2_en);//复位AD9833
void AD9833_WriteFreqReg(uint32_t data, bool channel1_en, bool channel2_en);//写入频率寄存器
void AD9833_AddPhaseReg(uint16_t data, bool channel1_en, bool channel2_en);//写入相位寄存器
void AD9833_SetFreq(double freq, bool channel1_en, bool channel2_en);//设置频率
void AD9833_AddPhase(double phase, bool channel1_en, bool channel2_en);//设置相位
void AD9833_SetWaveform(uint8_t waveform0,bool channel1_en, bool channel2_en);//设置波形
void AD9833_ALLInit(double freq_0,double phase_0, uint8_t wave_0,
					double freq_1,double phase_1, uint8_t wave_1);//初始化AD9833
void AD9833_Sleep(uint8_t sleep1_choice,uint8_t sleep2_chioce);//休眠