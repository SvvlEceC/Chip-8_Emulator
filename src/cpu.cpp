#include <random>
#include <time.h>
#include "../include/cpu.h"
#include "../include/instructions.h"

uint16_t cpu::fetch(uint8_t* ram){
    if(pc >= 4096) return -1;
    uint16_t opcode = (ram[pc] << 8) | ram[pc + 1];
    pc += 2;

    return opcode;
}

void cpu::decode_and_execute(chip8& chip, uint16_t opcode){
    uint16_t x((opcode & 0x0F00) >> 8);
    uint16_t y((opcode & 0x00F0) >> 4);
    uint16_t n(opcode & 0x000F);
    uint16_t nn(opcode & 0x00FF);
    uint16_t nnn(opcode & 0x0FFF);
    uint16_t s((opcode & 0xF000) >> 12);

    switch (s){
        case 0:
        break;

        case 1:
        pc = nnn;
        break;

        case 2:
        break;

        case 3:
        condition(*this, chip, x, y, nn, s);
        break;
        
        case 4:
        condition(*this, chip, x, y, nn, s);
        break;
        
        case 5:
        condition(*this, chip, x, y, nn, s);
        break;

        case 6:
        V[x] = nn;
        break;

        case 7:
        V[x] += nn;
        break;
        
        case 8:
        arithmetic(*this, x, y, n);
        break;

        case 9:
        condition(*this, chip, x, y, nn, s);           
        break;

        case 0x0A:
        I = nnn;
        break;

        case 0x0B:
        pc = nnn;
        break;

        case 0x0C:
        srand(time(0));
        V[x] = nn & (rand() % 255);
        break;

        case 0x0D:
        break;

        case 0x0E:
        condition(*this, chip, x, y, nn, s);           
        break;        

        case 0x0F:
        break;

        default:
        break;
    }
}