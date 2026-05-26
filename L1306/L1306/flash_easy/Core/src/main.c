/*
 * Copyright (c) 2021, Texas Instruments Incorporated
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * *  Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * *  Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * *  Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */


#include "ti_msp_dl_config.h"

#define  ADDRESS	(0x8000)		
uint32_t data[32];
uint8_t temp =16;
uint32_t DataArray[] = {
    0xABCDEF00, 0x12345678, 0x00FEDCBA, 0x87654321, 0xABCDEF00, 0x12345678,
    0x00FEDCBA, 0x87654321, 0xABCDEF00, 0x12345678, 0x00FEDCBA, 0x87654321,
    0xABCDEF00, 0x12345678, 0x00FEDCBA, 0x87654321, 0xABCDEF00, 0x12345678,
    0x00FEDCBA, 0x87654321, 0xABCDEF00, 0x12345678, 0x00FEDCBA, 0x87654321,
    0xABCDEF00, 0x12345678, 0x00FEDCBA, 0x87654321, 0xABCDEF00, 0x12345678};

int main(void)
{
		SYSCFG_DL_init();
	
		//read data 
		for(int i=0;i<128;i+=4)
			data[i/4]=*(uint32_t *)(ADDRESS+i);
	
		//erase flash
		DL_FlashCTL_unprotectSector( FLASHCTL, ADDRESS, DL_FLASHCTL_REGION_SELECT_MAIN);
		DL_FlashCTL_eraseMemoryFromRAM( FLASHCTL, ADDRESS, DL_FLASHCTL_COMMAND_SIZE_SECTOR);
		//write data
		DL_FlashCTL_unprotectSector( FLASHCTL, ADDRESS, DL_FLASHCTL_REGION_SELECT_MAIN);
		DL_FlashCTL_programMemoryFromRAM32( FLASHCTL, ADDRESS, data);
	
		//write data
		DL_FlashCTL_unprotectSector( FLASHCTL, ADDRESS, DL_FLASHCTL_REGION_SELECT_MAIN);
		DL_FlashCTL_programMemoryFromRAM32( FLASHCTL, ADDRESS+4, data);
	
	
		DL_FlashCTL_unprotectSector( FLASHCTL, ADDRESS, DL_FLASHCTL_REGION_SELECT_MAIN);
		DL_FlashCTL_programMemoryFromRAM( FLASHCTL, ADDRESS+8, DataArray, 30, DL_FLASHCTL_REGION_SELECT_MAIN);
		
}
