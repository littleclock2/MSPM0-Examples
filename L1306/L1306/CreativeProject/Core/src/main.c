#include "ti_msp_dl_config.h"
#include "oled_spi.h"
#include <stdio.h>

//定义把每个音符和频率值对应起来
#define NOTE_D0 100
#define NOTE_D1 294
#define NOTE_D2 330
#define NOTE_D3 350
#define NOTE_D4 393
#define NOTE_D5 441
#define NOTE_D6 495
#define NOTE_D7 556

#define NOTE_DL1 147
#define NOTE_DL2 165
#define NOTE_DL3 175
#define NOTE_DL4 196
#define NOTE_DL5 221
#define NOTE_DL6 248
#define NOTE_DL7 278

#define NOTE_DH1 589
#define NOTE_DH2 661
#define NOTE_DH3 700
#define NOTE_DH4 786
#define NOTE_DH5 882
#define NOTE_DH6 990
#define NOTE_DH7 112

//用英文对应拍子
#define WHOLE 1
#define HALF 0.5
#define QUARTER 0.25
#define EIGHTH 0.25
#define SIXTEENTH 0.625

//整首曲子的音符部分，用了一个序列定义为tune，整数
int tune[] ={
  NOTE_D0, NOTE_D0, NOTE_D0, NOTE_D6, NOTE_D7, NOTE_DH1, NOTE_D7, NOTE_DH1, NOTE_DH3, NOTE_D7, NOTE_D7, NOTE_D7, NOTE_D3, NOTE_D3,
  NOTE_D6, NOTE_D5, NOTE_D6, NOTE_DH1, NOTE_D5, NOTE_D5, NOTE_D5, NOTE_D3, NOTE_D4, NOTE_D3, NOTE_D4, NOTE_DH1,NOTE_D3, NOTE_D3,
  NOTE_D0, NOTE_DH1,NOTE_DH1, NOTE_DH1, NOTE_D7, NOTE_D4, NOTE_D4, NOTE_D7, NOTE_D7,NOTE_D7, NOTE_D0, NOTE_D6, NOTE_D7,
  NOTE_DH1, NOTE_D7, NOTE_DH1, NOTE_DH3, NOTE_D7, NOTE_D7, NOTE_D7, NOTE_D3, NOTE_D3, NOTE_D6, NOTE_D5, NOTE_D6, NOTE_DH1,
  NOTE_D5, NOTE_D5, NOTE_D5, NOTE_D2, NOTE_D3, NOTE_D4, NOTE_DH1, NOTE_D7, NOTE_D7, NOTE_DH1, NOTE_DH1, NOTE_DH2, NOTE_DH2, 
  NOTE_DH3, NOTE_DH1, NOTE_DH1, NOTE_DH1,NOTE_DH1, NOTE_D7, NOTE_D6, NOTE_D6, NOTE_D7, NOTE_D5, NOTE_D6, NOTE_D6, NOTE_D6, 
  NOTE_DH1, NOTE_DH2, NOTE_DH3, NOTE_DH2, NOTE_DH3, NOTE_DH5,NOTE_DH2, NOTE_DH2, NOTE_DH2, NOTE_D5, NOTE_D5, NOTE_DH1, NOTE_D7, 
  NOTE_DH1, NOTE_DH3, NOTE_DH3, NOTE_DH3, NOTE_DH3, NOTE_DH3,NOTE_D6, NOTE_D7, NOTE_DH1, NOTE_D7, NOTE_DH2, NOTE_DH2, NOTE_DH1, 
  NOTE_D5, NOTE_D5, NOTE_D5, NOTE_DH4, NOTE_DH3, NOTE_DH2, NOTE_DH1,NOTE_DH3, NOTE_DH3, NOTE_DH3, NOTE_DH3, NOTE_DH6, NOTE_DH6, 
  NOTE_DH5, NOTE_DH5, NOTE_DH3, NOTE_DH2, NOTE_DH1, NOTE_DH1, NOTE_D0, NOTE_DH1,NOTE_DH2, NOTE_DH1, NOTE_DH2, NOTE_DH2, NOTE_DH5, 
  NOTE_DH3, NOTE_DH3, NOTE_DH3, NOTE_DH3, NOTE_DH6, NOTE_DH6, NOTE_DH5, NOTE_DH5,NOTE_DH3, NOTE_DH2, NOTE_DH1, NOTE_DH1, NOTE_D0, 
  NOTE_DH1, NOTE_DH2, NOTE_DH1, NOTE_DH2, NOTE_DH2, NOTE_D7, NOTE_D6, NOTE_D6, NOTE_D6, NOTE_D6, NOTE_D7
};

//整首曲子的节拍部分，也定义个序列duration，浮点（数组的个数和前面音符的个数是一样的，一一对应）
float duration[] ={
  1, 1, 1, 0.5, 0.5,  1 + 0.5, 0.5, 1, 1,  1, 1, 1, 0.5, 0.5,
  1 + 0.5, 0.5, 1, 1,  1, 1, 1, 1,     1 + 0.5, 0.5, 1, 1,
  1, 1, 0.5, 0.5, 0.5, 0.5,    1 + 0.5, 0.5, 1, 1,     1, 1, 1, 0.5, 0.5,
  1 + 0.5, 0.5, 1, 1,    1, 1, 1, 0.5, 0.5,     1 + 0.5, 0.5, 1, 1,
  1, 1, 1, 0.5,     1, 0.5, 0.25, 0.25, 0.25, 0.5,    0.5, 0.5, 0.5, 0.25, 0.5, 1,
  0.5, 0.5, 0.5, 0.5, 1, 1,    1, 1, 1, 0.5, 0.5,    1 + 0.5, 0.5, 1, 1,
  1, 1, 1, 0.5, 0.5,    1.5, 0.5, 1, 1,    1, 1, 1, 1,
  0.5, 0.5, 1, 1, 0.5, 0.5,    1.5, 0.25, 0.5, 1,    1, 1, 1, 1,
  1, 1, 1, 1,    1, 1, 1, 1,    0.5, 0.5, 1, 1, 0.5, 0.5,
  1, 0.5, 0.5, 1, 1,    1, 1, 1, 1,    1, 1, 1, 1,
  0.5, 0.5, 1, 1, 0.5, 0.5,   1, 0.5, 0.25, 0.5, 1,    1, 1, 1, 0.5, 0.5
};
//串口重定向
int fputc(int ch, FILE *stream){
    //当串口0忙的时候等待，不忙的时候再发送传进来的字符
    while(DL_UART_isBusy(UART_0_INST)==true){}
    DL_UART_transmitDataBlocking(UART_0_INST,ch);
    return ch;
}

//自动储存内存地址 
#define  ADDRESS	(0x00008000)

//延时函数
void delay_ms(unsigned int ms){                         
	unsigned int a;
	ms*=10;
	while(ms)
	{
		a=360;
		while(a--);
		ms--;
	}
	return;
}

//变量声明
int key_value = 16;//矩阵键盘传递值
//系统时间时分秒
int system_time_second = 0;
int system_time_minute = 0;
int system_time_hour = 0;
//菜单变量
int menu = 1;
//debug模式变量
int debug_mode = 0;
//定义一个变量，表示共有多少个音符
int music_length;
//文本储存结构体变量
struct text{
	int is_created;
	uint32_t num[11];
}Text[4];
//数据位变量
uint8_t receive_data;
//记事本运行变量
int isTextbook = 0;
//短信运行变量
int isMessage = 0;
//通信接受变量
uint8_t data_receive = 0;
uint8_t text_saver1[11];
uint8_t text_saver2[11];
uint8_t text_saver3[11];

//函数声明
int Key();
void ActiveTime();
void TextBook();
void Message();
void MusicPlayer(int isActive);
int main(void){
	//变量初始化
	Text[0].is_created = 0;
//	for(int i = 0;i<11;i++){
//		Text[0].num[i] = 16;
//	}
	Text[1] = Text[0];
    Text[2] = Text[0];
    Text[3] = Text[0];
	
    SYSCFG_DL_init();
	//通信初始化
	NVIC_ClearPendingIRQ(UART_0_INST_INT_IRQN );//清除中断标志位
    NVIC_EnableIRQ(UART_0_INST_INT_IRQN );
	//时钟初始化
	DL_TimerG_startCounter(TIMER_0_INST);//启动计时器
	NVIC_EnableIRQ(TIMER_0_INST_INT_IRQN);//中断函数启动
	
	//按键中断初始化
	NVIC_ClearPendingIRQ(SWITCH_INT_IRQN);
	NVIC_EnableIRQ(SWITCH_INT_IRQN);
	//pwm波形输出启动
	NVIC_ClearPendingIRQ(PWM_0_INST_INT_IRQN );//清除中断标志位
	DL_TimerG_startCounter(PWM_0_INST);//pwm计数启动
    NVIC_EnableIRQ(PWM_0_INST_INT_IRQN);//pwm中断使能

    OLED_Init();
    OLED_Clear();
	OLED_ShowString(0,0,"Multi-functional");
	OLED_ShowString(10,2," Equipment");
	OLED_ShowString(2,4," Loading......");
	delay_ms(1000);
	OLED_Clear();
	OLED_ShowString(12,2," Remember:");
	OLED_ShowString(12,4," Exit -> 10");
	delay_ms(1000);
	OLED_Clear();
	uint8_t temp = 32;
    while(1){
//		for(int i = 0;i<10;i++){
//			printf("%d",temp);
//			delay_ms(1000);
//		}
		MusicPlayer(1);
		key_value = Key();
		if(key_value == 1){//切换菜单函数
			switch(menu){
				case 1:menu = 2;break;
				case 2:menu = 3;break;
				case 3:menu = 1;break;
			}
		}
		else if(key_value == 10){
			break;
		}
		switch(menu){
			case 1:
				OLED_ShowChar(0,2,'|');
				OLED_ShowChar(0,4,' ');
				OLED_ShowChar(0,6,' ');
				break;
			case 2:
				OLED_ShowChar(0,2,' ');
				OLED_ShowChar(0,4,'|');
				OLED_ShowChar(0,6,' ');
				break;
			case 3:
				OLED_ShowChar(0,2,' ');
				OLED_ShowChar(0,4,' ');
				OLED_ShowChar(0,6,'|');
				break;
		}
		OLED_ShowString(0,0,"MENU:");
		OLED_ShowString(12,2,"1.Text Book");
		OLED_ShowString(12,4,"2.Message");
		OLED_ShowString(12,6,"3.Greedy Snake");
		if(key_value == 2){//进入菜单选项菜单函数
			switch(menu){
				case 1:
					OLED_Clear();
					TextBook();
					break;
				case 2:
					OLED_Clear();
					Message();
					break;
				case 3:
					OLED_Clear();
					//GluttonousSnake();
					OLED_Clear();
					break;
			}
		}
    }
	OLED_Clear();
	OLED_ShowString(0,0,"System outline.");
	OLED_ShowString(12,2,"Total time:");
	OLED_ShowNum(12,4,system_time_hour,2,16);
	OLED_ShowChar(28,4,':');
	OLED_ShowNum(36,4,system_time_minute,2,16);
	OLED_ShowChar(54,4,':');
	OLED_ShowNum(62,4,system_time_second,2,16);
	delay_ms(2000);
}

//中断函数
void TIMER_0_INST_IRQHandler (void){
	switch( DL_TimerG_getPendingInterrupt (TIMER_0_INST)){
		case DL_TIMERG_IIDX_ZERO:
			DL_GPIO_togglePins(LED_PORT,LED_LED0_PIN);//1s的定时器系统
			system_time_second ++;
			ActiveTime();
			break;
		default:
			break;
	}
}
////按键中断函数
//void GROUP1_IRQHandler(void){
//	switch(DL_Interrupt_getPendingGroup (DL_INTERRUPT_GROUP_1)){
//		case SWITCH_INT_IIDX:{//实现按键查看系统运行时间
//			DL_GPIO_togglePins(LED_PORT,LED_LED0_PIN);
//			for(int i = 0;i<120;i++){
//				printf("%d\n",i);
//			}
//			 if(!isMessage && !isTextbook){
//			 }
//				 
//				

//			 }
//			break;
//		default:
//			break;
//	}
//}
//通信接受中断函数
//void  UART_0_INST_IRQHandler(){
//   switch (DL_UART_getPendingInterrupt(UART_0_INST )){ //检测是否串口中断
//        case DL_UART_MAIN_IIDX_RX:{
//			DL_UART_clearInterruptStatus(UART_0_INST,GPIO_UART_0_IOMUX_RX  );
//			DL_UART_clearInterruptStatus(UART_0_INST,GPIO_UART_0_IOMUX_TX  );
//			// data_receive = DL_UART_receiveData(UART_0_INST);
//			// OLED_ShowNum(100,0,data_receive,2,16);
//			// DL_UART_transmitData(UART_0_INST,data_receive);
//            break;
//		}
//        default:
//            break;
//    }
//}
void TextBook(){
	//读取数据
	for(int i=0;i< 4*11;i+=4){
		Text[1].num[i/4]=*(int *)(ADDRESS + i);//Text1数据读取
		Text[2].num[i/4]=*(int *)(ADDRESS + 64 +i);//Text1数据读取
		Text[3].num[i/4]=*(int *)(ADDRESS + 128 +i);//Text1数据读取
	}
	while(1){
		int show_num[11];
		int count = 0,i =0 ,j =0 ;
		//菜单选项
		OLED_Clear();
		OLED_ShowString(20,0,"Textbook");
		OLED_ShowString(20,2,"1.NewText");
		OLED_ShowString(20,4,"2.CheckText");
		OLED_ShowString(20,6,"3.DeleteText");
		//输入
		do{
			key_value = Key();
		}while(key_value >10);
		OLED_Clear();
		switch(key_value){
			case 1:{//创建新记事本
				OLED_ShowString(4,0,"#");
				OLED_ShowString(16,0,"Choose 1/2/3");
				OLED_ShowString(4,6,"Exit -> '10' ");
				do{//输入
					key_value = Key();
				}while(key_value>10);
				if(key_value == 10){
					delay_ms(50);
					OLED_Clear();
					break;
				}
				count = key_value;
				OLED_ShowString(4,2,"Max 11 Numbers");
				//输入函数
				for(i = 0 ;i < 11 ; i++ ){
					do{
						key_value = Key();
					}while(key_value>10);
					//未输入完整则补齐
					if(key_value == 10){
						for(int temp = i;temp<11;temp++){
							show_num[temp] = 16;
						}
						OLED_Clear();
						OLED_ShowString(2,2,"Input finish.");
						break;//退出
					}
					//展示输入的信息
					show_num[i] = key_value;
					for(j = 0;j<i+1;j++){
						OLED_ShowNum(4 + 8*j,4, show_num[j],1,16);
					}
					OLED_ShowString(4,6,"Exit -> '10' ");	
				}
				switch (count){//传入储存数组
					case 1:
						for(int i = 0;i<11;i++){
							Text[1].num[i] = show_num[i];
						}
						break;
					case 2:
						for(int i = 0;i<11;i++){
							Text[2].num[i] = show_num[i];
						}
						break;
					case 3:
						for(int i = 0;i<11;i++){
							Text[3].num[i] = show_num[i];
						}
						break;
					default:
						break;
				}
				OLED_Clear();
				OLED_ShowString(2,2,"Input finish.");
				//擦除数据
				DL_FlashCTL_unprotectSector( FLASHCTL, ADDRESS, DL_FLASHCTL_REGION_SELECT_MAIN);
				DL_FlashCTL_eraseMemoryFromRAM( FLASHCTL, ADDRESS, DL_FLASHCTL_COMMAND_SIZE_SECTOR);
				DL_FlashCTL_waitForCmdDone( FLASHCTL);
				//写入Text[count]数据
				DL_FlashCTL_unprotectSector( FLASHCTL, ADDRESS, DL_FLASHCTL_REGION_SELECT_MAIN);
				DL_FlashCTL_programMemoryFromRAM( FLASHCTL, ADDRESS, Text[1].num,11, DL_FLASHCTL_REGION_SELECT_MAIN);
				DL_FlashCTL_waitForCmdDone(FLASHCTL);
				//写入text2数据
				DL_FlashCTL_unprotectSector( FLASHCTL, ADDRESS, DL_FLASHCTL_REGION_SELECT_MAIN);
				DL_FlashCTL_programMemoryFromRAM( FLASHCTL, ADDRESS + 64, Text[2].num,11, DL_FLASHCTL_REGION_SELECT_MAIN);
				DL_FlashCTL_waitForCmdDone(FLASHCTL);
				//写入text3数据
				DL_FlashCTL_unprotectSector( FLASHCTL, ADDRESS, DL_FLASHCTL_REGION_SELECT_MAIN);
				DL_FlashCTL_programMemoryFromRAM( FLASHCTL, ADDRESS + 128, Text[3].num,11, DL_FLASHCTL_REGION_SELECT_MAIN);
				DL_FlashCTL_waitForCmdDone(FLASHCTL);
				break;
			}
			case 2:{
				while(1){
					//选择查看文本
					OLED_ShowString(4,0,"Choose 1/2/3");
					OLED_ShowString(4,6,"Exit -> '10' ");
					do{//输入
						key_value = Key();
					}while(key_value>10);
					if(key_value == 10){
						OLED_Clear();
						break;
					}
					switch (key_value){//显示不同文本
						case 1:
							for(int i = 0;i<11;i++){
								if(Text[1].num[i] == 16)OLED_ShowChar(4 + 8*i,4,'?');
								else OLED_ShowNum(4 + 8*i,4, Text[1].num[i],1,16);
							}
							break;
						case 2:
							for(int i = 0;i<11;i++){
								if(Text[2].num[i] == 16)OLED_ShowChar(4 + 8*i,4,'?');
								else OLED_ShowNum(4 + 8*i,4, Text[2].num[i],1,16);
							}
							break;
						case 3:
							for(int i = 0;i<11;i++){
								if(Text[3].num[i] == 16)OLED_ShowChar(4 + 8*i,4,'?');
								else OLED_ShowNum(4 + 8*i,4, Text[3].num[i],1,16);
							}
							break;
						default:
							break;
					}
				}
				key_value = 16;
				break;
			}
			case 3:{
				while(1){
					OLED_ShowString(4,0,"Choose 1/2/3");
					OLED_ShowString(4,6,"Exit -> '10' ");
					do{//输入
						key_value = Key();
					}while(key_value >10);
					if(key_value == 10){
						OLED_Clear();
						break;
					}
					switch (key_value){//删除不同文本（将其归位）
						case 1:
							Text[1].is_created = 0;
							for(int i = 0;i<11;i++){
								Text[1].num[i] = 16;
							}
							OLED_ShowString(0,2,"Text1 Deleted");
							break;
						case 2:
							Text[2].is_created = 0;
							for(int i = 0;i<11;i++){
								Text[2].num[i] = 16;
							}
							OLED_ShowString(0,2,"Text2 Deleted");
							break;
						case 3:
							Text[3].is_created = 0;
							for(int i = 0;i<11;i++){
								Text[3].num[i] = 16;
							}
							OLED_ShowString(0,2,"Text3 Deleted");
							break;
						default:
							break;
					}
				}
				key_value = 16;
				break;
			}
		}
		if(key_value == 10){
			break;
		}
		OLED_ShowString(4,6,"Exit -> '10' ");
		delay_ms(500);
	}
}
void Message(){
	while (1){
		OLED_Clear();
		//菜单
		OLED_ShowString(20,0,"Message");
		OLED_ShowString(20,2,"1.Note");
		OLED_ShowString(20,4,"2.Formwork");
		OLED_ShowString(20,6,"3.Debug Mode");

		do{//选择功能
			key_value = Key();
		}while(key_value >10);

		OLED_Clear();
		switch(key_value){
			case 1:{
				uint8_t temp[11] ;
				long output_num = 0;
				int exchange = 0;
				OLED_ShowString(4,0,"Please input:");
				for(int i = 0 ;i < 11 ; i++ ){//连续输入11个数字
					do{
						key_value = Key();
					}while(key_value>10);

					if(key_value == 10){
						for(int j = i;j<11;j++){
							temp[j] = 16;
						}
						OLED_Clear();
						break;//退出选项
					}
					temp[i] = key_value;
					for(int x = 0; x<i+1;x++){//将输入的信息存入临时数组
						OLED_ShowNum(4 + 8*i,4,temp[x],1,16);
					}
					if(exchange){
						OLED_ShowChar(4 + 8*( i + 1),4,'|');
						exchange = 0;
					}
					else if(!exchange){
						OLED_ShowChar(4 + 8*( i + 1),4,' ');
						exchange = 1;
					}
					OLED_ShowString(4,6,"Finish -> '10' ");	
				}
				OLED_Clear();
				OLED_ShowString(4,0,"Textbox");
				for(int x = 0; x<11;x++){//显示准备发送的的信息
					if(temp[x]!= 16)OLED_ShowNum(4 + 8*x,4,temp[x],1,16);
					else if(temp[x]==16)OLED_ShowChar(4 + 8*x,4,'?');
				}
				OLED_ShowString(4,6,"Ensure: 1/0");	
				do{
					key_value = Key();
				}while (key_value >1);

				switch (key_value){//根据确认与否执行不同的函数
					case 1:
						OLED_ShowString(4,2,"ing");
						printf("%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d\n",temp[0],temp[1],temp[2],temp[3],temp[4],temp[5],temp[6],temp[7],temp[8],temp[9],temp[10]);
						OLED_ShowString(4,2," O K !");	
						delay_ms(1000);
						OLED_Clear();
						break;
					case 0:
						OLED_ShowString(4,2,"Cancel !");	
						delay_ms(1000);
						OLED_Clear();
						break;
					default:
						break;
				}
				OLED_Clear();
				key_value = 16;
				break;
			}
			case 2:{
				while(1){
					OLED_ShowString(4,0,"Choose 1/2/3");
					OLED_ShowString(4,6,"Exit -> '10' ");
					do{
						key_value = Key();
					}while(key_value>10);
					if(key_value == 10){
						OLED_Clear();
						break;
					}
					uint8_t temp[11] ;
					long output_num = 0;
					OLED_Clear();
					OLED_ShowString(4,0,"Textbox");
					switch (key_value){//发送不同文本
						case 1:
							for( int i = 0;i<11;i++){
								OLED_ShowNum(4 + 8*i,4,Text[1].num[i],1,16);
								temp[i] = Text[1].num[i];
							}
							break;
						case 2:
							for(int i = 0;i<11;i++){
								OLED_ShowNum(4 + 8*i,4,Text[2].num[i],1,16);
								temp[i] = Text[2].num[i];
							}
							break;
						case 3:
							for(int i = 0;i<11;i++){
								OLED_ShowNum(4 + 8*i,4,Text[3].num[i],1,16);
								temp[i] = Text[3].num[i];
							}
							break;
						default:
							break;
					}
					OLED_ShowString(4,6,"Ensure: 1/0");	//确认发送
					do{
						key_value = Key();
					}while (key_value != 1 && key_value != 0);
					switch (key_value){
						case 1:
							printf("%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d\n",temp[0],temp[1],temp[2],temp[3],temp[4],temp[5],temp[6],temp[7],temp[8],temp[9],temp[10]);
							OLED_ShowString(4,2," O K !");	
							delay_ms(1000);
							OLED_Clear();
							break;
						case 0:
							OLED_ShowString(4,2,"Cancel !");	
							delay_ms(1000);
							OLED_Clear();
							break;
						default:
							break;
					}
				}
				key_value = 16;
				break;
			}
			case 3:{
				
				break;
			}
		}
		if(key_value == 10){
			break;
		}
		OLED_ShowString(4,6,"Exit -> '10' ");
		delay_ms(500);	
	}
}
void MusicPlayer(int ActiveMode){
	switch(ActiveMode){
		case 1:{//音乐播放
			music_length = sizeof(tune) / sizeof(tune[0]); //这里用了一个sizeof函数， 可以查出tone序列里有多少个音符
			for (int x = 0; x < music_length; ++x) {//循环音符的次数
				DL_Timer_setLoadValue(PWM_0_INST, tune[x]);
				DL_TimerG_setCaptureCompareValue(PWM_0_INST, tune[x] / 2 ,DL_TIMER_CC_0_INDEX);
				//每个音符持续的时间，即节拍duration，调整时间的越大，曲子速度越慢，越小曲子速度越快，节奏可自行调整
				delay_ms(500 * duration[x]);
				//停止当前音符，进入下一音符
			}
			break;
		}
		case 2:{//间隔播放闹铃声(蜂鸣器响三次间隔两秒)
			for(int i = 0;i<3;i++){
				DL_Timer_setLoadValue(PWM_0_INST, tune[7]);
				DL_TimerG_setCaptureCompareValue(PWM_0_INST, tune[7] / 2 ,DL_TIMER_CC_0_INDEX);
				delay_ms(1000);
				DL_TimerG_setCaptureCompareValue(PWM_0_INST, 0 ,DL_TIMER_CC_0_INDEX);
				delay_ms(2000);
			}
		}
	}
		
}
void ActiveTime(){//时间进位函数
	if( system_time_second > 59 ){
		system_time_second = 0;
		system_time_minute ++;
	} 
	if (system_time_minute > 59){
		system_time_minute= 0;
		system_time_hour ++;
	}
}
	

int Key(){//矩阵键盘函数
	int key_num = 16;         // 按键�?0-15，默认为16
	static uint32_t key_flag = 0; // 按下按键标志
	//是否为debug模式
	if (key_flag){
		delay_ms(300); // 300ms延迟，防止按下一次按键却被认为按下了多次按键，导致得到了多个相同的按键�?
		key_flag = 0;  // 按下按键标志清零
	}
	// 行扫描
	// ROW 0111
	DL_GPIO_clearPins(MAT_KEY_PORT, MAT_KEY_ROW0_PIN);
	DL_GPIO_setPins(MAT_KEY_PORT, MAT_KEY_ROW1_PIN | MAT_KEY_ROW2_PIN | MAT_KEY_ROW3_PIN);
	delay_ms(10); 
	if (!DL_GPIO_readPins(MAT_KEY_PORT, MAT_KEY_COL0_PIN)){
		key_num = 1;
		key_flag = 1; // 按键已按�?
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
		key_num = 10;//(1,4)
		key_flag = 1;
	}
	// ROW 1011
	DL_GPIO_clearPins(MAT_KEY_PORT, MAT_KEY_ROW1_PIN);
	DL_GPIO_setPins(MAT_KEY_PORT, MAT_KEY_ROW0_PIN | MAT_KEY_ROW2_PIN | MAT_KEY_ROW3_PIN);
	delay_ms(10);
	if (!DL_GPIO_readPins(MAT_KEY_PORT, MAT_KEY_COL0_PIN)){
		key_num = 4;
		key_flag = 1;
	}
	else if (!DL_GPIO_readPins(MAT_KEY_PORT, MAT_KEY_COL1_PIN)){
		key_num =5;
		key_flag = 1;
	}
	else if (!DL_GPIO_readPins(MAT_KEY_PORT, MAT_KEY_COL2_PIN)){
		key_num = 6;
		key_flag = 1;
	}
	else if (!DL_GPIO_readPins(MAT_KEY_PORT, MAT_KEY_COL3_PIN)){
		key_num = 11;
		key_flag = 1;//(2,4)
	}
	// ROW 1101
	DL_GPIO_clearPins(MAT_KEY_PORT, MAT_KEY_ROW2_PIN);
	DL_GPIO_setPins(MAT_KEY_PORT, MAT_KEY_ROW0_PIN | MAT_KEY_ROW1_PIN | MAT_KEY_ROW3_PIN);
	delay_ms(10);
	if (!DL_GPIO_readPins(MAT_KEY_PORT, MAT_KEY_COL0_PIN)){
		key_num = 7;
		key_flag = 1;
	}
	else if (!DL_GPIO_readPins(MAT_KEY_PORT, MAT_KEY_COL1_PIN)){
		key_num = 8;
		key_flag = 1;
	}
	else if (!DL_GPIO_readPins(MAT_KEY_PORT, MAT_KEY_COL2_PIN)){
		key_num = 9;
		key_flag = 1;
	}
	else if (!DL_GPIO_readPins(MAT_KEY_PORT, MAT_KEY_COL3_PIN)){
		key_num = 12;
		key_flag = 1;//(3,4)
	}
	DL_GPIO_clearPins(MAT_KEY_PORT, MAT_KEY_ROW3_PIN);
	DL_GPIO_setPins(MAT_KEY_PORT, MAT_KEY_ROW0_PIN | MAT_KEY_ROW1_PIN | MAT_KEY_ROW2_PIN);
	delay_ms(10);
	// ROW 1110
	if (!DL_GPIO_readPins(MAT_KEY_PORT, MAT_KEY_COL0_PIN)){
		key_num = 0;
		key_flag = 1;
	}
	else if (!DL_GPIO_readPins(MAT_KEY_PORT, MAT_KEY_COL1_PIN)){
		key_num = 13;
		key_flag = 1;//(4,2)
	}
	else if (!DL_GPIO_readPins(MAT_KEY_PORT, MAT_KEY_COL2_PIN)){
		key_num = 14;
		key_flag = 1;//(4,3)
	}
	else if (!DL_GPIO_readPins(MAT_KEY_PORT, MAT_KEY_COL3_PIN)){
		key_num = 15;
		key_flag = 1;//(4,4)
	}
	if(debug_mode){//通过uart进行数据输入
		key_num = data_receive;
	}
	return key_num;//返回�?
}
