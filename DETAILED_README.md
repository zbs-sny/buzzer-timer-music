# 蜂鸣器定时器与音乐生成器项目

## 📋 项目概述

本项目实现了一个基于**硬件定时器中断**的蜂鸣器控制系统与音乐生成器，包括：

- ✅ **蜂鸣器驱动**：PWM频率和音量控制
- ✅ **定时器中断**：1ms精度的周期中断
- ✅ **频率-音符映射**：十二平均律标准频率表
- ✅ **音乐生成引擎**：支持序列播放、暂停、循环
- ✅ **预设音乐**：包含多首经典旋律
- ✅ **物理声学关系**：探索频率与音高的关系

## 🏗️ 项目结构

```
buzzer-timer-music/
├── hardware/
│   ├── buzzer_control.h        # 蜂鸣器驱动接口
│   ├── buzzer_control.c        # 蜂鸣器驱动实现
│   ├── timer_interrupt.h       # 定时器中断接口
│   └── timer_interrupt.c       # 定时器中断实现
├── software/
│   ├── frequency_mapping.h     # 频率映射接口
│   ├── frequency_mapping.c     # 频率映射实现
│   ├── music_generator.h       # 音乐生成器接口
│   ├── music_generator.c       # 音乐生成器实现
│   └── music_data.h            # 预设音乐数据
├── demo/
│   ├── main_demo.c             # 主演示程序
│   ├── test_buzzer.c           # 蜂鸣器测试
│   └── test_music.c            # 音乐生成测试
├── Makefile                    # 编译配置
└── README.md                   # 本文件
```

## 🎵 核心原理

### 1. 十二平均律与频率关系

国际标准音A4 = 440 Hz，相邻半音频率比为 2^(1/12) ≈ 1.0595

**频率计算公式**：
```
f(n) = 440 × 2^((n-69)/12)
```
其中 n 是MIDI编号（0-127），69对应A4

### 2. 音符与频率表

| 音符 | MIDI编号 | 频率(Hz) |
|------|---------|---------|
| C4   | 48      | 261     |
| D4   | 50      | 293     |
| E4   | 52      | 329     |
| F4   | 53      | 349     |
| G4   | 55      | 392     |
| A4   | 57      | 440     |
| B4   | 59      | 494     |
| C5   | 60      | 523     |

### 3. 定时器中断机制

- **中断周期**：1ms（可配置）
- **用途**：驱动音乐生成器更新
- **调用频率**：音乐更新（1ms一次）
- **回调机制**：用户注册的回调函数

### 4. PWM蜂鸣器控制

- **频率范围**：20 Hz ~ 20 kHz
- **音量控制**：0-100%（通过PWM占空比）
- **驱动方式**：PWM/GPIO输出

## 📦 模块接口

### 蜂鸣器驱动（buzzer_control.h）

```c
void buzzer_init(void);                    // 初始化
void buzzer_set_frequency(uint16_t freq);  // 设置频率 (Hz)
void buzzer_set_volume(uint8_t volume);    // 设置音量 (0-100%)
void buzzer_start(void);                   // 启动蜂鸣器
void buzzer_stop(void);                    // 停止蜂鸣器
void buzzer_play_tone(uint16_t freq, uint16_t ms); // 播放音调
bool buzzer_is_playing(void);              // 获取状态
```

### 定时器中断（timer_interrupt.h）

```c
void timer_init(void);                     // 初始化
void timer_set_period(uint32_t ms);        // 设置周期 (ms)
void timer_set_callback(timer_callback_t); // 注册回调
void timer_start(void);                    // 启动
void timer_stop(void);                     // 停止
void timer_interrupt_handler(void);        // ISR处理函数
```

### 频率映射（frequency_mapping.h）

```c
uint16_t get_frequency_from_midi(uint8_t note);     // MIDI -> 频率
uint8_t get_midi_from_frequency(uint16_t freq);     // 频率 -> MIDI
const char* get_note_name(uint8_t note);            // MIDI -> 音符名
uint8_t get_octave(uint8_t note);                   // 获取八度数
```

### 音乐生成器（music_generator.h）

```c
void music_generator_init(void);
void music_start(const music_sequence_t *seq);
void music_stop(void);
void music_pause(void);
void music_resume(void);
bool music_is_playing(void);
uint16_t music_update(void);               // 更新 (在ISR中调用)
uint8_t music_get_progress(void);          // 获取进度 (0-100%)
```

## 🎼 预设音乐

项目包含以下预设旋律（music_data.h）：

1. **twinkle_star** - 小星星
2. **two_tigers** - 两只老虎
3. **happy_birthday** - 生日快乐
4. **ode_to_joy** - 欢乐颂
5. **scale_up** - 上升音阶 (C4→C5)
6. **scale_down** - 下降音阶 (C5→C4)
7. **single_note_loop** - 单音循环测试

## 🛠️ 编译与运行

### 编译所有程序

```bash
make
```

### 运行演示程序

```bash
make run_demo    # 主演示
make run_buzzer  # 蜂鸣器测试
make run_music   # 音乐生成测试
```

### 清理编译文件

```bash
make clean
```

## 📝 使用示例

### 基本蜂鸣器使用

```c
#include "hardware/buzzer_control.h"

int main(void) {
    buzzer_init();
    
    // 播放440Hz (A4) 的声音，持续1秒
    buzzer_play_tone(440, 1000);
    
    buzzer_stop();
    return 0;
}
```

### 音乐播放

```c
#include "hardware/timer_interrupt.h"
#include "software/music_generator.h"
#include "software/music_data.h"

void timer_isr(void) {
    uint16_t freq = music_update();
    if (freq > 0) {
        buzzer_set_frequency(freq);
        buzzer_start();
    } else {
        buzzer_stop();
    }
}

int main(void) {
    buzzer_init();
    timer_init();
    music_generator_init();
    
    timer_set_callback(timer_isr);
    timer_set_period(1);  // 1ms中断
    timer_start();
    
    music_start(&twinkle_star);  // 播放小星星
    
    while (music_is_playing()) {
        // 等待播放完成
    }
    
    timer_stop();
    return 0;
}
```

### 自定义音乐

```c
// 定义音符序列 (中央C为C4)
static const music_note_item_t my_song[] = {
    {NOTE_C4, 500},   // C4 持续 500ms
    {NOTE_D4, 500},   // D4 持续 500ms
    {NOTE_E4, 1000},  // E4 持续 1000ms
    {255, 500},       // 休止符 (255 = 无声)
};

static const music_sequence_t my_sequence = {
    .notes = my_song,
    .note_count = sizeof(my_song) / sizeof(music_note_item_t),
    .tempo = 120,
    .loop = false
};

// 播放
music_start(&my_sequence);
```

## 📊 频率与音高的物理关系

### 十二平均律的特点

1. **对数关系**：人耳感知音高是对数关系，不是线性的
2. **频率倍增**：每升高一个八度，频率翻倍
3. **半音间隔**：每个半音频率增加 2^(1/12) 倍
4. **可感知范围**：人类可听频率范围约 20Hz ~ 20kHz

### 应用的物理原理

- **共鸣频率**：蜂鸣器有固有共鸣频率，某些频率会使声音更大
- **频率响应**：不同频率的声学特性不同
- **谐波关系**：音乐的和谐与谐波比例有关

## 🔧 硬件配置

### STM32F1 配置示例

```c
/* 使用 TIM2 作为定时器 */
/* 使用 TIM1_CH1 (PA8) 作为PWM输出 */
/* 系统时钟 72MHz */
/* 预分频: 72 (得到 1MHz) */
/* 自动重装值: 1000 (得到 1kHz, 即 1ms中断) */
```

### AVR (ATmega328P) 配置示例

```c
/* 使用 Timer1 (16-bit) */
/* 使用 OC1A (PB1) 作为PWM输出 */
/* 系统时钟 16MHz */
/* 预分频: 16 (得到 1MHz) */
/* OCR1A: 1000 (得到 1ms中断) */
```

## 📚 技术文档

### 音符编码系统（MIDI）

- MIDI编号 0-127 代表不同的音符
- 中央C (C4) = MIDI 60
- 每12个编号跨越一个八度
- 编号69对应标准音A4 = 440Hz

### 节奏标记

```c
NOTE_WHOLE = 4000ms      // 全音符 (4拍)
NOTE_HALF = 2000ms       // 二分音符 (2拍)
NOTE_QUARTER = 1000ms    // 四分音符 (1拍)
NOTE_EIGHTH = 500ms      // 八分音符 (0.5拍)
NOTE_SIXTEENTH = 250ms   // 十六分音符 (0.25拍)
```

## 🐛 调试建议

1. **验证定时器**：检查ISR被正确调用
2. **频率测试**：使用示波器验证PWM频率
3. **音量测试**：调整占空比验证音量变化
4. **音乐播放**：检查音符序列是否正确加载
5. **内存使用**：监控预定义音乐的内存占用

## 📄 许可证

MIT License

## 👤 作者

蜂鸣器定时器与音乐生成器项目

## 🤝 贡献指南

欢迎提交Issue和Pull Request！

---

**最后更新**: 2026-06-09  
**项目版本**: 1.0.0
