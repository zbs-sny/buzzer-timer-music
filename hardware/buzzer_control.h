#ifndef BUZZER_CONTROL_H
#define BUZZER_CONTROL_H

#include <stdint.h>
#include <stdbool.h>

/* Buzzer control modes */
typedef enum {
    BUZZER_MODE_OFF,        /* 蜂鸣器关闭 */
    BUZZER_MODE_CONTINUOUS, /* 连续发音 */
    BUZZER_MODE_PWM         /* PWM脉宽调制 */
} buzzer_mode_t;

/* Buzzer configuration structure */
typedef struct {
    uint16_t frequency;     /* 频率 (Hz) */
    uint8_t volume;         /* 音量 (0-100%) */
    uint16_t duration_ms;   /* 持续时间 (ms) */
    buzzer_mode_t mode;     /* 工作模式 */
} buzzer_config_t;

/* 蜂鸣器初始化 */
void buzzer_init(void);

/* 设置蜂鸣器频率 */
void buzzer_set_frequency(uint16_t frequency);

/* 设置蜂鸣器音量 (0-100%) */
void buzzer_set_volume(uint8_t volume);

/* 启动蜂鸣器 */
void buzzer_start(void);

/* 停止蜂鸣器 */
void buzzer_stop(void);

/* 播放音调 (频率 + 时长) */
void buzzer_play_tone(uint16_t frequency, uint16_t duration_ms);

/* 获取当前状态 */
bool buzzer_is_playing(void);

/* 配置蜂鸣器 */
void buzzer_configure(const buzzer_config_t *config);

#endif /* BUZZER_CONTROL_H */
