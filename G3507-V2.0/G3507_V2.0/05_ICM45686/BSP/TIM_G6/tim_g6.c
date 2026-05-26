#include "TIM_G6/tim_g6.h"

/*
 * Timer clock configuration to be sourced by BUSCLK /  (80000000 Hz)
 * timerClkFreq = (timerClkSrc / (timerClkDivRatio * (timerClkPrescale + 1)))
 *   80000000 Hz = 80000000 Hz / (1 * (0 + 1))
 */
static const DL_TimerG_ClockConfig gTIMER_6ClockConfig = {
    .clockSel = DL_TIMER_CLOCK_BUSCLK,
    .divideRatio = DL_TIMER_CLOCK_DIVIDE_1,
    .prescale = 0U,
};

/*
 * Timer load value (where the counter starts from) is calculated as (timerPeriod * timerClockFreq) - 1
 * TIMER_0_INST_LOAD_VALUE = (100us * 80000000 Hz) - 1
 */
static const DL_TimerG_TimerConfig gTIMER_6TimerConfig = {
    .period = TIMER_6_INST_LOAD_VALUE,
    
    .timerMode = DL_TIMER_TIMER_MODE_PERIODIC_UP,
    .startTimer = DL_TIMER_STOP,
};

void tim_g6_init(void)
{
    /* 复位TIMER_6_INST定时器模块 */
    DL_TimerG_reset(TIMER_6_INST);
    /* TIMER_6_INST定时器上电使能 */
    DL_TimerG_enablePower(TIMER_6_INST);
    /* 设置定时器的时钟配置 */
    DL_TimerG_setClockConfig(TIMER_6_INST,
                             (DL_TimerG_ClockConfig *)&gTIMER_6ClockConfig);
    /* 初始化定时器模式 */
    DL_TimerG_initTimerMode(TIMER_6_INST,
                            (DL_TimerG_TimerConfig *)&gTIMER_6TimerConfig);
    /* 使能TIMER_6_INST定时器中断 */
    DL_TimerG_enableInterrupt(TIMER_6_INST, DL_TIMERG_INTERRUPT_ZERO_EVENT);
    /* 定时器TIMER_6_INST时钟使能 */
    DL_TimerG_enableClock(TIMER_6_INST);
    /* 定时器TIMER_6_INST中断使能 */
    NVIC_EnableIRQ(TIMER_6_INST_INT_IRQN);

    /* 启动定时器TIMER_6_INST */
    DL_TimerG_startCounter(TIMER_6_INST);
}

uint32_t nowtime = 0;

/* 中断服务函数 */
void TIMG6_IRQHandler(void)
{
    switch (DL_TimerG_getPendingInterrupt(TIMER_6_INST))
    {
    case GPTIMER_CPU_INT_IIDX_STAT_Z:
        nowtime++;
        break;
    default:
        break;
    }
}
