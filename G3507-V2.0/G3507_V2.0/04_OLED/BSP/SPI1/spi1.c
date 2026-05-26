#include "SPI1/spi1.h"

DL_SPI_backupConfig gSPI_1Backup;
/*
 * User should take care to save and restore register configuration in application.
 * See Retention Configuration section for more details.
 */
bool SYSCFG_DL_saveConfiguration(void)
{
    bool retStatus = true;

    retStatus &= DL_SPI_saveConfiguration(SPI_1_INST, &gSPI_1Backup);

    return retStatus;
}

bool SYSCFG_DL_restoreConfiguration(void)
{
    bool retStatus = true;

    retStatus &= DL_SPI_restoreConfiguration(SPI_1_INST, &gSPI_1Backup);

    return retStatus;
}

static const DL_SPI_Config gSPI_1_config = {
    .mode = DL_SPI_MODE_CONTROLLER,
    .frameFormat = DL_SPI_FRAME_FORMAT_MOTO3_POL1_PHA1,
    .parity = DL_SPI_PARITY_NONE,
    .dataSize = DL_SPI_DATA_SIZE_8,
    .bitOrder = DL_SPI_BIT_ORDER_MSB_FIRST,
};

static const DL_SPI_ClockConfig gSPI_1_clockConfig = {
    .clockSel = DL_SPI_CLOCK_BUSCLK,
    .divideRatio = DL_SPI_CLOCK_DIVIDE_RATIO_1};

void SPI1_init(void)
{
    DL_SPI_reset(SPI_1_INST);
    DL_SPI_enablePower(SPI_1_INST);

    DL_GPIO_initPeripheralOutputFunction(
        GPIO_SPI_1_IOMUX_SCLK, GPIO_SPI_1_IOMUX_SCLK_FUNC);
    DL_GPIO_initPeripheralOutputFunction(
        GPIO_SPI_1_IOMUX_PICO, GPIO_SPI_1_IOMUX_PICO_FUNC);

    //    DL_GPIO_initPeripheralOutputFunction(
    //        GPIO_SPI_1_IOMUX_CS0, GPIO_SPI_1_IOMUX_CS0_FUNC);

    //	DL_GPIO_initDigitalOutput(OLED_DC_IOMUX);
    //    DL_GPIO_setPins(OLED_PORT, OLED_DC_PIN);  // 初始状态为拉高
    //    DL_GPIO_enableOutput(OLED_PORT, OLED_DC_PIN);  // 使能输出
    //
    //	DL_GPIO_initDigitalOutput(OLED_RES_IOMUX);
    //    DL_GPIO_setPins(OLED_PORT, OLED_RES_PIN);  // 初始状态为拉高
    //    DL_GPIO_enableOutput(OLED_PORT, OLED_RES_PIN);  // 使能输出

    DL_SPI_setClockConfig(SPI_1_INST, (DL_SPI_ClockConfig *)&gSPI_1_clockConfig);

    DL_SPI_init(SPI_1_INST, (DL_SPI_Config *)&gSPI_1_config);

    /* Configure Controller mode */
    /*
     * Set the bit rate clock divider to generate the serial output clock
     *     outputBitRate = (spiInputClock) / ((1 + SCR) * 2)
     *     8000000 = (80000000)/((1 + 4) * 2)
     */
    DL_SPI_setBitRateSerialClockDivider(SPI_1_INST, 0);
    /* Set RX and TX FIFO threshold levels */
    DL_SPI_setFIFOThreshold(SPI_1_INST, DL_SPI_RX_FIFO_LEVEL_1_2_FULL, DL_SPI_TX_FIFO_LEVEL_1_2_EMPTY);

    /* Enable module */
    DL_SPI_enable(SPI_1_INST);
}
