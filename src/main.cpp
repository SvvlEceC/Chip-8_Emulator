#include <cstdlib>
#include <iostream>
#include <filesystem>
#include "display.h"
#include "chip8.h"

int main(int argc, char const *argv[]){
    if(argc < 2){
        std::cerr << "Error: NO ROM INPUT\nCorrect usage: ./chip8 <rom_path>";
        return 1;
    }

    chip8 chip;
    init_SDL(chip);

    std::string rom_path = argv[1];

    try
    {
        chip.load_rom(rom_path);
    }
    catch(const std::filesystem::filesystem_error& e)
    {
        std::cerr << e.what();
    }
    
    atexit(close);

    while (1){
        auto start(std::chrono::steady_clock::now());
        control_input(chip);
        for(int i = 0; i < 8; i++){
            chip.cpu.decode_and_execute(chip, chip.cpu.fetch(chip.ram));
        }
        
        prepare_scene();

        if(chip.update_display){
            present_scene(chip);
            chip.update_display = false;
        }

        auto end(std::chrono::steady_clock::now());
        uint32_t time_elapsed = (std::chrono::duration_cast<std::chrono::microseconds>(end- start).count());

        SDL_Delay((time_elapsed < 16666) ? (16666 - time_elapsed) / 1000 : 0);
    }

    return 0;
}
