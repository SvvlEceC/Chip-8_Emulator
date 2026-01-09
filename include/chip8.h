#ifndef CHIP8
#define CHIP8
#include <stdint.h>
#include "timer.h"
#include "cpu.h"

class chip8
{
private:
    uint8_t ram[4096];
    uint16_t stack[16];
    uint8_t keypad[16];
    bool display[64 * 32];
    cpu cpu;
    timer delay_timer;
    timer sound_timer;
public:
    chip8(/* args */);
    ~chip8();

    uint8_t get_delay_timer();
    uint8_t get_sound_timer();
};
#endif