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


#define GPIO_HFCLKIN_PORT                                                  GPIOA
#define GPIO_HFCLKIN_PIN                                           DL_GPIO_PIN_6
#define GPIO_HFCLKIN_IOMUX                                       (IOMUX_PINCM11)
#define GPIO_HFCLKIN_IOMUX_FUNC                  IOMUX_PINCM11_PF_SYSCTL_HFCLKIN
#define GPIO_LFCLKIN_PORT                                                  GPIOA
#define GPIO_LFCLKIN_PIN                                           DL_GPIO_PIN_4
#define GPIO_LFCLKIN_IOMUX                                        (IOMUX_PINCM9)
#define GPIO_LFCLKIN_IOMUX_FUNC                   IOMUX_PINCM9_PF_SYSCTL_LFCLKIN
#define CPUCLK_FREQ                                                     32000000



/* Defines for PWM_SG90 */
#define PWM_SG90_INST                                                      TIMG8
#define PWM_SG90_INST_IRQHandler                                TIMG8_IRQHandler
#define PWM_SG90_INST_INT_IRQN                                  (TIMG8_INT_IRQn)
#define PWM_SG90_INST_CLK_FREQ                                             20000
/* GPIO defines for channel 0 */
#define GPIO_PWM_SG90_C0_PORT                                              GPIOA
#define GPIO_PWM_SG90_C0_PIN                                       DL_GPIO_PIN_7
#define GPIO_PWM_SG90_C0_IOMUX                                   (IOMUX_PINCM14)
#define GPIO_PWM_SG90_C0_IOMUX_FUNC                  IOMUX_PINCM14_PF_TIMG8_CCP0
#define GPIO_PWM_SG90_C0_IDX                                 DL_TIMER_CC_0_INDEX



/* Defines for BlueTooth */
#define BlueTooth_INST                                                     UART3
#define BlueTooth_INST_IRQHandler                               UART3_IRQHandler
#define BlueTooth_INST_INT_IRQN                                   UART3_INT_IRQn
#define GPIO_BlueTooth_RX_PORT                                             GPIOB
#define GPIO_BlueTooth_TX_PORT                                             GPIOB
#define GPIO_BlueTooth_RX_PIN                                      DL_GPIO_PIN_3
#define GPIO_BlueTooth_TX_PIN                                      DL_GPIO_PIN_2
#define GPIO_BlueTooth_IOMUX_RX                                  (IOMUX_PINCM16)
#define GPIO_BlueTooth_IOMUX_TX                                  (IOMUX_PINCM15)
#define GPIO_BlueTooth_IOMUX_RX_FUNC                   IOMUX_PINCM16_PF_UART3_RX
#define GPIO_BlueTooth_IOMUX_TX_FUNC                   IOMUX_PINCM15_PF_UART3_TX
#define BlueTooth_BAUD_RATE                                             (115200)
#define BlueTooth_IBRD_32_MHZ_115200_BAUD                                   (17)
#define BlueTooth_FBRD_32_MHZ_115200_BAUD                                   (23)




/* Defines for SPI_0 */
#define SPI_0_INST                                                         SPI1
#define SPI_0_INST_IRQHandler                                   SPI1_IRQHandler
#define SPI_0_INST_INT_IRQN                                       SPI1_INT_IRQn
#define GPIO_SPI_0_PICO_PORT                                              GPIOB
#define GPIO_SPI_0_PICO_PIN                                       DL_GPIO_PIN_8
#define GPIO_SPI_0_IOMUX_PICO                                   (IOMUX_PINCM25)
#define GPIO_SPI_0_IOMUX_PICO_FUNC                   IOMUX_PINCM25_PF_SPI1_PICO
/* GPIO configuration for SPI_0 */
#define GPIO_SPI_0_SCLK_PORT                                              GPIOB
#define GPIO_SPI_0_SCLK_PIN                                       DL_GPIO_PIN_9
#define GPIO_SPI_0_IOMUX_SCLK                                   (IOMUX_PINCM26)
#define GPIO_SPI_0_IOMUX_SCLK_FUNC                   IOMUX_PINCM26_PF_SPI1_SCLK



/* Port definition for Pin Group LED */
#define LED_PORT                                                         (GPIOA)

/* Defines for L1: GPIOA.28 with pinCMx 3 on package pin 35 */
#define LED_L1_PIN                                              (DL_GPIO_PIN_28)
#define LED_L1_IOMUX                                              (IOMUX_PINCM3)
/* Defines for L2: GPIOA.31 with pinCMx 6 on package pin 39 */
#define LED_L2_PIN                                              (DL_GPIO_PIN_31)
#define LED_L2_IOMUX                                              (IOMUX_PINCM6)
/* Port definition for Pin Group OLED */
#define OLED_PORT                                                        (GPIOB)

/* Defines for DC: GPIOB.7 with pinCMx 24 on package pin 59 */
#define OLED_DC_PIN                                              (DL_GPIO_PIN_7)
#define OLED_DC_IOMUX                                            (IOMUX_PINCM24)
/* Defines for RES: GPIOB.1 with pinCMx 13 on package pin 48 */
#define OLED_RES_PIN                                             (DL_GPIO_PIN_1)
#define OLED_RES_IOMUX                                           (IOMUX_PINCM13)
/* Defines for CS: GPIOB.6 with pinCMx 23 on package pin 58 */
#define OLED_CS_PIN                                              (DL_GPIO_PIN_6)
#define OLED_CS_IOMUX                                            (IOMUX_PINCM23)
/* Port definition for Pin Group TDC */
#define TDC_PORT                                                         (GPIOB)

/* Defines for RSTN: GPIOB.10 with pinCMx 27 on package pin 62 */
#define TDC_RSTN_PIN                                            (DL_GPIO_PIN_10)
#define TDC_RSTN_IOMUX                                           (IOMUX_PINCM27)
/* Defines for INTN: GPIOB.11 with pinCMx 28 on package pin 63 */
#define TDC_INTN_PIN                                            (DL_GPIO_PIN_11)
#define TDC_INTN_IOMUX                                           (IOMUX_PINCM28)
/* Defines for SSN: GPIOB.12 with pinCMx 29 on package pin 64 */
#define TDC_SSN_PIN                                             (DL_GPIO_PIN_12)
#define TDC_SSN_IOMUX                                            (IOMUX_PINCM29)
/* Defines for SCK: GPIOB.13 with pinCMx 30 on package pin 1 */
#define TDC_SCK_PIN                                             (DL_GPIO_PIN_13)
#define TDC_SCK_IOMUX                                            (IOMUX_PINCM30)
/* Defines for SO: GPIOB.14 with pinCMx 31 on package pin 2 */
#define TDC_SO_PIN                                              (DL_GPIO_PIN_14)
#define TDC_SO_IOMUX                                             (IOMUX_PINCM31)
/* Defines for SI: GPIOB.15 with pinCMx 32 on package pin 3 */
#define TDC_SI_PIN                                              (DL_GPIO_PIN_15)
#define TDC_SI_IOMUX                                             (IOMUX_PINCM32)
/* Port definition for Pin Group PULSE */
#define PULSE_PORT                                                       (GPIOA)

/* Defines for START: GPIOA.13 with pinCMx 35 on package pin 6 */
#define PULSE_START_PIN                                         (DL_GPIO_PIN_13)
#define PULSE_START_IOMUX                                        (IOMUX_PINCM35)
/* Defines for SP1: GPIOA.12 with pinCMx 34 on package pin 5 */
#define PULSE_SP1_PIN                                           (DL_GPIO_PIN_12)
#define PULSE_SP1_IOMUX                                          (IOMUX_PINCM34)



/* clang-format on */

void SYSCFG_DL_init(void);
void SYSCFG_DL_initPower(void);
void SYSCFG_DL_GPIO_init(void);
void SYSCFG_DL_SYSCTL_init(void);
void SYSCFG_DL_PWM_SG90_init(void);
void SYSCFG_DL_BlueTooth_init(void);
void SYSCFG_DL_SPI_0_init(void);

void SYSCFG_DL_SYSTICK_init(void);

bool SYSCFG_DL_saveConfiguration(void);
bool SYSCFG_DL_restoreConfiguration(void);

#ifdef __cplusplus
}
#endif

#endif /* ti_msp_dl_config_h */
