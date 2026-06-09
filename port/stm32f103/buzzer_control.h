#ifndef STM32F103_BUZZER_H
#define STM32F103_BUZZER_H

#include "stm32f1xx_hal.h"

/* Buzzer Configuration for STM32F103 */
#define BUZZER_PORT             GPIOA
#define BUZZER_PIN              GPIO_PIN_8
#define BUZZER_TIMER            TIM1
#define BUZZER_TIMER_CHANNEL    TIM_CHANNEL_1

/* Function Prototypes */
void buzzer_init(void);
void buzzer_set_frequency(uint16_t freq);
void buzzer_set_volume(uint8_t volume);
void buzzer_start(void);
void buzzer_stop(void);
void buzzer_play_tone(uint16_t freq, uint16_t ms);
bool buzzer_is_playing(void);

#endif
