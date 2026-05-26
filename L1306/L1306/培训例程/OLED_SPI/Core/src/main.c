#include "ti_msp_dl_config.h"
#include "oled_spi.h"


int main(void)
{
    SYSCFG_DL_init();
    OLED_Init();
    OLED_Clear();
    for(int i = 0;i< 128 ;i++){
        for(int j = 0;j<63;j++){
            OLED_DrawPoint(i,j,1);
        }
    }
    for(int i = 24;i< 100 ;i++){
        for(int j = 24;j<48;j++){
            OLED_DrawPoint(i,j,0);
        }
    }
    delay_cycles(320000000);
    while (1){
    
    }
}