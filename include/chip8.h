#ifndef CHIP8
#define CHIP8
#include <stdint.h>
#include <string>
#include "timer.h"
#include "Cpu.h"

#define FONT_START_ADDRESS 0x50

class chip8
{
private:
public:
    uint8_t ram[4096];
    uint16_t stack[16];
    uint8_t keypad[16];
    uint8_t display[64 * 32];
    bool update_display;
    Cpu cpu;
    timer delay_timer;
    timer sound_timer;
    chip8();
    ~chip8();

    uint8_t get_delay_timer();
    uint8_t get_sound_timer();

    void load_rom(std::string path);
};
#endif