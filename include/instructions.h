#ifndef INSTRUCTIONS
#define INSTRUCTIONS
#include <cstdint>

struct cpu;
struct chip8;

void arithmetic(cpu& cpu, uint8_t x, uint8_t y, uint8_t n);
void condition(cpu& cpu, chip8& chip, uint8_t x, uint8_t y, uint16_t nn, uint8_t s);

#endif