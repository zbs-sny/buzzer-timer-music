#ifndef TIMER_INTERRUPT_H
#define TIMER_INTERRUPT_H

#include <stdint.h>
#include <stdbool.h>

/* Timer interrupt callback function type */
typedef void (*timer_callback_t)(void);

/* Timer configuration structure */
typedef struct {
    uint32_t period_ms;     /* 定时器周期 (ms) */
    timer_callback_t callback; /* 中断回调函数 */
} timer_config_t;

/* 定时器初始化 */
void timer_init(void);

/* 配置定时器周期 */
void timer_set_period(uint32_t period_ms);

/* 注册中断回调函数 */
void timer_set_callback(timer_callback_t callback);

/* 启动定时器 */
void timer_start(void);

/* 停止定时器 */
void timer_stop(void);

/* 检查定时器是否运行 */
bool timer_is_running(void);

/* 获取已用时间 (ms) */
uint32_t timer_get_elapsed(void);

/* 重置已用时间计数器 */
void timer_reset(void);

/* 定时器中断处理函数（ISR） */
void timer_interrupt_handler(void);

#endif /* TIMER_INTERRUPT_H */
