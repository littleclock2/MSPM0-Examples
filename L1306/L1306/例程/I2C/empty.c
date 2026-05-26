

#include "ti_msp_dl_config.h"
#define I2C_TARGET_ADDRESS (0xA0>>1)   //7位地址位，需要右移一位给预留MCU读写位
uint8_t WritePacket[8] = {
    0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08};   //往0x0201地址开始写入0x03,0x04,0x05,0x06,0x07,0x08
uint8_t ReadAddress[2]={0x01,0x02};
uint8_t ReadPacket[6];

int main(void)
{
		SYSCFG_DL_init();                          //初始化
		DL_I2C_fillControllerTXFIFO(I2C_0_INST, &WritePacket[0], 8);    //FIFO中填入数据
	
    while (!(DL_I2C_getControllerStatus(I2C_0_INST) &DL_I2C_CONTROLLER_STATUS_IDLE)) //等待I2C空闲
        ;
    DL_I2C_startControllerTransfer(I2C_0_INST, I2C_TARGET_ADDRESS,DL_I2C_CONTROLLER_DIRECTION_TX,8);//发送写数据

    while (DL_I2C_getControllerStatus(I2C_0_INST) &DL_I2C_CONTROLLER_STATUS_BUSY_BUS)    //的等待发送完成
        ;
		while (!(DL_I2C_getControllerStatus(I2C_0_INST) &DL_I2C_CONTROLLER_STATUS_IDLE))//等待I2C空闲
        ;
		
		delay_cycles(320000);//等待AT24C256写周期时间10ms
		DL_I2C_fillControllerTXFIFO(I2C_0_INST,&ReadAddress[0],2);  //在FIFO中装载要目标数据的地址0x0201
		DL_I2C_startControllerTransfer(I2C_0_INST, I2C_TARGET_ADDRESS,DL_I2C_CONTROLLER_DIRECTION_TX,2);//发送目标地址数据

    while (DL_I2C_getControllerStatus(I2C_0_INST) &DL_I2C_CONTROLLER_STATUS_BUSY_BUS)    //的等待发送完成
        ;
		while (!(DL_I2C_getControllerStatus(I2C_0_INST) &DL_I2C_CONTROLLER_STATUS_IDLE))//等待I2C空闲
			  ;
		delay_cycles(180000);	//等待
		DL_I2C_startControllerTransfer(I2C_0_INST, I2C_TARGET_ADDRESS,DL_I2C_CONTROLLER_DIRECTION_RX, 6);  //读取目标数据
		for (uint8_t i = 0; i < 6; i++)                //接收FIFO的数据
		{
        while (DL_I2C_isControllerRXFIFOEmpty(I2C_0_INST))
            ;
        ReadPacket[i] = DL_I2C_receiveControllerData(I2C_0_INST);
    }
		
    while (1) 
			{
					__BKPT(0);

			}
}



