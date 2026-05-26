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
 * @harfware    MicroController
 * @version     v1.0
 * @date        29-July-2024
 * @author      YunSword
 
*/


#include "ti_msp_dl_config.h"
#include "oled.h"
#include <stdio.h>

int fputc(int ch, FILE *stream){
    //当串�?0忙的时候等待，不忙的时候再发送传进来的字�?
    DL_UART_transmitData(UART_0_INST,ch);
	while(DL_UART_isBusy(UART_0_INST)==true){}
    return ch;
}
int choice = 0;//1-6分别代表年月日时分秒，通过输入来更�?
/*
//1.配置1s定时的LED灯及其管�?
//2.设置日期功能的要求：
	//切换模式实现：单独做一个切换的按键�?1个单独按键）
		//10个按键设置数字，最好能单独设置年月日（10个矩阵键盘按键）
	//(待测�?)12/24进制切换�?1个单独按键）
//(待测�?)3.掉电储存功能：自动定时储存，每次启动时先读取默认位置的数据并导入其中
//(待测�?)4.闹钟功能�?

*/
//自动储存内存地址 
#define  ADDRESS	(0x00008000)
#define  CLK        (3200-0000)//时钟速度
#define  NUMSIZE    (16)//数字字体大小
//函数声明
int Key();
int InputErrorCheckDay(int day,int special_year,int month);

void OLEDShow();
int getWeek(int y, int m, int d);
void SetAlarmClock(int clock);
void SetCountDownTime();
//全局变量定义
typedef struct {
	int year ;
	int month ;
	int day ;
	int hour ;
	int minute ;
	int second ;
	int weekday ;//时间显示变量
}ClockData;
//初始结构�?
ClockData ClockDataOrign;
//显示结构�?
ClockData ClockDataShow;
//设置结构�?
ClockData ClockDataSet;
//闹钟结构�?
ClockData ClockDataClock_1;
ClockData ClockDataClock_2;
ClockData ClockDataClock_3;

ClockData SetClockTime(int set_mode);
int AlarmClockCeck(ClockData object);

typedef struct {
	int hour ;
	int minute ;
	int second ;//时间显示变量
}CountDownClock;
//倒计时设置结构体
CountDownClock CountDownClockSet;
//倒计时显示结构体
CountDownClock CountDownClockShow;
//倒计时初始化结构�?
CountDownClock CountDownClockInit;

				
uint32_t auto_save[6] = {2000,1,1,1,1,1};//自动储存变量
uint32_t auto_read[6] = {1,1,1,1,1,1};//自动阅读变量

int isActiveClock_1 = 0,isActiveClock_2 = 0,isActiveClock_3 = 0;
int isActiveClockRing_1 = 0,isActiveClockRing_2 = 0,isActiveClockRing_3 = 0;//闹钟响铃函数
int key_value = 16;
int count_mode;//进制模式
int am = 0,pm = 0,count_timer = 0;
int menu = 1;//第x层菜�?
int isStopWatchActive = 0,stop_watch_second = 0,stop_watch_minute = 0,stop_watch_hour = 0,stop_watch_pause = 0;//秒表变量
int isSetCountDowmTime = 0,count_down_puase = 1,isCountDownClockRing = 0;//倒计时变�?
int ring_time = 3;
int main(void){
	//初始化变�?
		//时钟
		ClockDataOrign.year = 0;
		ClockDataOrign.month = 1;
		ClockDataOrign.day = 1;
		ClockDataOrign.second = 0;
		ClockDataOrign.hour = 0;
		ClockDataOrign.minute = 0;

		ClockDataShow = ClockDataOrign;
		//倒计�?
		CountDownClockInit.hour = 0;
		CountDownClockInit.minute= 0;
		CountDownClockInit.second = 1;

		CountDownClockSet = CountDownClockInit;
		CountDownClockShow = CountDownClockInit;
		//计时模式
		int count_mode = 0;
		

    SYSCFG_DL_init(); // Initialize the device
	//通信初始�?
		NVIC_ClearPendingIRQ(UART_0_INST_INT_IRQN );//清除中断标志�?
    	NVIC_EnableIRQ(UART_0_INST_INT_IRQN );
	//读取储存
		for(int i=0;i<24;i+=4){
			auto_read[i/4]=*(int *)(ADDRESS+i);
		}
		ClockDataShow.year = auto_read[0];
		ClockDataShow.month = auto_read[1];
		ClockDataShow.day = auto_read[2];
		ClockDataShow.hour = auto_read[3];
		ClockDataShow.minute = auto_read[4];
		ClockDataShow.second= auto_read[5];

	DL_TimerG_startCounter(TIMER_0_INST);//启动计时�?
	NVIC_EnableIRQ(TIMER_0_INST_INT_IRQN);//中断函数启动
	
	
	
	OLED_Init();//初始�?
	OLED_Clear();//清除缓存
	delay_ms(10);//延时
	//加载界面
	OLED_ShowString(32,0,"MCU CLOCK");
	OLED_ShowString(16,4,"Loading......");
	delay_ms(500);//显示时间
	OLED_Clear();
	while(1){
		//OLED_Clear();
		key_value = Key();
		if(key_value == 12 && !isSetCountDowmTime){//切换菜单函数
			switch(menu){
				case 1:menu = 2;break;
				case 2:menu = 3;break;
				case 3:menu = 4;break;
				case 4:menu = 1;break;
			}
		}
		switch(menu){
			//第一层菜单功能：三个闹钟设置(最后加上蜂鸣器)�?12/24进制切换，时钟设�?
			case 1:{
				//修改时间函数
				if(key_value == 10){
					count_mode = 0;//恢复24进制
					am = 0;
					pm = 0;
					ClockDataShow = SetClockTime(0);
				}
				//闹钟设置函数
				switch(key_value){
					case 13:
						SetAlarmClock(1);//闹钟1
						break;
					case 14:
						SetAlarmClock(2);//闹钟2
						break;
					case 15:
						SetAlarmClock(3);//闹钟3
						break;
				}
				//进制设置
				if( key_value == 11){
					switch (count_mode){
						case 0://24>>12						
								OLED_Clear();//清屏
								count_mode = 1;
								if(ClockDataShow.hour == 12){
									am = 0;
									pm = 1;
								}
								else if(ClockDataShow.hour > 12){
									ClockDataShow.hour -=12;
									count_timer = 1;
									am = 0;
									pm = 1;
								}
								else if(ClockDataShow.hour < 12){
									am = 1;
									pm = 0;
								}
							break;
						case 1://12>>24
								OLED_Clear();//清屏
								count_mode  = 0;
								if(pm && ClockDataShow.hour != 12){
									ClockDataShow.hour +=12;
								}
								am = 0;
								pm = 0;
							break;
					}
				}
				break;
			}
			//第二层菜单功能：计时�?(启动，暂停，复位，清�?)�?
			case 2:{
				if(key_value == 13) isStopWatchActive = 1;//停表启动
				if(isStopWatchActive){
					if(key_value == 14)stop_watch_pause = (stop_watch_pause==1)? 0 : 1;//暂停功能
					if(key_value == 15){//复位功能
						isStopWatchActive = 0;
						stop_watch_pause = 0;
						OLED_ShowNum(58,6,0,2,16);//�?
					}
				}
				if(key_value == 11){//强制停止功能
						isStopWatchActive = 0;
						stop_watch_pause = 0;
						OLED_Clear();		
					}
				break;
			}
			//第三层菜单功能：倒计时功�?(定时，启动，暂停，复位，结束，计时结束蜂鸣器提醒)�?
			case 3:{
				if(key_value == 10) {
					SetCountDownTime();
					isSetCountDowmTime = 1;
				}
				while(isSetCountDowmTime){
					key_value = Key();
					if(key_value == 11){
						OLED_Clear();
						OLED_ShowString(4,0,"By YunSword");
						//显示姓名
						OLED_ShowCHinese(2,2,0);
						OLED_ShowCHinese(18,2,1);
						OLED_ShowCHinese(34,2,2);
						OLED_ShowCHinese(50,2,3);
						OLED_ShowCHinese(66,2,4);
						OLED_ShowCHinese(82,2,5);
						OLED_ShowCHinese(98,2,6);
						//显示学号
						OLED_ShowString(4,4,"ID");
						OLED_ShowString(4,6,"Your ID Here");
						delay_ms(2000);
						OLED_Clear();
					}
					if(key_value == 13){
						count_down_puase = (count_down_puase == 1)?0:1;
					}
					if(key_value == 14){
						OLED_ShowString(80,0,"Reset!");
						delay_ms(1000);
						CountDownClockShow = CountDownClockSet;
						count_down_puase = 1;
						OLED_Clear();
					}
					//秒表显示
					if(isStopWatchActive){
						OLED_ShowChar(4,6,'#');
						OLED_ShowNum(14,6,stop_watch_hour,2,16);//�?
						OLED_ShowChar(30,6,':');
						OLED_ShowNum(36,6,stop_watch_minute,2,16);//�?
						OLED_ShowChar(52,6,':');
						OLED_ShowNum(58,6,stop_watch_second,2,16);//�?	
					}
					OLED_ShowString(4,0,"Count Down:");
					OLED_ShowNum(4,2,CountDownClockShow.hour,2,16);
					OLED_ShowChar(20,2,':');
					OLED_ShowNum(26,2,CountDownClockShow.minute,2,16);//�?
					OLED_ShowChar(42,2,':');
					OLED_ShowNum(48,2,CountDownClockShow.second,2,16);//�?	
					if(key_value == 15){
						OLED_ShowString(80,6,"Stop!");
						delay_ms(1000);
						isSetCountDowmTime = 0;
						count_down_puase = 1;
						CountDownClockSet = CountDownClockInit;
						CountDownClockShow = CountDownClockInit;
						OLED_Clear();
					}
					if(isCountDownClockRing){
						OLED_Clear();
						OLED_ShowString(12,4,"is ending!!!");
						delay_ms(2000);
						isCountDownClockRing = 0;
						OLED_Clear();
					}
				}
				break;
			}
		}
		//绘制时钟显示界面，每秒刷�?5�?
		OLEDShow();
		//delay_ms(200);
	}
}
//通信接受中断函数
void  UART_0_INST_IRQHandler(){
   switch (DL_UART_getPendingInterrupt(UART_0_INST )){ //检测是否串口中�?
        case DL_UART_MAIN_IIDX_RX:
			//choice = DL_UART_receiveData(UART1); 
			//ClockDataShow.year = (int)choice  ;
//            if(!choice)choice = DL_UART_receiveData(UART0);  //发送接收到的数�?
//			else if(choice){
//				switch(choice){
//					case 1:
//						ClockDataShow.year = DL_UART_receiveData(UART0);
//						choice = 0;
//						break;
//					case 2:
//						ClockDataShow.month = DL_UART_receiveData(UART0);
//						choice = 0;
//						break;
//					case 3:
//						ClockDataShow.day = DL_UART_receiveData(UART0);
//						choice = 0;
//						break;
//					case 4:
//						ClockDataShow.hour = DL_UART_receiveData(UART0);
//						choice = 0;	
//						break;
//					case 5:
//						ClockDataShow.minute = DL_UART_receiveData(UART0);
//						choice = 0;
//						break;
//					case 6:
//						ClockDataShow.second = DL_UART_receiveData(UART0);
//						choice = 0;
//						break;
//				}
//			}
            break;
        default:
            break;
    }
}
//中断函数
void TIMER_0_INST_IRQHandler (void){
	switch( DL_TimerG_getPendingInterrupt (TIMER_0_INST)){
		case DL_TIMERG_IIDX_ZERO:
			DL_GPIO_togglePins(LED_PORT,LED_LED0_PIN);//1s的定时器系统
			ClockDataShow.second ++;//秒数自增
			{//时分秒进�?
				if( ClockDataShow.second > 59 ){
					ClockDataShow.second = 0;
					ClockDataShow.minute ++;
				} 
				if (ClockDataShow.minute > 59){
					ClockDataShow.minute = 0;
					ClockDataShow.hour ++;
				}
				//24进制
				if(ClockDataShow.hour > 23 && !am && !pm){
					ClockDataShow.hour = 0;
					ClockDataShow.day ++;
				}
				//12进制
				if(ClockDataShow.hour >= 12 && am ){//上午到下�?
					ClockDataShow.hour = 12;
					am = 0;
					pm = 1;
				}
				if( ClockDataShow.hour > 12 && pm){//中午到下�?
					ClockDataShow.hour = 1;
					am = 0;
					pm = 1;
					count_timer = 1;
				}
				if( ClockDataShow.hour >= 12 && pm && count_timer){//晚上到第二天
					ClockDataShow.hour = 0;
					am = 1;
					pm = 0;
					ClockDataShow.day ++;
					count_timer = 0;
				}
				
				
			}
			{//年月日进�?
				int special_year = 0;
				if((ClockDataShow.year % 4 == 0 && ClockDataShow.year % 100 != 0)||(ClockDataShow.year % 400 == 0))
					special_year = 1;//判断是否为闰�?
				if(InputErrorCheckDay(ClockDataShow.day,special_year,ClockDataShow.month)){
					ClockDataShow.day = 1;
					ClockDataShow.month ++;
				} 
				if (ClockDataShow.month > 12){
					ClockDataShow.month = 1;
					ClockDataShow.year ++;
				}
			}
			//星期几计�?
			ClockDataShow.weekday = getWeek(ClockDataShow.year,ClockDataShow.month,ClockDataShow.day);
			{//每秒自动储存
				//擦除数据
				DL_FlashCTL_unprotectSector( FLASHCTL, ADDRESS, DL_FLASHCTL_REGION_SELECT_MAIN);
				DL_FlashCTL_eraseMemoryFromRAM( FLASHCTL, ADDRESS, DL_FLASHCTL_COMMAND_SIZE_SECTOR);
				DL_FlashCTL_waitForCmdDone( FLASHCTL);
				//写入数据
			    auto_save[0] = ClockDataShow.year ;
				auto_save[1] = ClockDataShow.month ;
				auto_save[2] = ClockDataShow.day ;
				auto_save[3] = ClockDataShow.hour ;
				auto_save[4] = ClockDataShow.minute ;
				auto_save[5] = ClockDataShow.second;
				DL_FlashCTL_unprotectSector( FLASHCTL, ADDRESS, DL_FLASHCTL_REGION_SELECT_MAIN);
				DL_FlashCTL_programMemoryFromRAM( FLASHCTL, ADDRESS, auto_save,6, DL_FLASHCTL_REGION_SELECT_MAIN);
				DL_FlashCTL_waitForCmdDone(FLASHCTL);
			}
			{//秒表系统
				if( isStopWatchActive && !stop_watch_pause)stop_watch_second++;//秒表自增
				if(!isStopWatchActive){
					
					stop_watch_second = 0;//归零
					stop_watch_minute = 0;
					stop_watch_hour = 0;
				}
				if( stop_watch_second > 59 ){
					stop_watch_second = 0;
					stop_watch_minute ++;
				}
				if (stop_watch_minute > 59){
					stop_watch_minute = 0;
					stop_watch_hour ++;
				}
			}
			{//闹钟函数校验比较
				if(isActiveClock_1){
					if(AlarmClockCeck(ClockDataClock_1))isActiveClockRing_1 = 1;
					//else isActiveClockRing_1 = 0;
				}
				if(isActiveClock_2){
					if(AlarmClockCeck(ClockDataClock_2))isActiveClockRing_2= 1;
					//else isActiveClockRing_2 = 0;
				}
				if(isActiveClock_3){
					if(AlarmClockCeck(ClockDataClock_3))isActiveClockRing_3 = 1;
					//else isActiveClockRing_3 = 0;
				}
			}
			{//倒计时系�?
				if(!count_down_puase)CountDownClockShow.second -- ;
				if( (CountDownClockShow.second %100 > 60) && !isCountDownClockRing && (CountDownClockShow.minute > 0 || CountDownClockShow.hour > 0)&& !count_down_puase){
					CountDownClockShow.second = 59;
					CountDownClockShow.minute --;
				}  
				if (CountDownClockShow.minute < 0 &&!isCountDownClockRing && CountDownClockShow.hour > 0 && !count_down_puase){
					CountDownClockShow.minute = 59;
					CountDownClockShow.hour --;
				}
				if(CountDownClockShow.hour < 1 && !isCountDownClockRing && !count_down_puase) CountDownClockShow.hour = 0;

				if(CountDownClockShow.hour == 0 && CountDownClockShow.minute == 0 && CountDownClockShow.second == 0 && !count_down_puase){
					isCountDownClockRing = 1;
				}
				else isCountDownClockRing = 0;
			}
			{//蜂鸣器启动函�?
			// 	if(isActiveClockRing_1 || isActiveClockRing_2 || isActiveClockRing_3 || isCountDownClockRing){
			// 		DL_GPIO_togglePins(BUZZER_PORT,BUZZER_Buzzer0_PIN);
			// 		ring_time --;
			// 	}
			// 	if(ring_time < 0 ){
			// 		isActiveClockRing_1 = 0;
			// 		isActiveClockRing_2 = 0;
			// 		isActiveClockRing_3 = 0;
			// 		isCountDownClockRing = 0;
			// 	}
			}
			 {//向外界实时发送信�?
			 	uint8_t year_1 = ClockDataShow.year/100;
				uint8_t year_2 = ClockDataShow.year%100;
			 	uint8_t month = ClockDataShow.month;
			 	uint8_t day = ClockDataShow.day;
			 	uint8_t hour = ClockDataShow.hour;
			 	uint8_t minute = ClockDataShow.minute;
			 	uint8_t second = ClockDataShow.second;
			 	//DL_UART_transmitData(UART_0_INST,year);
				//固定向外界发送信�?
				//printf("%d,%d,%d,%d,%d,%d\n",year_1*100 + year_2,month,day,hour,minute,second);
				//闹钟响向外界发送信�?
				if(isActiveClockRing_1)printf("%d\n",100);
				if(isActiveClockRing_2)printf("%d\n",200);
				if(isActiveClockRing_3)printf("%d\n",300);
			 }
			break;
		default:
			break;
	}
}
//倒计时设置函�?
void SetCountDownTime(){
	int t_key_value = 16;
	OLED_Clear();
	//初始�?
	OLED_ShowString(8,0,"Count Down Set");
	delay_ms(1000);
	OLED_Clear();
	OLED_Clear();
	t_key_value = Key();//变量复位
	//设置小时
	for(int i = 1;i<3;i++){//
		OLED_ShowString(16,0,"Hour:");
		if(i == 1 ){//首数字校�?
			do{
				t_key_value = Key();
			}while(t_key_value > 2);
		}
		if(i == 2 && ClockDataSet.hour != 2 ){//第二位数字校�?
			do{
				t_key_value = Key();
			}while(t_key_value > 9);
		}
		if(i == 2 && ClockDataSet.hour == 2){//第二位数字校�?
			do{
				t_key_value = Key();
			}while(t_key_value > 4);
		}
		CountDownClockSet.hour = t_key_value + CountDownClockSet.hour * 10;
		OLED_ShowNum(56,0,CountDownClockSet.hour,i,NUMSIZE);//小时显示
	}
	t_key_value = Key();//变量复位
	//设置�?
	for(int i = 1;i<3;i++){//
		OLED_ShowString(16,2,"Minute:");
		if(i == 1 ){//首数字校�?
			do{
				t_key_value = Key();
			}while(t_key_value > 5);
		}
		if(i == 2 ){//第二位数字校�?
			do{
				t_key_value = Key();
			}while(t_key_value > 9);
		}
		CountDownClockSet.minute = t_key_value + CountDownClockSet.minute * 10;
		OLED_ShowNum(72,2,CountDownClockSet.minute,i,NUMSIZE);//分钟显示
	}
	t_key_value = Key();//变量复位
	//设置�?
	for(int i = 1;i<3;i++){//
		OLED_ShowString(16,4,"Second:");
		if(i == 1){//首数字校�?
			do{
				t_key_value = Key();
			}while(t_key_value > 5);
		}
		if(i == 2 ){//第二位数字校�?
			do{
				t_key_value = Key();
			}while(t_key_value > 9);
		}
		CountDownClockSet.second = t_key_value + CountDownClockSet.second * 10;
		OLED_ShowNum(72,4,CountDownClockSet.second,i,NUMSIZE);//秒钟显示
	}
	//确认设置
	OLED_ShowString(2,6,"# Success");	
	delay_ms(500);
	OLED_Clear();
	CountDownClockShow =  CountDownClockSet ;
}
//闹钟比较函数
int AlarmClockCeck(ClockData object){
	int isEqual = 0;
	if(object.year == ClockDataShow.year && object.month == ClockDataShow.month && object.day == ClockDataShow.day && object.hour== ClockDataShow.hour && object.minute == ClockDataShow.minute && object.second == ClockDataShow.second)isEqual = 1;
	return isEqual;
}
//OLED显示控制函数
void OLEDShow(){
	//计算模块
	//数据显示模块
	//OLED_Clear();
	switch(menu){//菜单�?
		case 1:OLED_ShowString(114,0,"1");break;
		case 2:OLED_ShowString(114,0,"2");break;
		case 3:OLED_ShowString(114,0,"3");break;
		case 4:OLED_ShowString(114,0,"4");break;
	}
	switch(ClockDataShow.weekday){//星期�?
		case 1:OLED_ShowString(4,0,"Mon");break;
		case 2:OLED_ShowString(4,0,"Tue");break;
		case 3:OLED_ShowString(4,0,"Wes");break;
		case 4:OLED_ShowString(4,0,"Thu");break;
		case 5:OLED_ShowString(4,0,"Fri");break;
		case 6:OLED_ShowString(4,0,"Sat");break;
		case 7:OLED_ShowString(4,0,"Sun");break;
	}
	//闹钟开关状�?
	if(isActiveClock_1)OLED_ShowString(40,0,"@");
	if(isActiveClock_2)OLED_ShowString(48,0,"@");
	if(isActiveClock_3)OLED_ShowString(56,0,"@");
	//闹钟启停状�?
	if(isActiveClockRing_1){
		OLED_Clear();
		OLED_ShowString(12,0,"Clock_1");
		OLED_ShowString(8,4,"Ringing");
		delay_ms(4000);//显示时间
		OLED_Clear();
		isActiveClockRing_1 = 0;
		}
	if(isActiveClockRing_2){
		OLED_Clear();
		OLED_ShowString(12,2,"Clock_2");
		OLED_ShowString(8,4,"Ringing");
		delay_ms(4000);//显示时间
		OLED_Clear();
		isActiveClockRing_1 = 0;
		}
	if(isActiveClockRing_3){
		OLED_Clear();
		OLED_ShowString(12,4,"Clock_3");
		OLED_ShowString(8,6,"Ringing");
		delay_ms(4000);//显示时间
		OLED_Clear();
		
		}
	//年月日显�?
	OLED_ShowNum(14,2,ClockDataShow.year,4,16);//�?
	OLED_ShowChar(48,2,'.');
	OLED_ShowNum(56,2,ClockDataShow.month,2,16);//�?
	OLED_ShowChar(72,2,'.');
	OLED_ShowNum(80,2,ClockDataShow.day,2,16);//�?
	OLED_ShowNum(30,4,ClockDataShow.hour,2,16);//�?
	OLED_ShowChar(48,4,':');
	OLED_ShowNum(56,4,ClockDataShow.minute,2,16);//�?
	OLED_ShowChar(72,4,':');
	OLED_ShowNum(80,4,ClockDataShow.second,2,16);//�?
	if(am)OLED_ShowString(96,4,"AM");
	if(pm)OLED_ShowString(96,4,"PM");
	//秒表显示
	if(isStopWatchActive){
		OLED_ShowChar(4,6,'#');
		OLED_ShowNum(14,6,stop_watch_hour,2,16);//�?
		OLED_ShowChar(30,6,':');
		OLED_ShowNum(36,6,stop_watch_minute,2,16);//�?
		OLED_ShowChar(52,6,':');
		OLED_ShowNum(58,6,stop_watch_second,2,16);//�?	
	}
	
}
//闹钟设置函数
void SetAlarmClock(int clock){
	int t_key_value = 16;
	OLED_Clear();
	OLED_ShowString(16,0,"Alarm Clock");
	switch (clock){
		case 1:OLED_ShowChar(0,90,'1');break;
		case 2:OLED_ShowChar(0,90,'2');break;
		case 3:OLED_ShowChar(0,90,'3');break;
		default:break;
	}
	//选项界面
	OLED_ShowString(0,2,"1.Setting");
	OLED_ShowString(0,4,"2.Checking");
	OLED_ShowString(0,6,"3.Switch");
	do{
		t_key_value = Key();
	}while(t_key_value!=11 && t_key_value != 12 && t_key_value != 10);
	switch (t_key_value){
		case 10:
			switch(clock){//分项闹钟设置
				case 1:
					ClockDataClock_1 = SetClockTime(1);
					//星期几计�?
					ClockDataClock_1.weekday = getWeek(ClockDataClock_1.year,ClockDataClock_1.month,ClockDataClock_1.day);
					break;
				case 2:
					ClockDataClock_2 = SetClockTime(1);
					//星期几计�?
					ClockDataClock_2.weekday = getWeek(ClockDataClock_2.year,ClockDataClock_2.month,ClockDataClock_2.day);
					break;
				case 3:
					ClockDataClock_3 = SetClockTime(1);
					//星期几计�?
					ClockDataClock_3.weekday = getWeek(ClockDataClock_3.year,ClockDataClock_3.month,ClockDataClock_3.day);
					break;
			}
			break;
		case 11:
			switch(clock){//闹钟查看
				case 1:
					OLED_Clear();
					OLED_ShowString(4,0,"Clock 1");
					OLED_ShowNum(14,2,ClockDataClock_1.year,4,16);//�?
					OLED_ShowChar(48,2,'.');
					OLED_ShowNum(56,2,ClockDataClock_1.month,2,16);//�?
					OLED_ShowChar(72,2,'.');
					OLED_ShowNum(80,2,ClockDataClock_1.day,2,16);//�?
					OLED_ShowNum(30,4,ClockDataClock_1.hour,2,16);//�?
					OLED_ShowChar(48,4,'.');
					OLED_ShowNum(56,4,ClockDataClock_1.minute,2,16);//�?
					OLED_ShowChar(72,4,'.');
					OLED_ShowNum(80,4,ClockDataClock_1.second,2,16);//�?
					delay_ms(2000);
					OLED_Clear();
					break;
				case 2:
					OLED_Clear();
					OLED_ShowString(4,0,"Clock 2");
					OLED_ShowNum(14,2,ClockDataClock_2.year,4,16);//�?
					OLED_ShowChar(48,2,'.');
					OLED_ShowNum(56,2,ClockDataClock_2.month,2,16);//�?
					OLED_ShowChar(72,2,'.');  
					OLED_ShowNum(80,2,ClockDataClock_2.day,2,16);//�?
					OLED_ShowNum(30,4,ClockDataClock_2.hour,2,16);//�?
					OLED_ShowChar(48,4,'.');
					OLED_ShowNum(56,4,ClockDataClock_2.minute,2,16);//�?
					OLED_ShowChar(72,4,'.');
					OLED_ShowNum(80,4,ClockDataClock_2.second,2,16);//�?
					delay_ms(2000);
					OLED_Clear();
					break;
				case 3:
					OLED_Clear();
					OLED_ShowString(4,0,"Clock 3");
					OLED_ShowNum(14,2,ClockDataClock_3.year,4,16);//�?
					OLED_ShowChar(48,2,'.');
					OLED_ShowNum(56,2,ClockDataClock_3.month,2,16);//�?
					OLED_ShowChar(72,2,'.');
					OLED_ShowNum(80,2,ClockDataClock_3.day,2,16);//�?
					OLED_ShowNum(30,4,ClockDataClock_3.hour,2,16);//�?
					OLED_ShowChar(48,4,'.');
					OLED_ShowNum(56,4,ClockDataClock_3.minute,2,16);//�?
					OLED_ShowChar(72,4,'.');
					OLED_ShowNum(80,4,ClockDataClock_3.second,2,16);//�?
					delay_ms(2000);
					OLED_Clear();
					break;
			}
			break;
		case 12:
			OLED_Clear();
			switch(clock){//闹钟开关设�?
				case 1:
					isActiveClock_1 = (isActiveClock_1 == 1)? 0 : 1;//双目翻转
					OLED_ShowString(4,2,"Success");
					delay_ms(1000);
					OLED_Clear();
					break;
				case 2:
					isActiveClock_2 = (isActiveClock_2 == 1)? 0 : 1;//双目翻转
					OLED_ShowString(4,2,"Success");
					delay_ms(1000);
					OLED_Clear();
					break;
				case 3:
					isActiveClock_3 = (isActiveClock_3== 1)? 0 : 1;//双目翻转
					OLED_ShowString(4,2,"Success");
					delay_ms(1000);
					OLED_Clear();
					break;
			}
			break;
		default:break;
	}
}
//时间设置函数
ClockData SetClockTime(int set_mode){
	int t_key_value = 0;//临时变量
	
	OLED_Clear();
	ClockDataSet.year = 0;
	ClockDataSet.month = 0;
	ClockDataSet.day = 0;
	ClockDataSet.second = 0;
	ClockDataSet.hour = 0;
	ClockDataSet.minute = 0;
	//初始�?
	OLED_ShowString(4,1,"Please set the time.");
	delay_ms(1000);
	OLED_Clear();
	//设置�?
	for(int i = 1;i<5;i++){//
		OLED_ShowString(16,0,"Year:");
		do{
			t_key_value = Key();
			delay_ms(100);
		}while(t_key_value > 9);
		ClockDataSet.year = t_key_value + ClockDataSet.year * 10;
		OLED_ShowNum(56,0,ClockDataSet.year,i,NUMSIZE);//年份显示
	}
	t_key_value = Key();//变量复位
	//设置�?
	for(int i = 1;i<3;i++){//
		OLED_ShowString(16,2,"Month:");
		if(i == 1){//首数字校�?
			do{
				t_key_value = Key();
			}while(t_key_value != 0 && t_key_value != 1);
		}
		if(i == 2 && ClockDataSet.month == 1 ){//第二位数字校�?
			do{
				t_key_value = Key();
			}while(t_key_value > 2);
		}
		if(i == 2 && ClockDataSet.month != 1 ){//第二位数字校�?
			do{
				t_key_value = Key();
			}while(t_key_value >9);
		}
		ClockDataSet.month = t_key_value + ClockDataSet.month * 10;
		OLED_ShowNum(64,2,ClockDataSet.month,i,NUMSIZE);//月份显示
	}
	t_key_value = Key();//变量复位
	//设置�?
	for(int i = 1;i<3;i++){//
		OLED_ShowString(16,4,"Day:");
		do{
			t_key_value = Key();
		}while(t_key_value > 9);
		//检查是否为闰年
		int special_year = 0,isErrror = 0;
		if((ClockDataSet.year % 4 == 0 && ClockDataSet.year % 100 != 0)||(ClockDataSet.year % 400 == 0))
			special_year = 1;//判断是否为闰�?
		if( i == 1 && t_key_value > 3 ){
			i--;
			continue;
		}
		ClockDataSet.day = t_key_value + ClockDataSet.day * 10;
		if(i == 2){//判断日期是否符合规则
			isErrror =  InputErrorCheckDay( ClockDataSet.day ,special_year,ClockDataSet.month);
		}
		if(isErrror){
			OLED_Clear();
			OLED_ShowString(4,3,"Error days!");
			OLED_ShowString(4,6,"Please reset!");
			delay_ms(1000);
			OLED_Clear();
			if(set_mode)return ClockDataOrign;//时钟的当前�?
			else return ClockDataShow;//时钟的当前�?
		}
		OLED_ShowNum(56,4,ClockDataSet.day,i,NUMSIZE);//日期显示
	}
	OLED_Clear();
	t_key_value = Key();//变量复位
	//设置小时
	for(int i = 1;i<3;i++){//
		OLED_ShowString(16,0,"Hour:");
		if(i == 1 ){//首数字校�?
			do{
				t_key_value = Key();
			}while(t_key_value > 2);
		}
		if(i == 2 && ClockDataSet.hour != 2 ){//第二位数字校�?
			do{
				t_key_value = Key();
			}while(t_key_value > 9);
		}
		if(i == 2 && ClockDataSet.hour == 2){//第二位数字校�?
			do{
				t_key_value = Key();
			}while(t_key_value > 4);
		}
		ClockDataSet.hour = t_key_value + ClockDataSet.hour * 10;
		OLED_ShowNum(56,0,ClockDataSet.hour,i,NUMSIZE);//小时显示
	}
	t_key_value = Key();//变量复位
	//设置�?
	for(int i = 1;i<3;i++){//
		OLED_ShowString(16,2,"Minute:");
		if(i == 1 ){//首数字校�?
			do{
				t_key_value = Key();
			}while(t_key_value > 5);
		}
		if(i == 2 ){//第二位数字校�?
			do{
				t_key_value = Key();
			}while(t_key_value > 9);
		}
		ClockDataSet.minute = t_key_value + ClockDataSet.minute * 10;
		OLED_ShowNum(72,2,ClockDataSet.minute,i,NUMSIZE);//分钟显示
	}
	t_key_value = Key();//变量复位
	//设置�?
	for(int i = 1;i<3;i++){//
		OLED_ShowString(16,4,"Second:");
		if(i == 1){//首数字校�?
			do{
				t_key_value = Key();
			}while(t_key_value > 5);
		}
		if(i == 2 ){//第二位数字校�?
			do{
				t_key_value = Key();
			}while(t_key_value > 9);
		}
		ClockDataSet.second = t_key_value + ClockDataSet.second * 10;
		OLED_ShowNum(72,4,ClockDataSet.second,i,NUMSIZE);//秒钟显示
	}
	//确认设置
	OLED_ShowString(2,6,"Ensure 1/0");	
	do{
		t_key_value  = Key();
	}while (t_key_value != 1 && t_key_value != 0);
	OLED_Clear();
	if(t_key_value){
		return ClockDataSet;
	}
	else{
		if(set_mode)return ClockDataOrign;//闹钟的初始�?
		else return ClockDataShow;//取消设置后恢复原�?
	}
}
//星期计算函数
int getWeek(int y, int m, int d){//传入参数分别为年、月、日�?
	if(m==1||m==2) {
		m+=12;
		y--;
	}
	return (d+2*m+3*(m+1)/5+y+y/4-y/100+y/400)%7+1;
}
//月份对应日期校验函数
int InputErrorCheckDay(int day,int special_year,int month){
	int isError = 0;
	switch (month){
		case 1:
			if(day > 31 || day < 1){
				isError = 1;
			}
			break;
		case 2:
			if((day > 29 || day < 1 )&& special_year == 1){
				isError = 1;
			}
			else if((day > 28 ||  day < 1) && special_year == 0){
				isError = 1;
			}
			break;
		case 3:			
			if(day > 31 ||  day < 1){
				isError = 1;
			}
			break;
		case 4:
			if(day > 30 ||  day < 1){
				isError = 1;
			}
			break;
		case 5:
				if(day > 31 ||  day < 1){
				isError = 1;
			}
			break;
		case 6:
			if(day > 30 ||  day < 1){
				isError = 1;
			}
			break;
		case 7:
			if(day > 31 ||  day < 1){
				isError = 1;
			}
			break;
		case 8:
			if(day > 31 ||  day < 1){
				isError = 1;
			}
			break;
		case 9:
			if(day > 30 ||  day < 1){
				isError = 1;
			}
			break;
		case 10:
				if(day > 31 ||  day < 1){
				isError = 1;
			}
			break;
		case 11:
			if(day > 30 ||  day < 1){
				isError = 1;
			}
			break;
		case 12:
			if(day > 31 ||  day < 1){
				isError = 1;
			}
			break;
		}
	return isError;
}
//矩阵键盘函数
int Key(){
	int key_num = 16;         // 按键�?0-15，默认为16
	static uint32_t key_flag = 0; // 按下按键标志

	if (key_flag){
		delay_ms(300); // 300ms延迟，防止按下一次按键却被认为按下了多次按键，导致得到了多个相同的按键�?
		key_flag = 0;  // 按下按键标志清零
	}
	// 行扫�?
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
	return key_num;//返回�?
}

