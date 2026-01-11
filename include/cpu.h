#ifndef CPU
#define CPU
#include <cstdint>

struct chip8;

class cpu{
public:
    uint16_t I;
    uint16_t pc;
    uint8_t sp;
    uint8_t V[16];
    cpu();
    ~cpu();

    uint16_t fetch(uint8_t* ram);
    void decode_and_execute(chip8& chip, uint16_t opcode);
};
#endif