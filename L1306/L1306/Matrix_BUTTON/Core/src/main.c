#include "ti_msp_dl_config.h"
#include "oled.h"
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
float SV;
#define COMP_0_INST_REF_VOLTAGE_mV (3300)//代表参考电压,其值为3300mV
#define COMP_0_INST_DAC8_OUTPUT_VOLTAGE_mV (800)//设置初始直流输出电压值

volatile bool gCheckADC;//用于判断ADC是否就绪的标志
volatile uint16_t gAdcResult;

typedef struct{
    uint16_t volt[200];  
    uint32_t time[200];  
    uint16_t index; // 当前数据点  
    uint16_t size;  // 当前有效数据的数量 
}WaveDateDef;//波形数据储存

uint32_t utick = 0;//计时器中断使用计数装置
WaveDateDef WaveData;//定义波形数据变量
uint16_t vpp,vmid,duty;

float vrms,term = 0,hz = 0;
//函数声明阶段
uint16_t CalDutyCycle(WaveDateDef * wfd, uint32_t period, uint16_t threshold);
uint16_t Vpp();
float Rms();
uint16_t Max(uint16_t a,uint16_t b);
uint16_t Min(uint16_t a,uint16_t b);
void TermCalc();
void SV_Calc();
uint8_t Judgement();
uint8_t Judgement_1();
int CalF();
int main(void){
    int circle = 0;
	gCheckADC = false;
	
    SYSCFG_DL_init(); // Initialize the device

	NVIC_EnableIRQ(ADC12_0_INST_INT_IRQN);//ADC中断使能
    DL_COMP_enable(COMP_0_INST);//比较器与AD模块启动
    DL_ADC12_startConversion(ADC12_0_INST);//ADC开始转换
	
    const uint32_t dacValue = (COMP_0_INST_DAC8_OUTPUT_VOLTAGE_mV * 255) /COMP_0_INST_REF_VOLTAGE_mV;//计算输出的直流电压值对应的DACCode0
	
	DL_COMP_setDACCode0(COMP_0_INST, dacValue);//写入dacValue
	//初始化数据
    WaveData.index = 0;
    WaveData.size = 0;

	OLED_Init();//初始化
	OLED_Clear();//清除缓存
    OLED_ShowString(2,2,"Your ID Here");
    delay_ms(2000);
	while (false == gCheckADC){
        __WFE();
    }
    OLED_Clear();
    OLED_ShowString(2,0,"Info:");
    OLED_ShowString(48,0,"Hz:");
	OLED_ShowString(2,2,"Vpp:");
	OLED_ShowString(2,4,"Vrms:");
	OLED_ShowString(72,6,"Duty:");
	OLED_ShowString(2,6,"F:");
    while(1){
        gAdcResult =  WaveData.volt[WaveData.index];
        vpp = Vpp() * 0.94;//计算峰峰值
        vmid = vpp/2;//计算中间值
        vrms = Rms() *1000 ;//计算vrms
        SV_Calc();
		// term = (SV * 2 * 1000 / 10000);
		// hz = 1000/term;
        hz = CalF() *50;
        if((int)hz%100>=50)hz+=50;
        term = (1/hz)*100000;
        uint8_t typeflag;
        typeflag = Judgement_1();
        
        if(circle >= 100){//刷新显示区域

            OLED_ShowNum(70,0,hz,4,16);//显示频率
            OLED_ShowNum(40,2,vpp,4,16);//显示Vpp
            OLED_ShowNum(48,4,vrms/1000,4,16);OLED_ShowChar(84,4,'.');OLED_ShowNum(88,4,((int)vrms)%100,2,16);//显示Vrms
            OLED_ShowNum(16,6,term,6,16);//显示周期
            OLED_ShowNum(112,6,duty,2,16);//显示占空比
            
            switch(typeflag){
				case 1:
					OLED_ShowString(72,2,"Fang    ");
					break;
				case 2:
					OLED_ShowString(72,2,"Juchi    ");
					break;
				case 3:
					OLED_ShowString(72,2,"ZhengXian");
					break;
				default:
					break;
			}
            circle = 0;
        }
        ++circle;//循环自增
    }
		
}
// 计算占空比  
uint16_t CalDutyCycle(WaveDateDef * wfd, uint32_t period, uint16_t threshold) {  
    uint32_t highTime = 0;  
    for (uint16_t i = 0; i < wfd->size; ++i) {  
        // 查找高电平的开始  
        if (wfd->volt[i] > threshold) {  
            int start = i;  
            // 查找高电平的结束  
            while (i < wfd->size && wfd->volt[i + 1] > threshold) {  
                ++i;  
            }  
            // 计算高电平时间并累加到highTime  
            highTime += (wfd->time[i] - wfd->time[start]);  
        }  
    }  
    // 计算占空比  
    return (highTime / period);  
}
void ADC12_0_INST_IRQHandler(void)//ADC的中断函数
{
    switch (DL_ADC12_getPendingInterrupt(ADC12_0_INST)) {
        case DL_ADC12_IIDX_MEM0_RESULT_LOADED://如果MEM0（对应通道0）中有数据写入，则存储其数据进入数组adcdata
            gCheckADC = true;	
			if (WaveData.size < 200) {  //循环添加数据点
                WaveData.volt[WaveData.index] = DL_ADC12_getMemResult(ADC12_0_INST, DL_ADC12_MEM_IDX_0)*20/23; 
                WaveData.time[WaveData.index] = utick;
                WaveData.size++;  
			} 
            else {  // 覆盖最旧的数据  
                WaveData.volt[WaveData.index] = DL_ADC12_getMemResult(ADC12_0_INST, DL_ADC12_MEM_IDX_0)*20/23;
                WaveData.time[WaveData.index] = utick;
                WaveData.index = (WaveData.index + 1) % 200;  
			}
            break;
        default:
            break;
    }
}
uint16_t Vpp(){
    uint16_t max_volt = 0,min_volt = 65535;
    for (int i = 0; i < WaveData.size; i++){
        if(WaveData.volt[i] < min_volt){
            min_volt = WaveData.volt[i];
        }
        else if(WaveData.volt[i] > max_volt){
            max_volt = WaveData.volt[i];
        }
    }
    return max_volt - min_volt;
}
uint16_t Max(uint16_t a,uint16_t b){
    return a>b?a:b;
}
uint16_t Min(uint16_t a,uint16_t b){
    return a<b?a:b;
}
void SV_Calc(){
	bool abmid = (WaveData.volt[0] > vmid);
	uint8_t Ccnt = 0;
	for(uint16_t i = 1;i < WaveData.size;++i){
		if(WaveData.volt[i] > vmid&&!abmid){
			abmid = true;
			++Ccnt;
		} else if(WaveData.volt[i] < vmid&&abmid){
			abmid = false;
			++Ccnt;
		} 
	}
	SV = (float)(WaveData.size - 1)*1.0 / (float)Ccnt * 2.0;
}
void TermCalc(){
	bool abmid = (WaveData.volt[0] > vmid);
	uint8_t count = 0;
    float temp;
	for(uint16_t i = 1;i < WaveData.size;++i){//判断在中值电压上下的点数
		if(WaveData.volt[i] > vmid && !abmid){
			abmid = true;
			++count;
		} 
        else if(WaveData.volt[i] < vmid && abmid){
			abmid = false;
			++count;
		} 
	}
	temp = (float)(WaveData.size - 1)*1.0 / (float)count * 2.0;
    term = (temp * 2 * 1000 / 10000);//计算周期
}
float Rms(){
    float sum,temp_rms;
    for (int i = 0; i < WaveData.size; i++){
        sum += (float) WaveData.volt[i]*WaveData.volt[i];
    }
    temp_rms = sqrt(sum/WaveData.size);
    return temp_rms;
}
void SysTick_Handler(){
	//Milisecond Source
	SysTick->CTRL &= ~(1<<16);
	++utick;
	if(utick >= 4294967295ul) utick = 0;
}
uint8_t Judgement(){
    int flag_1 = 0,flag_2 = 0,flag_3 = 0;
    uint16_t max_volt = 0,min_volt = 65535,mid ,temp_flag;
    int j = 0;
    for (int i = 0; i < WaveData.size; i++){
        if(WaveData.volt[i] < min_volt){
            min_volt = WaveData.volt[i];
        }
        else if(WaveData.volt[i] > max_volt){
            max_volt = WaveData.volt[i];
        }
    }
    for(;j<200;j++){
        if((WaveData.volt[j]>(max_volt-100)) ||(WaveData.volt[j]<(min_volt < 100)))flag_1 ++;
    }
    if(flag_1>170)return 1;
    mid = (max_volt + min_volt)/2;
    temp_flag = Rms(); 
    if((max_volt-min_volt)*1000/(temp_flag/1000)>1350)return 3;
    return 2;
}
int CalF(){
    uint16_t v,max = 0,min = 63355,temp_mid;
    int cycle = 0,flag = 0;
    for(int i = 0;i<180;i++){
        max = WaveData.volt[i] > max ? WaveData.volt[i] : max;
        min = WaveData.volt[i] < min ? WaveData.volt[i] : min;
    }
    temp_mid = (max+min)/2;
    for(;cycle<180;cycle ++){
        if((WaveData.volt[cycle]<temp_mid)&&(WaveData.volt[cycle+1]>temp_mid)) flag++;
    }
    return flag;
}
uint8_t Judgement_1(){
    int flag_1 = 0,flag_down = 0,flag_3 = 0;
    uint16_t max_volt = 0,min_volt = 65535,mid ,temp_vpp;
    temp_vpp = vpp;
    int j = 0;
    for (int i = 0; i < WaveData.size; i++){
        if(WaveData.volt[i] < min_volt){
            min_volt = WaveData.volt[i];
        }
        else if(WaveData.volt[i] > max_volt){
            max_volt = WaveData.volt[i];
        }
    }
    for(;j<200;j++){
        if((WaveData.volt[j]>(max_volt-150)) ||(WaveData.volt[j]<(min_volt < 150)))flag_1 ++;
        if(WaveData.volt[j]<vmid)flag_down++;
    }
    if(flag_1>170){
        duty = 100 - 100*flag_down/200;
        return 1;
    }
    if(temp_vpp*1000/(vrms/1000)<1615){
        duty = 100 - 100*flag_down/200;
        return 3;
    }
    else return 2;
};