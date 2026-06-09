#ifndef MUSIC_GENERATOR_H
#define MUSIC_GENERATOR_H

#include <stdint.h>
#include <stdbool.h>
#include "frequency_mapping.h"

typedef enum {
    NOTE_WHOLE = 4000,
    NOTE_HALF = 2000,
    NOTE_QUARTER = 1000,
    NOTE_EIGHTH = 500,
    NOTE_SIXTEENTH = 250,
} note_duration_t;

typedef struct {
    uint8_t midi_note;
    uint16_t duration_ms;
} music_note_item_t;

typedef struct {
    const music_note_item_t *notes;
    uint16_t note_count;
    uint8_t tempo;
    bool loop;
} music_sequence_t;

typedef struct {
    const music_sequence_t *sequence;
    uint16_t current_index;
    uint32_t current_time;
    bool is_playing;
    bool paused;
} music_generator_state_t;

void music_generator_init(void);
void music_start(const music_sequence_t *sequence);
void music_stop(void);
void music_pause(void);
void music_resume(void);
bool music_is_playing(void);
uint8_t music_get_progress(void);
uint8_t music_get_current_note(void);
uint16_t music_update(void);
void music_set_tempo(uint8_t tempo);

#endif
