#ifndef MUSIC_DATA_H
#define MUSIC_DATA_H

#include "music_generator.h"
#include "frequency_mapping.h"

/* 小星星 (Twinkle Twinkle Little Star) */
static const music_note_item_t twinkle_star_notes[] = {
    {NOTE_C4, 500}, {NOTE_C4, 500}, {NOTE_G4, 500}, {NOTE_G4, 500},
    {NOTE_A4, 500}, {NOTE_A4, 500}, {NOTE_G4, 1000},
    {NOTE_F4, 500}, {NOTE_F4, 500}, {NOTE_E4, 500}, {NOTE_E4, 500},
    {NOTE_D4, 500}, {NOTE_D4, 500}, {NOTE_C4, 1000},
};

static const music_sequence_t twinkle_star = {
    .notes = twinkle_star_notes,
    .note_count = sizeof(twinkle_star_notes) / sizeof(music_note_item_t),
    .tempo = 120,
    .loop = false
};

/* 两只老虎 (Two Tigers) */
static const music_note_item_t two_tigers_notes[] = {
    {NOTE_C4, 500}, {NOTE_D4, 500}, {NOTE_E4, 500}, {NOTE_C4, 500},
    {NOTE_C4, 500}, {NOTE_D4, 500}, {NOTE_E4, 500}, {NOTE_C4, 500},
    {NOTE_E4, 500}, {NOTE_F4, 500}, {NOTE_G4, 1000},
    {NOTE_E4, 500}, {NOTE_F4, 500}, {NOTE_G4, 1000},
};

static const music_sequence_t two_tigers = {
    .notes = two_tigers_notes,
    .note_count = sizeof(two_tigers_notes) / sizeof(music_note_item_t),
    .tempo = 120,
    .loop = false
};

/* 生日快乐 (Happy Birthday) */
static const music_note_item_t happy_birthday_notes[] = {
    {NOTE_C4, 500}, {NOTE_C4, 500}, {NOTE_D4, 1000},
    {NOTE_C4, 1000}, {NOTE_F4, 1000}, {NOTE_E4, 2000},
    {NOTE_C4, 500}, {NOTE_C4, 500}, {NOTE_D4, 1000},
    {NOTE_C4, 1000}, {NOTE_G4, 1000}, {NOTE_F4, 2000},
};

static const music_sequence_t happy_birthday = {
    .notes = happy_birthday_notes,
    .note_count = sizeof(happy_birthday_notes) / sizeof(music_note_item_t),
    .tempo = 120,
    .loop = false
};

/* 欢乐颂 (Ode to Joy) */
static const music_note_item_t ode_to_joy_notes[] = {
    {NOTE_E4, 500}, {NOTE_E4, 500}, {NOTE_F4, 500}, {NOTE_G4, 500},
    {NOTE_G4, 500}, {NOTE_F4, 500}, {NOTE_E4, 500}, {NOTE_D4, 500},
    {NOTE_C4, 500}, {NOTE_C4, 500}, {NOTE_D4, 500}, {NOTE_E4, 500},
    {NOTE_E4, 750}, {NOTE_D4, 250}, {NOTE_D4, 1000},
};

static const music_sequence_t ode_to_joy = {
    .notes = ode_to_joy_notes,
    .note_count = sizeof(ode_to_joy_notes) / sizeof(music_note_item_t),
    .tempo = 120,
    .loop = false
};

/* 一闪一闪亮晶晶 (Twinkle Twinkle Little Star - Full Version) */
static const music_note_item_t shine_bright_notes[] = {
    /* 第一段：一闪一闪亮晶晶 */
    {NOTE_C4, 500}, {NOTE_C4, 500}, {NOTE_G4, 500}, {NOTE_G4, 500},
    {NOTE_A4, 500}, {NOTE_A4, 500}, {NOTE_G4, 1000},
    {NOTE_F4, 500}, {NOTE_F4, 500}, {NOTE_E4, 500}, {NOTE_E4, 500},
    {NOTE_D4, 500}, {NOTE_D4, 500}, {NOTE_C4, 1000},
    /* 第二段：天上的星星 */
    {255, 500},
    {NOTE_G4, 500}, {NOTE_G4, 500}, {NOTE_G4, 500}, {NOTE_G4, 500},
    {NOTE_A4, 500}, {NOTE_A4, 500}, {NOTE_G4, 1000},
    {NOTE_F4, 500}, {NOTE_F4, 500}, {NOTE_E4, 500}, {NOTE_E4, 500},
    {NOTE_D4, 500}, {NOTE_D4, 500}, {NOTE_C4, 1000},
};

static const music_sequence_t shine_bright = {
    .notes = shine_bright_notes,
    .note_count = sizeof(shine_bright_notes) / sizeof(music_note_item_t),
    .tempo = 120,
    .loop = false
};

/* 生日快乐歌 (Happy Birthday Song - Extended Version) */
static const music_note_item_t happy_birthday_song_notes[] = {
    /* 第一句：祝你生日快乐 */
    {NOTE_C4, 400}, {NOTE_C4, 400}, {NOTE_D4, 800},
    {NOTE_C4, 800}, {NOTE_F4, 800}, {NOTE_E4, 1600},
    /* 第二句：祝你生日快乐 */
    {255, 400},
    {NOTE_C4, 400}, {NOTE_C4, 400}, {NOTE_D4, 800},
    {NOTE_C4, 800}, {NOTE_G4, 800}, {NOTE_F4, 1600},
    /* 第三句：祝你生日快乐 */
    {255, 400},
    {NOTE_C5, 400}, {NOTE_A4, 400}, {NOTE_F4, 400},
    {NOTE_E4, 400}, {NOTE_D4, 400}, {NOTE_B4, 800},
    {NOTE_B4, 400}, {NOTE_A4, 400}, {NOTE_F4, 400},
    {NOTE_G4, 400}, {NOTE_F4, 800},
};

static const music_sequence_t happy_birthday_song = {
    .notes = happy_birthday_song_notes,
    .note_count = sizeof(happy_birthday_song_notes) / sizeof(music_note_item_t),
    .tempo = 120,
    .loop = false
};

/* 上升音阶 (Scale Up: C4 to C5) */
static const music_note_item_t scale_up_notes[] = {
    {NOTE_C4, 500}, {NOTE_D4, 500}, {NOTE_E4, 500}, {NOTE_F4, 500},
    {NOTE_G4, 500}, {NOTE_A4, 500}, {NOTE_B4, 500}, {NOTE_C5, 500},
};

static const music_sequence_t scale_up = {
    .notes = scale_up_notes,
    .note_count = sizeof(scale_up_notes) / sizeof(music_note_item_t),
    .tempo = 120,
    .loop = false
};

/* 下降音阶 (Scale Down: C5 to C4) */
static const music_note_item_t scale_down_notes[] = {
    {NOTE_C5, 500}, {NOTE_B4, 500}, {NOTE_A4, 500}, {NOTE_G4, 500},
    {NOTE_F4, 500}, {NOTE_E4, 500}, {NOTE_D4, 500}, {NOTE_C4, 500},
};

static const music_sequence_t scale_down = {
    .notes = scale_down_notes,
    .note_count = sizeof(scale_down_notes) / sizeof(music_note_item_t),
    .tempo = 120,
    .loop = false
};

/* 单音循环测试 */
static const music_note_item_t single_note_test[] = {
    {NOTE_A4, 500}, {255, 500},
};

static const music_sequence_t single_note_loop = {
    .notes = single_note_test,
    .note_count = sizeof(single_note_test) / sizeof(music_note_item_t),
    .tempo = 120,
    .loop = true
};

#endif
