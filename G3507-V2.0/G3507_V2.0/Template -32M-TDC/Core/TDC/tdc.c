#include "tdc.h"

// TDC-GP22 SPI通信格式
// Clock Polarity Low：空闲时钟为低电平
// Clock Phase 2：数据在第二个时钟边沿（下降沿）被采样
// MSB First：从最高位（MSB）开始传输以最低位（LSB）结束
// SSN：传输数据时为低电平

// 引脚配置

#define SSN1  DL_GPIO_setPins(TDC_PORT, TDC_SSN_PIN)
#define SSN0  DL_GPIO_clearPins(TDC_PORT, TDC_SSN_PIN)

#define SCK1  DL_GPIO_setPins(TDC_PORT,TDC_SCK_PIN)
#define SCK0  DL_GPIO_clearPins(TDC_PORT, TDC_SCK_PIN)

#define SI1   DL_GPIO_setPins(TDC_PORT, TDC_SI_PIN)
#define SI0   DL_GPIO_clearPins(TDC_PORT,  TDC_SI_PIN)

#define RSTN1 DL_GPIO_setPins(TDC_PORT, TDC_RSTN_PIN)
#define RSTN0 DL_GPIO_clearPins(TDC_PORT, TDC_RSTN_PIN)

#define SO()    DL_GPIO_readPins(TDC_PORT,TDC_SO_PIN)
#define INTN()  DL_GPIO_readPins(TDC_PORT,TDC_INTN_PIN)

// 写8位数据，不操作SSN(从选)引脚
static void _write8(uint8_t buf) {
    for (int i = 7; i >= 0; i--) {
        SCK1;
        if (buf & (1 << i))
            SI1;
        else
            SI0;
        delay_us(1);
        SCK0;
        delay_us(1);
    }
}

// 写32位数据，不操作SSN(从选)引脚
static void _write32(uint32_t buf) {
    for (int i = 31; i >= 0; i--) {
        SCK1;
        if (buf & (1 << i))
            SI1;
        else
            SI0;
        delay_us(1);
        SCK0;
        delay_us(1);
    }
}

// 读8位数据，不操作SSN(从选)引脚
static uint32_t _read8() {
    uint32_t buf = 0;
    for (int i = 7; i >= 0; i--) {
        SCK1;
        delay_us(1);
        SCK0;
        if (SO())
            buf |= (1 << i);
        delay_us(1);
    }
    return buf;
}

// 读32位数据，不操作SSN(从选)引脚
static uint32_t _read32() {
    uint32_t buf = 0;
    for (int i = 31; i >= 0; i--) {
        SCK1;
        delay_us(1);
        SCK0;
        if (SO())
            buf |= (1 << i);
        delay_us(1);
    }
    return buf;
}

// 写8位数据，操作SSN(从选)引脚
static void write8(uint8_t buf) {
    SSN0;
    delay_us(1);

    _write8(buf);

    delay_us(1);
    SSN1;
}

// 写32位数据，操作SSN(从选)引脚
static void write32(uint32_t buf32) {
    SSN0;
    delay_us(1);

    _write32(buf32);

    delay_us(1);
    SSN1;
}

// 首先写8位数据，然后读8位数据，操作一次SSN(从选)引脚
static uint32_t write8_Read8(uint8_t wbuf8) {
    SSN0;
    delay_us(1);

    // 写8位数据
    _write8(wbuf8);

    // 读32位数据
    uint32_t rbuf = _read8();

    delay_us(1);
    SSN1;

    return rbuf;
}

// 首先写8位数据，然后读32位数据，操作一次SSN(从选)引脚
static uint32_t write8_read32(uint8_t wbuf8) {
    SSN0;
    delay_us(1);

    // 写8位数据
    _write8(wbuf8);

    // 读32位数据
    uint32_t rbuf = _read32();

    delay_us(1);
    SSN1;

    return rbuf;
}

// 定点数转浮点数
static float fixed_to_float(uint32_t fixedPoint) {
    int16_t integerPart = (int16_t) ((fixedPoint >> 16) & 0xFFFF);  // 获取高16位整数部分
    uint16_t fractionalPart = fixedPoint & 0xFFFF;  // 获取低16位小数部分

    float result = (float)integerPart + ((float)fractionalPart / 65536);    // 将小数部分除以2^16转换为浮点数

    return result;
}

// TDC硬件初始化
void TDC_Reset_Hardware() {
    RSTN1;
    delay_us(100);
    RSTN0;
    delay_us(100);
    RSTN1;
    delay_ms(1); // 要至少等待500us让模拟电路部分启动
}

// TDC软件初始化
void TDC_Reset_Software() {
    write8(0x50); // Power On Reset
    delay_ms(1); // 要至少等待500us让模拟电路部分启动
}

// TDC配置
void TDC_Config() {
    TDC_Reset_Hardware();
	TDC_Reset_Software();
	
//    write32(0x80009620); // 测量范围1，4M晶振二分频，4M晶振上电后一直起振，自动校准，校准陶瓷晶振时间为8个32K周期，上升沿敏感
//    write32(0x81014100); // STOP1-START
//    write32(0x82E00000); // 开启所有中断源，单边沿敏感
//    write32(0x83180000); // 几乎全为默认值
//    write32(0x84200000); // 全为默认值
//    write32(0x85080000); // 关闭噪声单元
//    write32(0x86000010); // 测量精度从90ps加倍到45ps

//     write32(0x80E30BE8); // 测量范围1，4M晶振二分频，4M晶振上电后一直起振，自动校准，校准陶瓷晶振时间为8个32K周期，上升沿敏感
//     write32(0x81214200); // STOP1-START
//     write32(0x82E00000); // 开启所有中断源，单边沿敏感
//     write32(0x83000000); // 几乎全为默认值
//     write32(0x84200000); // 全为默认值
//     write32(0x85100000); // 关闭噪声单元
//     write32(0x86000010); // 测量精度从90ps加倍到45ps
	
	write32(0x80E30BE0); //    测量范围1，4M晶振二分频，4M晶振上电后一直起振，自动校准，校准陶瓷晶振时间为8个32K周期，上升沿敏感
     write32(0x81014200); // STOP1-START
     write32(0x82E00000); // 开启所有中断源，单边沿敏感
     write32(0x83000000); // 几乎全为默认值
     write32(0x84200000); // 全为默认值
     write32(0x85100000); // 关闭噪声单元
     write32(0x86000000); // 测量精度从90ps加倍到45ps
	
}

// 测试TDC通信，返回寄存器1的高8位
uint32_t TDC_Test() {
    gp22_wr_config_reg_gpio(0x81, 0x88011022); // 写寄存器1，测试通信
    delay_us(10);
    uint32_t reg1_msb8 = write8_Read8(0xB5); // 显示写寄存器1中的高8位, 用来测试通信
	//uint8_t reg = write8_Read8(0x11); // 显示写寄存器1中的高8位, 用来测试通信
	//uint8_t out = write8_Read8(0xB5);
    return reg1_msb8;
}

// 将TDC测量值转换为时间差（ns）
float TDC_Value_to_Time_ns(uint32_t tdc_value) {
    float tdc_value_float = fixed_to_float(tdc_value);
    float ns = tdc_value_float / (4e6f / 2) * 1e9f;
	ns = (ns - 3093.1)/1.97726;
    return ns;
}

// 启动一次TDC测量，start、stop开始接收信号
void TDC_Start_Measure() {
    write8(0x70); // Init
	delay_ms(1);
//	uint32_t status = write8_read32(0xB4);
	write8(0x05);
	delay_ms(1);
}

// 等待读取TDC测量结果，需要先启动TDC测量，超时返回0xFFFFFFFF
// 测量模式1下最大时间差：2*Tref*DIV_CLKHS=1us，超时TDC读出的数据为0xFFFFFFFF
uint32_t TDC_Get_Measure_Value(uint32_t timeout_ms) {
    uint32_t t = DL_SYSTICK_getValue();

   while (INTN()) {
       delay_us(1);
        if (DL_SYSTICK_getValue() - t > timeout_ms) {
            return 0xFFFFFFFF; // 测量超时
        }
   }
//	uint32_t timeout = 100; // ms
//		  while(INTN() && timeout--) delay_ms(1);
//		  
//		  if(timeout == 0 ||timeout >100) {
//			// 超时处理
//	uint32_t status = write8_read32(0xB4);
//			// 分析status寄存器
//		  } else {
//			// 成功读取数据
//			uint32_t result = write8_read32(0xB0);
//		  }
    delay_us(1);
    uint32_t value = write8_read32(0xB0); // Read REG0

    return value;
}

void gp22_wr_config_reg_gpio(uint8_t opcode_address, uint32_t config_reg_data) {
    // 片选使能
    SSN0;
    delay_us(1);
    
    // 发送操作码+地址
    _write8(opcode_address);
    delay_us(1);
    
    // 发送数据字节（高位在前）
    _write8(config_reg_data >> 24);  // Data Byte High
    delay_us(1);
    _write8(config_reg_data >> 16);  // Data Byte Mid2
    delay_us(1);
    _write8(config_reg_data >> 8);   // Data Byte Mid1
    delay_us(1);
    _write8(config_reg_data);        // Data Byte Low
    delay_us(1);
    
    // 片选禁用
    SSN1;
}

// 使用GPIO模拟SPI的版本
uint32_t gp22_read_n_bytes_gpio(uint8_t n_bytes,uint8_t read_addr){
    uint32_t Result_read = 0;
    uint8_t read_opcode_addr = read_addr;

    // 片选使能
    SSN0;
    delay_us(1);

    // 发送读取操作码+地址
    _write8(read_opcode_addr);
    delay_us(1);

    // 丢弃第一个接收字节（虚拟读取）
    (void)_read8();
    delay_us(1);
	Result_read = _read32();
//    // 读取n字节数据
//    for (uint8_t n = 1; n < n_bytes; n++){
//        Result_read <<= 8;
//        Result_read |= _read8();
//        delay_us(1);
//    }
    // 片选禁用
    SSN1;
    // 整形返回
    return Result_read;
}