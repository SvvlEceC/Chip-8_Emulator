#ifndef CPU
#define CPU
#include <cstdint>

struct chip8;

class cpu
{
private:
    uint16_t I;
    uint16_t pc;
    uint8_t sp;
    uint8_t V[16];
public:
    cpu(/* args */);
    ~cpu();

    uint16_t fetch(uint8_t* ram){
        if(pc >= 4096) return -1;
        uint16_t opcode = (ram[pc] << 8) | ram[pc + 1];
        pc += 2;

        return opcode;
    }

    void decode_and_execute(chip8& chip, uint16_t opcode){
        uint16_t x((opcode & 0x0F00) >> 8);
        uint16_t y((opcode & 0x00F0) >> 4);
        uint16_t n(opcode & 0x000F);
        uint16_t nn(opcode & 0x00FF);
        uint16_t nnn(opcode & 0x0FFF);

        switch (x)
        {
        case 8:
            
            break;
        default:
            break;
        }
    }
};
#endif