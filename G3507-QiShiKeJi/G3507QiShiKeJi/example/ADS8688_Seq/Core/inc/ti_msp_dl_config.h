/*
 * Copyright (c) 2023, Texas Instruments Incorporated - http://www.ti.com
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

/*
 *  ============ ti_msp_dl_config.h =============
 *  Configured MSPM0 DriverLib module declarations
 *
 *  DO NOT EDIT - This file is generated for the MSPM0G350X
 *  by the SysConfig tool.
 */
#ifndef ti_msp_dl_config_h
#define ti_msp_dl_config_h

#define CONFIG_MSPM0G350X

#if defined(__ti_version__) || defined(__TI_COMPILER_VERSION__)
#define SYSCONFIG_WEAK __attribute__((weak))
#elif defined(__IAR_SYSTEMS_ICC__)
#define SYSCONFIG_WEAK __weak
#elif defined(__GNUC__)
#define SYSCONFIG_WEAK __attribute__((weak))
#endif

#include <ti/devices/msp/msp.h>
#include <ti/driverlib/driverlib.h>
#include <ti/driverlib/m0p/dl_core.h>

#ifdef __cplusplus
extern "C" {
#endif

/*
 *  ======== SYSCFG_DL_init ========
 *  Perform all required MSP DL initialization
 *
 *  This function should be called once at a point before any use of
 *  MSP DL.
 */


/* clang-format off */

#define POWER_STARTUP_DELAY                                                (16)



#define CPUCLK_FREQ                                                     32000000



/* Defines for UART_0 */
#define UART_0_INST                                                        UART0
#define UART_0_INST_IRQHandler                                  UART0_IRQHandler
#define UART_0_INST_INT_IRQN                                      UART0_INT_IRQn
#define GPIO_UART_0_RX_PORT                                                GPIOA
#define GPIO_UART_0_TX_PORT                                                GPIOA
#define GPIO_UART_0_RX_PIN                                        DL_GPIO_PIN_11
#define GPIO_UART_0_TX_PIN                                        DL_GPIO_PIN_10
#define GPIO_UART_0_IOMUX_RX                                     (IOMUX_PINCM22)
#define GPIO_UART_0_IOMUX_TX                                     (IOMUX_PINCM21)
#define GPIO_UART_0_IOMUX_RX_FUNC                      IOMUX_PINCM22_PF_UART0_RX
#define GPIO_UART_0_IOMUX_TX_FUNC                      IOMUX_PINCM21_PF_UART0_TX
#define UART_0_BAUD_RATE                                                (115200)
#define UART_0_IBRD_4_MHZ_115200_BAUD                                        (2)
#define UART_0_FBRD_4_MHZ_115200_BAUD                                       (11)




/* Defines for SPI_OLED */
#define SPI_OLED_INST                                                      SPI0
#define SPI_OLED_INST_IRQHandler                                SPI0_IRQHandler
#define SPI_OLED_INST_INT_IRQN                                    SPI0_INT_IRQn
#define GPIO_SPI_OLED_PICO_PORT                                           GPIOA
#define GPIO_SPI_OLED_PICO_PIN                                    DL_GPIO_PIN_5
#define GPIO_SPI_OLED_IOMUX_PICO                                (IOMUX_PINCM10)
#define GPIO_SPI_OLED_IOMUX_PICO_FUNC                IOMUX_PINCM10_PF_SPI0_PICO
/* GPIO configuration for SPI_OLED */
#define GPIO_SPI_OLED_SCLK_PORT                                           GPIOA
#define GPIO_SPI_OLED_SCLK_PIN                                    DL_GPIO_PIN_6
#define GPIO_SPI_OLED_IOMUX_SCLK                                (IOMUX_PINCM11)
#define GPIO_SPI_OLED_IOMUX_SCLK_FUNC                IOMUX_PINCM11_PF_SPI0_SCLK
#define GPIO_SPI_OLED_CS0_PORT                                            GPIOA
#define GPIO_SPI_OLED_CS0_PIN                                     DL_GPIO_PIN_2
#define GPIO_SPI_OLED_IOMUX_CS0                                  (IOMUX_PINCM7)
#define GPIO_SPI_OLED_IOMUX_CS0_FUNC                   IOMUX_PINCM7_PF_SPI0_CS0



/* Port definition for Pin Group OLED */
#define OLED_PORT                                                        (GPIOA)

/* Defines for DC: GPIOA.4 with pinCMx 9 on package pin 10 */
#define OLED_DC_PIN                                              (DL_GPIO_PIN_4)
#define OLED_DC_IOMUX                                             (IOMUX_PINCM9)
/* Port definition for Pin Group ADS8688 */
#define ADS8688_PORT                                                     (GPIOA)

/* Defines for PICO: GPIOA.18 with pinCMx 40 on package pin 33 */
#define ADS8688_PICO_PIN                                        (DL_GPIO_PIN_18)
#define ADS8688_PICO_IOMUX                                       (IOMUX_PINCM40)
/* Defines for POCI: GPIOA.16 with pinCMx 38 on package pin 31 */
#define ADS8688_POCI_PIN                                        (DL_GPIO_PIN_16)
#define ADS8688_POCI_IOMUX                                       (IOMUX_PINCM38)
/* Defines for CS: GPIOA.26 with pinCMx 59 on package pin 46 */
#define ADS8688_CS_PIN                                          (DL_GPIO_PIN_26)
#define ADS8688_CS_IOMUX                                         (IOMUX_PINCM59)
/* Defines for SCLK: GPIOA.17 with pinCMx 39 on package pin 32 */
#define ADS8688_SCLK_PIN                                        (DL_GPIO_PIN_17)
#define ADS8688_SCLK_IOMUX                                       (IOMUX_PINCM39)
/* Defines for RST_N: GPIOA.22 with pinCMx 47 on package pin 40 */
#define ADS8688_RST_N_PIN                                       (DL_GPIO_PIN_22)
#define ADS8688_RST_N_IOMUX                                      (IOMUX_PINCM47)

/* clang-format on */

void SYSCFG_DL_init(void);
void SYSCFG_DL_initPower(void);
void SYSCFG_DL_GPIO_init(void);
void SYSCFG_DL_SYSCTL_init(void);
void SYSCFG_DL_UART_0_init(void);
void SYSCFG_DL_SPI_OLED_init(void);


bool SYSCFG_DL_saveConfiguration(void);
bool SYSCFG_DL_restoreConfiguration(void);

#ifdef __cplusplus
}
#endif

#endif /* ti_msp_dl_config_h */
