#include "timer_interrupt.h"

/* 全局定时器状态 */
static struct {
    uint32_t period_ms;     /* 定时器周期 */
    uint32_t elapsed_ms;    /* 已用时间 */
    bool is_running;        /* 是否运行 */
    timer_callback_t callback; /* 回调函数 */
} timer_state = {
    .period_ms = 1000,
    .elapsed_ms = 0,
    .is_running = false,
    .callback = NULL
};

/* 定时器基础计数 (假设1ms一次中断) */
static uint32_t tick_count = 0;

/**
 * @brief 定时器初始化
 * 初始化硬件定时器（周期为1ms）
 * 
 * 平台相关配置:
 * STM32F1:
 * - 使用 TIM2 (通用定时器)
 * - 系统时钟 72 MHz
 * - 预分频: 72 (得到 1 MHz)
 * - 自动重装值: 1000 (得到 1 kHz 中断频率，即 1ms)
 * 
 * AVR (ATmega328P):
 * - 使用 Timer1 (16-bit)
 * - 系统时钟 16 MHz
 * - 预分频: 16 (得到 1 MHz)
 * - OCR1A: 1000 (得到 1 kHz 中断频率)
 */
void timer_init(void)
{
    tick_count = 0;
    timer_state.elapsed_ms = 0;
    timer_state.is_running = false;
    timer_state.callback = NULL;
    timer_state.period_ms = 1000;
}

/**
 * @brief 配置定时器周期
 * @param period_ms 周期 (ms)
 */
void timer_set_period(uint32_t period_ms)
{
    if (period_ms == 0) {
        return;
    }
    timer_state.period_ms = period_ms;
}

/**
 * @brief 注册定时器中断回调函数
 * @param callback 回调函数指针
 */
void timer_set_callback(timer_callback_t callback)
{
    timer_state.callback = callback;
}

/**
 * @brief 启动定时器
 */
void timer_start(void)
{
    timer_state.is_running = true;
    tick_count = 0;
    timer_state.elapsed_ms = 0;
    
    /* 使能定时器和中断 */
    /* STM32: TIM_Cmd(TIM2, ENABLE); TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE); */
    /* AVR: TIMSK1 |= (1 << OCIE1A); */
}

/**
 * @brief 停止定时器
 */
void timer_stop(void)
{
    timer_state.is_running = false;
    
    /* 禁用定时器和中断 */
    /* STM32: TIM_Cmd(TIM2, DISABLE); */
    /* AVR: TIMSK1 &= ~(1 << OCIE1A); */
}

/**
 * @brief 检查定时器是否运行
 * @return true 如果定时器正在运行
 */
bool timer_is_running(void)
{
    return timer_state.is_running;
}

/**
 * @brief 获取已用时间
 * @return 已用时间 (ms)
 */
uint32_t timer_get_elapsed(void)
{
    return timer_state.elapsed_ms;
}

/**
 * @brief 重置时间计数器
 */
void timer_reset(void)
{
    timer_state.elapsed_ms = 0;
    tick_count = 0;
}

/**
 * @brief 定时器中断处理函数 (ISR)
 * 
 * 此函数由硬件定时器中断触发
 * 调用频率: 每 1ms 一次 (假设定时器配置为 1kHz)
 */
void timer_interrupt_handler(void)
{
    if (!timer_state.is_running) {
        return;
    }
    
    tick_count++;
    timer_state.elapsed_ms++;
    
    /* 检查是否达到周期 */
    if (timer_state.elapsed_ms >= timer_state.period_ms) {
        /* 执行回调函数 */
        if (timer_state.callback != NULL) {
            timer_state.callback();
        }
        
        /* 重置计数器 */
        timer_state.elapsed_ms = 0;
    }
}
