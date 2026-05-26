#ifndef _ADF4351_H_
#define _ADF4351_H_
#include  "oled_spi.h"
#include "ti_msp_dl_config.h"

#define ADF4351_CLK ADF4351_CLK_PIN
#define ADF4351_OUTPUT_DATA ADF4351_DATA_PIN
#define ADF4351_LE ADF4351_LE_PIN
#define ADF4351_CE ADF4351_CE_PIN

#define ADF4351_INPUT_DATA ADF4351_INPUT_PIN

#define ADF_CE_Set (DL_GPIO_setPins(ADF4351_PORT,ADF4351_CE))         
#define ADF_CE_Clr (DL_GPIO_clearPins(ADF4351_PORT,ADF4351_CE);))

#define ADF_LE_Set (DL_GPIO_setPins(ADF4351_PORT,ADF4351_LE))         
#define ADF_LE_Clr (DL_GPIO_clearPins(ADF4351_PORT,ADF4351_LE))

#define ADF_DATA_Set (DL_GPIO_setPins(ADF4351_PORT,ADF4351_OUTPUT_DATA))         
#define ADF_DATA_Clr (DL_GPIO_clearPins(ADF4351_PORT,ADF4351_OUTPUT_DATA))

#define ADF_CLK_Set (DL_GPIO_setPins(ADF4351_PORT,ADF4351_CLK))         
#define ADF_CLK_Clr (DL_GPIO_clearPins(ADF4351_PORT,ADF4351_CLK))

extern void ADF4351_Wdata(u32 date);
extern void ADF4351_Init(u32 date); 
extern void GPIO_AD4351_Init(void);
extern void ADF4351_WriteFre(u32 F);
//void ADF4351Init(void); 
//void ReadToADF4351(u8 count, u8 *buf);
//void WriteToADF4351(u8 count, u8 *buf);
//void WriteOneRegToADF4351(u32 Regster);
//void ADF4351_Init_some(void);
//void ADF4351WriteFreq(float Fre);		//	(xxx.x) M Hz

#endif
