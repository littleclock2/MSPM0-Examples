#include "adf4351.h"
#include "oled_spi.h"

//-----------------------------------------------------------------
u32 R=125;  // R为参考分配器的数值，计算公式：输入频率/（2*R）=0.1  
						// 注：输入频率的单位为MHz，R的范围为0~1023的整数
					  // 默认输入频率为板载25M晶振，故得R为125。 
//-----------------------------------------------------------------

//-----------------------------------------------------------------
// 初始化程序区
//-----------------------------------------------------------------



//-----------------------------------------------------------------
// void GPIO_AD4351_Init(void)
// 函数功能: ADF4351引脚配置函数
// 入口参数: 无
// 返回参数: 无
// 全局变量: 无
// 注意事项: 无
//-----------------------------------------------------------------

void GPIO_AD4351_Init(void)
{ 
//	GPIO_InitTypeDef GPIO_InitStructure;

//	RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOD, ENABLE);   
//	
//	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_14 | GPIO_Pin_12 |	GPIO_Pin_10 | GPIO_Pin_8 ; 
//	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
//	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;		// 推挽输出
//	GPIO_Init(GPIOD, &GPIO_InitStructure);
}

//-----------------------------------------------------------------
//函数名称:void ADF4351_Init(u32 date)
//函数功能:ADF4351初始化
//入口参数:无
//出口参数:无
//-----------------------------------------------------------------

void ADF4351_Init(u32 date)
{
	ADF_CE_Set;										
	delay_us (5);
	ADF_CLK_Clr;
	ADF_LE_Set;
	ADF_DATA_Clr;
	ADF4351_Wdata(0x00580005);	 // 设置寄存器5 ：LD设置为数字锁定监测模式
	ADF4351_Wdata(0x0060a43c);	 // 设置寄存器4 : 差分输出功率设置为5dbm，使能静音至检测到锁定，频段选择时钟设为10K 
	ADF4351_Wdata(0x006004b3);	 // 设置寄存器3	：charge cancellation，ABP设为1
    ADF4351_Wdata(0x0D003Fc2| R<<14);	  // 设置寄存器2：电荷泵电流设为5mA，LDP,LDF设为1。
	ADF4351_Wdata(0x08008011);			     //	设置寄存器1 ：预分配器设为8/9
	ADF4351_Wdata(0x00000000|date<<15);	 // N分配器数据写入寄存器R0 
}

//-----------------------------------------------------------------
//函数名称:void ADF4351_Wdata(u32 dat)
//函数功能:ADF4351写数据
//入口参数:无
//出口参数:无
//-----------------------------------------------------------------

void ADF4351_Wdata(u32 dat)
{
	u8 i;
	ADF_CLK_Clr;
	ADF_LE_Clr;
	for(i=0; i<32; i++)
	{
		if( dat & 0x80000000 )
			ADF_DATA_Set;
		else
			ADF_DATA_Clr;	
		dat <<= 1;		
		ADF_CLK_Set;
		ADF_CLK_Clr;	
	}
	ADF_LE_Set;	
}
void ADF4351_WriteFre(u32 F)
{
    F *=10;
    // 根据频率范围设置寄存器4（RF Divider）
    if(F >= 690 && F <= 1370) {
        ADF4351_Wdata(0x0050443C);
    } else if(F > 1370 && F <= 2740) {
        ADF4351_Wdata(0x0040443C);
    } else if(F > 2740 && F <= 5490) {
        ADF4351_Wdata(0x0030143C);
    } else if(F > 5490 && F <= 10990) {
        ADF4351_Wdata(0x0020143C);
    } else if(F > 10990 && F <= 21990) {
        ADF4351_Wdata(0x0010143C);
    } else if(F > 21990) {
        ADF4351_Wdata(0x0000143C);
    } else {
        ADF4351_Wdata(0x0060443C);
    }

    // 设置寄存器0（频率字）
    ADF4351_Wdata(0x00000000 | (F << 15)); // F左移15位构成频率字
}