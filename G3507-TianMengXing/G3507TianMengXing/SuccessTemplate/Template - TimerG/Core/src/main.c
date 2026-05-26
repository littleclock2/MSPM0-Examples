

#include "ti_msp_dl_config.h"
#include "oled_spi.h"
#include "arm_const_structs.h"
#include "arm_math.h"
#include "stdio.h"
//#include "key.h"
#define TIMER_CAPTURE_DURATION (CAPTURE_0_INST_LOAD_VALUE)
volatile bool gCheckEdgeCaptureTime;
uint8_t choice  =0;
uint16_t index = 0;

#define DAC12_REF_VOLTAGE_mV (3300)
#define DAC12_OUTPUT_VOLTAGE_mV (1000)
#define BUFFER_SIZE 1024
uint16_t dac_value =0;
uint32_t dac_output; // 用于存储计算出的DAC值
double current_power = 0;

uint32_t period;//平均计数值
uint32_t freq;
//PID结构体定义
typedef struct{
  float kp, ki, kd; 						      // 三个静态系数
  float change_p, change_i, change_d;	          // 三个动态参数
  float error, last_error; 						  // 误差、之前误差
  float max_change_i; 							  // 积分限幅
  float output, max_output; 				      // 输出、输出限幅
  int target;                                     // 目标
}PID;
PID power_pid;//创立结构体
volatile bool gCheckADC;        //ADC采集成功标志位
volatile uint16_t ADC_VALUE[BUFFER_SIZE];//ADC采集的数据保存地址
void OLED_Show();
float PID_Calc(PID *pid, float target, double current);
void PID_Init(PID* pid, float p, float i, float d, float maxI, float maxOut, int target);
void PowerDetect(void);
PID Power_Control(int target_power);
//void DMA_Reset(void* data, uint16_t size);
int main(void){

	uint32_t edgeCapture[24] = {0};
	
	char show_buff[100]={0};
    unsigned int adc_value = 0;
    float voltage_value = 0;
    //传入power_pid地址
    //设定 kp 为35
    //设定 ki 为6
    //设定 kd 为10
    //设定 I的最大值 为9999
    //设定 PID最大输出值 为9999
    //设定 目标值 为 98
    PID_Init(&power_pid, 35, 6, 10, 9999, 2000, 2000);
	
    /* 系统初始化 */
    SYSCFG_DL_init();
	//开启捕获定时器
    NVIC_EnableIRQ(CAPTURE_0_INST_INT_IRQN);
    gCheckEdgeCaptureTime = false;
    DL_TimerG_startCounter(CAPTURE_0_INST);
	
    //通信初始化
	NVIC_ClearPendingIRQ(UART_0_INST_INT_IRQN );//清除中断标志??
    NVIC_EnableIRQ(UART_0_INST_INT_IRQN ); 
    //开启ADC
	gCheckADC = false;
    NVIC_ClearPendingIRQ(ADC_Volt_INST_INT_IRQN );//
    NVIC_EnableIRQ(ADC_Volt_INST_INT_IRQN);    
	DL_ADC12_enableConversions(ADC_Volt_INST);
    //开启按键引脚的GPIOB端口中断
    NVIC_EnableIRQ(KEY_INT_IRQN);
	//开启定时器
	NVIC_EnableIRQ(TIMER_0_INST_INT_IRQN);
	DL_TimerG_startCounter(TIMER_0_INST);
    //开启OLED显示
    OLED_Init();
    OLED_Clear();
	
	uint8_t react = 0;
	uint8_t isTestFreq = 0;
	uint8_t isFinish = 0;
	uint32_t temp;
    while (1){
		 if(isTestFreq<10){
			//测频模块
			for(int i  =0;i<24;i++){
				while (false == gCheckEdgeCaptureTime) {
					__WFE();
				}
				gCheckEdgeCaptureTime = false;
				edgeCapture[i] =TIMER_CAPTURE_DURATION - (DL_Timer_getCaptureCompareValue(CAPTURE_0_INST, DL_TIMER_CC_0_INDEX));
				DL_TimerG_setTimerCount(CAPTURE_0_INST, TIMER_CAPTURE_DURATION);
			}
			for(int i =0 ;i<22;i++){
				period += edgeCapture[i+2];
			}
			period = period/23 + react;
			freq  = 1000000/period;
			if(freq >= 9800)//频率均值修正
				react = freq/2001;
			else
				react = freq/2000;
			if(freq<1000)freq +=5;
			//调控采样率
			//DL_ADC12_setSampleTime0(ADC_Volt_INST,16000) ;
			//temp = DL_ADC12_getSampleTime0(ADC_Volt_INST);
			isTestFreq++;
		 }
		
		//采样
		if(isTestFreq>=10){
			NVIC_DisableIRQ(CAPTURE_0_INST_INT_IRQN);
			DL_ADC12_startConversion(ADC_Volt_INST);
			while (false == gCheckADC) {
				__WFE();
			}
			 ADC_VALUE[index++] = DL_ADC12_getMemResult(ADC_Volt_INST, DL_ADC12_MEM_IDX_0);
			if(index >= BUFFER_SIZE){
				index = 0;
				isFinish = 1;
				
			}
			DL_ADC12_enableConversions(ADC_Volt_INST);
			gCheckADC = false;
		}
		//控制部分
		if(isFinish){
			//功耗自动控制模块
			PowerDetect();
		
			Power_Control(power_pid.target);
			delay_ms(50);
			//OLED显示模块
			OLED_Show();
			OLED_Refresh();
			isFinish = 0;
			NVIC_EnableIRQ(CAPTURE_0_INST_INT_IRQN);
		}
		
    }
}
void PowerDetect(void){ //功耗计算
	uint16_t index_hand = 0;
	uint16_t index_tail  =0;
	uint16_t index_flag  =0;
	double temp_rms = 0;
	double actual_rms = 0;
	//归一化为0-3300mV
	for(int i =0;i<BUFFER_SIZE;i++){
		ADC_VALUE[i] = ADC_VALUE[i]*3300/4095;
	}
	//寻找一个完整的波形
	for(int i = 0;i<BUFFER_SIZE;i++){//找1024个点
		if(ADC_VALUE[i]<100 && ADC_VALUE[i+1]>100) { //找第一个完整波形
			index_hand = i;
			index_flag = 1;
		}
		if(index_flag){//
			if(ADC_VALUE[i]>100 && ADC_VALUE[i+1]<100){
				index_tail  =i;//找出一个完整波形的索引
				index_flag = 0;
				break;
			}
		}
	}
	//有效值计算
	for(int i = index_hand;i<index_tail+1;i++){
		temp_rms += pow(ADC_VALUE[i],2);//平方和相加、	
	}
	temp_rms /= (index_tail - index_hand);
	temp_rms = sqrt(temp_rms);//得到平方根,即为有效值
	//滤波后有效值换算为真实有效值
	actual_rms += 0.000000000865416*pow(temp_rms,3);
	actual_rms -= 0.000002607772180 *pow(temp_rms,2);
	actual_rms += 0.003841876391707 *pow(temp_rms,1);
	actual_rms += 0.51594176418395;
	//当前功耗最终计算
	current_power = actual_rms*actual_rms/4;
}
void CAPTURE_0_INST_IRQHandler(void)
{
    switch (DL_TimerG_getPendingInterrupt(CAPTURE_0_INST)) {
        case DL_TIMERG_IIDX_CC0_DN:
			
            gCheckEdgeCaptureTime = true;
            break;
        default:
            break;
    }
}

//通信接受中断函数
void  UART_0_INST_IRQHandler(){
   switch (DL_UART_getPendingInterrupt(UART_0_INST )){ //检测是否串口中??
        case DL_UART_MAIN_IIDX_RX:
            choice = DL_UART_receiveData(UART_0_INST);
            DL_UART_transmitData(UART_0_INST,1);
            break;
        default:
            break;
    }
}

/* adc中断服务函数 */
void ADC_Volt_INST_IRQHandler(void){
    switch (DL_ADC12_getPendingInterrupt(ADC_Volt_INST)){
    /* adc转换完成后进入中断 */
    case DL_ADC12_IIDX_MEM0_RESULT_LOADED:
        gCheckADC = true;
        break;
    default:
        break;
    }
}

void GROUP1_IRQHandler(void){//Group1的中断服务函数
    //读取Group1的中断寄存器并清除中断标志位
    switch( DL_Interrupt_getPendingGroup(DL_INTERRUPT_GROUP_1) ){
        //检查是否是KEY的GPIOB端口中断，注意是INT_IIDX，不是PIN_22_IIDX
        case KEY_INT_IIDX:
            //如果按键按下变为高电平
            if( DL_GPIO_readPins(KEY_PORT, KEY_B21_PIN) > 0 ){
                //设置LED引脚状态翻转
                DL_GPIO_togglePins(LED_PORT, LED_PIN_1_PIN);
                power_pid.target += 200;
                if(power_pid.target >2000){
                    power_pid.target =200;
                }
            }
        break;
    }
}
 void OLED_Show(void){
    //当前功耗
	OLED_ShowString(0,0,"Current Power");
	OLED_ShowNum(0,2,current_power,5,16);
	//目标功耗
    OLED_ShowString(0,4,"Target Power");
    OLED_ShowNum(0,6,power_pid.target,5,16);OLED_ShowNum(60,6,freq,5,16);
    OLED_ShowString(44,6,"mW");
 }  
 
////DMA重新设置
//void DMA_Reset(void* data, uint16_t size) {
//    DL_DMA_setSrcAddr(DMA, DMA_CH0_CHAN_ID, DL_ADC12_getMemResultAddress(ADC_Volt_INST,DL_ADC12_MEM_IDX_0));
//    DL_DMA_setDestAddr(DMA, DMA_CH0_CHAN_ID, (uint32_t)data);
//    DL_DMA_setTransferSize(DMA, DMA_CH0_CHAN_ID, size);
//    DL_DMA_enableChannel(DMA, DMA_CH0_CHAN_ID);
//    return;
//}

 /****************************************************
功能：PID计算
参数：pid = pid的参数输入
     target = 目标值
     current = 当前值
返回：PID计算后的结果
****************************************************/
float PID_Calc(PID *pid, float target, double current)
{
    //用上一次的误差值更新 之前误差last_error
    pid->last_error = pid->error;
    //获取新的误差 = 目标值 - 当前值
    pid->error = target - current;

    //计算比例P = 目标值与实际值之间的误差e
    float pout = pid->error;
    //计算积分I = 误差e的累加
    pid->change_i += pid->error;
    //计算微分D = 当前误差e - 之前的误差last_e
    float dout = pid->error - pid->last_error;

    //积分I 限制不能超过正负最大值
    if(pid->change_i > pid->max_change_i)
    {
      pid->change_i = pid->max_change_i;
    }
    else if(pid->change_i < -pid->max_change_i)
    {
      pid->change_i = -pid->max_change_i;
    }

    //计算输出PID_OUT = （Kp x P）+ （Ki x I）+（Kd x D）
    pid->output = (pid->kp * pout) + (pid->ki * pid->change_i) + (pid->kd * dout);

    //输出 限制不能超过正负最大值
    if(pid->output > pid->max_output) pid->output = pid->max_output;
    else if(pid->output < -pid->max_output) pid->output = -pid->max_output;

    //返回PID计算的结果
    return pid->output;
}

/************************************************
功能：初始化PID各参数
参数：pid = 对应pid的结构体地址
      p = pid的静态kp值
      i = pid的静态ki值
      d = pid的静态kd值
      maxI = pid计算后的I最大值，即最大误差累加值
      maxOut = PID最大输出值
      target = 目标值
************************************************/
void PID_Init(PID* pid, float p, float i, float d, float maxI, float maxOut, int target)
{
    pid->kp = p;
    pid->ki = i;
    pid->kd = d;
    pid->max_change_i = maxI;
    pid->max_output = maxOut;
    pid->target = target;
}

/************************************************
功能：PID-DAC电压输出控制器
参数：target_power = 目标值
返回：对应PID的地址
************************************************/
PID Power_Control(int target_power)
{
	int temp;
    //传入PID静态参数、目标值（目标功率）、当前值（当前获取的实时功率）
    //PID输出的值为控制信号，传入到PWM变量中
	temp = PID_Calc( &power_pid, target_power, current_power);
    //设置DAC输出值
	// 将PID输出转换为DAC值 (0-4095)
    dac_value = (uint16_t)( ( (2000 - temp) * 4095) / 3300);
    
    // 计算实际输出电压值(mV)
    dac_output = (dac_value * DAC12_REF_VOLTAGE_mV) / 4095;
    
    // 设置DAC输出
    DL_DAC12_output12(DAC0, dac_value);  
    DL_DAC12_enable(DAC0);
	return power_pid;
}

