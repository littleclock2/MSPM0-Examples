/*

      ___           ___           ___           ___           ___           ___           ___           ___     
     |\__\         /\__\         /\__\         /\  \         /\__\         /\  \         /\  \         /\  \    
     |:|  |       /:/  /        /::|  |       /::\  \       /:/ _/_       /::\  \       /::\  \       /::\  \   
     |:|  |      /:/  /        /:|:|  |      /:/\ \  \     /:/ /\__\     /:/\:\  \     /:/\:\  \     /:/\:\  \  
     |:|__|__   /:/  /  ___   /:/|:|  |__   _\:\~\ \  \   /:/ /:/ _/_   /:/  \:\  \   /::\~\:\  \   /:/  \:\__\ 
     /::::\__\ /:/__/  /\__\ /:/ |:| /\__\ /\ \:\ \ \__\ /:/_/:/ /\__\ /:/__/ \:\__\ /:/\:\ \:\__\ /:/__/ \:|__|
    /:/~~/~    \:\  \ /:/  / \/__|:|/:/  / \:\ \:\ \/__/ \:\/:/ /:/  / \:\  \ /:/  / \/_|::\/:/  / \:\  \ /:/  /
   /:/  /       \:\  /:/  /      |:/:/  /   \:\ \:\__\    \::/_/:/  /   \:\  /:/  /     |:|::/  /   \:\  /:/  / 
   \/__/         \:\/:/  /       |::/  /     \:\/:/  /     \:\/:/  /     \:\/:/  /      |:|\/__/     \:\/:/  /  
                  \::/  /        /:/  /       \::/  /       \::/  /       \::/  /       |:|  |        \::/__/   
                   \/__/         \/__/         \/__/         \/__/         \/__/         \|__|         ~~       

 * @brief       main
 * @language    C
 * @harfware   Template
 * @version     v1.0
 * @date        29-July-2024
 * @author      YunSword
 
*/

/*
 * （待验证）ADC单通道转换使用内部2.5V参考电压示例
 * 主函数循环启动ADC转换，OLED屏幕显示采样值
 * 旋转底板VR1滑动变阻器可以看到数值变化
 * Author: zjs
 */
#include "ti_msp_dl_config.h"
#include "oled_spi.h"
#include "key.h"
#include <stdio.h>
#include "uart_screen.h"

/*以下变量由kbk声明*/
#define BUFFER_CAPA 12
char buffer[BUFFER_CAPA];//数据缓冲区，用于将存储发送的数据,BUFFER_CAPA是宏定义的大小
/* 检查adc是否完成转换 */
volatile bool gCheckADC;
int choice = 0;
void UART_Send(uint8_t *Data_Temp){
	uint8_t i;

	for(i=0;i<2;i++){
		DL_UART_transmitData(UART0,*(Data_Temp+1));
		while(DL_UART_isTXFIFOFull(UART0)){
			
		}
		Data_Temp--;
	}
}

uint8_t second = 7;
uint8_t year = 1;
void send_data(void);
int main(void){
    /* adc转换结果 */
    uint16_t adcResult;         // adc转换结果（12bit，数字量）
    float adcResult_voltage;    // adc转换结果对应的电压值（单位:mV）

    /* 系统初始化 */
    SYSCFG_DL_init();
    
    //通信初始化
	NVIC_ClearPendingIRQ(UART_0_INST_INT_IRQN );//清除中断标志??
    NVIC_EnableIRQ(UART_0_INST_INT_IRQN );
    
    DL_TimerG_startCounter(TIMER_0_INST);//启动计时器
	NVIC_EnableIRQ(TIMER_0_INST_INT_IRQN);//中断函数启动
    
    OLED_Init();
    OLED_Clear();
    OLED_ShowString(0, 0, "ADC val:");
    OLED_ShowString(0, 2, "voltage:");
    OLED_ShowString(104, 2, "mV");
    /* 开启 adc 中断 */
    NVIC_EnableIRQ(ADC12_0_INST_INT_IRQN);

    /* 变量初始化 */
    gCheckADC = false;

    /* 确保内部参考电压在adc转换前已完成配置 */
    while (DL_VREF_CTL1_READY_NOTRDY == DL_VREF_getStatus(VREF))
        ;
    /* 启动adc转换 */
   DL_ADC12_startConversion(ADC12_0_INST);

    /* 等待adc转换完成 */
    while (false == gCheckADC){
        /* 进入低功耗模式 wait for event */
        __WFE();
    }
    while (1){
        

        /* 将adc采样值读出 */
        adcResult = DL_ADC12_getMemResult(ADC12_0_INST, DL_ADC12_MEM_IDX_0);

        /* 根据公式计算对应的电压值，参考电压2.5V（sysconfig里设置） */
        adcResult_voltage = adcResult * 2500.0 / (4096.0 - 1) - 0.5 * 2500.0 / 4096.0;

        /* 在OLED上显示采样值 */
        OLED_ShowNum(72, 0, adcResult, 4, 16);
        OLED_ShowNum(72, 2, (uint16_t)adcResult_voltage, 4, 16);
        int num  =getKeyValue();
        OLED_ShowNum(0,6,num,2,16);
        OLED_ShowNum(72,6,second,1,16);
        OLED_ShowNum(108,6,year,1,16);
        //UART_Send((uint8_t*)&adcResult);                //发送ADC数据
        
        /* 控制大概0.2s更新一次 */
        delay_cycles(32000000 * 0.2);
        //send_data();
        
        /* 准备下一次采样 */
        gCheckADC = false;
        DL_ADC12_enableConversions(ADC12_0_INST);
    }
}

//通信接受中断函数
void  UART_0_INST_IRQHandler(){
    uint8_t t = 0;
   switch (DL_UART_getPendingInterrupt(UART_0_INST )){ //检测是否串口中??
        case DL_UART_MAIN_IIDX_RX:
            //choice = DL_UART_receiveData(UART_0_INST);
          
            t = DL_UART_receiveData(UART_0_INST);

            HMISendb(UART_0_INST,0xff);
            if(t==0x01) year=2;
			else if(t==0x02) year=3;
			else if(t==0x00) year=1;
            break;
        default:
            break;
    }
}

/* adc中断服务函数 */
void ADC12_0_INST_IRQHandler(void){
    switch (DL_ADC12_getPendingInterrupt(ADC12_0_INST)){
    /* adc转换完成后进入中断 */
    case DL_ADC12_IIDX_MEM0_RESULT_LOADED:
        gCheckADC = true;
        break;
    default:
        break;
    }
}
//通信接受中断函数
void  UART_1_INST_IRQHandler(){
    uint8_t t = 0;
   switch (DL_UART_getPendingInterrupt(UART_1_INST )){ //检测是否串口中??
        case DL_UART_MAIN_IIDX_RX:
            t = DL_UART_receiveData(UART_1_INST);

            HMISendb(UART_1_INST,0xff);
            if(t==0x01) year=2;
			else if(t==0x02) year=3;
			else if(t==0x00) year=1;
            break;
        default:
            break;
    }
}
//中断函数
void TIMER_0_INST_IRQHandler (void){
	switch( DL_TimerG_getPendingInterrupt (TIMER_0_INST)){
		case DL_TIMERG_IIDX_ZERO:
			{//向外界实时发送信??
				
				uint8_t month = 3;
				uint8_t day = 4;
				uint8_t hour = 5;
				uint8_t minute = 6;
				
				//DL_UART_transmitData(UART_0_INST,year);
				//固定向外界发送信??
				//printf("%d,%d,%d,%d,%d,%d\n",year_1*100 + year_2,month,day,hour,minute,second);
				unsigned char  buf[64];
				sprintf((char *)buf,"n0.val=%d",year);  //显示年
				HMISends(UART_1_INST,(char *)buf);
				HMISendb(UART_1_INST,0xff);

				sprintf((char *)buf,"n1.val=%d",month);  //显示月
				HMISends(UART_1_INST,(char *)buf);
				HMISendb(UART_1_INST,0xff);

				sprintf((char *)buf,"n2.val=%d",day);  //显示日
				HMISends(UART_1_INST,(char *)buf);
				HMISendb(UART_1_INST,0xff);

				sprintf((char *)buf,"n3.val=%d",hour);  //显示时
				HMISends(UART_1_INST,(char *)buf);
				HMISendb(UART_1_INST,0xff);

				sprintf((char *)buf,"n4.val=%d",minute);  //显示分
				HMISends(UART_1_INST,(char *)buf);
				HMISendb(UART_1_INST,0xff);

				sprintf((char *)buf,"n5.val=%d",second);  //显示秒
				HMISends(UART_1_INST,(char *)buf);
				HMISendb(UART_1_INST,0xff);
                second++;
			}
            send_data();
			break;
		default:
			break;
	}
}
/*下面两个函数由kbk编写*/
void to_byte(char* space,u8 byte_num,u8 capa,uint32_t data){//space是要储存到的位置，byte_num是该数据所占的字节数,capa是数组的容量
	static u8 cnt = 0;//cnt是已经存入数据的个数 
	char* p = (char*) & data;
	for(u8 i = 0;i < byte_num;i++){
		space[cnt] = * p;
		p++;
		cnt = (cnt + 1 ) % capa;
	}
}
void send_data(void){
/*在verilog代码里面，mode占4位，一个byte就够了，
	其中高两位是：
				00：不调制
				01：AM
				02: FM
				低两位：
				00: 没有波形
				01：sine
				10: 三角
				11：方波
	wave_form+4*modulation得到传输数据
*/
    
int wave_form = 3,modulation_frequency= 5000 , frequency= 500000, modulation_coefficient= 10, modulation=1;
	to_byte(buffer,1,BUFFER_CAPA,(wave_form == 4 ? 0 : wave_form) + 4 * modulation);//存储mode
	to_byte(buffer,4,BUFFER_CAPA,frequency);//存储frequency
	to_byte(buffer,2,BUFFER_CAPA,modulation_frequency);//存储modulation_frequency
	to_byte(buffer,1,BUFFER_CAPA,modulation_coefficient);//存储modulation_coefficient
	to_byte(buffer,4,BUFFER_CAPA,0x7f800000);//存储尾帧
	//连续发送信号
	for(u8 i = 0;i < BUFFER_CAPA;i++)
		DL_UART_Main_transmitDataBlocking(UART_1_INST,buffer[i]);
}