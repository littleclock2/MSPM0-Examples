// TDC-GP22库，软件SPI实现

#ifndef TDC_H
#define TDC_H

#include "ti_msp_dl_config.h"
#include <stdint.h>
#include "oled_spi.h"

#define	DUMMY_DATA		            0xFF

#define POWER_ON_RESET                      0x50                   /// Power on reset
#define INIT_MEASURE                        0x70                   /// Init measure

#define WRITE_REG0                          0x80                   /// Write register0 operation address
#define WRITE_REG1                          0x81                   /// Write register1 operation address
#define WRITE_REG2                          0x82                   /// Write register2 operation address
#define WRITE_REG3                          0x83                   /// Write register3 operation address
#define WRITE_REG4                          0x84                   /// Write register4 operation address
#define WRITE_REG5                          0x85                   /// Write register5 operation address
#define WRITE_REG6                          0x86                   /// Write register6 operation address
#define READ_RES0                           0xB0                   /// Read 32bit result register0 address
#define READ_RES1                           0xB1                   /// Read 32bit result register1 address
#define READ_RES2                           0xB2                   /// Read 32bit result register2 address
#define READ_RES3                           0xB3                   /// Read 32bit result register3 address
#define READ_STAT                           0xB4                   /// Read 16bit state register address
#define READ_REG5                           0xB5                   /// Read 8bit what write to reg1 data, use to test communication
//#define READ_REG6                           0xB6                   /// Read register6 operation address
#define READ_IDBIT                          0xB7                   /// Read TDC ID bit(56 bits)
#define READ_PW1ST                          0xB8                   /// Read TDC PW1ST(8 bits)

#define REG_TO_EEPROM                       0xC0                   /// Write configure register to EEPROM
#define EEPROM_TO_REG                       0xF0                   /// Read configure register to EEPROM
#define EEPROM_REG_COMPARE                  0xC5                   /// Compare configure register with EEPROM

#define START_TOF                           0x01                   /// Start TOF measure
#define START_TEMP                          0x02                   /// Start temperature measure
#define START_CAL_OSC                       0x03                   /// Calibrate oscillator
#define START_CAL_TDC                       0x04                   /// Calibrate TDC
#define START_TOF_RESTART                   0x05                   /// Restart TOF measure
#define START_TEMP_RESTART                  0x06                   /// Restart temperature measure


void TDC_Reset_Hardware();

void TDC_Reset_Software();

void TDC_Config();

uint32_t TDC_Test();

void TDC_Start_Measure();

uint32_t TDC_Get_Measure_Value(uint32_t timeout_ms);

float TDC_Value_to_Time_ns(uint32_t tdc_value);

void gp22_wr_config_reg_gpio(uint8_t opcode_address, uint32_t config_reg_data) ;
uint32_t gp22_read_n_bytes_gpio(uint8_t n_bytes,  uint8_t read_addr);
#endif // TDC_H