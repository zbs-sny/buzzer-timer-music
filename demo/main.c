#include <stdio.h>
#include "../hardware/buzzer_control.h"
#include "../hardware/timer_interrupt.h"
#include "../software/music_generator.h"
#include "../software/music_data.h"

/* 定时器中断回调函数 */
static void timer_callback(void)
{
    /* 获取当前音频频率并更新蜂鸣器 */
    uint16_t freq = music_update();
    
    if (freq > 0) {
        buzzer_set_frequency(freq);
        buzzer_start();
    } else {
        buzzer_stop();
    }
}

/* 初始化系统 */
static void system_init(void)
{
    printf("System Initializing...\n");
    
    buzzer_init();
    printf("Buzzer initialized\n");
    
    timer_init();
    printf("Timer initialized\n");
    
    timer_set_period(10); /* 10ms timer */
    timer_set_callback(timer_callback);
    printf("Timer callback registered\n");
    
    music_generator_init();
    printf("Music generator initialized\n");
}

/* 演示蜂鸣器基本功能 */
static void demo_buzzer_beep(void)
{
    printf("\n=== Buzzer Beep Test ===\n");
    
    printf("Beep 1: 1000 Hz, 500ms\n");
    buzzer_play_tone(1000, 500);
    
    printf("Beep 2: 2000 Hz, 500ms\n");
    buzzer_play_tone(2000, 500);
    
    printf("Beep 3: 500 Hz, 500ms\n");
    buzzer_play_tone(500, 500);
}

/* 演示音阶 */
static void demo_scale(void)
{
    printf("\n=== Scale Test (C4 to C5) ===\n");
    
    music_start(&scale_up);
    timer_start();
    
    printf("Playing ascending scale...\n");
    
    /* 模拟等待 (实际应用中应使用真实的时间管理) */
    for (int i = 0; i < 100; i++) {
        timer_interrupt_handler();
        if (!music_is_playing()) break;
    }
    
    timer_stop();
}

/* 演示音乐播放 */
static void demo_music(void)
{
    printf("\n=== Music Playback Test ===\n");
    printf("Playing: Twinkle Star\n");
    
    music_start(&twinkle_star);
    timer_start();
    
    /* 模拟音乐播放 */
    uint32_t elapsed = 0;
    while (music_is_playing() && elapsed < 20000) {
        timer_interrupt_handler();
        elapsed += 10;
        
        uint8_t progress = music_get_progress();
        uint8_t current = music_get_current_note();
        
        if (progress % 25 == 0) {
            printf("Progress: %d%%, Current Note: %d\n", progress, current);
        }
    }
    
    timer_stop();
    printf("Playback complete!\n");
}

/* 主函数 */
int main(void)
{
    printf("========================================\n");
    printf("  Buzzer Timer & Music Generator Test\n");
    printf("========================================\n\n");
    
    system_init();
    
    /* 运行演示 */
    demo_buzzer_beep();
    demo_scale();
    demo_music();
    
    printf("\n========================================\n");
    printf("  All tests completed!\n");
    printf("========================================\n");
    
    return 0;
}
