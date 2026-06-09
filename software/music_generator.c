#include "music_generator.h"
#include <string.h>

static music_generator_state_t music_state = {
    .sequence = NULL,
    .current_index = 0,
    .current_time = 0,
    .is_playing = false,
    .paused = false
};

static uint8_t current_tempo = 120;

void music_generator_init(void)
{
    memset(&music_state, 0, sizeof(music_generator_state_t));
    current_tempo = 120;
}

void music_start(const music_sequence_t *sequence)
{
    if (sequence == NULL || sequence->notes == NULL) {
        return;
    }
    music_state.sequence = sequence;
    music_state.current_index = 0;
    music_state.current_time = 0;
    music_state.is_playing = true;
    music_state.paused = false;
    if (sequence->tempo > 0) {
        current_tempo = sequence->tempo;
    }
}

void music_stop(void)
{
    music_state.is_playing = false;
    music_state.paused = false;
    music_state.current_index = 0;
    music_state.current_time = 0;
}

void music_pause(void)
{
    if (music_state.is_playing) {
        music_state.paused = true;
    }
}

void music_resume(void)
{
    if (music_state.is_playing) {
        music_state.paused = false;
    }
}

bool music_is_playing(void)
{
    return music_state.is_playing && !music_state.paused;
}

uint8_t music_get_progress(void)
{
    if (music_state.sequence == NULL || music_state.sequence->note_count == 0) {
        return 0;
    }
    return (uint8_t)((music_state.current_index * 100) / 
                     music_state.sequence->note_count);
}

uint8_t music_get_current_note(void)
{
    if (!music_state.is_playing || music_state.sequence == NULL) {
        return 255;
    }
    if (music_state.current_index >= music_state.sequence->note_count) {
        return 255;
    }
    return music_state.sequence->notes[music_state.current_index].midi_note;
}

void music_set_tempo(uint8_t tempo)
{
    if (tempo > 0) {
        current_tempo = tempo;
    }
}

uint16_t music_update(void)
{
    if (!music_state.is_playing || music_state.paused || 
        music_state.sequence == NULL) {
        return 0;
    }
    if (music_state.current_index >= music_state.sequence->note_count) {
        if (music_state.sequence->loop) {
            music_state.current_index = 0;
            music_state.current_time = 0;
        } else {
            music_state.is_playing = false;
            return 0;
        }
    }
    const music_note_item_t *current_note = 
        &music_state.sequence->notes[music_state.current_index];
    music_state.current_time += 1;
    if (music_state.current_time >= current_note->duration_ms) {
        music_state.current_index++;
        music_state.current_time = 0;
        if (current_note->duration_ms == 0) {
            return music_update();
        }
    }
    uint8_t midi_note = current_note->midi_note;
    if (midi_note == 255) {
        return 0;
    }
    return get_frequency_from_midi(midi_note);
}
