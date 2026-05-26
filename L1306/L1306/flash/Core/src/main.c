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

#include <eeprom_emulation_type_a.h>
#include "ti_msp_dl_config.h"

uint32_t DataArray[EEPROM_EMULATION_DATA_SIZE / sizeof(uint32_t)] = {
    0xABCDEF00, 0x12345678, 0x00FEDCBA, 0x87654321, 0xABCDEF00, 0x12345678,
    0x00FEDCBA, 0x87654321, 0xABCDEF00, 0x12345678, 0x00FEDCBA, 0x87654321,
    0xABCDEF00, 0x12345678, 0x00FEDCBA, 0x87654321, 0xABCDEF00, 0x12345678,
    0x00FEDCBA, 0x87654321, 0xABCDEF00, 0x12345678, 0x00FEDCBA, 0x87654321,
    0xABCDEF00, 0x12345678, 0x00FEDCBA, 0x87654321, 0xABCDEF00, 0x12345678};
uint32_t EEPROMEmulationBuffer[EEPROM_EMULATION_DATA_SIZE / sizeof(uint32_t)];

int main(void)
{
    uint32_t EEPROMEmulationState;

    SYSCFG_DL_init();
	EEPROM_TypeA_eraseAllSectors();

    /* Initialize the virtual EEPROM */
    EEPROMEmulationState = EEPROM_TypeA_init(&EEPROMEmulationBuffer[0]);

		
   // while (1) {
        /* Change the content of EEPROMEmulationBuffer */


        /* Store the EEPROMEmulationBuffer to the flash to be a new record */
        EEPROMEmulationState = EEPROM_TypeA_writeData(DataArray);
        if (EEPROMEmulationState != EEPROM_EMULATION_WRITE_OK) {
            __BKPT(0);
        }
				for(int i=0;i<EEPROM_EMULATION_DATA_SIZE / sizeof(uint32_t);i++)
					EEPROMEmulationBuffer[i]=0;
				EEPROM_TypeA_readData(EEPROMEmulationBuffer);
        if (gEEPROMTypeAEraseFlag == 1) {
            /* In this demo, when the sector is full, it will be erased immediately */
            EEPROM_TypeA_eraseLastSector();
            gEEPROMTypeAEraseFlag = 0;
        }
        __BKPT(0);
   // }
}
