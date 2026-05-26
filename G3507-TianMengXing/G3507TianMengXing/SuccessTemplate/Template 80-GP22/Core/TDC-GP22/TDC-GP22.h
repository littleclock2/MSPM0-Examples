#include "ti_msp_dl_config.h"
#include <stdlib.h>
#include <math.h>
#include "oled_spi.h"
#define uint unsigned int
#define u16 uint16_t
#define SPI_TDC_INST SPI_1_INST


void SPIwrite32(uint32_t data);
uint32_t Tdc_Read32Bits(uint8_t command);
void  Tdc_test(void);