#include "ESP.h"
#include "stdio.h"
#include "string.h"
#include <stdlib.h>

uint8_t wifi_link_flag = 0;//设备连接状态

/* 函数名称：fput系列函数
 * 函数说明：重定向printf函数到UART1
 * 参数：_c - 要输出的字符，_fp - 文件指针（未使用）
 * 返回值：输出的字符
*/
int fputc(int _c, FILE *_fp) {
  DL_UART_Main_transmitDataBlocking(UART_1_INST, _c);
  return _c;
}

int fputs(const char *restrict s, FILE *restrict stream) {
  uint16_t i, len;
  len = strlen(s);
  for (i = 0; i < len; i++) {
    DL_UART_Main_transmitDataBlocking(UART_1_INST, s[i]);
  }
  return len;
}

int puts(const char *_ptr) {
  int cnt = fputs(_ptr, stdout);
  cnt += fputs("\n", stdout);
  return cnt;
}


//函 数 说 明：向WIFI模块发送单个字符
void WIFI_USART_Send_Bit(unsigned char ch){
    //当串口0忙的时候等待，不忙的时候再发送传进来的字符
    while( DL_UART_isBusy(UART_1_INST) == true );
    //发送单个字符
    DL_UART_Main_transmitData(UART_1_INST, ch);
}

uint8_t WIFI_Send_Data(char *data, uint16_t len){
    uint8_t ret = 0;
    char send_buff[20];

    // 设置发送数据长度
    sprintf(send_buff, "AT+CIPSEND=%d\r\n", len);
    WIFI_Send_Cmd(send_buff, ">", 20, 3); // 等待 ">" 提示符
    // 发送实际数据
    WIFI_Send_Cmd(data, "SEND OK", 20, 3); // 等待发送完成
    return ret;
}

//函 数 说 明：向WIFI模块发送字符串
void WIFI_USART_send_String(unsigned char *str){
        while( str && *str ) // 地址为空或者值为空跳出
        {
                WIFI_USART_Send_Bit(*str++);
        }
}
//函 数 说 明：向WIFI模块发送指令，并查看WIFI模块是否返回想要的数据
//函 数 形 参：cmd=发送的AT指令        ack=想要的应答                waitms=等待应答的时间                cnt=等待应答多少次
char WIFI_Send_Cmd(char *cmd,char *ack,unsigned int waitms,unsigned char cnt){
        WIFI_USART_send_String((unsigned char*)cmd);//1.发送AT指令
        // while(cnt--)
        // {
        //       //时间间隔
        //       delay_ms(waitms);
        //       //串口中断接收蓝牙应答
        //       if( WIFI_RX_FLAG == 1 )
        //       {
        //               WIFI_RX_FLAG = 0;
        //               WIFI_RX_LEN = 0;
        //               //查找是否有想要的数据
        //               if( strstr((char*)WIFI_RX_BUFF, ack) != NULL )
        //               {
        //                       return 1;
        //               }
        //               //清除接收的数据
        //               memset( WIFI_RX_BUFF, 0, sizeof(WIFI_RX_BUFF) );
        //       }
        // }
        // WIFI_RX_FLAG = 0;
        // WIFI_RX_LEN = 0;
        return 0;
}


//函 数 说 明：开启AP模式，即模块开启热点让手机连接
uint8_t WIFI_MODE_AP_Init(void){
    uint8_t ret = 0;
    char send_buff[200];

    WIFI_Send_Cmd("AT\r\n", "OK", 10, 3);//测试指令：AT\r\n  成功返回OK  失败返回ERROR

    WIFI_Send_Cmd("AT+CWMODE=2\r\n","OK",30,3);   //配置WIFI AP模式

    sprintf(send_buff, "AT+CWSAP=\"%s\",\"%s\",11,4\r\n", AP_WIFISSID,AP_WIFIPASS );
    WIFI_Send_Cmd(send_buff,"OK",30,3);  //设置wifi账号与密码

    WIFI_Send_Cmd("AT+RST\r\n","ready",800,3); //重新复位
    WIFI_Send_Cmd("AT+CIPMUX=1\r\n","OK",50,3); //开启多个连接

    WIFI_Send_Cmd("AT+CIPSERVER=1,5000\r\n","OK",50,3); //开启服务器设置端口号为5000

    return ret;
}

// STA_AP模式初始化,根据mode参数选择模式，mode=0为非透传模式，mode=1为透传模式
uint8_t WIFI_MODE_STA_AP_Init(int mode){
    uint8_t ret = 0;
    char send_buff[200];
    // 发送测试指令
    WIFI_Send_Cmd("AT\r\n", "OK", 10, 3);
    // 配置WIFI为STA_AP模式
    WIFI_Send_Cmd("AT+CWMODE=3\r\n", "OK", 30, 3);
    //重置
    WIFI_Send_Cmd("AT+RST\r\n", "OK", 50, 3);
    // 连接到指定的WiFi网络
    sprintf(send_buff, "AT+CWJAP=\"%s\",\"%s\"\r\n", STA_WIFISSID, STA_WIFIPASS);
    WIFI_Send_Cmd(send_buff, "OK", 1000, 3); // 连接WiFi可能需要较长时间	
    // 作为客户端连接服务器
    sprintf(send_buff, "AT+CIPSTART=\"TCP\",\"%s\",%d\r\n", SERVER_IP, SERVER_PORT);
    WIFI_Send_Cmd(send_buff, "OK", 100, 3);
    if(mode == 0) {
        // 非透传模式
        WIFI_Send_Cmd("AT+CIPMODE=0\r\n", "OK", 30, 3);
    } else if(mode == 1) {
        // 透传模式
        WIFI_Send_Cmd("AT+CIPMODE=1\r\n", "OK", 30, 3);
        WIFI_Send_Cmd("AT+CIPSEND\r\n", "OK", 30, 3);
    }
    return ret;
}

//函 数 说 明：AP模式下，WIFI发送数据至客户端（连接AP模式下热点的设备）
uint8_t WIFI_Send_To_Client(uint8_t id,char * data){
        uint8_t send_buf[20]={0};
        sprintf((char*)send_buf,"AT+CIPSEND=%d,%d\r\n",id,strlen(data));
        if(WIFI_Send_Cmd((char*)send_buf,">",20,3))
        {
                WIFI_USART_send_String((unsigned char *)data);
                return 1;
        }
        return 0;
}

 //函 数 说 明：WIFI自动测量长度发送数据
uint8_t WIFI_Send_Auto(char * data){
        uint8_t send_buf[20]={0};
        sprintf((char*)send_buf,"AT+CIPSEND=%d\r\n",strlen(data));
        WIFI_Send_Cmd((char*)send_buf,">",20,3);
        //if(WIFI_Send_Cmd((char*)send_buf,">",20,3)){
                WIFI_USART_send_String((unsigned char *)data);
                //return 1;
        //}
        return 0;
}

uint8_t WIFI_Send_Through(char *data){//透传模式下发送数据
        WIFI_Send_Cmd(data, "SEND OK", 20, 3); // 等待发送完成
        return 1; // 返回1表示发送成功
} 

uint8_t WIFI_Send_OutThrough(void){//退出透传模式
        WIFI_Send_Data("+++",6); //发送退出透传模式的指令
        return 1; // 返回1表示退出成功
}
// /******************************************************************
//  * 函 数 名 称：Get_Device_connection_status
//  * 函 数 说 明：获取设备连接状态(AP模式)
//  * 函 数 形 参：无
//  * 函 数 返 回：0=没有设备连接
//  *              1=有设备连接了WIFI
//  *              2=有设备断开了WIFI
//  *              3=有设备连接了服务器
//  *              4=有设备断开了服务器
//  * 作       者：LC
//  * 备       注：手机要连接WIFI模块的步骤是先连接WIFI再连接服务器
// //当有设备连接AP模式下的热点时，WIFI模块会给连接的设备分配IP地址
// //我们只需检测是否有分配地址，则知道是否有设备连接。
// //设备连接时WIFI返回：
// //  +STA_CONNECTED:"f0:6c:5d:d6:f6:18"
// //  +DIST_STA_IP:"f0:6c:5d:d6:f6:18","192.0.2.1"
// //设备断开连接时返回：
// //  +STA_DISCONNECTED:"f0:6c:5d:d6:f6:18"
// ******************************************************************/
// uint8_t Get_Device_connection_status(void)
// {
//     //串口中断接收WIFI应答
//     if( WIFI_RX_FLAG == 1 )
//     {
//         WIFI_RX_FLAG = 0;
//         WIFI_RX_LEN = 0;
//         //有设备连接了热点
//         if( strstr((char*)WIFI_RX_BUFF, "+STA_CONNECTED") != NULL )
//         {
//             //清除接收的数据
//             wifi_link_flag = 1;
//             memset( WIFI_RX_BUFF, 0, sizeof(WIFI_RX_BUFF) );
// #if        DEBUG
//  printf("The device is connected to a hotspot.\r\n");
//  #endif
//             return 1;
//         }
//         //有设备断开了热点
//         if( strstr((char*)WIFI_RX_BUFF, "+STA_DISCONNECTED") != NULL )
//         {
//             //清除接收的数据
//             wifi_link_flag = 0;
//             memset( WIFI_RX_BUFF, 0, sizeof(WIFI_RX_BUFF) );
// #if        DEBUG
//  printf("The device is disconnected from the hotspot.\r\n");
//  #endif
//             return 2;
//         }
//         //有设备连接了服务器
//         if( strstr((char*)WIFI_RX_BUFF, ",CONNECT") != NULL )
//         {
//             //清除接收的数据
//             wifi_link_flag = 2;
//             memset( WIFI_RX_BUFF, 0, sizeof(WIFI_RX_BUFF) );
//             return 3;
// #if        DEBUG
//  printf("The device is connected to the server.\r\n");
//  #endif
//         }
//         //有设备断开了服务器
//         if( strstr((char*)WIFI_RX_BUFF, ",CLOSED") != NULL )
//         {
//             //清除接收的数据
//             wifi_link_flag = 3;
//             memset( WIFI_RX_BUFF, 0, sizeof(WIFI_RX_BUFF) );
//             return 4;
// #if        DEBUG
//  printf("The device is disconnected from the server.\r\n");
//  #endif
//         }
//     }
//     return 0;
// }


// /**********************************************************
//  * 函 数 名 称：Get_WIFI_AP_Data
//  * 函 数 功 能：解析设备发送过来的数据
//  * 传 入 参 数：ap_parameter要将数据保存的地址
//  * 函 数 返 回：1：有设备发送过来数据        0：没有设备发送过来数据
//  * 作       者：LC
//  * 备       注：device_id最大5个  //+IPD,1,4:abcd
// **********************************************************/
// uint8_t Get_WIFI_AP_Data(AP_PARAMETER *ap_parameter)
// {
//     char buff[50];
//     char *test;

//     char i=0;

//     //接收到设备发过来的数据
//     if( strstr((char*)WIFI_RX_BUFF,"+IPD,") != NULL )
//     {
//         test = strstr((char*)WIFI_RX_BUFF,"+IPD,");

//         //记录设备ID号
//         strncpy(buff,test+5,1);
//         buff[1] ='\0';
//         ap_parameter->device_id = atoi(buff);
//         printf("device_id = %s\r\n",buff);

//         //记录发送过来的数据长度
//         strncpy(buff,test+7,strcspn(test+7,":") );
//         buff[ strcspn(test+7,":") ] ='\0';
//                 printf("device_data = %s\r\n",buff);
//         ap_parameter->device_datalen = atoi(buff);
//         printf("device_datalen = %s\r\n",buff);
//         //记录发送过来的数据
//         memset(buff,0,sizeof(buff));
//         while(test[i++]!=':');
//         strncpy(buff, test+i,strcspn(test+i,"\r") );
//                 printf("device_data = %s\r\n",buff);
//         strcpy((char*)ap_parameter->device_data, buff);

//         //清除串口接近缓存
//         Clear_WIFI_RX_BUFF();
//         return 1;
//     }
//     return 0;
// }


/******************************************************************
 * 函 数 名 称：mstrcat
 * 函 数 说 明：字符串连接
 * 函 数 形 参：s1：目标字符串， s2：源字符串
 * 函 数 返 回：无
 * 作       者：LC
 * 备       注：哈希使用
******************************************************************/
// static void mstrcat(char *s1, const char *s2)
// {
//         if(*s1 != NULL)
//                 while(*++s1);
//         while((*s1++ = *s2++));
// }


/******************************************************************
 * 函 数 名 称：WIFI_USART_IRQHandler
 * 函 数 说 明：连接WIFI的串口中断服务函数
 * 函 数 形 参：无
 * 函 数 返 回：无
 * 作       者：LC
 * 备       注：无
******************************************************************/

// void WIFI_USART_IRQHandler(void)
// {
//         if(USART_GetITStatus(WIFI_USART, USART_IT_RXNE) == SET) // 接收缓冲区不为空
//         {
//         //接收数据
//                 WIFI_RX_BUFF[ WIFI_RX_LEN ] = USART_ReceiveData(WIFI_USART);

// #if DEBUG
//         //测试，查看接收到了什么数据
//         printf("%c", WIFI_RX_BUFF[ WIFI_RX_LEN ]);
// #endif
//                 //接收长度限制
//         WIFI_RX_LEN = ( WIFI_RX_LEN + 1 ) % WIFI_RX_LEN_MAX;
//         }
//         if(USART_GetITStatus(WIFI_USART, USART_IT_IDLE) == SET) // 检测到空闲中断
//         {
//                 volatile uint32_t temp;
//                 temp = WIFI_USART->SR; // 读取状态寄存器以清除IDLE标志
//                 temp = WIFI_USART->DR; // 读取数据寄存器以清除IDLE标志

//                 WIFI_RX_BUFF[WIFI_RX_LEN] = '\0'; //字符串结尾补 '\0'
//                 WIFI_RX_FLAG = SET;            // 接收完成
//         }
// }

