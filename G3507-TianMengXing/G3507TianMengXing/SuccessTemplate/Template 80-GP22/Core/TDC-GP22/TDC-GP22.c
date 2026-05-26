#include "TDC-GP22.h"
#include "oled_spi.h"

#define ENABLE_TDC DL_GPIO_clearPins(TDC_GPIO_PORT,TDC_GPIO_TDC_NSS_PIN);
#define DISABLE_TDC DL_GPIO_setPins(TDC_GPIO_PORT,TDC_GPIO_TDC_NSS_PIN);
//定义片选信号
void Tdc_Reset(void)
{
    DL_GPIO_setPins(TDC_GPIO_PORT,TDC_GPIO_TDC_RTN_PIN);
    delay_cycles(10000000);
    ENABLE_TDC DL_GPIO_clearPins(TDC_GPIO_PORT,TDC_GPIO_TDC_RTN_PIN);
    delay_cycles(10000000);
    DL_GPIO_setPins(TDC_GPIO_PORT,TDC_GPIO_TDC_RTN_PIN);
}
void Tdc_test(void)
{
	  
    int Reset = 0x50;
    uint32_t RES0 = 0;

    Tdc_Reset();//硬件复位
    delay_cycles(10000000);
    ENABLE_TDC;
    delay_us(1);
    DL_SPI_transmitData8(SPI_1_INST,Reset); ;//软件复位
    DISABLE_TDC;
    ENABLE_TDC;
    delay_us(1);
    SPIwrite32(0x80009620);
    DISABLE_TDC;
    ENABLE_TDC;
    delay_us(1);
    SPIwrite32(0x81014100);
    DISABLE_TDC;
    ENABLE_TDC;
    delay_us(1);
    SPIwrite32(0x82E00000);
    DISABLE_TDC;
    ENABLE_TDC;
    delay_us(1);
    SPIwrite32(0x83180000);
    DISABLE_TDC;
    ENABLE_TDC;
    delay_us(1);
    SPIwrite32(0x84200000);
    DISABLE_TDC;
    ENABLE_TDC;
    delay_us(1);
    SPIwrite32(0x85080000);
    DISABLE_TDC;
    ENABLE_TDC;
    delay_us(1);
    SPIwrite32(0x86000010);
    DISABLE_TDC;
    delay_cycles(10000000);
    ENABLE_TDC;
    delay_us(1);
    RES0=Tdc_Read32Bits(0xB5);//这里使用的写入8位读取32位的函数，实际上在测试的时候返回8位就可以了，这里不做修改了
    //u1_printf_nonblocking("0x%08x\r\n", RES0);
	DISABLE_TDC;  //验证寄存器
};
uint32_t Tdc_Read32Bits(uint8_t command)//写8读32
{
    uint8_t rx_buffer[4] = {0};
    uint32_t result = 0;

    ENABLE_TDC;                          // 拉低片选使能
    DL_SPI_transmitData8(SPI_1_INST,command);               // 发送8位命令
	result = DL_SPI_receiveData32(SPI_1_INST);
    // 连续接收4个字节
//    if ()
//    {
//        // 组合为32位数据（大端模式）
//        result = ((uint32_t)rx_buffer[0] << 24) |
//                 ((uint32_t)rx_buffer[1] << 16) |
//                 ((uint32_t)rx_buffer[2] << 8)  |
//                 (uint32_t)rx_buffer[3];
//        //u1_printf_nonblocking("rx_buffer: 0x%02x 0x%02x 0x%02x 0x%02x\r\n",
//        //                rx_buffer[0], rx_buffer[1], rx_buffer[2], rx_buffer[3]);  测试使用
//    }
//    else
//    {
//        // 错误处理
//       // u1_printf_nonblocking("SPI Read Error\r\n");
//    }
	 delay_us(1);
    DISABLE_TDC;                         // 拉高片选禁用
    return result;


}
void SPIwrite32(uint32_t data)//写32
{
    uint8_t bytes[4];
    bytes[0] = (data >> 24) & 0xFF;  // 地址 + 高8位
    bytes[1] = (data >> 16) & 0xFF;
    bytes[2] = (data >> 8)  & 0xFF;
    bytes[3] = data & 0xFF;
    // 逐字节发送
    for (uint8_t i = 0; i < 4; i++) {
        DL_SPI_transmitDataBlocking8(SPI_1_INST, bytes[i]);
    }
}
