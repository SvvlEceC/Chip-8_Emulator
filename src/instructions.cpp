#include "../include/instructions.h"
#include "../include/cpu.h"

void arithmetic(cpu& cpu, uint8_t x, uint8_t y, uint8_t n){
    switch(n){
        case 0:
        cpu.V[x] = cpu.V[y];
        break;

        case 1:
        cpu.V[x] |= cpu.V[y];
        break;

        case 2:
        cpu.V[x] &= cpu.V[y];
        break;

        case 3:
        cpu.V[x] ^= cpu.V[y];
        break;        

        case 4:
        cpu.V[x] += cpu.V[y];
        cpu.V[15] = (uint16_t)cpu.V[x] + (uint16_t)cpu.V[y] > 0x00FF ?  1 : 0;
        break;

        case 5:
        cpu.V[x] -= cpu.V[y];
        cpu.V[15] = cpu.V[x] < cpu.V[y] ? 0 : 1; 
        break;

        case 6:
        cpu.V[x] >>= 1;
        cpu.V[15] = (1UL & cpu.V[x]);
        break;

        case 7:
        cpu.V[x] = cpu.V[y] - cpu.V[x];
        cpu.V[15] = cpu.V[x] > cpu.V[y] ? 0 : 1;
        break;

        case 14:
        cpu.V[x] <<= 1;
        cpu.V[15] = ((1UL << 7) & cpu.V[x]) >> 7;
        break;
    }
}