#include "ti_msp_dl_config.h"
#include "oled.h"
#include "stdio.h"
#include "string.h"
#define CLK_HZ 32e+06 // 系统时钟
#define  ADDRESS	(0x9000)		      //define了一个地址   初始地址

//时钟及显示设置
int num=-1;                 //默认值-1
uint32_t Record[6];   //从0~5分别是年月日时分秒
int mode=1;           //mpu的显示
uint32_t Change[8];   //用于改日期和时间
int cursor=0;  //光标位置，光标是“-”

//mpu6050
#define I2C_TARGET_ADDRESS (0x68)   //6050的地址
uint8_t recv_buf[100];            //保存数据   
uint8_t target[1]={0x3B};          //x轴加速度的寄存器
uint8_t	MPU6050_PWR_MGMT_1[2]={0x6B,0x01};      //电源管理寄存器1，取消睡眠模式，选择时钟源为X轴陀螺仪
uint8_t	MPU6050_PWR_MGMT_2[2]={0x6C,0x00};      //电源管理寄存器2，保持默认值0，所有轴均不待机
uint8_t	MPU6050_SMPLRT_DIV[2]={0x19,0x09};     //采样率分频寄存器，配置采样率
uint8_t	MPU6050_CONFIG[2]={0x1A,0x06};         //配置寄存器，配置DLPF
uint8_t	MPU6050_GYRO_CONFIG[2]={0x1B,0x18};    //陀螺仪配置寄存器，选择满量程为±2000°/s
uint8_t	MPU6050_ACCEL_CONFIG[2]={0x1C,0x18};    //加速度计配置寄存器，选择满量程为±16g
int16_t acc_x,acc_y,acc_z,temp;          //接收数据
float final_acc_x,final_acc_y,final_acc_z,final_temp;       //最终数据
char str[200];

int uart=1;  //决定是否uart通信

void Write_MPU6050(uint8_t*buf)      //往mpu6050的寄存器里写数据
{
	DL_I2C_fillControllerTXFIFO(I2C_0_INST, &buf[0], 2);

    while (!(DL_I2C_getControllerStatus(I2C_0_INST) & DL_I2C_CONTROLLER_STATUS_IDLE));

    DL_I2C_startControllerTransfer(I2C_0_INST, I2C_TARGET_ADDRESS, DL_I2C_CONTROLLER_DIRECTION_TX, 2);  

    while (DL_I2C_getControllerStatus(I2C_0_INST) &DL_I2C_CONTROLLER_STATUS_BUSY_BUS);
    while (!(DL_I2C_getControllerStatus(I2C_0_INST) & DL_I2C_CONTROLLER_STATUS_IDLE));

    delay_cycles(32000);
}
void Init_MPU6050()         //mpu6050初始化
{
	Write_MPU6050(MPU6050_PWR_MGMT_1);
	Write_MPU6050(MPU6050_PWR_MGMT_2);
	Write_MPU6050(MPU6050_SMPLRT_DIV);
	Write_MPU6050(MPU6050_CONFIG);
	Write_MPU6050(MPU6050_GYRO_CONFIG);
	Write_MPU6050(MPU6050_ACCEL_CONFIG);
}

void Read_MPU6050()          //从mpu6050中读数据
{				
	
	
    DL_I2C_fillControllerTXFIFO(I2C_0_INST, &target[0], 1);
    DL_I2C_startControllerTransfer(I2C_0_INST, I2C_TARGET_ADDRESS, DL_I2C_CONTROLLER_DIRECTION_TX, 1);      //传寄存器位置	
    while (DL_I2C_getControllerStatus(I2C_0_INST) &DL_I2C_CONTROLLER_STATUS_BUSY_BUS);
    while (!(DL_I2C_getControllerStatus(I2C_0_INST) & DL_I2C_CONTROLLER_STATUS_IDLE));   
	DL_I2C_startControllerTransfer(I2C_0_INST, I2C_TARGET_ADDRESS, DL_I2C_CONTROLLER_DIRECTION_RX, 8);     //接收信息

	
	
	for(int i=0;i<8;i++)
	{
	   while(DL_I2C_isControllerRXFIFOEmpty(I2C_0_INST));
		 recv_buf[i] = DL_I2C_receiveControllerData(I2C_0_INST);
	}
	

		acc_x = (recv_buf[0] << 8) | recv_buf[1];
		acc_y =	(recv_buf[2] << 8) | recv_buf[3];
		acc_z = (recv_buf[4] << 8) | recv_buf[5];
		temp =	(recv_buf[6] << 8) | recv_buf[7];
		
		final_acc_x=16*9.8f*(double)(acc_x/32768.0f);
		final_acc_y=16*9.8f*(double)(acc_y/32768.0f);
		final_acc_z=16*9.8f*(double)(acc_z/32768.0f);	
	    final_temp=36.53f+(double)(temp/340.0f);
	
}


// void Trans_Uart(char *data,uint16_t length)         //发送数据到uart
// {
//     for(uint16_t i=0;i<length;i++){
//         DL_UART_transmitDataBlocking(UART_0_INST,data[i]);
//     }
// 		DL_UART_transmitDataBlocking(UART_0_INST,'\n');
// }








void delay(int x)       //延迟
{
  delay_cycles(CLK_HZ / 1000 * x);
}
int Matrix()        //矩阵键盘基本函数
{
	 int num = -1;         // 按键值0-15，默认为-1
   static uint8_t key_flag = 0; // 按下按键标志

  if (key_flag)
  {
    delay(300); // 300ms延迟防止按下一次按键却得到了多个相同的按键值
    key_flag = 0;  // 按下按键标志清零
  }
	
	
        DL_GPIO_clearPins(Matrix_PORT, Matrix_H1_PIN);
				DL_GPIO_setPins(Matrix_PORT, Matrix_H2_PIN);
				DL_GPIO_setPins(Matrix_PORT, Matrix_H3_PIN);
				DL_GPIO_setPins(Matrix_PORT, Matrix_H4_PIN);
		    delay(10);
		if(DL_GPIO_readPins(Matrix_PORT, Matrix_V1_PIN)==0||DL_GPIO_readPins(Matrix_PORT, Matrix_V2_PIN)==0||DL_GPIO_readPins(Matrix_PORT, Matrix_V3_PIN)==0||DL_GPIO_readPins(Matrix_PORT, Matrix_V4_PIN)==0)
				{
				  if(DL_GPIO_readPins(Matrix_PORT, Matrix_V1_PIN)==0) num=0;
					if(DL_GPIO_readPins(Matrix_PORT, Matrix_V2_PIN)==0) num=1;
					if(DL_GPIO_readPins(Matrix_PORT, Matrix_V3_PIN)==0) num=2;
					if(DL_GPIO_readPins(Matrix_PORT, Matrix_V4_PIN)==0) num=3;	
					key_flag=1;
				}
				
					
        DL_GPIO_setPins(Matrix_PORT, Matrix_H1_PIN);
				DL_GPIO_clearPins(Matrix_PORT, Matrix_H2_PIN);
				DL_GPIO_setPins(Matrix_PORT, Matrix_H3_PIN);
				DL_GPIO_setPins(Matrix_PORT, Matrix_H4_PIN);
				 delay(10);
				if(DL_GPIO_readPins(Matrix_PORT, Matrix_V1_PIN)==0||DL_GPIO_readPins(Matrix_PORT, Matrix_V2_PIN)==0||DL_GPIO_readPins(Matrix_PORT, Matrix_V3_PIN)==0||DL_GPIO_readPins(Matrix_PORT, Matrix_V4_PIN)==0)
			{
		      
					if(DL_GPIO_readPins(Matrix_PORT, Matrix_V1_PIN)==0) num=4;
					if(DL_GPIO_readPins(Matrix_PORT, Matrix_V2_PIN)==0) num=5;
					if(DL_GPIO_readPins(Matrix_PORT, Matrix_V3_PIN)==0) num=6;
					if(DL_GPIO_readPins(Matrix_PORT, Matrix_V4_PIN)==0) num=7;	
				key_flag=1;
				}
					
				DL_GPIO_setPins(Matrix_PORT, Matrix_H1_PIN);
				DL_GPIO_setPins(Matrix_PORT, Matrix_H2_PIN);
				DL_GPIO_clearPins(Matrix_PORT, Matrix_H3_PIN);
				DL_GPIO_setPins(Matrix_PORT, Matrix_H4_PIN);
			 delay(10);
				if(DL_GPIO_readPins(Matrix_PORT, Matrix_V1_PIN)==0||DL_GPIO_readPins(Matrix_PORT, Matrix_V2_PIN)==0||DL_GPIO_readPins(Matrix_PORT, Matrix_V3_PIN)==0||DL_GPIO_readPins(Matrix_PORT, Matrix_V4_PIN)==0)
				{
				
					if(DL_GPIO_readPins(Matrix_PORT, Matrix_V1_PIN)==0) num=8;
					if(DL_GPIO_readPins(Matrix_PORT, Matrix_V2_PIN)==0) num=9;
					if(DL_GPIO_readPins(Matrix_PORT, Matrix_V3_PIN)==0) num=10;
					if(DL_GPIO_readPins(Matrix_PORT, Matrix_V4_PIN)==0) num=11;	
					key_flag=1;
				}
					
				
				DL_GPIO_setPins(Matrix_PORT, Matrix_H1_PIN);
				DL_GPIO_setPins(Matrix_PORT, Matrix_H2_PIN);
				DL_GPIO_setPins(Matrix_PORT, Matrix_H3_PIN);
				DL_GPIO_clearPins(Matrix_PORT, Matrix_H4_PIN);
				delay(10);
				if(DL_GPIO_readPins(Matrix_PORT, Matrix_V1_PIN)==0||DL_GPIO_readPins(Matrix_PORT, Matrix_V2_PIN)==0||DL_GPIO_readPins(Matrix_PORT, Matrix_V3_PIN)==0||DL_GPIO_readPins(Matrix_PORT, Matrix_V4_PIN)==0)
			{
			   
					if(DL_GPIO_readPins(Matrix_PORT, Matrix_V1_PIN)==0) num=12;
					if(DL_GPIO_readPins(Matrix_PORT, Matrix_V2_PIN)==0) num=13;
					if(DL_GPIO_readPins(Matrix_PORT, Matrix_V3_PIN)==0) num=14;
					if(DL_GPIO_readPins(Matrix_PORT, Matrix_V4_PIN)==0) num=15;	
			   	key_flag=1;
			}

			
        DL_GPIO_clearPins(Matrix_PORT, Matrix_H1_PIN);       //电平归位，便于下次中断
				DL_GPIO_clearPins(Matrix_PORT, Matrix_H2_PIN);
				DL_GPIO_clearPins(Matrix_PORT, Matrix_H3_PIN);
				DL_GPIO_clearPins(Matrix_PORT, Matrix_H4_PIN);
			
			
			return num;
			
}




bool LeapYear(int year)    //判断是否是闰年
{
	if (year % 4 == 0) //必须能被4整除
	{
		if (year % 100 == 0)
		{
			if (year % 400 == 0)
				return 1;           //如果以00结尾,还要能被400整除 	   
			else
				return 0;
		}
		else return 1;
	}
	else
		return 0;
}



int Maxday(int year,int month)  //判断某年某月有多少天
{
    if(month==1||month==3||month==5||month==7||month==8||month==10||month==12)
		{return 31;}
		else if(month==4||month==6||month==9||month==11)
		{return 30;}
		else if(month==2)
		{
		   if(LeapYear(year))
			   return 29;
			 else
				 return 28;
		}
		else 
			return -1;

}



int WeekCal(int year, int Month, int Date)//星期计算算法,蔡勒公式
{
	int SWeek;
	int M, c, y;
	int WYear;
	if (Month == 1 || Month == 2)
	{
		M = Month + 12;
		WYear = year - 1;
	}
	else
	{
		M = Month;
		WYear = year;
	}
	y = WYear % 100;
	c = WYear / 100;
	SWeek = y + y / 4 + c / 4 - 2 * c + 26 * (M + 1) / 10 + Date - 1;
	while (SWeek < 0)
	{
		SWeek += 7;
	}
	SWeek %= 7;
	if (SWeek == 0)
		SWeek = 7;
	return SWeek;
}











void SaveData()    //保存数据
{
//erase flash        
DL_FlashCTL_unprotectSector( FLASHCTL, ADDRESS, DL_FLASHCTL_REGION_SELECT_MAIN);          
DL_FlashCTL_eraseMemoryFromRAM( FLASHCTL, ADDRESS, DL_FLASHCTL_COMMAND_SIZE_SECTOR);
//write flash
DL_FlashCTL_unprotectSector( FLASHCTL, ADDRESS, DL_FLASHCTL_REGION_SELECT_MAIN);
DL_FlashCTL_programMemoryFromRAM( FLASHCTL, ADDRESS, Record,6, DL_FLASHCTL_REGION_SELECT_MAIN); 
}	


void ShowTime()   //显示时间
{
	OLED_ShowNum(0,2,Record[3],2,18);
	OLED_ShowNum(24,2,Record[4],2,18);
	OLED_ShowNum(48,2,Record[5],2,18);
	OLED_ShowChar(40,2,':');  //分后面的“：”
	OLED_ShowChar(16,2,':');  //时后面的“：”
}
void ShowDate()  //显示日期
{
	OLED_ShowNum(0,0,Record[0],4,18);
	OLED_ShowNum(48,0,Record[1],2,18);
	OLED_ShowNum(72,0,Record[2],2,18); 
	OLED_ShowChar(40,0,'.');    //年后面的“.”
	OLED_ShowChar(64,0,'.');  //月后面的“.”
}

void ShowWeek()  //显示星期
{
    int w=WeekCal(Record[0],Record[1],Record[2]);
	switch (w)
	{
		case 1:
		OLED_ShowString(92,0,"Mon");	
    break;
		case 2:
		OLED_ShowString(92,0,"Tues");	
		break;
		case 3:
		OLED_ShowString(92,0,"Wed");		
    break;
		case 4:
		OLED_ShowString(92,0,"Thur");	
    break;
		case 5:
		OLED_ShowString(92,0,"Thur");	
    break;
		case 6:
	  OLED_ShowString(92,0,"Sat");	
    break;
		case 7:
		OLED_ShowString(92,0,"Sun");	
    break;
		default:
		break;
	}		
   

}


void put_datecursor()     //置日期的光标
{
   switch(cursor)
	 {
	   case 0:
			 OLED_ShowChar(0,4,'-');
			 break;
		  case 1:
			OLED_ShowChar(8,4,'-');
			 break;
		 case 2:
			 OLED_ShowChar(16,4,'-');
			 break;
		 case 3:
			 OLED_ShowChar(24,4,'-');
			 break;
		 case 4:
			 OLED_ShowChar(40,4,'-');
			 break;
		 case 5:
			 OLED_ShowChar(48,4,'-');
			 break;
		 case 6:
			 OLED_ShowChar(64,4,'-');
			 break;
		 case 7:
			 OLED_ShowChar(72,4,'-');
			 break;
	   default:
			 cursor=0;    //防止错误
			 break;
	 } 
}
void erase_datecursor()         //擦日期的光标
{
switch(cursor)
	  {
	   case 0:
			 OLED_ShowChar(0,4,' ');
			 break;
		  case 1:
			OLED_ShowChar(8,4,' ');
			 break;
		 case 2:
			 OLED_ShowChar(16,4,' ');
			 break;
		 case 3:
			 OLED_ShowChar(24,4,' ');
			 break;
		 case 4:
			 OLED_ShowChar(40,4,' ');
			 break;
		 case 5:
			 OLED_ShowChar(48,4,' ');
			 break;
		 case 6:
			 OLED_ShowChar(64,4,' ');
			 break;
		 case 7:
			 OLED_ShowChar(72,4,' ');
			 break;
	   default:
			 cursor=0;    //防止错误
			 break;
	 } 



}
void ini_changedate()      //更改日期的初始化        
{
    Change[0] = Record[0]/ 1000;   //千年
	Change[1] = (Record[0] - 1000 *Change[0] ) / 100;  //百年
    Change[2] = (Record[0]- 1000 * Change[0] - 100 *Change[1]) / 10;  //十年
	Change[3] = Record[0] - 1000 * Change[0] - 100 * Change[1] - 10 *Change[2];		//年
    Change[4] =	Record[1]/10;    //十月
    Change[5] =	Record[1]-10*Change[4];  //月
    Change[6] =	Record[2]/10;    //十日
    Change[7] =	Record[2]-10*Change[6];  //日						   
}
void save_changedate()              //更改日期的保存
{
	Record[0]=1000*Change[0]+100*Change[1]+10*Change[2]+Change[3];
	Record[1]=10*Change[4]+Change[5];
	Record[2]=10*Change[6]+Change[7];
	OLED_ShowString(0,4,"Save");
}


void ChangeDate()              //更改日期——合函数
{
	OLED_Clear();			 
	ini_changedate();
	while(1)
	{
		OLED_ShowChar(0,2,Change[0]+'0');
		OLED_ShowChar(8,2,Change[1]+'0');
		OLED_ShowChar(16,2,Change[2]+'0');
		OLED_ShowChar(24,2,Change[3]+'0');
		OLED_ShowChar(40,2,Change[4]+'0');
		OLED_ShowChar(48,2,Change[5]+'0');
		OLED_ShowChar(64,2,Change[6]+'0'); 
		OLED_ShowChar(72,2,Change[7]+'0');

		OLED_ShowChar(32,2,'.');
		OLED_ShowChar(56,2,'.');
		put_datecursor();
		num=Matrix();
		if(num!=-1)
		{
			if(num==4)   //S2 左移
			{
				erase_datecursor();
				cursor=(cursor-1+8)%8;									 
			}   	
			else if(num==6)  //S10 右移
			{
					erase_datecursor();
					cursor=(cursor+1+8)%8;
			}  
			else if(num==1)   //S5 加
			{
				Change[cursor]=(Change[cursor]+1+10)%10;
			}   
			else if(num==9)   //S7 减
			{
				Change[cursor]=(Change[cursor]-1+10)%10;
			}   
			else if(num==5)   //S6 保存
			{
				OLED_Clear();
				save_changedate();													 
				delay(1000);
				cursor=0;    //光标归位
				break; 
			}								
			else
			{
				cursor=0;    //光标归位
				break; 
			}					
		}
	}		 
	OLED_Clear(); 
}


void put_timecursor()      //置时间的光标
{
   switch(cursor)
	{
	    case 0:
			 OLED_ShowChar(0,4,'-');
			 break;
		  case 1:
			OLED_ShowChar(8,4,'-');
			 break;
		 case 2:
			 OLED_ShowChar(24,4,'-');
			 break;
		 case 3:
			 OLED_ShowChar(32,4,'-');
			 break;
		 case 4:
			 OLED_ShowChar(48,4,'-');
			 break;
		 case 5:
			 OLED_ShowChar(56,4,'-');
			 break;
	    default:
			 cursor=0;    //防止错误
			 break;
	} 
}
void erase_timecursor()      //擦时间的光标
{
   switch(cursor)
	 {
	   case 0:
			 OLED_ShowChar(0,4,' ');
			 break;
		  case 1:
			OLED_ShowChar(8,4,' ');
			 break;
		 case 2:
			 OLED_ShowChar(24,4,' ');
			 break;
		 case 3:
			 OLED_ShowChar(32,4,' ');
			 break;
		 case 4:
			 OLED_ShowChar(48,4,' ');
			 break;
		 case 5:
			 OLED_ShowChar(56,4,' ');
			 break;
	   default:
			 cursor=0;    //防止错误
			 break;
	 } 
}
void ini_changetime()         //更改时间时的初始化
{
	Change[0] =	Record[3]/10;    //十时
	Change[1] =	Record[3]-10*Change[0];  //时
		
	Change[2] =	Record[4]/10;    //十分
	Change[3] =	Record[4]-10*Change[2];  //分
		
	Change[4] =	Record[5]/10;    //十秒
	Change[5] =	Record[5]-10*Change[4];  //秒
}
void save_changetime()      //更改时间的保存
{
	Record[3]=10*Change[0]+Change[1];
	Record[4]=10*Change[2]+Change[3];
	Record[5]=10*Change[4]+Change[5];
	OLED_ShowString(0,4,"Save");
}







void ChangeTime()         //更改时间——合函数
{
	OLED_Clear();			 
	ini_changetime();
	while(1)
	{
		OLED_ShowChar(0,2,Change[0]+'0');
		OLED_ShowChar(8,2,Change[1]+'0');
		OLED_ShowChar(16,2,':');
		OLED_ShowChar(24,2,Change[2]+'0');
		OLED_ShowChar(32,2,Change[3]+'0');
		OLED_ShowChar(40,2,':');
		OLED_ShowChar(48,2,Change[4]+'0');
		OLED_ShowChar(56,2,Change[5]+'0');
		put_timecursor();
		num=Matrix();
		if(num!=-1)
		{
			if(num==4)   //S2 左移
			{
				erase_timecursor();
				cursor=(cursor-1+6)%6;									 
			} 
			else if(num==6)  //S10 右移
			{
				erase_timecursor();
				cursor=(cursor+1+6)%6;
			}  
			else if(num==1)   //S5 加
			{
				Change[cursor]=(Change[cursor]+1+10)%10;
			}   
			else if(num==9)   //S7 减
			{
				Change[cursor]=(Change[cursor]-1+10)%10;
			}   
			else if(num==5)   //S6 保存
			{
				OLED_Clear();
				save_changetime();													 
				delay(1000);
				cursor=0;    //光标归位
				break; 
			}								
			else
			{
				cursor=0;    //光标归位
				break; 
			}					
		}
	}		 
	OLED_Clear();
}




int main(void)
{
	SYSCFG_DL_init();                      //初始化
	OLED_Init();			//初始化OLED  
	OLED_Clear();

	NVIC_EnableIRQ(Matrix_INT_IRQN);       //按键中断使能，第四列有效
	DL_TimerG_startCounter(clock_1s_INST);

	NVIC_EnableIRQ(clock_1s_INST_INT_IRQN);         //  秒钟使能	

	NVIC_ClearPendingIRQ(UART1_INT_IRQn);          //UART使能
	NVIC_EnableIRQ(UART1_INT_IRQn);	
	
	Init_MPU6050();         //mpu初始化
	//年月日时秒分置数
	for(int i=0;i<24;i+=4)
		Record[i/4]=*(uint32_t *)(ADDRESS+i);
		
	uart=1;	
	while(1)
	{}
}





//按键中断
void GROUP1_IRQHandler(void)
{
	switch(DL_Interrupt_getPendingGroup(DL_INTERRUPT_GROUP_1))
  	{
     	case Matrix_INT_IIDX:        
			OLED_Clear(); 
			while(1)
			{
				//ShowOptions();
				OLED_ShowString(0,0,"S1:mpu");
				OLED_ShowString(0,2,"S5:change date");
				OLED_ShowString(0,4,"S9:change time");
			     num=Matrix();
				if(num!=-1)
         		{ 
					if(num==0)              // S1： 切换小时制 
				 	{
					    OLED_Clear(); 
						mode=-mode;
					    OLED_ShowString(0,4,"Switched");
						delay(1000);
					 	OLED_Clear(); 
						break;
					}
		   			else if(num==1)            //S5：改日期
					{
						ChangeDate();
					    break;
				    }
				   	else if(num==2)    //S9:改时间
           			{
			     		ChangeTime();
					    break;
					}								
					 
					else        //其他：退出
					{
						OLED_Clear(); 
						break;
					}
			  	}
		  	} 
			break; 
      	default: 
			break; 
  }
}





void clock_1s_INST_IRQHandler(void)   //秒中断
{
	DL_GPIO_togglePins(Light_PORT,Light_LED1_PIN);
	Record[5]++;     
	if(Record[5]>=60)           //秒归零，分进位
		{Record[5]=0;Record[4]++;}
	if(Record[4]>=60)           //分归零，时进位
		{Record[4]=0;Record[3]++;}
	if(Record[3]>=24)           //时归零，天进位
		{Record[3]=0;Record[2]++;}
	if(Record[2]>Maxday(Record[0],Record[1]))    //天归零，月进位
		{Record[2]=0;Record[1]++;}
	if(Record[1]>12)            //月归零，年进位
		{Record[1]=1;Record[0]++;}
	if(Record[0]>9999)          //年归零
		{Record[0]=0;}
	Read_MPU6050();
	if(mode==1)    //正常显示
	{	
		SaveData();
		ShowDate();
		ShowTime();
		ShowWeek();
	}
	else            //显示mpu
	{
		char str_acc_x[20];
		sprintf(str_acc_x,"ax= %.2f",final_acc_x);
		OLED_ShowString(0, 0, str_acc_x);
		
		char str_acc_y[20];
		sprintf(str_acc_y,"ay= %.2f",final_acc_y);
		OLED_ShowString(0, 2, str_acc_y);
		
		char str_acc_z[20];
		sprintf(str_acc_z,"az= %.2f",final_acc_z);
		OLED_ShowString(0, 4, str_acc_z);
			
		char str_temp[20];
		sprintf(str_temp,"t= %.2f",final_temp);//转化成字符串
		OLED_ShowString(0, 6, str_temp);
	}

	if(uart==1)
	{
		// sprintf(str,"%d/%d/%d %d.%d:%d  ax= %.1f,ay= %.1f,az= %.1f,temp= %.2f",
		// Record[0],Record[1],Record[2],Record[3],Record[4],Record[5],
		// final_acc_x,final_acc_y,final_acc_z,final_temp);
		// Trans_Uart(str,strlen(str));
	}
	//sprintf(str,"%d/%d/%d %d.%d:%d  ax= %.1f,ay= %.1f,az= %.1f,temp= %.2f",
	//Record[0],Record[1],Record[2],Record[3],Record[4],Record[5],
	//final_acc_x,final_acc_y,final_acc_z,final_temp);
	//Trans_Uart(str,strlen(str));

}





// void  UART_0_INST_IRQHandler()
// {
//    	switch (DL_UART_Main_getPendingInterrupt(UART_0_INST)) //检测是否串口中断
// 	{
// 		case DL_UART_MAIN_IIDX_RX:
// 					  DL_UART_Main_receiveData(UART_0_INST); 
// 			//	DL_GPIO_togglePins(GPIO_GRP_0_PORT,GPIO_GRP_0_PIN_0_PIN);
// 				 uart = -uart;
// 		 	delay_cycles(32000);
//             break;
//         default:
//             break;
// 	}
// }








