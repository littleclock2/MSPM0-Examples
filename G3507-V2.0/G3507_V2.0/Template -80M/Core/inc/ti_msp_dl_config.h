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
#define BlueTooth_IBRD_80_MHZ_115200_BAUD                                   (43)
#define BlueTooth_FBRD_80_MHZ_115200_BAUD                                   (26)




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

/* clang-format on */

void SYSCFG_DL_init(void);
void SYSCFG_DL_initPower(void);
void SYSCFG_DL_GPIO_init(void);
void SYSCFG_DL_SYSCTL_init(void);
void SYSCFG_DL_PWM_SG90_init(void);
void SYSCFG_DL_BlueTooth_init(void);
void SYSCFG_DL_SPI_0_init(void);


bool SYSCFG_DL_saveConfiguration(void);
bool SYSCFG_DL_restoreConfiguration(void);

#ifdef __cplusplus
}
#endif

#endif /* ti_msp_dl_config_h */
