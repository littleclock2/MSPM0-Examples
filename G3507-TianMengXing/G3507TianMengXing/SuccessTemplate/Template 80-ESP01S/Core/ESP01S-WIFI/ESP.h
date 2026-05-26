#include "ti_msp_dl_config.h"
#include <stdlib.h>
#include <math.h>
#include "stdio.h"
#include "oled_spi.h"
#include "string.h"
#define uint unsigned int
#define u16 uint16_t

/****************************   STA模式    ****************************/
//STA模式下，WIFI模块要连接的热点（需要自行修改为自己的参数）
#define  STA_WIFISSID       \"YOUR_WIFI_SSID\"               //wifi热点名称
#define  STA_WIFIPASS       \"YOUR_WIFI_PASSWORD\"          //wifi热点密码
#define  SERVER_PORT       8080                //连接的热点端口（一般为80或8080）
#define  SERVER_IP          \"192.0.2.1\"              //连接的协议（TCP或UDP）

/****************************   AP模式    ****************************/
//AP模式下，WIFI开启的热点
#define AP_WIFISSID "ESP-01S"
#define AP_WIFIPASS \"YOUR_AP_PASSWORD\"
typedef struct{
    uint8_t device_id;
    uint8_t device_datalen;
    uint8_t device_data[200];
}AP_PARAMETER;
extern uint8_t wifi_link_flag;//设备连接状态

uint8_t WIFI_Send_To_Client(uint8_t id,char * data); //WIFI发送数据至客户端
uint8_t WIFI_Send_Auto(char * data);//WIFI自动测量长度发送数据
uint8_t WIFI_Send_Data( char *data, uint16_t len);
uint8_t WIFI_Send_Through(char *data); //透传模式下发送数据
uint8_t WIFI_Send_OutThrough(void); //退出透传模式
void WIFI_USART_send_String(unsigned char *str);
uint8_t WIFI_MODE_STA_AP_Init(int mode);        //STA模式初始化
uint8_t WIFI_MODE_AP_Init(void);        //AP模式初始化
//uint8_t Get_Device_connection_status(void);//获取连接状态
//uint8_t Get_WIFI_AP_Data(AP_PARAMETER *ap_parameter);

char WIFI_Send_Cmd(char *cmd,char *ack,unsigned int waitms,unsigned char cnt);
int fputc(int _c, FILE *_fp) ; //重定向printf函数到UART1
int fputs(const char *restrict s, FILE *restrict stream);
int puts(const char *_ptr);