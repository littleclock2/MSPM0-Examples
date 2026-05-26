#include "ti_msp_dl_config.h"

uint8_t TxPacket[4] = {0x90, 0x00, 0x00, 0x00};  //发送数据
uint8_t RxPacket[4]={0x00, 0x00, 0x00, 0x00};   //接收数据
uint8_t RxTemp; //临时数据，清空接收FIFO用

int main(void)
{
  SYSCFG_DL_init();                      //初始化
	DL_GPIO_clearPins(GPIOA,DL_GPIO_PIN_3);  //CS信号拉低
	for(uint8_t i=0;i<4;i++)
	{
		DL_SPI_transmitData8(SPI_0_INST, TxPacket[i]);  //发送4字节命令
		while (DL_SPI_isBusy(SPI_0_INST));                //等待发送完成
		RxTemp= DL_SPI_receiveDataBlocking8(SPI_0_INST);  //清空接收FIFO中的数据
	}
	
			DL_SPI_setRepeatTransmit(SPI_0_INST, 1);     //设置重复发送次数，需要接收2个字节，所以重复发送1次
  		DL_SPI_transmitData8(SPI_0_INST, 0);          //用于触发接收用的时钟
	for(uint8_t i=0;i<2;i++)
	{
		//DL_SPI_transmitData8(SPI_0_INST, 0);      //如果不使用重复发送命令，需要在接收每一帧数据的时候做一次发送操作
		RxPacket[i]= DL_SPI_receiveDataBlocking8(SPI_0_INST);  //接收数据
	}
	while (DL_SPI_isBusy(SPI_0_INST));   //等待接收完成
			
	DL_GPIO_setPins(GPIOA,DL_GPIO_PIN_3);     //CS信号拉高，结束操作
    while (1) 
			{
				__NOP();
    }
}


