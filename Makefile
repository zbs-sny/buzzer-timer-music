CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -I.
LDFLAGS = -lm

SRC_HARDWARE = hardware/buzzer_control.c hardware/timer_interrupt.c
SRC_SOFTWARE = software/frequency_mapping.c software/music_generator.c

OBJ_HARDWARE = $(SRC_HARDWARE:.c=.o)
OBJ_SOFTWARE = $(SRC_SOFTWARE:.c=.o)

BUILD_DIR = build

TARGETS = $(BUILD_DIR)/main_demo $(BUILD_DIR)/test_buzzer $(BUILD_DIR)/test_music

.PHONY: all clean

all: $(BUILD_DIR) $(TARGETS)

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD_DIR)/main_demo: demo/main_demo.c $(OBJ_HARDWARE) $(OBJ_SOFTWARE)
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS)

$(BUILD_DIR)/test_buzzer: demo/test_buzzer.c $(OBJ_HARDWARE) $(OBJ_SOFTWARE)
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS)

$(BUILD_DIR)/test_music: demo/test_music.c $(OBJ_HARDWARE) $(OBJ_SOFTWARE)
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS)

clean:
	rm -rf $(BUILD_DIR)
	rm -f $(OBJ_HARDWARE) $(OBJ_SOFTWARE)

run_demo: $(BUILD_DIR)/main_demo
	./$(BUILD_DIR)/main_demo

run_buzzer: $(BUILD_DIR)/test_buzzer
	./$(BUILD_DIR)/test_buzzer

run_music: $(BUILD_DIR)/test_music
	./$(BUILD_DIR)/test_music
