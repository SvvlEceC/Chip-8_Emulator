#ifndef INSTRUCTIONS
#define INSTRUCTIONS
#include <cstdint>

struct Cpu;
struct chip8;

void arithmetic(Cpu& cpu, uint8_t x, uint8_t y, uint8_t n);
void condition(Cpu& cpu, chip8& chip, uint8_t x, uint8_t y, uint16_t nn, uint8_t s);
void system_ops(Cpu& cpu, chip8& chip, uint8_t x, uint8_t nn);

#endif