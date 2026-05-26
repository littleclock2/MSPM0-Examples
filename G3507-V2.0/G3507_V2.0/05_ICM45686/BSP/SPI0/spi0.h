#ifndef SPI0_H
#define SPI0_H
#include "bsp.h"

/* Defines for SPI_0 */
#define SPI_0_INST SPI0
#define SPI_0_INST_IRQHandler SPI0_IRQHandler
#define SPI_0_INST_INT_IRQN SPI0_INT_IRQn
#define GPIO_SPI_0_PICO_PORT GPIOB
#define GPIO_SPI_0_PICO_PIN DL_GPIO_PIN_17
#define GPIO_SPI_0_IOMUX_PICO (IOMUX_PINCM43)
#define GPIO_SPI_0_IOMUX_PICO_FUNC IOMUX_PINCM43_PF_SPI0_PICO
#define GPIO_SPI_0_POCI_PORT GPIOA
#define GPIO_SPI_0_POCI_PIN DL_GPIO_PIN_4
#define GPIO_SPI_0_IOMUX_POCI (IOMUX_PINCM9)
#define GPIO_SPI_0_IOMUX_POCI_FUNC IOMUX_PINCM9_PF_SPI0_POCI
/* GPIO configuration for SPI_0 */
#define GPIO_SPI_0_SCLK_PORT GPIOB
#define GPIO_SPI_0_SCLK_PIN DL_GPIO_PIN_18
#define GPIO_SPI_0_IOMUX_SCLK (IOMUX_PINCM44)
#define GPIO_SPI_0_IOMUX_SCLK_FUNC IOMUX_PINCM44_PF_SPI0_SCLK

/* Port definition for Pin Group CS */
#define CS_PORT (GPIOA)

/* Defines for PIN: GPIOA.2 with pinCMx 7 on package pin 42 */
#define CS_PIN_PIN (DL_GPIO_PIN_2)
#define CS_PIN_IOMUX (IOMUX_PINCM7)
#define SPI_CS(x) ((x) ? DL_GPIO_setPins(CS_PORT, CS_PIN_PIN) : DL_GPIO_clearPins(CS_PORT, CS_PIN_PIN))

void SPI0_init(void);

uint8_t spi0_read_write_byte(uint8_t dat);

#endif
