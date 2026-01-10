#ifndef INSTRUCTIONS
#define INSTRUCTIONS
#include <cstdint>

struct cpu;
struct chip8;

void arithmetic(cpu& cpu, uint8_t x, uint8_t y, uint8_t n);


#endif