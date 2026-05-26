#include "AD5933.h"
#include "math.h"
#include "stdio.h"
extern u32 Frequency; //别忘了定义这个
double AD5933_Correction[10];
float resistance[200];
float rads[200];
int 	AD5933_Dat_Re[200];
int 	AD5933_Dat_Im[200];
long ReadTemp,realArr[3],imageArr[3];
float magnitude;

void GetACK(void)
{   
	u8 ucErrTime=0;
	
	SDA_IN();      //SDA设置为输入  
	SDA(1);delay_us(1);	   
	SCL(1);delay_us(1);	 
	while(READ_SDA)
	{
		ucErrTime++;
		if(ucErrTime>250)
		{
			STOP();
			return;
		}
	}
	SCL(0);//时钟输出0 	
}

void SendNACK(void)
{
	SCL(0);
	SDA_OUT();
	SDA(1);
	delay_us(2);
	SCL(1);
	delay_us(2);
	SCL(0);
}

void START(void)    // 启动数据总线	
{
	SDA_OUT();     //sda线输出
	SDA(1);	  	  
	SCL(1);
	delay_us(4);
 	SDA(0);//START:when CLK is high,DATA change form high to low 
	delay_us(4);
	SCL(0);//钳住I2C总线，准备发送或接收数据 
}

void STOP(void)
{
	SDA_OUT();//sda线输出
	SCL(0);
	SDA(0);//STOP:when CLK is high DATA change form low to high
 	delay_us(4);
	SCL(1); 
	SDA(1);//发送I2C总线结束信号
	delay_us(4);		
}

void SendByte(u8 txd)	// 发送一个字节数据子函数 
{
    u8 t;   
		SDA_OUT(); 	    
    SCL(0);//拉低时钟开始数据传输
    for(t=0;t<8;t++)
    {              
       SDA((txd&0x80)>>7);
       txd<<=1; 	  
		delay_us(2);   //对TEA5767这三个延时都是必须的
		SCL(1);
		delay_us(2); 
		SCL(0);	
		delay_us(2);
    }	 
}

u8 ReadByte(void)  //读一个字节数据
{
	unsigned char i,receive=0;
	SDA_IN();//SDA设置为输入
    for(i=0;i<8;i++ )
	{
        SCL(0); 
        delay_us(2);
		SCL(1);
        receive<<=1;
        if(READ_SDA)receive++;   
		delay_us(1); 
    }					 
		SendNACK();
    return receive;
}

void Write_Byte(char nAddr,uint nValue)//nAddr中写入字节nValue
{   
	int nTemp = 0x1A;      // AD5933的默认地址&写控制位（低）
	
  START(); 
	SendByte(nTemp);     // 发送地址	
	GetACK();   
	
	SendByte(nAddr);     // 发送地址字节
	GetACK();
	
	SendByte(nValue);	// 发送数据字节	
	GetACK();
		
	STOP();	// 停止总线			
  return;
}

void SetPointer(char nAddr)  //   设置地址指针
{          
	int nTemp = 0x1A;      // AD5933的默认地址&写控制位（低）
	
  START(); 
	SendByte(nTemp);     // 发送地址	
	GetACK();     // 等待 ACK		

	SendByte(0xB0);     // 发送指针命令1101 0000
	GetACK();

	SendByte(nAddr);	// 发送地址指针	
	GetACK();	

	STOP();	// 停止总线			
  return;
}

int Rece_Byte(char nAddr)//读取nAddr中的字节到返回值
{   
	int nTemp ;    
	
  SetPointer(nAddr);   //地址指针指向nAddr
  nTemp=0x1B;      // AD5933的默认地址&读控制位（高）
  START(); 

	SendByte(nTemp);     // 发送地址	
	GetACK();  

	nTemp=ReadByte();//读一个字节数据		
	SendNACK();//发送NO_ACK
	
	STOP();	// 停止总线			
	return nTemp;
}

u16 AD5933_Tempter(void)
{
	 unsigned int Tm;        //保存实部，虚部，温度
   
   Write_Byte(0x80,0x90);  //启动温度测量
   Tm=Rece_Byte(0x92);     //读出温度，保存在Tm中
   Tm<<=8;
   Tm+=Rece_Byte(0x93);
	 Tm<<=2;
	 return Tm;
}


void Fre_To_Hex(float fre,u8 *buf)
{
	u32 dat;
	dat=(536870912/(double)(AD5933_MCLK*1000000))*fre;  
	buf[0]=dat>>16;
	buf[1]=dat>>8;
	buf[2]=dat;
}
//void GET_REG(void)
//{
//	realArr[0]=Rece_Byte(0x94);
//	realArr[1]=Rece_Byte(0x95);
//	realArr[2]=(realArr[0]*0x100)+realArr[1];		
//	imageArr[0]=Rece_Byte(0x96);
//	imageArr[1]=Rece_Byte(0x97);
//	imageArr[2]=(imageArr[0]<<8)+imageArr[1]; 
//	printf("realArr=%ld \r\n",realArr[2]);
//	printf("imageArr=%ld \r\n",imageArr[2]);
//}
/*Fre_Begin起始频率，Fre_UP频率增量，UP_Num增量数，OUTPUT_Vatage输出电压，Gain增益系数，SWeep_Rep扫频为1重复为0*/
/*
Fre_Begin 		开始频率 （HZ）
Fre_UP				步进频率（HZ）
UP_Num				步进次数
OUTPUT_Vatage	输出电压
								AD5933_OUTPUT_2V
								AD5933_OUTPUT_1V
								AD5933_OUTPUT_400mV
								AD5933_OUTPUT_200mV
								
Gain					PGA增益			
							AD5933_Gain_1
							AD5933_Gain_5

SWeep_Rep			扫描模式
							AD5933_Fre_UP 	递增频率
							AD5933_Fre_Rep	重复频率
*/

float AD5933_Sweep (float Fre_Begin,float Fre_UP,u16 UP_Num,u16 OUTPUT_Vatage,u16 Gain,u16 SWeep_Rep)
{
	u8 SValue[3], IValue[3], NValue[2], CValue[2];
	u16 buf=0;
	
	Fre_To_Hex(Fre_Begin,SValue);
	Fre_To_Hex(Fre_UP,IValue);
	
	NValue[0]=UP_Num>>8;
	NValue[1]=UP_Num;
	
#ifdef AD5933_MCLK_USE_OUT
	buf=OUTPUT_Vatage|Gain|SWeep_Rep|AD5933_OUT_MCLK;
#else
	buf=OUTPUT_Vatage|Gain|SWeep_Rep|AD5933_IN_MCLK;
#endif
	
	CValue[0]=buf>>8;
	CValue[1]=buf;
	
	Scale_imp(SValue,IValue,NValue,CValue);
	
	return 0;
}

/*SValue[3]起始频率，IValue[3]频率增量，NValue[2]增量数，CValue[2]控制字，ki增益系数，Ps扫频为1重复为0*/

float Scale_imp (u8 *SValue,u8 *IValue,u8 *NValue,u8 *CValue)
{
		int i,AddrTemp;
		u8 Gain=((~CValue[0])&0x01)?5:1;
	
		u8 SWeep_Rep=((CValue[0]&0xF0)==(AD5933_Fre_UP>>8))?1:0;
	
		u8 Mode=CValue[0]&0x0f;
			 
		AddrTemp=0X82; //初始化起始频率寄存器
		for(i = 0;i <3;i++)
		{
				Write_Byte(AddrTemp,SValue[i]);
				AddrTemp++;
		}     
		
		AddrTemp=0X85; //初始化频率增量寄存器
		for(i = 0;i <3;i++)
		{
				Write_Byte(AddrTemp,IValue[i]);
				AddrTemp++;
		} 
		
		AddrTemp=0X88; //初始化频率点数寄存器
		for(i = 0;i <2;i++)
	 {
				Write_Byte(AddrTemp,NValue[i]);
				AddrTemp++;
	 } 
	 
	 //初始化控制寄存器，1011 0001 0000 0000待机模式，2V，一倍放大，内部时钟
	 
		AddrTemp=0X80; 
		Write_Byte(AddrTemp,Mode|(AD5933_Standby>>8));
	 
		AddrTemp++;
		Write_Byte(AddrTemp,CValue[1]);
	 
		AddrTemp++;
		Write_Byte(0x80,Mode|(AD5933_SYS_Init>>8));//控制寄存器写入初始化频率扫描命令
		
	  delay_ms(10);
		Write_Byte(0X80,Mode|(AD5933_Begin_Fre_Scan>>8));//控制寄存器写入开始频率扫描命令
	 
		while(1)
	  { 
			while(1)
			{
				 ReadTemp=Rece_Byte(0x8F);  //读取状态寄存器检查DFT是否完成
				
				 if (ReadTemp&0x02)
				 break; 
			}  
		
			realArr[0]=Rece_Byte(0x94);
			realArr[1]=Rece_Byte(0x95);
		//	printf("Rs=%ld \r\n",realArr[0]);
			//printf("Rs=%ld \r\n",realArr[1]);
			realArr[2]=(realArr[0]*0x100)+realArr[1];
		
			imageArr[0]=Rece_Byte(0x96);
			imageArr[1]=Rece_Byte(0x97);
		//	printf("Rs=%ld \r\n",realArr[0]);
			//printf("Rs=%ld \r\n",realArr[1]);
			imageArr[2]=(imageArr[0]<<8)+imageArr[1]; 
			
			//printf("realArr=%ld \r\n",realArr[2]);
			//printf("imageArr=%ld \r\n",imageArr[2]);
			
			
			if (realArr[2]>=0x8000)  //计算实部的原码(除符号位外，取反加一)
			{
					realArr[2]^=0xFFFF; 
					realArr[2]^=0x8000; 
					realArr[2]+=1;
					realArr[2]^=0x8000;
			}
			if (imageArr[2]>=0x8000)  //计算虚部的原码(除符号位外，取反加一)
			{
					imageArr[2]^=0xFFFF; 
					imageArr[2]^=0x8000; 
					imageArr[2]+=1;
					imageArr[2]^=0x8000;
			}
//      
//			printf("imageArr=%lf \r\n",b);
		
			
			ReadTemp=Rece_Byte(0x8F);  //读取状态寄存器检查频率扫描是否完成
			
			if (ReadTemp&0x04)
			break;
			
			if (SWeep_Rep==1)
			Write_Byte(0X80,CValue[0]);	//控制寄存器写入增加频率（跳到下一个频率点)的命令
			
			else
			Write_Byte(0X80,CValue[0]);	//控制寄存器写入重复当前频率点扫描	
	  }  
		
			return magnitude;
}
	//	Rs=1/magnitude*40067000;
float DA5933_Get_Rs(void)
{
	float Rs;	
	
	AD5933_Sweep(Frequency,0,0,AD5933_OUTPUT_2V,AD5933_Gain_1,AD5933_Fre_UP);/*扫AD5933_Fre_UP  重复AD5933_Fre_Rep*/
	magnitude=sqrt(realArr[2]*realArr[2]+imageArr[2]*imageArr[2]); 
	//Rs=1/magnitude*96000000;//100k-2m
	Rs=1/magnitude*100000000;//10k-100k
	//Rs=(-0.0266)*magnitude+561.66;//20k-100k
	
	//printf("realArr=%ld \r\n",realArr[2]);
    //printf("imageArr=%ld \r\n",imageArr[2]);
	//delay_ms(500);
	return Rs;
}


float DA5933_Get_Cap()
{
	float cap;
	
	AD5933_Sweep(1000,50,1,AD5933_OUTPUT_1V,AD5933_Gain_1,AD5933_Fre_UP);/*扫AD5933_Fre_UP  重复AD5933_Fre_Rep*/
	magnitude=sqrt(realArr[2]*realArr[2]+imageArr[2]*imageArr[2]); 
	cap=1/magnitude*100000000;
//	printf("realArr=%ld \r\n",realArr[2]);
//  printf("imageArr=%ld \r\n",imageArr[2]);
//	printf("magnitude=%lf \r\n",magnitude);
//	printf("impedance=%lf \r\n",cap);
	return cap;	
}

float DA5933_Get_L()
{
	float l;
	AD5933_Sweep(10000,1000,10,AD5933_OUTPUT_2V,AD5933_Gain_1,AD5933_Fre_UP);/*扫AD5933_Fre_UP  重复AD5933_Fre_Rep*/
	magnitude=sqrt(realArr[2]*realArr[2]+imageArr[2]*imageArr[2]); 
	l=1/magnitude*100000000;
//	printf("Rs=%ld \r\n",realArr[2]);
//  printf("Rs=%ld \r\n",imageArr[2]);
//	printf("imageArr=%lf \r\n",l);
	return l;
}

