#include <stdio.h>
#include <stdint.h>
#include "../hardware/buzzer_control.h"
#include "../hardware/timer_interrupt.h"
#include "../software/music_generator.h"
#include "../software/music_data.h"

static volatile uint16_t current_frequency = 0;

void timer_callback(void)
{
    current_frequency = music_update();
    
    if (current_frequency > 0) {
        buzzer_set_frequency(current_frequency);
        if (!buzzer_is_playing()) {
            buzzer_start();
        }
    } else {
        buzzer_stop();
    }
}

int main(void)
{
    buzzer_init();
    timer_init();
    music_generator_init();
    
    timer_set_period(1);
    timer_set_callback(timer_callback);
    timer_start();
    
    printf("Playing Twinkle Star\n");
    music_start(&twinkle_star);
    
    while (music_is_playing()) {
    }
    
    printf("Finished\n");
    timer_stop();
    buzzer_stop();
    
    return 0;
}
