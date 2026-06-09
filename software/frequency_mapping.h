#ifndef FREQUENCY_MAPPING_H
#define FREQUENCY_MAPPING_H

#include <stdint.h>

typedef enum {
    NOTE_C4 = 48, NOTE_D4 = 50, NOTE_E4 = 52, NOTE_F4 = 53,
    NOTE_G4 = 55, NOTE_A4 = 57, NOTE_B4 = 59,
    NOTE_C5 = 60, NOTE_D5 = 62, NOTE_E5 = 64, NOTE_F5 = 65,
    NOTE_G5 = 67, NOTE_A5 = 69, NOTE_B5 = 71,
    NOTE_REST = 255
} music_note_t;

uint16_t get_frequency_from_midi(uint8_t midi_note);
uint8_t get_midi_from_frequency(uint16_t frequency);
const char* get_note_name(uint8_t midi_note);
uint8_t get_octave(uint8_t midi_note);

extern const uint16_t frequency_table[128];

#endif
