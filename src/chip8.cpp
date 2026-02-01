#include <string.h>
#include <fstream>
#include <filesystem>
#include "chip8.h"

chip8::chip8(){
    uint8_t font_set[80] = {
    0xF0, 0x90, 0x90, 0x90, 0xF0, // 0
    0x20, 0x60, 0x20, 0x20, 0x70, // 1
    0xF0, 0x10, 0xF0, 0x80, 0xF0, // 2
    0xF0, 0x10, 0xF0, 0x10, 0xF0, // 3
    0x90, 0x90, 0xF0, 0x10, 0x10, // 4
    0xF0, 0x80, 0xF0, 0x10, 0xF0, // 5
    0xF0, 0x80, 0xF0, 0x90, 0xF0, // 6
    0xF0, 0x10, 0x20, 0x40, 0x40, // 7
    0xF0, 0x90, 0xF0, 0x90, 0xF0, // 8
    0xF0, 0x90, 0xF0, 0x10, 0xF0, // 9
    0xF0, 0x90, 0xF0, 0x90, 0x90, // A
    0xE0, 0x90, 0xE0, 0x90, 0xE0, // B
    0xF0, 0x80, 0x80, 0x80, 0xF0, // C
    0xE0, 0x90, 0x90, 0x90, 0xE0, // D
    0xF0, 0x80, 0xF0, 0x80, 0xF0, // E
    0xF0, 0x80, 0xF0, 0x80, 0x80  // F
    };

    memset(&ram, 0, sizeof(ram));
    memset(&stack, 0, sizeof(stack));
    memset(&keypad, 0, sizeof(keypad));
    memset(&display, 0, sizeof(display));

    update_display = false;
    delay_timer.set(0);
    sound_timer.set(0);

    for(int i = 0; i < 80; i++){
        ram[i + FONT_START_ADDRESS] = font_set[i];
    }
}

chip8::~chip8() {}

void chip8::load_rom(std::string path){
    if(std::ifstream in{path, std::ios::binary}){
        in.seekg(0, std::ios::end);
        auto size = in.tellg();
        in.seekg(0, std::ios::beg);

        if(size > 3584){
            throw std::filesystem::filesystem_error("Unable to load rom, Capacity exceeded\n", std::error_code());
            return;
        }

        in.read((char*)(ram + 0x200), size);
    }
    else{
        throw std::filesystem::filesystem_error("The rom file does not exist\n", std::error_code());
    }
}
