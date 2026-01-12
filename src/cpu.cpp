#include <random>
#include <time.h>
#include <string.h>
#include "../include/cpu.h"
#include "../include/chip8.h"
#include "../include/instructions.h"

cpu::cpu(): pc(0x200), sp(0), I(0){
    srand(time(0));
    memset(&V, 0, sizeof(uint8_t) * 16);
}

uint16_t cpu::fetch(uint8_t* ram){
    if(pc >= 4096) exit(1);
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
        if(nn == 0xE0){
            for(int i = 0; i < 64 * 32; i++){
                chip.display[i] = 0;
            }
        }
        else if(nn == 0xEE){
            pc = chip.stack[sp];
            sp--;
        }
        break;

        case 1:
        pc = nnn;
        break;

        case 2:
        if(sp + 1 >= 16){
            printf("Stack Overflow!");
            abort();
        }
        chip.stack[++sp] = pc;
        pc = nnn;

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
        pc = nnn + V[0];
        break;

        case 0x0C:
        V[x] = nn & (rand() % 256);
        break;

        case 0x0D:{
            V[0xF] = 0;
            for(int i = 0; i < n; i++){
                uint8_t val = chip.ram[i + I];
                uint8_t x_s = V[x] % 64;
                uint8_t y_s = V[y] % 32;
                
                for(int j = 7; j >= 0; j--){
                    uint8_t px = (7 - j) + x_s;
                    uint8_t py = y_s + i;

                    if(px >= 64 || py >= 32)
                        continue;
                    
                    uint16_t display_idx = (py * 64) + px;
                    uint8_t new_px_val = (val & (1 << j)) >> j;

                    if(chip.display[display_idx] & new_px_val)
                        V[0xF] = 1;

                    chip.display[display_idx] ^= new_px_val;
                }
            }
            chip.update_display = true;
        }
        break;

        case 0x0E:
        condition(*this, chip, x, y, nn, s);           
        break;        

        case 0x0F:
        system_ops(*this, chip, x, nn);
        break;
    }
}