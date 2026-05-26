#ifndef LED_H
#define LED_H
#include "bsp.h"

#define LED1_PORT (GPIOA)
#define LED1_PIN (DL_GPIO_PIN_28)

#define LED1_IOMUX ((IOMUX_PINCM3))

#define LED2_PORT (GPIOA)
#define LED2_PIN (DL_GPIO_PIN_31)
#define LED2_IOMUX ((IOMUX_PINCM6))

/*控制LED1高低电平*/
#define LED1(en)                                      \
    if (en)                                           \
        DL_GPIO_writePinsVal(LED1_PORT, LED1_PIN, 1); \
    else                                              \
        DL_GPIO_writePinsVal(LED1_PORT, LED1_PIN, 0);

/*控制LED1反转*/
#define LED1_toggle DL_GPIO_togglePins(LED1_PORT, LED1_PIN);

/*控制LED2高低电平*/
#define LED2(en)                                      \
    if (en)                                           \
        DL_GPIO_writePinsVal(LED2_PORT, LED2_PIN, 1); \
    else                                              \
        DL_GPIO_writePinsVal(LED2_PORT, LED2_PIN, 0);

/*控制LED2反转*/
#define LED2_toggle DL_GPIO_togglePins(LED2_PORT, LED2_PIN);

void LED_init(void);
#endif
