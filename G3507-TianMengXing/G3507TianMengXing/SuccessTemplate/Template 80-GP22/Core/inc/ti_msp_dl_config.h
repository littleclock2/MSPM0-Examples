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


#define GPIO_HFXT_PORT                                                     GPIOA
#define GPIO_HFXIN_PIN                                             DL_GPIO_PIN_5
#define GPIO_HFXIN_IOMUX                                         (IOMUX_PINCM10)
#define GPIO_HFXOUT_PIN                                            DL_GPIO_PIN_6
#define GPIO_HFXOUT_IOMUX                                        (IOMUX_PINCM11)
#define GPIO_LFXT_PORT                                                     GPIOA
#define GPIO_LFXIN_PIN                                             DL_GPIO_PIN_3
#define GPIO_LFXIN_IOMUX                                          (IOMUX_PINCM8)
#define GPIO_LFXOUT_PIN                                            DL_GPIO_PIN_4
#define GPIO_LFXOUT_IOMUX                                         (IOMUX_PINCM9)
#define CPUCLK_FREQ                                                     80000000



/* Defines for PWM_SG90 */
#define PWM_SG90_INST                                                      TIMG8
#define PWM_SG90_INST_IRQHandler                                TIMG8_IRQHandler
#define PWM_SG90_INST_INT_IRQN                                  (TIMG8_INT_IRQn)
#define PWM_SG90_INST_CLK_FREQ                                             25000
/* GPIO defines for channel 0 */
#define GPIO_PWM_SG90_C0_PORT                                              GPIOA
#define GPIO_PWM_SG90_C0_PIN                                       DL_GPIO_PIN_7
#define GPIO_PWM_SG90_C0_IOMUX                                   (IOMUX_PINCM14)
#define GPIO_PWM_SG90_C0_IOMUX_FUNC                  IOMUX_PINCM14_PF_TIMG8_CCP0
#define GPIO_PWM_SG90_C0_IDX                                 DL_TIMER_CC_0_INDEX



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
#define UART_0_IBRD_40_MHZ_115200_BAUD                                      (21)
#define UART_0_FBRD_40_MHZ_115200_BAUD                                      (45)




/* Defines for SPI_0 */
#define SPI_0_INST                                                         SPI1
#define SPI_0_INST_IRQHandler                                   SPI1_IRQHandler
#define SPI_0_INST_INT_IRQN                                       SPI1_INT_IRQn
#define GPIO_SPI_0_PICO_PORT                                              GPIOB
#define GPIO_SPI_0_PICO_PIN                                       DL_GPIO_PIN_8
#define GPIO_SPI_0_IOMUX_PICO                                   (IOMUX_PINCM25)
#define GPIO_SPI_0_IOMUX_PICO_FUNC                   IOMUX_PINCM25_PF_SPI1_PICO
#define GPIO_SPI_0_POCI_PORT                                              GPIOB
#define GPIO_SPI_0_POCI_PIN                                       DL_GPIO_PIN_7
#define GPIO_SPI_0_IOMUX_POCI                                   (IOMUX_PINCM24)
#define GPIO_SPI_0_IOMUX_POCI_FUNC                   IOMUX_PINCM24_PF_SPI1_POCI
/* GPIO configuration for SPI_0 */
#define GPIO_SPI_0_SCLK_PORT                                              GPIOB
#define GPIO_SPI_0_SCLK_PIN                                       DL_GPIO_PIN_9
#define GPIO_SPI_0_IOMUX_SCLK                                   (IOMUX_PINCM26)
#define GPIO_SPI_0_IOMUX_SCLK_FUNC                   IOMUX_PINCM26_PF_SPI1_SCLK
/* Defines for SPI_1 */
#define SPI_1_INST                                                         SPI0
#define SPI_1_INST_IRQHandler                                   SPI0_IRQHandler
#define SPI_1_INST_INT_IRQN                                       SPI0_INT_IRQn
#define GPIO_SPI_1_PICO_PORT                                              GPIOA
#define GPIO_SPI_1_PICO_PIN                                       DL_GPIO_PIN_9
#define GPIO_SPI_1_IOMUX_PICO                                   (IOMUX_PINCM20)
#define GPIO_SPI_1_IOMUX_PICO_FUNC                   IOMUX_PINCM20_PF_SPI0_PICO
#define GPIO_SPI_1_POCI_PORT                                              GPIOA
#define GPIO_SPI_1_POCI_PIN                                      DL_GPIO_PIN_13
#define GPIO_SPI_1_IOMUX_POCI                                   (IOMUX_PINCM35)
#define GPIO_SPI_1_IOMUX_POCI_FUNC                   IOMUX_PINCM35_PF_SPI0_POCI
/* GPIO configuration for SPI_1 */
#define GPIO_SPI_1_SCLK_PORT                                              GPIOA
#define GPIO_SPI_1_SCLK_PIN                                      DL_GPIO_PIN_12
#define GPIO_SPI_1_IOMUX_SCLK                                   (IOMUX_PINCM34)
#define GPIO_SPI_1_IOMUX_SCLK_FUNC                   IOMUX_PINCM34_PF_SPI0_SCLK



/* Port definition for Pin Group LED */
#define LED_PORT                                                         (GPIOB)

/* Defines for PIN_1: GPIOB.22 with pinCMx 50 on package pin 21 */
#define LED_PIN_1_PIN                                           (DL_GPIO_PIN_22)
#define LED_PIN_1_IOMUX                                          (IOMUX_PINCM50)
/* Port definition for Pin Group OLED */
#define OLED_PORT                                                        (GPIOB)

/* Defines for DC: GPIOB.11 with pinCMx 28 on package pin 63 */
#define OLED_DC_PIN                                             (DL_GPIO_PIN_11)
#define OLED_DC_IOMUX                                            (IOMUX_PINCM28)
/* Defines for RES: GPIOB.10 with pinCMx 27 on package pin 62 */
#define OLED_RES_PIN                                            (DL_GPIO_PIN_10)
#define OLED_RES_IOMUX                                           (IOMUX_PINCM27)
/* Defines for CS: GPIOB.14 with pinCMx 31 on package pin 2 */
#define OLED_CS_PIN                                             (DL_GPIO_PIN_14)
#define OLED_CS_IOMUX                                            (IOMUX_PINCM31)
/* Defines for P0: GPIOA.27 with pinCMx 60 on package pin 31 */
#define AD9959_P0_PORT                                                   (GPIOA)
#define AD9959_P0_PIN                                           (DL_GPIO_PIN_27)
#define AD9959_P0_IOMUX                                          (IOMUX_PINCM60)
/* Defines for P1: GPIOA.25 with pinCMx 55 on package pin 26 */
#define AD9959_P1_PORT                                                   (GPIOA)
#define AD9959_P1_PIN                                           (DL_GPIO_PIN_25)
#define AD9959_P1_IOMUX                                          (IOMUX_PINCM55)
/* Defines for P2: GPIOB.25 with pinCMx 56 on package pin 27 */
#define AD9959_P2_PORT                                                   (GPIOB)
#define AD9959_P2_PIN                                           (DL_GPIO_PIN_25)
#define AD9959_P2_IOMUX                                          (IOMUX_PINCM56)
/* Defines for P3: GPIOB.20 with pinCMx 48 on package pin 19 */
#define AD9959_P3_PORT                                                   (GPIOB)
#define AD9959_P3_PIN                                           (DL_GPIO_PIN_20)
#define AD9959_P3_IOMUX                                          (IOMUX_PINCM48)
/* Defines for UPDATE: GPIOA.22 with pinCMx 47 on package pin 18 */
#define AD9959_UPDATE_PORT                                               (GPIOA)
#define AD9959_UPDATE_PIN                                       (DL_GPIO_PIN_22)
#define AD9959_UPDATE_IOMUX                                      (IOMUX_PINCM47)
/* Defines for CS_AD9959: GPIOA.15 with pinCMx 37 on package pin 8 */
#define AD9959_CS_AD9959_PORT                                            (GPIOA)
#define AD9959_CS_AD9959_PIN                                    (DL_GPIO_PIN_15)
#define AD9959_CS_AD9959_IOMUX                                   (IOMUX_PINCM37)
/* Defines for SCLK: GPIOA.17 with pinCMx 39 on package pin 10 */
#define AD9959_SCLK_PORT                                                 (GPIOA)
#define AD9959_SCLK_PIN                                         (DL_GPIO_PIN_17)
#define AD9959_SCLK_IOMUX                                        (IOMUX_PINCM39)
/* Defines for SDIO0: GPIOA.14 with pinCMx 36 on package pin 7 */
#define AD9959_SDIO0_PORT                                                (GPIOA)
#define AD9959_SDIO0_PIN                                        (DL_GPIO_PIN_14)
#define AD9959_SDIO0_IOMUX                                       (IOMUX_PINCM36)
/* Defines for SDIO1: GPIOA.16 with pinCMx 38 on package pin 9 */
#define AD9959_SDIO1_PORT                                                (GPIOA)
#define AD9959_SDIO1_PIN                                        (DL_GPIO_PIN_16)
#define AD9959_SDIO1_IOMUX                                       (IOMUX_PINCM38)
/* Defines for SDIO2: GPIOB.17 with pinCMx 43 on package pin 14 */
#define AD9959_SDIO2_PORT                                                (GPIOB)
#define AD9959_SDIO2_PIN                                        (DL_GPIO_PIN_17)
#define AD9959_SDIO2_IOMUX                                       (IOMUX_PINCM43)
/* Defines for SDIO3: GPIOB.18 with pinCMx 44 on package pin 15 */
#define AD9959_SDIO3_PORT                                                (GPIOB)
#define AD9959_SDIO3_PIN                                        (DL_GPIO_PIN_18)
#define AD9959_SDIO3_IOMUX                                       (IOMUX_PINCM44)
/* Defines for PWR: GPIOA.24 with pinCMx 54 on package pin 25 */
#define AD9959_PWR_PORT                                                  (GPIOA)
#define AD9959_PWR_PIN                                          (DL_GPIO_PIN_24)
#define AD9959_PWR_IOMUX                                         (IOMUX_PINCM54)
/* Defines for REST: GPIOB.24 with pinCMx 52 on package pin 23 */
#define AD9959_REST_PORT                                                 (GPIOB)
#define AD9959_REST_PIN                                         (DL_GPIO_PIN_24)
#define AD9959_REST_IOMUX                                        (IOMUX_PINCM52)
/* Port definition for Pin Group TDC_GPIO */
#define TDC_GPIO_PORT                                                    (GPIOB)

/* Defines for TDC_NSS: GPIOB.21 with pinCMx 49 on package pin 20 */
#define TDC_GPIO_TDC_NSS_PIN                                    (DL_GPIO_PIN_21)
#define TDC_GPIO_TDC_NSS_IOMUX                                   (IOMUX_PINCM49)
/* Defines for TDC_INT: GPIOB.1 with pinCMx 13 on package pin 48 */
#define TDC_GPIO_TDC_INT_PIN                                     (DL_GPIO_PIN_1)
#define TDC_GPIO_TDC_INT_IOMUX                                   (IOMUX_PINCM13)
/* Defines for TDC_RTN: GPIOB.0 with pinCMx 12 on package pin 47 */
#define TDC_GPIO_TDC_RTN_PIN                                     (DL_GPIO_PIN_0)
#define TDC_GPIO_TDC_RTN_IOMUX                                   (IOMUX_PINCM12)

/* clang-format on */

void SYSCFG_DL_init(void);
void SYSCFG_DL_initPower(void);
void SYSCFG_DL_GPIO_init(void);
void SYSCFG_DL_SYSCTL_init(void);
void SYSCFG_DL_PWM_SG90_init(void);
void SYSCFG_DL_UART_0_init(void);
void SYSCFG_DL_SPI_0_init(void);
void SYSCFG_DL_SPI_1_init(void);


bool SYSCFG_DL_saveConfiguration(void);
bool SYSCFG_DL_restoreConfiguration(void);

#ifdef __cplusplus
}
#endif

#endif /* ti_msp_dl_config_h */
