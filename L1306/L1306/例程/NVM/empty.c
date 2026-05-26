#include "ti_msp_dl_config.h"


#define MAIN_BASE_ADDRESS (0x00001000)    //FLASH起始地址
uint8_t data8 = 0x11;                 //8位写入数据
uint16_t data16 = 0x2222;             //16位写入数据
uint32_t data32 = 0x33333333;         //32位写入数据
uint32_t dataArray64[] = {0xABCDEF00, 0x12345678};  //64位写入数据

int main(void)
{
    SYSCFG_DL_init();
    DL_FlashCTL_unprotectSector(FLASHCTL, MAIN_BASE_ADDRESS, DL_FLASHCTL_REGION_SELECT_MAIN);//解锁FLASH
    DL_FlashCTL_eraseMemory(FLASHCTL, MAIN_BASE_ADDRESS, DL_FLASHCTL_COMMAND_SIZE_SECTOR);    //擦除FLASH

 
    DL_FlashCTL_unprotectSector(FLASHCTL, MAIN_BASE_ADDRESS, DL_FLASHCTL_REGION_SELECT_MAIN);   //每次执行完操作后，FLASH写保护寄存器会自动置位，所以需要再次解锁
    DL_FlashCTL_programMemoryFromRAM8(FLASHCTL, MAIN_BASE_ADDRESS, &data8);           //8位无ECC位写入
    DL_FlashCTL_waitForCmdDone(FLASHCTL);                                      //等待写入完成
  
    DL_FlashCTL_unprotectSector(FLASHCTL, MAIN_BASE_ADDRESS, DL_FLASHCTL_REGION_SELECT_MAIN);   //解锁
   DL_FlashCTL_programMemoryFromRAM16(FLASHCTL, (MAIN_BASE_ADDRESS + 8), &data16);   //16位无ECC写入
    DL_FlashCTL_waitForCmdDone(FLASHCTL);                                      //等待写入完成
  
    DL_FlashCTL_unprotectSector(FLASHCTL, MAIN_BASE_ADDRESS, DL_FLASHCTL_REGION_SELECT_MAIN);   //解锁
   DL_FlashCTL_programMemoryFromRAM32(FLASHCTL, (MAIN_BASE_ADDRESS + 16), &data32);                   //32位无ECC写入
    DL_FlashCTL_waitForCmdDone(FLASHCTL);                                       //等待写入完成

    DL_FlashCTL_unprotectSector( FLASHCTL, MAIN_BASE_ADDRESS, DL_FLASHCTL_REGION_SELECT_MAIN);   //解锁
    DL_FlashCTL_programMemoryFromRAM64(FLASHCTL, (MAIN_BASE_ADDRESS + 24), &dataArray64[0]);           //64位无ECC写入，每次只能写入32位，所以先传递第一个数据的地址
    DL_FlashCTL_waitForCmdDone(FLASHCTL);                                                  //等待写入完成

		while (1) 
		{
        __BKPT(0);
    }
}
