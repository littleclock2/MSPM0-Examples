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
 *  DO NOT EDIT - This file is generated for the MSPM0L130X
 *  by the SysConfig tool.
 */
#ifndef ti_msp_dl_config_h
#define ti_msp_dl_config_h

#define CONFIG_MSPM0L130X

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




/* Port definition for Pin Group Switch */
#define Switch_PORT                                                      (GPIOA)

/* Defines for H1: GPIOA.0 with pinCMx 1 on package pin 1 */
#define Switch_H1_PIN                                            (DL_GPIO_PIN_0)
#define Switch_H1_IOMUX                                           (IOMUX_PINCM1)
/* Port definition for Pin Group LED */
#define LED_PORT                                                         (GPIOA)

/* Defines for L0: GPIOA.8 with pinCMx 9 on package pin 12 */
#define LED_L0_PIN                                               (DL_GPIO_PIN_8)
#define LED_L0_IOMUX                                              (IOMUX_PINCM9)
/* Defines for H2: GPIOA.1 with pinCMx 2 on package pin 2 */
#define Switch_H2_PIN                                            (DL_GPIO_PIN_1)
#define Switch_H2_IOMUX                                           (IOMUX_PINCM2)
/* Defines for H3: GPIOA.7 with pinCMx 8 on package pin 11 */
#define Switch_H3_PIN                                            (DL_GPIO_PIN_7)
#define Switch_H3_IOMUX                                           (IOMUX_PINCM8)
/* Defines for H4: GPIOA.12 with pinCMx 13 on package pin 16 */
#define Switch_H4_PIN                                           (DL_GPIO_PIN_12)
#define Switch_H4_IOMUX                                          (IOMUX_PINCM13)
/* Defines for V1: GPIOA.13 with pinCMx 14 on package pin 17 */
#define Switch_V1_PIN                                           (DL_GPIO_PIN_13)
#define Switch_V1_IOMUX                                          (IOMUX_PINCM14)
/* Defines for V2: GPIOA.14 with pinCMx 15 on package pin 18 */
#define Switch_V2_PIN                                           (DL_GPIO_PIN_14)
#define Switch_V2_IOMUX                                          (IOMUX_PINCM15)
/* Defines for V3: GPIOA.17 with pinCMx 18 on package pin 21 */
#define Switch_V3_PIN                                           (DL_GPIO_PIN_17)
#define Switch_V3_IOMUX                                          (IOMUX_PINCM18)
/* Defines for V4: GPIOA.18 with pinCMx 19 on package pin 22 */
#define Switch_V4_PIN                                           (DL_GPIO_PIN_18)
#define Switch_V4_IOMUX                                          (IOMUX_PINCM19)
/* Defines for L1: GPIOA.9 with pinCMx 10 on package pin 13 */
#define LED_L1_PIN                                               (DL_GPIO_PIN_9)
#define LED_L1_IOMUX                                             (IOMUX_PINCM10)
/* Defines for L2: GPIOA.10 with pinCMx 11 on package pin 14 */
#define LED_L2_PIN                                              (DL_GPIO_PIN_10)
#define LED_L2_IOMUX                                             (IOMUX_PINCM11)
/* Defines for L3: GPIOA.11 with pinCMx 12 on package pin 15 */
#define LED_L3_PIN                                              (DL_GPIO_PIN_11)
#define LED_L3_IOMUX                                             (IOMUX_PINCM12)
/* Defines for L4: GPIOA.2 with pinCMx 3 on package pin 6 */
#define LED_L4_PIN                                               (DL_GPIO_PIN_2)
#define LED_L4_IOMUX                                              (IOMUX_PINCM3)
/* Defines for L5: GPIOA.3 with pinCMx 4 on package pin 7 */
#define LED_L5_PIN                                               (DL_GPIO_PIN_3)
#define LED_L5_IOMUX                                              (IOMUX_PINCM4)
/* Defines for L6: GPIOA.15 with pinCMx 16 on package pin 19 */
#define LED_L6_PIN                                              (DL_GPIO_PIN_15)
#define LED_L6_IOMUX                                             (IOMUX_PINCM16)
/* Defines for L7: GPIOA.4 with pinCMx 5 on package pin 8 */
#define LED_L7_PIN                                               (DL_GPIO_PIN_4)
#define LED_L7_IOMUX                                              (IOMUX_PINCM5)

/* clang-format on */

void SYSCFG_DL_init(void);
void SYSCFG_DL_initPower(void);
void SYSCFG_DL_GPIO_init(void);
void SYSCFG_DL_SYSCTL_init(void);



#ifdef __cplusplus
}
#endif

#endif /* ti_msp_dl_config_h */
