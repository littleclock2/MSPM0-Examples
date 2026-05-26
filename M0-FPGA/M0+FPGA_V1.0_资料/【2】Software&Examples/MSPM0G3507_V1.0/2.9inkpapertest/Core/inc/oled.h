#ifndef __OLED_H
#define __OLED_H 
#include "ti_msp_dl_config.h"
#include "stdlib.h"	

#define u8 uint8_t
#define u16 uint16_t
#define u32 uint32_t

//-----------------OLED端口定义---------------- 

#define OLED_SCL_Clr() DL_GPIO_clearPins(GPIO_GRP_0_PORT ,GPIO_GRP_0_SCL_PIN)//SCL
#define OLED_SCL_Set() DL_GPIO_setPins(GPIO_GRP_0_PORT ,GPIO_GRP_0_SCL_PIN)

#define OLED_SDA_Clr() DL_GPIO_clearPins(GPIO_GRP_0_PORT ,GPIO_GRP_0_SDA_PIN)//SDA
#define OLED_SDA_Set() DL_GPIO_setPins(GPIO_GRP_0_PORT ,GPIO_GRP_0_SDA_PIN)

#define OLED_RES_Clr() DL_GPIO_clearPins(GPIO_GRP_0_PORT ,GPIO_GRP_0_RES_PIN)//RES
#define OLED_RES_Set() DL_GPIO_setPins(GPIO_GRP_0_PORT ,GPIO_GRP_0_RES_PIN)

#define OLED_DC_Clr()  DL_GPIO_clearPins(GPIO_GRP_0_PORT ,GPIO_GRP_0_DC_PIN)//DC
#define OLED_DC_Set()  DL_GPIO_setPins(GPIO_GRP_0_PORT ,GPIO_GRP_0_DC_PIN)
 		     
#define OLED_CS_Clr()  DL_GPIO_clearPins(GPIO_GRP_0_PORT ,GPIO_GRP_0_CS_PIN)//CS
#define OLED_CS_Set()  DL_GPIO_setPins(GPIO_GRP_0_PORT ,GPIO_GRP_0_CS_PIN)

#define OLED_BUSY()    DL_GPIO_readPins(GPIO_GRP_0_PORT ,GPIO_GRP_0_BUSY_PIN)


#define OLED_W   128
#define OLED_H   296


typedef struct {
    u8 *Image;
    u16 Width;
    u16 Height;
    u16 WidthMemory;
    u16 HeightMemory;
    u16 Color;
    u16 Rotate;
    u16 WidthByte;
    u16 HeightByte;
} PAINT;
extern PAINT Paint;

#define ROTATE_0            0   //屏幕正向显示
#define ROTATE_90           90  //屏幕旋转90度显示
#define ROTATE_180          180 //屏幕旋转180度显示
#define ROTATE_270          270 //屏幕旋转270度显示

#define WHITE          0xFF   //显示白色
#define BLACK          0x00   //显示黑色
#define RED            BLACK   //显示红色

void OLED_WR_Bus(u8 dat);   //模拟SPI时序
void OLED_WR_REG(u8 reg);   //写入一个命令
void OLED_WR_DATA8(u8 dat); //写入一个字节
void OLED_AddressSet(u16 xs,u16 ys,u16 xe,u16 ye);  //设置位置函数
void OLED_Init(void);       //初始化屏幕

void Epaper_READBUSY(void); 
void EPD_Update(void);      

void Paint_NewImage(u8 *image,u16 Width,u16 Height,u16 Rotate,u16 Color); 					 //创建画布控制显示方向
void OLED_Clear(u16 Color);																													 //清屏函数
void OLED_DrawPoint(u16 Xpoint,u16 Ypoint,u16 Color);                                //画点
void OLED_DrawLine(u16 Xstart,u16 Ystart,u16 Xend,u16 Yend,u16 Color);               //画线
void OLED_DrawRectangle(u16 Xstart,u16 Ystart,u16 Xend,u16 Yend,u16 Color,u8 mode);  //画矩形
void OLED_DrawCircle(u16 X_Center,u16 Y_Center,u16 Radius,u16 Color,u8 mode);        //画圆
void OLED_ShowChar(u16 x,u16 y,char chr,u16 size1,u16 color);                         //显示字符
void OLED_ShowString(u16 x,u16 y,char *chr,u16 size1,u16 color);                       //显示字符串
void OLED_ShowNum(u16 x,u16 y,u32 num,u16 len,u16 size1,u16 color);                  //显示数字
void OLED_ShowChinese(u16 x,u16 y,u16 num,u16 size1,u16 color);                      //显示中文
void OLED_ShowPicture(u16 x,u16 y,u16 sizex,u16 sizey,const u8 BMP[],u16 color);      //显示图片
void OLED_Display(u8 *Image1,u8 *Image2);																	 				 //更新到屏幕
void OLED_GUIInit(void);																														 //屏幕GUI初始化
void OLED_SelectImage(u8 *image);

#endif


