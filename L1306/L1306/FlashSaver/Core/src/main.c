#include "ti_msp_dl_config.h"
#include "oled.h"
#include <stdio.h>
int fputc(int ch, FILE *stream){
    //当串口0忙的时候等待，不忙的时候再发送传进来的字符
    
    DL_UART_transmitData(UART_0_INST,ch);
	while(DL_UART_isBusy(UART_0_INST)==true){}
    return ch;
}
#define  ADDRESS	(0x00008000)//内存地址

uint32_t data[8] = {17,17,17,17,17,17,17,17};
uint32_t temp[8] = {0};
uint8_t key_num = 0;
uint8_t Key();
int i = 0;
int count = 0,j = 0;//计时器变量
int main(void){
	
    SYSCFG_DL_init(); // Initialize the device
	NVIC_ClearPendingIRQ(UART_0_INST_INT_IRQN );//清除中断标志位
    NVIC_EnableIRQ(UART_0_INST_INT_IRQN );
	DL_TimerG_startCounter(TIMER_0_INST);//启动计时器
	NVIC_EnableIRQ(TIMER_0_INST_INT_IRQN);//中断函数启动
	
	DL_Common_delayCycles(1000);//待机
	
	OLED_Init();//初始化
	OLED_Clear();//清除缓存
	delay_ms(100);//延时
	
	OLED_ShowString(32,0,"Textbook");
	delay_ms(5000);//显示时间
	OLED_Clear();
	while(1){
		key_num = Key();
		if(key_num!=0 && key_num!= 15 && key_num!=16 && i<8 &&i!= -1){//储存输入
			OLED_Clear();
			data[i] = key_num;
			int bit = data[i]<10?1:2;
			for(int j = 0;j<=i;j++)OLED_ShowNum(2 +18*j,3,data[j],bit,16);
			i++;
			if(i>=8){
				OLED_Clear();
				for(int i=0;i<8;i++){
					int t_bit = data[i]<10?1:2;
					OLED_ShowNum(2 +16*i ,2,data[i],t_bit,16);
				}
				OLED_ShowString(32,4,"Full!!!");
				OLED_ShowString(8,6,"Please Save !");
				i = -1;
			}
			key_num = 0;
		}
		if(key_num==15){
			OLED_Clear();
			//擦除数据
			DL_FlashCTL_unprotectSector( FLASHCTL, ADDRESS, DL_FLASHCTL_REGION_SELECT_MAIN);
			DL_FlashCTL_eraseMemoryFromRAM( FLASHCTL, ADDRESS, DL_FLASHCTL_COMMAND_SIZE_SECTOR);
			DL_FlashCTL_waitForCmdDone( FLASHCTL);
			//写入数据
			DL_FlashCTL_unprotectSector( FLASHCTL, ADDRESS, DL_FLASHCTL_REGION_SELECT_MAIN);
			DL_FlashCTL_programMemoryFromRAM( FLASHCTL, ADDRESS, data,8, DL_FLASHCTL_REGION_SELECT_MAIN);
			DL_FlashCTL_waitForCmdDone(FLASHCTL);
			OLED_ShowString(30,0,"Finished!!!");
			i = 0;//重置 i的数值
			
		}
		if(key_num == 16){
			OLED_Clear();
			OLED_ShowString(32,2,"isReading");
			//读取系统
			for(int i=0;i<32;i+=4){
				temp[i/4]=*(int *)(ADDRESS+i);
				if(temp[i/4] == 17)OLED_ShowString(2+4*i,4,"?");
				else{
					int t_bit = temp[i/4]<10?1:2;
					OLED_ShowNum(2 + 4*i,4,temp[i/4],t_bit,16);
				}
			}
			key_num = 0;
		}
	}
}
//矩阵键盘
uint8_t Key(){
	uint32_t key_num = 0;         // 按键值1-16，默认为0
	static uint32_t key_flag = 0; // 按下按键标志

	if (key_flag){
		delay_ms(3000); // 300ms延迟，防止按下一次按键却被认为按下了多次按键，导致得到了多个相同的按键值
		key_flag = 0;  // 按下按键标志清零
	}

	  // 行扫描
	  // ROW 0111
	  // 0111-1011-1101-1110
	DL_GPIO_clearPins(MAT_KEY_PORT, MAT_KEY_ROW0_PIN);
	DL_GPIO_setPins(MAT_KEY_PORT, MAT_KEY_ROW1_PIN | MAT_KEY_ROW2_PIN | MAT_KEY_ROW3_PIN);
	delay_ms(100); // 按键消抖延迟，一般为10ms，一定要在外界改变时延迟，而不是读取输入后再延迟
				  // 所谓的外界改变时，即改变行扫描时，如行输出由0111变为1011
				  // 这里实际上有两个外界改变时，一个是用户刚刚按下时，另一个是改变行扫描时
			      // 然而由于按键消抖延迟只需10ms，扫描一轮也只需40ms，远小于用户按下的时间
				  // 因此选择改变行扫描时作为外界改变时，总能涵盖两种外界改变
				  // 并且在按键消抖例程中提到，无法得知用户刚刚按下的时刻
				  // 同时不断判断低电平也不能近似这个时刻，因为低电平出现有两种情况
				  // 一种是用户先按下，然后改变行扫描，另一种是先改变行扫描，用户再按下
				  // 普遍错误写法如下:
	// DL_GPIO_clearPins(MAT_KEY_PORT, MAT_KEY_ROW0_PIN);
	// DL_GPIO_setPins(MAT_KEY_PORT, MAT_KEY_ROW1_PIN | MAT_KEY_ROW2_PIN | MAT_KEY_ROW3_PIN);

	// if (!DL_GPIO_readPins(MAT_KEY_PORT, MAT_KEY_COL0_PIN))//每次改变行扫描后，直接读取并未经过延迟，有可能只能读到抖动中的高电平，从而永远检测不到，如常见的第二行“不灵敏”问题，究其原因是134行过于灵敏导致消抖错误也能检测正确
	// {
	//   delay_ms(10);
	//   if (!DL_GPIO_readPins(MAT_KEY_PORT, MAT_KEY_COL0_PIN))
	//   {
	//     key_num = 1;
	//     key_flag = 1;
	//   }
	// }

	if (!DL_GPIO_readPins(MAT_KEY_PORT, MAT_KEY_COL0_PIN)){
		key_num = 1;
		key_flag = 1; // 按键已按下
	}
	else if (!DL_GPIO_readPins(MAT_KEY_PORT, MAT_KEY_COL1_PIN)){
		key_num = 2;
		key_flag = 1;
	}
	else if (!DL_GPIO_readPins(MAT_KEY_PORT, MAT_KEY_COL2_PIN)){
		key_num = 3;
		key_flag = 1;
	}
	else if (!DL_GPIO_readPins(MAT_KEY_PORT, MAT_KEY_COL3_PIN)){
		key_num = 4;
		key_flag = 1;
	}

	// ROW 1011
	DL_GPIO_clearPins(MAT_KEY_PORT, MAT_KEY_ROW1_PIN);
	DL_GPIO_setPins(MAT_KEY_PORT, MAT_KEY_ROW0_PIN | MAT_KEY_ROW2_PIN | MAT_KEY_ROW3_PIN);
	delay_ms(100);

	if (!DL_GPIO_readPins(MAT_KEY_PORT, MAT_KEY_COL0_PIN)){
		key_num = 5;
		key_flag = 1;
	}
	else if (!DL_GPIO_readPins(MAT_KEY_PORT, MAT_KEY_COL1_PIN)){
		key_num = 6;
		key_flag = 1;
	}
	else if (!DL_GPIO_readPins(MAT_KEY_PORT, MAT_KEY_COL2_PIN)){
		key_num = 7;
		key_flag = 1;
	}
	else if (!DL_GPIO_readPins(MAT_KEY_PORT, MAT_KEY_COL3_PIN)){
		key_num = 8;
		key_flag = 1;
	}

	// ROW 1101
	DL_GPIO_clearPins(MAT_KEY_PORT, MAT_KEY_ROW2_PIN);
	DL_GPIO_setPins(MAT_KEY_PORT, MAT_KEY_ROW0_PIN | MAT_KEY_ROW1_PIN | MAT_KEY_ROW3_PIN);
	delay_ms(100);

	if (!DL_GPIO_readPins(MAT_KEY_PORT, MAT_KEY_COL0_PIN)){
		key_num = 9;
		key_flag = 1;
	}
	else if (!DL_GPIO_readPins(MAT_KEY_PORT, MAT_KEY_COL1_PIN)){
		key_num = 10;
		key_flag = 1;
	}
	else if (!DL_GPIO_readPins(MAT_KEY_PORT, MAT_KEY_COL2_PIN)){
		key_num = 11;
		key_flag = 1;
	}
	else if (!DL_GPIO_readPins(MAT_KEY_PORT, MAT_KEY_COL3_PIN)){
		key_num = 12;
		key_flag = 1;
	}

	DL_GPIO_clearPins(MAT_KEY_PORT, MAT_KEY_ROW3_PIN);
	DL_GPIO_setPins(MAT_KEY_PORT, MAT_KEY_ROW0_PIN | MAT_KEY_ROW1_PIN | MAT_KEY_ROW2_PIN);
	delay_ms(100);

	// ROW 1110
	if (!DL_GPIO_readPins(MAT_KEY_PORT, MAT_KEY_COL0_PIN)){
		key_num = 13;
		key_flag = 1;
	}
	else if (!DL_GPIO_readPins(MAT_KEY_PORT, MAT_KEY_COL1_PIN)){
		key_num = 14;
		key_flag = 1;
	}
	else if (!DL_GPIO_readPins(MAT_KEY_PORT, MAT_KEY_COL2_PIN)){
		key_num = 15;
		key_flag = 1;
	}
	else if (!DL_GPIO_readPins(MAT_KEY_PORT, MAT_KEY_COL3_PIN)){
		key_num = 16;
		key_flag = 1;
	}

	return key_num;//返回值
}

void TIMER_0_INST_IRQHandler (void){//中断后执行的函数
	switch(DL_TimerG_getPendingInterrupt (TIMER_0_INST)){
		case DL_TIMERG_IIDX_ZERO:
			count++;
			if(count%5 == 0){
				printf("%d",1);
			}
			if(count%20==0){
				OLED_ShowString(0,6,"isAutoSaving");
				delay_ms(2500);
				OLED_Clear();
				//擦除数据
				DL_FlashCTL_unprotectSector( FLASHCTL, ADDRESS, DL_FLASHCTL_REGION_SELECT_MAIN);
				DL_FlashCTL_eraseMemoryFromRAM( FLASHCTL, ADDRESS, DL_FLASHCTL_COMMAND_SIZE_SECTOR);
				DL_FlashCTL_waitForCmdDone(FLASHCTL);
				//写入数据
				DL_FlashCTL_unprotectSector( FLASHCTL, ADDRESS, DL_FLASHCTL_REGION_SELECT_MAIN);
				DL_FlashCTL_programMemoryFromRAM( FLASHCTL, ADDRESS, data,8,DL_FLASHCTL_REGION_SELECT_MAIN);
				DL_FlashCTL_waitForCmdDone(FLASHCTL);
				OLED_ShowString(0,6,"isFinished!!!");
				//重置数值
				i = 0;
				key_num = 0;
				count = 0;
				for(int k = 0;k<8;k++)data[k] = 17;
			}	
			break;
		default:
			break;
	}
}
