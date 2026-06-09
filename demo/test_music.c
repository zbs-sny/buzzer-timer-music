#include <stdio.h>
#include <stdint.h>
#include "../hardware/buzzer_control.h"
#include "../hardware/timer_interrupt.h"
#include "../software/music_generator.h"
#include "../software/frequency_mapping.h"
#include "../software/music_data.h"

volatile uint16_t test_frequency = 0;

void test_timer_callback(void)
{
    test_frequency = music_update();
    
    if (test_frequency > 0) {
        buzzer_set_frequency(test_frequency);
        buzzer_start();
    } else {
        buzzer_stop();
    }
}

int main(void)
{
    printf("=== Music Generation Test ===\n\n");
    
    buzzer_init();
    timer_init();
    music_generator_init();
    
    printf("Test 1: Frequency Mapping\n");
    for (int note = 48; note <= 72; note += 4) {
        uint16_t freq = get_frequency_from_midi(note);
        printf("MIDI %d -> %d Hz\n", note, freq);
    }
    
    printf("\nTest 2: Scale Playback\n");
    printf("Playing ascending scale...\n");
    
    timer_set_callback(test_timer_callback);
    timer_set_period(1);
    timer_start();
    
    music_start(&scale_up);
    
    for (int i = 0; i < 5000; i++) {
        timer_interrupt_handler();
        if (!music_is_playing()) break;
    }
    
    printf("Scale up completed\n");
    
    printf("\nTest 3: Music Playback\n");
    printf("Playing Twinkle Star...\n");
    
    music_start(&twinkle_star);
    
    int elapsed = 0;
    while (music_is_playing() && elapsed < 20000) {
        timer_interrupt_handler();
        elapsed++;
    }
    
    printf("Twinkle Star completed\n");
    
    printf("\nTest 4: Progress Tracking\n");
    music_start(&two_tigers);
    
    for (int i = 0; i < 15000; i++) {
        timer_interrupt_handler();
        if (i % 2000 == 0) {
            printf("Progress: %d%%\n", music_get_progress());
        }
        if (!music_is_playing()) break;
    }
    
    timer_stop();
    buzzer_stop();
    
    printf("\n=== All Music Tests Completed ===\n");
    
    return 0;
}
