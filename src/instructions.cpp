#include "../include/instructions.h"
#include "../include/Cpu.h"
#include "../include/chip8.h"

void arithmetic(Cpu& cpu, uint8_t x, uint8_t y, uint8_t n){
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

        case 4:{
            uint8_t vx = cpu.V[x];
            cpu.V[x] += cpu.V[y];
            cpu.V[0xF] = (uint16_t)vx + (uint16_t)cpu.V[y] > 0x00FF ?  1 : 0;
        }break;

        case 5:{
            uint8_t vx = cpu.V[x];
            cpu.V[x] -= cpu.V[y];
            cpu.V[0xF] = vx < cpu.V[y] ? 0 : 1; 
        }break;

        case 6:{
            uint8_t vx = cpu.V[x];
            cpu.V[x] >>= 1;
            cpu.V[0xF] = (1UL & vx);
        }break;

        case 7:{
            uint8_t vx = cpu.V[x];
            cpu.V[x] = cpu.V[y] - cpu.V[x];
            cpu.V[0xF] = vx > cpu.V[y] ? 0 : 1;
        }break;

        case 0xE:{
            uint8_t vx = cpu.V[x];
            cpu.V[x] <<= 1;
            cpu.V[0xF] = ((1UL << 7) & vx) >> 7;
        }break;
    }
}

void condition(Cpu& cpu, chip8& chip, uint8_t x, uint8_t y, uint16_t nn, uint8_t s){
    switch(s){
        case 3:
        if(cpu.V[x] == nn) cpu.pc += 2;
        break;

        case 4:
        if(cpu.V[x] != nn) cpu.pc += 2;
        break;

        case 5:
        if(cpu.V[x] == cpu.V[y]) cpu.pc += 2;
        break;

        case 9:
        if(cpu.V[x] != cpu.V[y]) cpu.pc += 2;
        break;

        case 0xE:
        if(nn == 0x9E){
            if(chip.keypad[cpu.V[x]]) cpu.pc += 2;
        }

        else if(nn == 0xA1){
            if(!chip.keypad[cpu.V[x]]) cpu.pc += 2;
        }
        break;
    }
}

void system_ops(Cpu& cpu, chip8& chip, uint8_t x, uint8_t nn){
    switch (nn)
    {
        case 0x07:
        cpu.V[x] = chip.delay_timer.get();
        break;

        case 0x0A:{
            bool key_pressed = false;
            for(int i = 0; i < 16; i++){
                if(chip.keypad[i] == 1){
                    key_pressed = true; 
                    cpu.V[x] = i;
                    break;
                }
            }
            cpu.pc = key_pressed ? cpu.pc : cpu.pc - 2;
        }break;

        case 0x15:
        chip.delay_timer.set(cpu.V[x]);
        break;
    
        case 0x18:
        chip.sound_timer.set(cpu.V[x]);
        break;

        case 0x1E:
        cpu.I += cpu.V[x];
        break;

        case 0x29:
        cpu.I = FONT_START_ADDRESS + (cpu.V[x] * 5);
        break;

        case 0x33:
        chip.ram[cpu.I] = cpu.V[x] / 100;
        chip.ram[cpu.I + 1] = (cpu.V[x] / 10) % 10;
        chip.ram[cpu.I + 2] = (cpu.V[x] % 10);
        break;

        case 0x55:
        for(int i = 0; i <= x; i++)
            chip.ram[cpu.I + i] = cpu.V[i];
        break;

        case 0x65:
        for(int i = 0; i <= x; i++)
            cpu.V[i] = chip.ram[cpu.I + i]; 
        break;

        default:
        break;
    }
}