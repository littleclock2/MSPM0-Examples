#include "oled_spi.h"
#include "oledfont.h"
unsigned int OLED_GRAM[128][8];
// 向SSD1306写入一个字节
// dat: 要写入的数据/命令内容
// cmd: 命令类型标志 0-命令模式，1-数据模式
void OLED_WR_Byte(u8 dat, u8 cmd){
    if (cmd){
        OLED_DC_Set();
    }
    else{
        OLED_DC_Clr();
    }
    while (DL_SPI_isBusy(SPI_OLED_INST)){
    }
    DL_SPI_transmitData8(SPI_OLED_INST, dat);
    while (DL_SPI_isBusy(SPI_OLED_INST)){
    }
    OLED_DC_Set();
}

void OLED_Set_Pos(unsigned char x, unsigned char y)
{
    OLED_WR_Byte(0xb0 + y, OLED_CMD);
    OLED_WR_Byte(((x & 0xf0) >> 4) | 0x10, OLED_CMD);
    OLED_WR_Byte((x & 0x0f) | 0x01, OLED_CMD);
}
// 开启OLED显示
void OLED_Display_On(void)
{
    OLED_WR_Byte(0X8D, OLED_CMD); // SET DCDC命令
    OLED_WR_Byte(0X14, OLED_CMD); // DCDC ON
    OLED_WR_Byte(0XAF, OLED_CMD); // DISPLAY ON
}
// 关闭OLED显示
void OLED_Display_Off(void)
{
    OLED_WR_Byte(0X8D, OLED_CMD); // SET DCDC命令
    OLED_WR_Byte(0X10, OLED_CMD); // DCDC OFF
    OLED_WR_Byte(0XAE, OLED_CMD); // DISPLAY OFF
}
// 清空显存并刷新屏幕，执行后屏幕全黑
void OLED_Clear(void)
{
    u8 i, n;
    for (i = 0; i < 8; i++)
    {
        for (n = 0; n < 128; n++)
            OLED_GRAM[n][i] = 0;
    }
    OLED_Refresh();
}

// 在指定位置显示一个字符,包括部分字符
// x:0~127
// y:0~7 (页地址)
void OLED_ShowChar(u8 x, u8 y, char chr)
{
    unsigned char c = 0, i = 0;
    c = chr - ' '; // 得到偏移后的值
    if (x > Max_Column - 1)
    {
        x = 0;
        y = y + 2;
    }
    if (SIZE == 16)
    {
        for (i = 0; i < 8; i++)
            OLED_GRAM[x + i][y] = F8X16[c * 16 + i];
        for (i = 0; i < 8; i++)
            OLED_GRAM[x + i][y + 1] = F8X16[c * 16 + i + 8];
    }
    else
    {
        for (i = 0; i < 6; i++)
            OLED_GRAM[x + i][y] = F6x8[c][i];
    }
}
// m^n函数
u32 oled_pow(u8 m, u8 n)
{
    u32 result = 1;
    while (n--)
        result *= m;
    return result;
}
// 显示数字
// x,y :起点坐标
// len :数字的位数
// size2:字体大小
// num:数值(0~4294967295);
void OLED_ShowNum(u8 x, u8 y, u32 num, u8 len, u8 size2)
{
    u8 t, temp;
    u8 enshow = 0;
    for (t = 0; t < len; t++)
    {
        temp = (num / oled_pow(10, len - t - 1)) % 10;
        if (enshow == 0 && t < (len - 1))
        {
            if (temp == 0)
            {
                OLED_ShowChar(x + (size2 / 2) * t, y, ' ');
                continue;
            }
            else
                enshow = 1;
        }
        OLED_ShowChar(x + (size2 / 2) * t, y, temp + '0');
    }
}
// 显示一个字符号串
void OLED_ShowString(u8 x, u8 y, char *chr)
{
    unsigned char j = 0;
    while (chr[j] != '\0')
    {
        OLED_ShowChar(x, y, chr[j]);
        x += 8;
        if (x > 120)
        {
            x = 0;
            y += 2;
        }
        j++;
    }
}
// 显示汉字
void OLED_ShowCHinese(u8 x, u8 y, u8 no)
{
    u8 t;
    for (t = 0; t < 16; t++)
    {
        OLED_GRAM[x + t][y] = Hzk[2 * no][t];
    }
    for (t = 0; t < 16; t++)
    {
        OLED_GRAM[x + t][y + 1] = Hzk[2 * no + 1][t];
    }
}

/***********功能描述：显示显示BMP图片128×64起始点坐标(x,y),x的范围0～127，y为需要使用的页的范围1～8*****************/
void OLED_DrawBMP(unsigned char x0, unsigned char y0, unsigned char x1, unsigned char y1, const unsigned char BMP[])
{
    unsigned int j = 0;
    unsigned char x, y;
    unsigned char page_start = y0 / 8;
    unsigned char page_end = (y1 - 1) / 8;
    
    for(y = page_start; y <= page_end; y++)
    {
        for(x = x0; x < x1; x++)
        {
            OLED_GRAM[x][y] = BMP[j++];
        }
    }
    OLED_Refresh();
} 

// 画点函数
// x:0~127
// y:0~63
// t:1 填充 0,清空
void OLED_DrawPoint(u8 x, u8 y, u8 t){
    u8 pos, bx= 0;
    if (x > 127 || y > 63)
        return; // 超出范围直接返回
    
    pos = y / 8; // 计算页地址
    bx = y % 8;  // 计算位偏移
    if(t)
        OLED_GRAM[x][pos] |= 0x01 << bx;
    else
        OLED_GRAM[x][pos] &= ~(0x01 << bx);
}
// 更新显示
void OLED_Refresh(void){
    u8 i, n;
    for (i = 0; i < 8; i++){
        OLED_WR_Byte(0xb0 + i, OLED_CMD); // 设置页地址（0~7）
        OLED_WR_Byte(0x02, OLED_CMD);     // 设置显示位置—列低地址
        OLED_WR_Byte(0x10, OLED_CMD);     // 设置显示位置—列高地址
        for (n = 0; n < 128; n++)// 统一写入数据
            OLED_WR_Byte(OLED_GRAM[n][i], OLED_DATA);
    } // 更新显示
}
// 初始化SSD1306
void OLED_Init(void)
{
    OLED_WR_Byte(0xAE, OLED_CMD); // 关闭OLED显示
    OLED_WR_Byte(0x02, OLED_CMD); // 设置列地址低位
    OLED_WR_Byte(0x10, OLED_CMD); // 设置列地址高位
    OLED_WR_Byte(0x40, OLED_CMD); // 设置显示起始行地址(0x00~0x3F)
    OLED_WR_Byte(0x81, OLED_CMD); // 设置对比度控制寄存器
    OLED_WR_Byte(0xCF, OLED_CMD); // 设置段输出电流亮度(0x00~0xFF)
    OLED_WR_Byte(0xA1, OLED_CMD); // 设置列地址正常模式(0xA0左右反置，0xA1正常)
    OLED_WR_Byte(0xC8, OLED_CMD); // 设置行扫描方向正常(0xC0上下反置，0xC8正常)
    OLED_WR_Byte(0xA6, OLED_CMD); // 设置正常显示模式(0xA6正常，0xA7反色)
    OLED_WR_Byte(0xA8, OLED_CMD); // 设置复用比率(1/64 duty)
    OLED_WR_Byte(0x3f, OLED_CMD); // 具体复用比率值(0x3F表示1/64)
    OLED_WR_Byte(0xD3, OLED_CMD); // 设置显示偏移量，映射RAM计数器(0x00~0x3F)
    OLED_WR_Byte(0x00, OLED_CMD); // 无偏移
    OLED_WR_Byte(0xd5, OLED_CMD); // 设置显示时钟分频比/振荡器频率
    OLED_WR_Byte(0x80, OLED_CMD); // 设置分频比，时钟频率为100帧/秒
    OLED_WR_Byte(0xD9, OLED_CMD); // 设置预充电周期
    OLED_WR_Byte(0xF1, OLED_CMD); // 预充电15个时钟，放电1个时钟
    OLED_WR_Byte(0xDA, OLED_CMD); // 设置COM引脚硬件配置
    OLED_WR_Byte(0x12, OLED_CMD); // COM引脚配置值
    OLED_WR_Byte(0xDB, OLED_CMD); // 设置VCOMH电平
    OLED_WR_Byte(0x40, OLED_CMD); // VCOM取消选择电平(0.65×VCC)
    OLED_WR_Byte(0x20, OLED_CMD); // 设置页寻址模式(0x00/0x01/0x02)
    OLED_WR_Byte(0x02, OLED_CMD); // 页寻址模式值
    OLED_WR_Byte(0x8D, OLED_CMD); // 设置电荷泵使能/禁用
    OLED_WR_Byte(0x14, OLED_CMD); // 电荷泵使能(0x14使能，0x10禁用)
    OLED_WR_Byte(0xA4, OLED_CMD); // 禁用全屏显示(0xA4正常，0xA5全亮)
    OLED_WR_Byte(0xA6, OLED_CMD); // 禁用反色显示(0xA6正常，0xA7反色)
    OLED_WR_Byte(0xAF, OLED_CMD); // 开启OLED面板
    OLED_WR_Byte(0xAF, OLED_CMD); // 显示屏开启
    OLED_Clear();
    OLED_Set_Pos(0, 0);
}
