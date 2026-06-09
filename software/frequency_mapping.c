#include "frequency_mapping.h"
#include <string.h>

const uint16_t frequency_table[128] = {
    8, 9, 9, 10, 10, 11, 12, 12, 13, 14, 15, 15,
    16, 17, 18, 19, 20, 21, 22, 23, 24, 26, 27, 29,
    30, 32, 33, 35, 36, 38, 40, 41, 43, 46, 48, 51,
    261, 277, 293, 310, 329, 349, 369, 392, 415, 440, 466, 493,
    523, 554, 587, 622, 659, 698, 784, 831, 880, 932, 987, 1046,
    1046, 1108, 1174, 1244, 1318, 1396, 1568, 1662, 1760, 1864, 1975, 2093,
    2093, 2217, 2349, 2489, 2637, 2793, 2959, 3135, 3322, 3520, 3729, 3951,
    4186, 4434, 4698, 4978, 5274, 5587, 5919, 6271, 6644, 7040, 7458, 7902,
    8372, 8869, 9397, 9956, 10548, 11175, 11839, 12543
};

static const char* note_names[12] = {
    "C", "C#", "D", "D#", "E", "F",
    "F#", "G", "G#", "A", "A#", "B"
};

uint16_t get_frequency_from_midi(uint8_t midi_note)
{
    if (midi_note >= 128) return 0;
    return frequency_table[midi_note];
}

uint8_t get_midi_from_frequency(uint16_t frequency)
{
    if (frequency == 0) return 255;
    uint8_t best_midi = 0;
    uint16_t best_diff = 32000;
    for (uint8_t i = 0; i < 128; i++) {
        uint16_t diff = frequency > frequency_table[i] ? 
                        frequency - frequency_table[i] : 
                        frequency_table[i] - frequency;
        if (diff < best_diff) {
            best_diff = diff;
            best_midi = i;
        }
        if (diff == 0) break;
    }
    return best_midi;
}

const char* get_note_name(uint8_t midi_note)
{
    if (midi_note >= 128 || midi_note == 255) return "REST";
    static char note_str[8];
    uint8_t octave = get_octave(midi_note);
    uint8_t semitone = midi_note % 12;
    snprintf(note_str, sizeof(note_str), "%s%d", note_names[semitone], octave);
    return note_str;
}

uint8_t get_octave(uint8_t midi_note)
{
    if (midi_note >= 128) return 0;
    return midi_note / 12;
}
