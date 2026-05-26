#include "ti_msp_dl_config.h"
#define CLK_HZ 32e+06 //????
void ws2812_delay(unsigned int time)
{
	while(time--);
}

//void delay_us(int nus)
//{		
//	delay_cycles(CLK_HZ / 1000000 * nus);
//}

//void delay_ms(int nms)
//{	 		  	  
//	delay_cycles(CLK_HZ / 1000 * nms);
//} 


//void write_bitH(){
//	DL_GPIO_setPins(LED_PORT, LED_RGB_PIN);
//	delay_cycles(25);//781.25ns
//	DL_GPIO_clearPins(LED_PORT, LED_RGB_PIN);
//	delay_cycles(10);//312.5ns
//}
//void write_bitL(){
//	DL_GPIO_setPins(LED_PORT, LED_RGB_PIN);
//	delay_cycles(10);//781.25ns
//	DL_GPIO_clearPins(LED_PORT, LED_RGB_PIN);
//	delay_cycles(25);//312.5ns
//}
//void write_reset(){
//	DL_GPIO_clearPins(LED_PORT, LED_RGB_PIN);
//	delay_us(400);//400us
//} 
//void ws2812_sendone(unsigned int data)
//{
//    unsigned char i=0;
//    unsigned char byte=0;
//    for(i=24 ; i>0 ; i--)
//    {
//        byte = ((data>>i) & 0x01);
//        if(byte == 1){
//            write_bitH();
//		}
//		else{
//			write_bitL(); 
//		}
//    }
//}
int main(void)
{
    SYSCFG_DL_init();                      //Sysconfig≥ı ºªØ
    DL_TimerG_startCounter(PWM_0_INST);
    ws2812_delay(1000);
    DL_TimerG_setCaptureCompareValue(PWM_0_INST, 5, DL_TIMER_CC_0_INDEX);
    DL_TimerG_stopCounter(PWM_0_INST);
    while (1) 
    { 
        //ws2812_sendone(0x00FF0000);

    }
}